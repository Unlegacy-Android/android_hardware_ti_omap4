/*************************************************************************/ /*!
@Title          Ion driver inter-operability code.
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@License        Dual MIT/GPLv2

The contents of this file are subject to the MIT license as set out below.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Alternatively, the contents of this file may be used under the terms of
the GNU General Public License Version 2 ("GPL") in which case the provisions
of GPL are applicable instead of those above.

If you wish to allow use of your version of this file only under the terms of
GPL, and not to allow others to use your version of this file under the terms
of the MIT license, indicate your decision by deleting the provisions above
and replace them with the notice and other provisions required by GPL as set
out in the file called "GPL-COPYING" included in this distribution. If you do
not delete the provisions above, a recipient may use your version of this file
under the terms of either the MIT license or GPL.

This License is also included in this distribution in the file called
"MIT-COPYING".

EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/ /**************************************************************************/

#include "dmabuf.h"
#include <linux/platform_device.h>
#include <linux/dma-buf.h>
#include <linux/dma-direction.h>
#include <linux/scatterlist.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/err.h>

extern struct platform_device *gpsPVRLDMDev;

#define MAX_IMPORT_DMABUF_FDS 3

typedef struct _DMABUF_IMPORT_DATA_
{
	/* Number of dma_buf handles represented by this import */
	IMG_UINT32 ui32NumHandles;

	/* Array of dma_buf handles in use by services */
	struct dma_buf *apsDmaBuf[MAX_IMPORT_DMABUF_FDS];

        /* Array of dma_buf attachments */
	struct dma_buf_attachment *apsDmaBufAttachment[MAX_IMPORT_DMABUF_FDS];

	/* Array of sg_tables */
	struct sg_table *apsSgTable[MAX_IMPORT_DMABUF_FDS];

	/* Array of physical addresses represented by these buffers */
	IMG_SYS_PHYADDR *psSysPhysAddr;

#if defined(PDUMP)
	 /* FIXME: Not sure if this is needed here */
	IMG_PVOID pvKernAddr0;
#endif /* defined(PDUMP) */
}
DMABUF_IMPORT_DATA;

