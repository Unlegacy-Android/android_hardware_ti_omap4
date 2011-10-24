/*
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*==============================================================
 *! Revision History
 *! ============================
 *! 21-Oct-2011 Rajesh vandanapu sarthav@ti.com: Initial Version
 *================================================================*/

/******************************************************************
 *   INCLUDE FILES
 ******************************************************************/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "omx_proxy_common.h"
#include <timm_osal_interfaces.h>
#include "OMX_TI_IVCommon.h"
#include "OMX_TI_Video.h"
#include "OMX_TI_Index.h"

#define COMPONENT_NAME "OMX.TI.DUCATI1.VIDEO.DECODER"
/* needs to be specific for every configuration wrapper */

/* DEFINITIONS for parsing the config information & sequence header for WMV*/
#define VIDDEC_GetUnalignedDword( pb, dw ) \
    (dw) = ((OMX_U32) *(pb + 3) << 24) + \
        ((OMX_U32) *(pb + 2) << 16) + \
        ((OMX_U16) *(pb + 1) << 8) + *pb;

#define VIDDEC_GetUnalignedDwordEx( pb, dw )   VIDDEC_GetUnalignedDword( pb, dw ); (pb) += sizeof(OMX_U32);
#define VIDDEC_LoadDWORD( dw, p )  VIDDEC_GetUnalignedDwordEx( p, dw )
#define VIDDEC_MAKEFOURCC(ch0, ch1, ch2, ch3) \
    ((OMX_U32)(OMX_U8)(ch0) | ((OMX_U32)(OMX_U8)(ch1) << 8) |   \
    ((OMX_U32)(OMX_U8)(ch2) << 16) | ((OMX_U32)(OMX_U8)(ch3) << 24 ))

#define VIDDEC_FOURCC(ch0, ch1, ch2, ch3)  VIDDEC_MAKEFOURCC(ch0, ch1, ch2, ch3)

#define FOURCC_WMV3     VIDDEC_FOURCC('W','M','V','3')
#define FOURCC_WMV2     VIDDEC_FOURCC('W','M','V','2')
#define FOURCC_WMV1     VIDDEC_FOURCC('W','M','V','1')
#define FOURCC_WVC1     VIDDEC_FOURCC('W','V','C','1')

#define CSD_POSITION    51 /*Codec Specific Data position on the "stream propierties object"(ASF spec)*/

typedef struct VIDDEC_WMV_RCV_struct {
    OMX_U32 nNumFrames : 24;
    OMX_U32 nFrameType : 8;
    OMX_U32 nID : 32;
    OMX_U32 nStructData : 32;   //STRUCT_C
    OMX_U32 nVertSize;          //STRUCT_A-1
    OMX_U32 nHorizSize;         //STRUCT_A-2
    OMX_U32 nID2 : 32;
    OMX_U32 nSequenceHdr : 32;   //STRUCT_B
} VIDDEC_WMV_RCV_struct;

typedef struct VIDDEC_WMV_VC1_struct {
    OMX_U32 nNumFrames  : 24;
    OMX_U32 nFrameType  : 8;
    OMX_U32 nID         : 32;
    OMX_U32 nStructData : 32;   //STRUCT_C
    OMX_U32 nVertSize;          //STRUCT_A-1
    OMX_U32 nHorizSize;         //STRUCT_A-2
    OMX_U32 nID2        : 32;
    OMX_U32 nSequenceHdr : 32;   //STRUCT_B
} VIDDEC_WMV_VC1_struct;


OMX_ERRORTYPE PrearrageEmptyThisBuffer(OMX_HANDLETYPE hComponent,
    OMX_BUFFERHEADERTYPE * pBufferHdr)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE *pCompPrv = NULL;
    OMX_COMPONENTTYPE *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_U8* pBuffer = NULL;
    OMX_U8* pData = NULL;
    OMX_U32 nValue = 0;
    OMX_U32 nWidth = 0;
    OMX_U32 nHeight = 0;
    OMX_U32 nActualCompression = 0;
    OMX_U8* pCSD = NULL;
    OMX_U32 nSize_CSD = 0;
    DOMX_ENTER("");

    PROXY_assert(pBufferHdr != NULL, OMX_ErrorBadParameter, NULL);

    if (pBufferHdr->nFlags & OMX_BUFFERFLAG_CODECCONFIG){
        PROXY_assert(hComp->pComponentPrivate != NULL, OMX_ErrorBadParameter, NULL);

        pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
        /* Get component role */
        OMX_PARAM_COMPONENTROLETYPE compRole;
        compRole.nSize = sizeof(OMX_PARAM_COMPONENTROLETYPE);
        compRole.nVersion.s.nVersionMajor = 1;
        compRole.nVersion.s.nVersionMinor = 1; //Ducati OMX version
        compRole.nVersion.s.nRevision = 0;
        compRole.nVersion.s.nStep = 0;

        eError = PROXY_GetParameter(hComp, OMX_IndexParamStandardComponentRole, &compRole);
        if(eError != OMX_ErrorNone){
            DOMX_ERROR("Error getting OMX_IndexParamStandardComponentRole");
        }

        if(!strcmp(compRole.cRole, "video_decoder.wmv")){
            pBuffer = pBufferHdr->pBuffer;

            VIDDEC_WMV_RCV_struct sStructRCV;

            DOMX_DEBUG("nFlags: %x", pBufferHdr->nFlags);

            pData = pBufferHdr->pBuffer + 15; /*Position to Width & Height*/
            VIDDEC_LoadDWORD(nValue, pData);
            nWidth = nValue;
            VIDDEC_LoadDWORD(nValue, pData);
            nHeight = nValue;

            pData += 4; /*Position to compression type*/
            VIDDEC_LoadDWORD(nValue, pData);
            nActualCompression = nValue;

            /*Seting pCSD to proper position*/
            pCSD = pBufferHdr->pBuffer;
            pCSD += CSD_POSITION;
            nSize_CSD = pBufferHdr->nFilledLen - CSD_POSITION;

            if(nActualCompression == FOURCC_WMV3){

                //From VC-1 spec: Table 265: Sequence Layer Data Structure
                sStructRCV.nNumFrames = 0xFFFFFF; /*Infinite frame number*/
                sStructRCV.nFrameType = 0xc5; /*0x85 is the value given by ASF to rcv converter*/
                sStructRCV.nID = 0x04; /*WMV3*/
                sStructRCV.nStructData = 0x018a3106; /*0x06318a01zero fill 0x018a3106*/
                sStructRCV.nVertSize = nHeight;
                sStructRCV.nHorizSize = nWidth;
                sStructRCV.nID2 = 0x0c; /* Fix value */
                sStructRCV.nSequenceHdr = 0x00002a9f; /* This value is not provided by parser, so giving a value from a video*/

                DOMX_DEBUG("initial: nStructData: %x", sStructRCV.nStructData);
                DOMX_DEBUG("pCSD = %x", (OMX_U32)*pCSD);

                sStructRCV.nStructData = (OMX_U32)pCSD[0] << 0  |
                    pCSD[1] << 8  |
                    pCSD[2] << 16 |
                    pCSD[3] << 24;

                DOMX_DEBUG("FINAL: nStructData: %x", sStructRCV.nStructData);

                //Copy RCV structure to actual buffer
                assert(pBufferHdr->nFilledLen < pBufferHdr->nAllocLen);
                pBufferHdr->nFilledLen = sizeof(VIDDEC_WMV_RCV_struct);
                TIMM_OSAL_Memcpy(pBufferHdr->pBuffer, (OMX_U8*)(&sStructRCV),
                    pBufferHdr->nFilledLen);

            }
            else if (nActualCompression == FOURCC_WVC1){
                DOMX_DEBUG("VC-1 Advance Profile prearrange");
                pBufferHdr->nOffset = pBufferHdr->nOffset+52;
                pBufferHdr->nFilledLen= pBufferHdr->nFilledLen-52;
            }
        }
    }

    EXIT:
    DOMX_EXIT("eError: %d", eError);

    return PROXY_EmptyThisBuffer(hComponent, pBufferHdr);
}