PVRSRV_ERROR DmabufImportBufferAndAcquirePhysAddr(IMG_UINT32 ui32NumFDs,
											   IMG_INT32  *pai32BufferFDs,
											   IMG_UINT32 *pui32PageCount,
											   IMG_SYS_PHYADDR **ppsSysPhysAddr,
											   IMG_PVOID  *ppvKernAddr0,
											   IMG_HANDLE *phPriv,
											   IMG_HANDLE *phUnique)
{
	struct scatterlist *psTemp, *psScatterList[MAX_IMPORT_DMABUF_FDS] = {};
	PVRSRV_ERROR eError = PVRSRV_ERROR_OUT_OF_MEMORY;
	IMG_UINT32 i, k, ui32PageCount = 0;
	DMABUF_IMPORT_DATA *psImportData;

	if(ui32NumFDs > MAX_IMPORT_DMABUF_FDS)
	{
		printk(KERN_ERR "%s: More passed in than supported "
						"(%d provided, %d max)", __func__, ui32NumFDs,
						MAX_IMPORT_DMABUF_FDS);
		return PVRSRV_ERROR_INVALID_PARAMS;
	}

	psImportData = kzalloc(sizeof(DMABUF_IMPORT_DATA), GFP_KERNEL);
	if (psImportData == NULL)
	{
		goto exitFailKMallocImportData;
	}

	/* Set up import data for free call */
	psImportData->ui32NumHandles = ui32NumFDs;

	for(i = 0; i < ui32NumFDs; i++)
	{
		int fd = (int)pai32BufferFDs[i];

		/* connect to the buffer */
		psImportData->apsDmaBuf[i] = dma_buf_get(fd);
		if (IS_ERR_OR_NULL(psImportData->apsDmaBuf[i]))
		{
			dev_err(&gpsPVRLDMDev->dev,
				   "dma_buf_get() returned bad dma_buf handle\n");
			eError = PVRSRV_ERROR_BAD_MAPPING;
			goto exitFailImport;
		}

		psImportData->apsDmaBufAttachment[i] = dma_buf_attach(psImportData->apsDmaBuf[i],
									&gpsPVRLDMDev->dev);
        if (IS_ERR_OR_NULL(psImportData->apsDmaBufAttachment[i]))
        {
			dev_err(&gpsPVRLDMDev->dev,
				   "dma_buf_attach() returned bad attachment struct\n");
            eError = PVRSRV_ERROR_BAD_MAPPING;
            goto exitFailImport;
        }

		/* requesting access to the buffer */
		psImportData->apsSgTable[i] = dma_buf_map_attachment(psImportData->apsDmaBufAttachment[i],
							DMA_BIDIRECTIONAL);
        if (IS_ERR_OR_NULL(psImportData->apsSgTable[i]))
        {
			dev_err(&gpsPVRLDMDev->dev,
				   "dma_buf_map_attachment returned stale sgtable: %d\n",
				   (int)psImportData->apsSgTable[i]);
#if defined(DEBUG)
            /* lets dump the stack trace here */
            WARN_ON(true);
			/* TODO: print all the current omap bo info */
#endif
            dma_buf_detach(psImportData->apsDmaBuf[i],
                    psImportData->apsDmaBufAttachment[i]);
            eError = PVRSRV_ERROR_OUT_OF_MEMORY;
            goto exitFailImport;
        }

		psScatterList[i] = psImportData->apsSgTable[i]->sgl;
		if (psScatterList[i] == NULL)
		{
			eError = PVRSRV_ERROR_INVALID_PARAMS;
			goto exitFailImport;
		}

		/* Although all heaps will provide an sg_table, the tables cannot
		 * always be trusted because sg_lists are just pointers to "struct
		 * page" values, and some memory e.g. carveout may not have valid
		 * "struct page" values. In particular, on ARM, carveout is
		 * generally reserved with memblock_remove(), which leaves the
		 * "struct page" entries uninitialized when SPARSEMEM is enabled.
		 * The effect of this is that page_to_pfn(pfn_to_page(pfn)) != pfn.
		 *
		 * There's more discussion on this mailing list thread:
		 * http://lists.linaro.org/pipermail/linaro-mm-sig/2012-August/002440.html
		 *
		 * probably a contiguous allocator. If the phys() function is
		 * implemented, we'll use it to check sg_table->sgl[0]. If we find
		 * they don't agree, we'll assume phys() is more reliable and use
		 * that.
		 *
		 * Some heaps out there will implement phys() even though they are
		 * not for physically contiguous allocations (so the sg_table must
		 * be used). Therefore use the sg_table if the phys() and first
		 * sg_table entry match. This should be reliable because for most
		 * contiguous allocators, the sg_table should be a single span
		 * from 'start' to 'start+size'.
		 *
		 * Also, ion prints out an error message if the heap doesn't implement
		 * ->phys(), which we want to avoid, so only use ->phys() if the
		 * sg_table contains a single span and therefore could plausibly
		 * be a contiguous allocator.
		 */
		#if 0
		if(!sg_next(psScatterList[i]))
		{
			ion_phys_addr_t sPhyAddr;
			size_t sLength;

			if(!ion_phys(psIonClient, psImportData->apsIonHandle[i],
						 &sPhyAddr, &sLength))
			{
				BUG_ON(sLength & ~PAGE_MASK);

				if(sg_phys(psScatterList[i]) != sPhyAddr)
				{
					psScatterList[i] = IMG_NULL;
					ui32PageCount += sLength / PAGE_SIZE;
				}
			}
		}
		#endif
		for(psTemp = psScatterList[i]; psTemp; psTemp = sg_next(psTemp))
		{
			IMG_UINT32 j;
			for (j = 0; j < psTemp->length; j += PAGE_SIZE)
			{
				ui32PageCount++;
			}
		}
	}

	BUG_ON(ui32PageCount == 0);

	psImportData->psSysPhysAddr = kmalloc(sizeof(IMG_SYS_PHYADDR) * ui32PageCount, GFP_KERNEL);
	if (psImportData->psSysPhysAddr == NULL)
	{
		goto exitFailImport;
	}

	for(i = 0, k = 0; i < ui32NumFDs; i++)
	{
		if(psScatterList[i])
		{
			for(psTemp = psScatterList[i]; psTemp; psTemp = sg_next(psTemp))
			{
				IMG_UINT32 j;
				for (j = 0; j < psTemp->length; j += PAGE_SIZE)
				{
					psImportData->psSysPhysAddr[k].uiAddr = sg_phys(psTemp) + j;
					k++;
				}
			}
		}
#if 0
		else
		{
			ion_phys_addr_t sPhyAddr;
			size_t sLength, j;

			ion_phys(psIonClient, psImportData->apsIonHandle[i],
					 &sPhyAddr, &sLength);

			for(j = 0; j < sLength; j += PAGE_SIZE)
			{
				psImportData->psSysPhysAddr[k].uiAddr = sPhyAddr + j;
				k++;
			}
		}
#endif
	}

	*pui32PageCount = ui32PageCount;
	*ppsSysPhysAddr = psImportData->psSysPhysAddr;

#if defined(PDUMP)
	if(ui32NumFDs == 1)
	{
		/*FIXME */
		/* Need to handle kernel mapping */
	}
	else
#endif /* defined(PDUMP) */
	{
		*ppvKernAddr0 = NULL;
	}

	*phPriv = psImportData;
	*phUnique = (IMG_HANDLE)psImportData->psSysPhysAddr[0].uiAddr;

	return PVRSRV_OK;

exitFailImport:
	for(i = 0; psImportData->apsDmaBuf[i] != NULL; i++)
	{
		dma_buf_put(psImportData->apsDmaBuf[i]);
	}
	kfree(psImportData);
exitFailKMallocImportData:
	return eError;
}

IMG_VOID DmabufUnimportBufferAndReleasePhysAddr(IMG_HANDLE hPriv)
{
	DMABUF_IMPORT_DATA *psImportData = hPriv;
	IMG_UINT32 i;

#if defined(PDUMP)
	if (psImportData->pvKernAddr0)
	{
		//FIXME
	}
#endif /* defined(PDUMP) */
	for(i = 0; i < psImportData->ui32NumHandles; i++)
	{
		dma_buf_unmap_attachment(psImportData->apsDmaBufAttachment[i],
						psImportData->apsSgTable[i],
						DMA_BIDIRECTIONAL);
		dma_buf_detach(psImportData->apsDmaBuf[i],
					psImportData->apsDmaBufAttachment[i]);
		dma_buf_put(psImportData->apsDmaBuf[i]);
	}

	kfree(psImportData->psSysPhysAddr);
	kfree(psImportData);
}
