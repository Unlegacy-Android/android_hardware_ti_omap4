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

/**
 *  @file  omx_proxy_camera.c
 *         This file contains methods that provides the functionality for
 *         the OpenMAX1.1 DOMX Framework Tunnel Proxy component.
 ******************************************************************************
 This is the proxy specific wrapper that passes the component name to the
 generic proxy init() The proxy wrapper also does some runtime/static time
 config on per proxy basis This is a thin wrapper that is called when
 componentiit() of the proxy is called  static OMX_ERRORTYPE PROXY_Wrapper_init
 (OMX_HANDLETYPE hComponent, OMX_PTR pAppData);
 this layer gets called first whenever a proxy s get handle is called
 ******************************************************************************
 *  @path WTSD_DucatiMMSW\omx\omx_il_1_x\omx_proxy_component\src
 *
 *  @rev 1.0
 */

/*==============================================================
 *! Revision History
 *! ============================
 *! 19-August-2009 B Ravi Kiran ravi.kiran@ti.com: Initial Version
 *! 20-April-2012 Phanish phanish.hs@ti.com: updated wrt Slice processing
 *================================================================*/

/******************************************************************
 *   INCLUDE FILES
 ******************************************************************/
#include "omx_proxy_camera.h"

#ifdef USE_ION
#include <unistd.h>
#include <ion/ion.h>
#include "ion_ti_custom.h"
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/eventfd.h>
#include <fcntl.h>
#include <errno.h>
#endif

/* Tiler heap resservation specific */
#define OMAP_ION_HEAP_TILER_ALLOCATION_MASK (1<<4)

/* Incase of multiple instance, making sure DCC is initialized only for
   first instance */
static OMX_S16 numofInstance = 0;
TIMM_OSAL_PTR cam_mutex = NULL;

#ifdef USES_LEGACY_DOMX_DCC
int dcc_flag = 0;
/* To store DCC buffer size */
OMX_S32 dccbuf_size = 0;
/* DCC buff accessors */
MEMPLUGIN_BUFFER_ACCESSOR sDccBuffer;
OMX_BOOL dcc_loaded = OMX_FALSE;
#endif

#ifdef OMAP_ENHANCEMENT_VTC
/* ===========================================================================*/
/**
 * @name _OMX_CameraVtcFreeMemory
 * @brief Allocated buffers are freed in this api
 *
 * @param
 * @return OMX_ErrorNone = Successful
 */
/* ===========================================================================*/
OMX_ERRORTYPE OMX_CameraVtcFreeMemory(OMX_IN OMX_HANDLETYPE hComponent)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE *pCompPrv;
    OMX_PROXY_CAM_PRIVATE* pCamPrv;
    OMX_COMPONENTTYPE *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_U32 i = 0;
    RPC_OMX_ERRORTYPE eRPCError = RPC_OMX_ErrorNone;
    MEMPLUGIN_BUFFER_PARAMS delBuffer_params;
    MEMPLUGIN_BUFFER_PROPERTIES delBuffer_prop;

    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
    pCamPrv = (OMX_PROXY_CAM_PRIVATE*)pCompPrv->pCompProxyPrv;

    MEMPLUGIN_BUFFER_PARAMS_INIT(delBuffer_params);

    for(i=0; i < MAX_NUM_INTERNAL_BUFFERS; i++) {
        if (pCamPrv->sInternalBuffers[i][0].pBufferHandle != NULL) {
            eRPCError = RPC_UnRegisterBuffer(pCompPrv->hRemoteComp, pCamPrv->sInternalBuffers[i][0].pRegBufferHandle, NULL , IONPointers);
            if (eRPCError != RPC_OMX_ErrorNone) {
                DOMX_ERROR("%s: DOMX: Unexpected error occurred while Unregistering Y Buffer#%d: eRPCError = 0x%x", __func__, i, eRPCError);
            }
            delBuffer_prop.sBuffer_accessor.pBufferHandle =  pCamPrv->sInternalBuffers[i][0].pBufferHandle;
            MemPlugin_Free(pCompPrv->pMemPluginHandle,pCompPrv->nMemmgrClientDesc,&delBuffer_params,&delBuffer_prop);
            pCamPrv->sInternalBuffers[i][0].pRegBufferHandle = NULL;
            pCamPrv->sInternalBuffers[i][0].pBufferHandle = NULL;
            DOMX_DEBUG("%s: DOMX: #%d Y Memory freed; eRPCError = 0x%x", __func__, i, eRPCError);
        }
        if (pCamPrv->sInternalBuffers[i][1].pBufferHandle != NULL) {
            eRPCError = RPC_UnRegisterBuffer(pCompPrv->hRemoteComp, pCamPrv->sInternalBuffers[i][1].pRegBufferHandle, NULL , IONPointers);
            if (eRPCError != RPC_OMX_ErrorNone) {
                DOMX_ERROR("%s: DOMX: Unexpected error occurred while Unregistering UV Buffer#%d: eRPCError = 0x%x", __func__, i, eRPCError);
            }
            delBuffer_prop.sBuffer_accessor.pBufferHandle =  pCamPrv->sInternalBuffers[i][1].pBufferHandle;
            MemPlugin_Free(pCompPrv->pMemPluginHandle,pCompPrv->nMemmgrClientDesc,&delBuffer_params,&delBuffer_prop);
            pCamPrv->sInternalBuffers[i][1].pRegBufferHandle = NULL;
            pCamPrv->sInternalBuffers[i][1].pBufferHandle = NULL;
            DOMX_DEBUG("%s: DOMX: #%d UV Memory freed; eRPCError = 0x%x", __func__, i, eRPCError);
        }
    }

EXIT:
   DOMX_EXIT("eError: %d", eError);
   return eError;
}

OMX_ERRORTYPE GLUE_CameraVtcAllocateMemory(OMX_IN OMX_HANDLETYPE hComponent, OMX_TI_PARAM_VTCSLICE *pVtcConfig,
											OMX_U32 nFrmWidth, OMX_U32 nFrmHeight);

/* ===========================================================================*/
/**
 * @name _OMX_CameraVtcAllocateMemory
 * @brief Allocate 2D buffers for intermediate output at the output of isp
 *
 * @param
 * @return OMX_ErrorNone = Successful
 */
/* ===========================================================================*/
static OMX_ERRORTYPE _OMX_CameraVtcAllocateMemory(OMX_IN OMX_HANDLETYPE hComponent)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone, eCompReturn = OMX_ErrorNone;
    OMX_STATETYPE tState= OMX_StateInvalid;
    PROXY_COMPONENT_PRIVATE *pCompPrv;
    OMX_PROXY_CAM_PRIVATE* pCamPrv;
    OMX_COMPONENTTYPE *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_U32 i = 0;
    OMX_CONFIG_RECTTYPE tFrameDim;
    OMX_U32 nFrmWidth, nFrmHeight;
    OMX_TI_PARAM_VTCSLICE tVtcConfig;
    RPC_OMX_ERRORTYPE eRPCError = RPC_OMX_ErrorNone;

    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
    pCamPrv = (OMX_PROXY_CAM_PRIVATE*)pCompPrv->pCompProxyPrv;

    _PROXY_OMX_INIT_PARAM(&tFrameDim, OMX_CONFIG_RECTTYPE);
    _PROXY_OMX_INIT_PARAM(&tVtcConfig, OMX_TI_PARAM_VTCSLICE);

    /* Get the current state of the component */
    eError = OMX_GetState(hComponent, &tState);
    if(OMX_ErrorNone != eError)
    {
        DOMX_ERROR("%s: Error in fetching current state - %d", __func__, tState);
    }
    else
    {
        if (tState == OMX_StateLoaded) {
            DOMX_DEBUG("%s: Current state returned is %d", __func__, tState);

            if(OMX_GetParameter(hComponent, (unsigned int)OMX_TI_IndexParamVtcSlice, &tVtcConfig) == OMX_ErrorNone) {
                if (tVtcConfig.nSliceHeight != 0 ) {
                    OMX_CONFIG_BOOLEANTYPE tVstabParam;
                    OMX_PARAM_VIDEONOISEFILTERTYPE tVnfParam;
                    OMX_TI_PARAM_VTCSLICE *pVtcConfig = &tVtcConfig;

                    tFrameDim.nPortIndex = PREVIEW_PORT; //Preview Port
                    if(OMX_GetParameter(hComponent, (unsigned int)OMX_TI_IndexParam2DBufferAllocDimension, &tFrameDim) == OMX_ErrorNone){
                        DOMX_DEBUG("Acquired OMX_TI_IndexParam2DBufferAllocDimension data. nWidth = %d, nHeight = %d.\n\n", tFrameDim.nWidth, tFrameDim.nHeight);
                        nFrmWidth = tFrameDim.nWidth;
                        nFrmHeight = tFrameDim.nHeight;
                    }else {
                        DOMX_DEBUG("%s: No OMX_TI_IndexParam2DBufferAllocDimension data.\n\n", __func__);
                        nFrmWidth = MAX_VTC_WIDTH_WITH_VNF;
                        nFrmHeight = MAX_VTC_HEIGHT_WITH_VNF;
                    }

                    _PROXY_OMX_INIT_PARAM(&tVnfParam, OMX_PARAM_VIDEONOISEFILTERTYPE);
                    _PROXY_OMX_INIT_PARAM(&tVstabParam, OMX_CONFIG_BOOLEANTYPE);
                    eError = OMX_GetParameter(hComponent, (unsigned int)OMX_IndexParamFrameStabilisation, &tVstabParam);
                    if(eError != OMX_ErrorNone) {
                        DOMX_ERROR("OMX_GetParameter for OMX_IndexParamFrameStabilisation returned error %x", eError);
                        goto EXIT;
                    }
                    tVnfParam.nPortIndex = PREVIEW_PORT;
                    eError = OMX_GetParameter(hComponent, (unsigned int)OMX_IndexParamVideoNoiseFilter, &tVnfParam);
                    if(eError != OMX_ErrorNone) {
                        DOMX_ERROR("OMX_GetParameter for OMX_IndexParamVideoNoiseFilter returned error %x", eError);
                        goto EXIT;
                    }
                    DOMX_DEBUG(" Acquired OMX_TI_IndexParamVtcSlice data. nSliceHeight = %d, bVstabOn = %d, Vnfmode = %d, nWidth = %d, nHeight = %d.\n\n", tVtcConfig.nSliceHeight, tVstabParam.bEnabled, tVnfParam.eMode, nFrmWidth, nFrmHeight);
                    if (tVstabParam.bEnabled == OMX_FALSE && tVnfParam.eMode != OMX_VideoNoiseFilterModeOff) {
                        eError = GLUE_CameraVtcAllocateMemory(hComponent,
                                                              pVtcConfig,
                                                              nFrmWidth,
                                                              nFrmHeight);
                        if(eError != OMX_ErrorNone) {
                           DOMX_ERROR("Allocate Memory for vtc config returned error %x", eError);
                           goto EXIT;
                        }
                   }
                }
            }
        }
    }
EXIT:

   DOMX_EXIT("eError: %d", eError);
   return eError;
}
#endif

static OMX_ERRORTYPE ComponentPrivateDeInit(OMX_IN OMX_HANDLETYPE hComponent)
{
	OMX_ERRORTYPE eError = OMX_ErrorNone, eCompReturn = OMX_ErrorNone;
	TIMM_OSAL_ERRORTYPE eOsalError = TIMM_OSAL_ERR_NONE;
	PROXY_COMPONENT_PRIVATE *pCompPrv;
	OMX_COMPONENTTYPE *hComp = (OMX_COMPONENTTYPE *) hComponent;
	OMX_U32 i, j;
    OMX_PROXY_CAM_PRIVATE* pCamPrv;
    MEMPLUGIN_BUFFER_PARAMS delBuffer_params;
    MEMPLUGIN_BUFFER_PROPERTIES delBuffer_prop;
    RPC_OMX_ERRORTYPE eRPCError = RPC_OMX_ErrorNone;

        MEMPLUGIN_BUFFER_PARAMS_INIT(delBuffer_params);
	pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;

#ifdef USES_LEGACY_DOMX_DCC
        if (dcc_flag)
        {
            eOsalError =
                TIMM_OSAL_MutexObtain(cam_mutex, TIMM_OSAL_SUSPEND);
            if (eOsalError != TIMM_OSAL_ERR_NONE)
            {
                    TIMM_OSAL_Error("Mutex Obtain failed");
            }
            numofInstance = numofInstance - 1;
            eOsalError = TIMM_OSAL_MutexRelease(cam_mutex);
            PROXY_assert(eOsalError == TIMM_OSAL_ERR_NONE,
                OMX_ErrorInsufficientResources, "Mutex release failed");
        }
        dcc_loaded = OMX_FALSE;
#endif

#ifdef OMAP_ENHANCEMENT_VTC
        OMX_CameraVtcFreeMemory(hComponent);
#endif

    if(pCompPrv->pCompProxyPrv != NULL) {
        pCamPrv = (OMX_PROXY_CAM_PRIVATE*)pCompPrv->pCompProxyPrv;
        for (i = 0; i < PROXY_MAXNUMOFPORTS; i++) {
            for (j = 0; j < MAX_NUM_INTERNAL_BUFFERS; j++) {
                if (pCamPrv->gComponentBufferAllocation[i][j]) {
                    delBuffer_prop.sBuffer_accessor.pBufferHandle = pCamPrv->gComponentBufferAllocation[i][j];
                    MemPlugin_Free(pCompPrv->pMemPluginHandle,pCompPrv->nMemmgrClientDesc,&delBuffer_params,&delBuffer_prop);
                }
                pCamPrv->gComponentBufferAllocation[i][j] = NULL;
            }
        }

        TIMM_OSAL_Free(pCompPrv->pCompProxyPrv);
        pCompPrv->pCompProxyPrv = NULL;
        pCamPrv = NULL;
    }

	eError = PROXY_ComponentDeInit(hComponent);

      EXIT:
	return eError;
}

static OMX_ERRORTYPE Camera_SendCommand(OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_COMMANDTYPE eCmd,
    OMX_IN OMX_U32 nParam, OMX_IN OMX_PTR pCmdData)

{
    OMX_ERRORTYPE eError = OMX_ErrorNone, eCompReturn;
#ifdef USES_LEGACY_DOMX_DCC
    OMX_ERRORTYPE dcc_eError = OMX_ErrorNone;
#endif
    OMX_COMPONENTTYPE *hComp = (OMX_COMPONENTTYPE *) hComponent;
    PROXY_COMPONENT_PRIVATE *pCompPrv;
    OMX_PROXY_CAM_PRIVATE   *pCamPrv;
    MEMPLUGIN_BUFFER_PARAMS delBuffer_params;
    MEMPLUGIN_BUFFER_PROPERTIES delBuffer_prop;
    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;

    pCamPrv = (OMX_PROXY_CAM_PRIVATE*)pCompPrv->pCompProxyPrv;

    MEMPLUGIN_BUFFER_PARAMS_INIT(delBuffer_params);
    if ((eCmd == OMX_CommandStateSet) &&
        (nParam == (OMX_STATETYPE) OMX_StateIdle))
    {
#ifdef OMAP_ENHANCEMENT_VTC
        /* Allocate memory for Video VTC usecase, if applicable. */
        eError = _OMX_CameraVtcAllocateMemory(hComponent);
        if (eError != OMX_ErrorNone) {
            DOMX_ERROR("DOMX: _OMX_CameraVtcAllocateMemory completed with error 0x%x\n", eError);
            goto EXIT;
        }
#endif
#ifdef USES_LEGACY_DOMX_DCC
        if (!dcc_loaded)
        {
            dcc_eError = DCC_Init(hComponent);
            if (dcc_eError != OMX_ErrorNone)
            {
                DOMX_ERROR(" Error in DCC Init");
            }
            /* Configure Ducati to use DCC buffer from A9 side
             *ONLY* if DCC_Init is successful. */
            if (dcc_eError == OMX_ErrorNone)
            {
                dcc_eError = send_DCCBufPtr(hComponent);
                if (dcc_eError != OMX_ErrorNone)
                {
                    DOMX_ERROR(" Error in Sending DCC Buf ptr");
                }
                DCC_DeInit(hComponent);
            }
            dcc_loaded = OMX_TRUE;
        }
#endif
    } else if (eCmd == OMX_CommandPortDisable) {
        unsigned int i;
        int j;
        for (i = 0; i < PROXY_MAXNUMOFPORTS; i++) {
            if ((i == nParam) || (nParam == OMX_ALL)) {
                for (j = 0; j < MAX_NUM_INTERNAL_BUFFERS; j++) {
                     if (pCamPrv->gComponentBufferAllocation[i][j]) {
                     delBuffer_prop.sBuffer_accessor.pBufferHandle = pCamPrv->gComponentBufferAllocation[i][j];
                        MemPlugin_Free(pCompPrv->pMemPluginHandle, pCompPrv->nMemmgrClientDesc,
                                       &delBuffer_params,&delBuffer_prop);
                        pCamPrv->gComponentBufferAllocation[i][j] = NULL;
                    }
                }
            }
        }
    }

#ifdef OMAP_ENHANCEMENT_VTC
    if ((eCmd == OMX_CommandStateSet) &&
	(nParam == (OMX_STATETYPE) OMX_StateLoaded))
    {
        /* Clean up resources for Video VTC usecase. */
        OMX_CameraVtcFreeMemory(hComponent);
    }
#endif

    eError =
	PROXY_SendCommand(hComponent,eCmd,nParam,pCmdData);

EXIT:

   DOMX_EXIT("eError: %d", eError);
   return eError;
}

/* ===========================================================================*/
/**
 * @name CameraGetConfig()
 * @brief For some specific indices, buffer allocated on A9 side
 *        needs to be mapped and sent to Ducati.
 * @param
 * @return OMX_ErrorNone = Successful
 */
/* ===========================================================================*/

static OMX_ERRORTYPE CameraGetConfig(OMX_IN OMX_HANDLETYPE
    hComponent, OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR pComponentParameterStructure)
{
	OMX_ERRORTYPE eError = OMX_ErrorNone;
	OMX_TI_CONFIG_SHAREDBUFFER *pConfigSharedBuffer = NULL;
	OMX_PTR pTempSharedBuff = NULL;
	OMX_U32 status = 0;

	switch ((unsigned int)nParamIndex)
	{
	case OMX_TI_IndexConfigAAAskipBuffer:
	case OMX_TI_IndexConfigCamCapabilities:
	case OMX_TI_IndexConfigExifTags:
	case OMX_TI_IndexConfigAlgoAreas:
#ifndef DOMX_TUNA
	case OMX_TI_IndexConfigGammaTable:
        case OMX_TI_IndexConfigDynamicCameraDescriptor:
#endif
		pConfigSharedBuffer =
			(OMX_TI_CONFIG_SHAREDBUFFER *) pComponentParameterStructure;

		pTempSharedBuff = pConfigSharedBuffer->pSharedBuff;

		// TODO(XXX): Cache API is not yet available. Client needs to
		// allocate tiler buffer directly and assign to pSharedBuff.
		// Ptr allocated by MemMgr_Alloc in uncacheable so there
		// would be no need to cache API

		eError = __PROXY_GetConfig(hComponent,
								nParamIndex,
								pConfigSharedBuffer,
								&(pConfigSharedBuffer->pSharedBuff));

		PROXY_assert((eError == OMX_ErrorNone), eError,
		    "Error in GetConfig");

		pConfigSharedBuffer->pSharedBuff = pTempSharedBuff;

		goto EXIT;
		break;
	default:
		break;
	}

	return __PROXY_GetConfig(hComponent,
							nParamIndex,
							pComponentParameterStructure,
							NULL);

 EXIT:
	return eError;
}

/* ===========================================================================*/
/**
 * @name CameraSetConfig()
 * @brief For some specific indices, buffer allocated on A9 side needs to
 *        be mapped and sent to Ducati.
 * @param
 * @return OMX_ErrorNone = Successful
 */
/* ===========================================================================*/


static OMX_ERRORTYPE CameraSetConfig(OMX_IN OMX_HANDLETYPE
    hComponent, OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR pComponentParameterStructure)
{
	OMX_ERRORTYPE eError = OMX_ErrorNone;
	OMX_TI_CONFIG_SHAREDBUFFER *pConfigSharedBuffer = NULL;
	OMX_PTR pTempSharedBuff = NULL;
	OMX_U32 status = 0;

	switch ((unsigned int)nParamIndex)
	{
	case OMX_TI_IndexConfigAAAskipBuffer:
	case OMX_TI_IndexConfigCamCapabilities:
	case OMX_TI_IndexConfigExifTags:
	case OMX_TI_IndexConfigAlgoAreas:
#ifndef DOMX_TUNA
	case OMX_TI_IndexConfigGammaTable:
        case OMX_TI_IndexConfigDynamicCameraDescriptor:
#endif
		pConfigSharedBuffer =
			(OMX_TI_CONFIG_SHAREDBUFFER *)
			pComponentParameterStructure;

		pTempSharedBuff = pConfigSharedBuffer->pSharedBuff;

		// TODO(XXX): Cache API is not yet available. Client needs to
		// allocate tiler buffer directly and assign to pSharedBuff.
		// Ptr allocated by MemMgr_Alloc in uncacheable so there
		// would be no need to cache API

		eError = __PROXY_SetConfig(hComponent,
								nParamIndex,
								pConfigSharedBuffer,
								&(pConfigSharedBuffer->pSharedBuff));

		PROXY_assert((eError == OMX_ErrorNone), eError,
		    "Error in GetConfig");

		pConfigSharedBuffer->pSharedBuff = pTempSharedBuff;

		goto EXIT;
		break;
	default:
		break;
	}

	return __PROXY_SetConfig(hComponent,
							nParamIndex,
							pComponentParameterStructure,
							NULL);

 EXIT:
	return eError;
}

OMX_ERRORTYPE GLUE_CameraSetParam(OMX_IN OMX_HANDLETYPE
    hComponent, OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR pComponentParameterStructure);

static OMX_ERRORTYPE CameraSetParam(OMX_IN OMX_HANDLETYPE
    hComponent, OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR pComponentParameterStructure)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE *pCompPrv;
    OMX_COMPONENTTYPE *hComp = (OMX_COMPONENTTYPE *)hComponent;
    pCompPrv = (PROXY_COMPONENT_PRIVATE *)hComp->pComponentPrivate;

    switch ((unsigned int)nParamIndex)
    {
#ifndef DOMX_TUNA
	case OMX_TI_IndexParamComponentBufferAllocation:
             eError = GLUE_CameraSetParam(hComponent,
                                          nParamIndex,
                                          pComponentParameterStructure);
		goto EXIT;
		break;
#endif
	default:
		 break;
	}
	eError = __PROXY_SetParameter(hComponent,
								nParamIndex,
								pComponentParameterStructure,
							NULL, 0);
EXIT:
	if (eError != OMX_ErrorNone) {
		DOMX_ERROR(" CameraSetParam: Error in SetParam 0x%x", eError);
	}
    return eError;
}

OMX_ERRORTYPE OMX_ComponentInit(OMX_HANDLETYPE hComponent)
{
	OMX_ERRORTYPE eError = OMX_ErrorNone;
	OMX_ERRORTYPE dcc_eError = OMX_ErrorNone;
	OMX_COMPONENTTYPE *pHandle = NULL;
	PROXY_COMPONENT_PRIVATE *pComponentPrivate;
    OMX_U32 i = 0, j = 0;
    OMX_PROXY_CAM_PRIVATE* pCamPrv;
	MEMPLUGIN_ERRORTYPE eMemError = MEMPLUGIN_ERROR_NONE;
	pHandle = (OMX_COMPONENTTYPE *) hComponent;
	TIMM_OSAL_ERRORTYPE eOsalError = TIMM_OSAL_ERR_NONE;
	DOMX_ENTER("_____________________INSIDE CAMERA PROXY"
	    "WRAPPER__________________________\n");
	pHandle->pComponentPrivate = (PROXY_COMPONENT_PRIVATE *)
	    TIMM_OSAL_Malloc(sizeof(PROXY_COMPONENT_PRIVATE),
	    TIMM_OSAL_TRUE, 0, TIMMOSAL_MEM_SEGMENT_INT);

#ifdef USES_LEGACY_DOMX_DCC
        // Should not be needed as PrivateDeInit will set it, but resetting
        // it here just in case there's some codepath that skips PrivateDeInit.
        dcc_loaded = OMX_FALSE;
#endif

	pComponentPrivate =
	    (PROXY_COMPONENT_PRIVATE *) pHandle->pComponentPrivate;
	if (pHandle->pComponentPrivate == NULL)
	{
		DOMX_ERROR(" ERROR IN ALLOCATING PROXY COMPONENT"
		    "PRIVATE STRUCTURE");
		eError = OMX_ErrorInsufficientResources;
		goto EXIT;
	}
	TIMM_OSAL_Memset(pComponentPrivate, 0,
		sizeof(PROXY_COMPONENT_PRIVATE));

	pComponentPrivate->cCompName =
	    TIMM_OSAL_Malloc(MAX_COMPONENT_NAME_LENGTH * sizeof(OMX_U8),
	    TIMM_OSAL_TRUE, 0, TIMMOSAL_MEM_SEGMENT_INT);
	/*Copying component Name - this will be picked up in the proxy common */
	assert(strlen(COMPONENT_NAME) + 1 < MAX_COMPONENT_NAME_LENGTH);
	TIMM_OSAL_Memcpy(pComponentPrivate->cCompName, COMPONENT_NAME,
	    strlen(COMPONENT_NAME) + 1);

        pComponentPrivate->pCompProxyPrv =
            (OMX_PROXY_CAM_PRIVATE *)
            TIMM_OSAL_Malloc(sizeof(OMX_PROXY_CAM_PRIVATE), TIMM_OSAL_TRUE,
            0, TIMMOSAL_MEM_SEGMENT_INT);

        PROXY_assert(pComponentPrivate->pCompProxyPrv != NULL,
            OMX_ErrorInsufficientResources,
            "Could not allocate memory for proxy component private data structure");
        pCamPrv = (OMX_PROXY_CAM_PRIVATE*)pComponentPrivate->pCompProxyPrv;
        TIMM_OSAL_Memset(pComponentPrivate->pCompProxyPrv, 0,
                sizeof(OMX_PROXY_CAM_PRIVATE));

	pComponentPrivate->bMapBuffers = OMX_TRUE;
	/*Calling Proxy Common Init() */
	eError = OMX_ProxyCommonInit(hComponent);
	if (eError != OMX_ErrorNone)
	{
		DOMX_ERROR("\Error in Initializing Proxy");
		TIMM_OSAL_Free(pComponentPrivate->cCompName);
		TIMM_OSAL_Free(pComponentPrivate);
		TIMM_OSAL_Free(pComponentPrivate->pCompProxyPrv);
		goto EXIT;
	}

        for (i = 0; i < PROXY_MAXNUMOFPORTS; i++) {
            for (j = 0; j < MAX_NUM_INTERNAL_BUFFERS; j++) {
                pCamPrv->gComponentBufferAllocation[i][j] = NULL;
            }
        }

	pHandle->ComponentDeInit = ComponentPrivateDeInit;
	pHandle->GetConfig = CameraGetConfig;
	pHandle->SetConfig = CameraSetConfig;
	pHandle->SendCommand = Camera_SendCommand;
	pHandle->SetParameter = CameraSetParam;

      EXIT:
	return eError;
}

#ifdef USES_LEGACY_DOMX_DCC
/* ===========================================================================*/
/**
 * @name DCC_Init()
 * @brief
 * @param void
 * @return OMX_ErrorNone = Successful
 * @sa TBD
 *
 */
/* ===========================================================================*/
OMX_ERRORTYPE DCC_Init(OMX_HANDLETYPE hComponent)
{
       OMX_TI_PARAM_DCCURIINFO param;
       OMX_PTR ptempbuf;
       OMX_U16 nIndex = 0;
       OMX_ERRORTYPE eError = OMX_ErrorNone;
       PROXY_COMPONENT_PRIVATE *pComponentPrivate;
       OMX_COMPONENTTYPE *pHandle = NULL;
       MEMPLUGIN_BUFFER_PARAMS sDccBuff_params;
       MEMPLUGIN_BUFFER_PROPERTIES sDccBuff_prop;
       MEMPLUGIN_ERRORTYPE eMemError = MEMPLUGIN_ERROR_NONE;
       OMX_S32 status = 0;
       OMX_STRING dcc_dir[200];
       OMX_U16 i;
       _PROXY_OMX_INIT_PARAM(&param, OMX_TI_PARAM_DCCURIINFO);

       DOMX_ENTER("ENTER");
       pHandle = (OMX_COMPONENTTYPE *) hComponent;
       pComponentPrivate = (PROXY_COMPONENT_PRIVATE *)pHandle->pComponentPrivate;
       if(pComponentPrivate == NULL)
       {
              eError = OMX_ErrorBadParameter;
              DOMX_ERROR("%s: Component private data NULL",__FUNCTION__);
              goto EXIT;
       }
       /* Read the the DCC URI info */
       for (nIndex = 0; eError != OMX_ErrorNoMore; nIndex++)
       {
               param.nIndex = nIndex;
               eError =
                       OMX_GetParameter(hComponent,
                       OMX_TI_IndexParamDccUriInfo, &param);

               PROXY_assert((eError == OMX_ErrorNone) ||
                       (eError == OMX_ErrorNoMore), eError,
                       "Error in GetParam for Dcc URI info");

               if (eError == OMX_ErrorNone)
               {
                       DOMX_DEBUG("DCC URI's %s ", param.sDCCURI);
                       dcc_dir[nIndex] =
                               TIMM_OSAL_Malloc(sizeof(OMX_U8) *
                               (strlen(DCC_PATH) + MAX_URI_LENGTH + 1),
                               TIMM_OSAL_TRUE, 0, TIMMOSAL_MEM_SEGMENT_INT);
                       PROXY_assert(dcc_dir[nIndex] != NULL,
                               OMX_ErrorInsufficientResources, "Malloc failed");
                       strcpy(dcc_dir[nIndex], DCC_PATH);
                       strncat(dcc_dir[nIndex], (OMX_STRING) param.sDCCURI, MAX_URI_LENGTH);
                       strcat(dcc_dir[nIndex], "/");
               }
       }

       /* setting  back errortype OMX_ErrorNone */
       if (eError == OMX_ErrorNoMore)
       {
               eError = OMX_ErrorNone;
       }

       dccbuf_size = read_DCCdir(NULL, dcc_dir, nIndex);

    if(dccbuf_size <= 0)
    {
           DOMX_DEBUG("No DCC files found, switching back to default DCC");
        return OMX_ErrorInsufficientResources;
    }
    if(pComponentPrivate->pMemPluginHandle == NULL)
    {
                eMemError = MemPlugin_Init("MEMPLUGIN_ION",&(pComponentPrivate->pMemPluginHandle));
                if(eMemError != MEMPLUGIN_ERROR_NONE)
                {
                     DOMX_ERROR("MEMPLUGIN configure step failed");
                     eError = OMX_ErrorUndefined;
                     goto EXIT;
                }
     }
       pComponentPrivate->bMapBuffers = OMX_TRUE;

       eMemError = MemPlugin_Open(pComponentPrivate->pMemPluginHandle,&(pComponentPrivate->nMemmgrClientDesc));
       if(eMemError != MEMPLUGIN_ERROR_NONE)
       {
               DOMX_ERROR("Mem manager client creation failed!!!");
               eError = OMX_ErrorInsufficientResources;
               goto EXIT;
       }
       dccbuf_size = (dccbuf_size + LINUX_PAGE_SIZE -1) & ~(LINUX_PAGE_SIZE - 1);
       MEMPLUGIN_BUFFER_PARAMS_INIT(sDccBuff_params);
       sDccBuff_params.nWidth = dccbuf_size;
       sDccBuff_params.bMap = pComponentPrivate->bMapBuffers;
       eMemError = MemPlugin_Alloc(pComponentPrivate->pMemPluginHandle,pComponentPrivate->nMemmgrClientDesc,&sDccBuff_params,&sDccBuff_prop);
       sDccBuffer.pBufferHandle = sDccBuff_prop.sBuffer_accessor.pBufferHandle;
       sDccBuffer.pBufferMappedAddress = sDccBuff_prop.sBuffer_accessor.pBufferMappedAddress;
       sDccBuffer.bufferFd = sDccBuff_prop.sBuffer_accessor.bufferFd;
       ptempbuf = sDccBuffer.pBufferMappedAddress;
       dccbuf_size = read_DCCdir(ptempbuf, dcc_dir, nIndex);
       PROXY_assert(dccbuf_size > 0, OMX_ErrorInsufficientResources,
               "ERROR in copy DCC files into buffer");
EXIT:
       for (i = 0; i < nIndex - 1; i++)
       {
                       TIMM_OSAL_Free(dcc_dir[i]);
       }

       return eError;

}

/* ===========================================================================*/
/**
 * @name send_DCCBufPtr()
 * @brief : Sending the DCC uri buff addr to ducati
 * @param void
 * @return return = 0 is successful
 * @sa TBD
 *
 */
/* ===========================================================================*/

OMX_ERRORTYPE send_DCCBufPtr(OMX_HANDLETYPE hComponent)
{
       OMX_TI_CONFIG_SHAREDBUFFER uribufparam;
       OMX_ERRORTYPE eError = OMX_ErrorNone;
       PROXY_COMPONENT_PRIVATE *pComponentPrivate;
       OMX_COMPONENTTYPE *pHandle = NULL;

       _PROXY_OMX_INIT_PARAM(&uribufparam, OMX_TI_CONFIG_SHAREDBUFFER);
       uribufparam.nPortIndex = OMX_ALL;

       DOMX_ENTER("ENTER");
       pHandle = (OMX_COMPONENTTYPE *) hComponent;
       pComponentPrivate = (PROXY_COMPONENT_PRIVATE *)pHandle->pComponentPrivate;
       uribufparam.nSharedBuffSize = dccbuf_size;
if(pComponentPrivate->bMapBuffers)
       uribufparam.pSharedBuff = (OMX_PTR) sDccBuffer.bufferFd;
else
       uribufparam.pSharedBuff = sDccBuffer.pBufferHandle;

       DOMX_DEBUG("SYSLINK MAPPED ADDR:  0x%x sizeof buffer %d",
               uribufparam.pSharedBuff, uribufparam.nSharedBuffSize);

       eError = __PROXY_SetParameter(hComponent,
                                                               OMX_TI_IndexParamDccUriBuffer,
                                                               &uribufparam,
                                                               &(uribufparam.pSharedBuff), 1);

       if (eError != OMX_ErrorNone) {
               DOMX_ERROR(" Error in SetParam for DCC Uri Buffer 0x%x", eError);
       }

       DOMX_EXIT("EXIT");
       return eError;
}

/* ===========================================================================*/
/**
 * @name read_DCCdir()
 * @brief : copies all the dcc profiles into the allocated 1D-Tiler buffer
 *          and returns the size of the buffer.
 * @param void : OMX_PTR is null then returns the size of the DCC directory
 * @return return = size of the DCC directory or error in case of any failures
 *                 in file read or open
 * @sa TBD
 *
 */
/* ===========================================================================*/
OMX_S32 read_DCCdir(OMX_PTR buffer, OMX_STRING * dir_path, OMX_U16 numofURI)
{
       FILE *pFile;
       OMX_S32 lSize;
       OMX_S32 dcc_buf_size = 0;
       size_t result;
       OMX_STRING filename;
       char temp[200];
       OMX_STRING dotdot = "..";
       DIR *d;
       struct dirent *dir;
       OMX_U16 i = 0;
       OMX_S32 ret = 0;

       DOMX_ENTER("ENTER");
       for (i = 0; i < numofURI - 1; i++)
       {
               d = opendir(dir_path[i]);
               if (d)
               {
                       /* read each filename */
                       while ((dir = readdir(d)) != NULL)
                       {
                               filename = dir->d_name;
                               strcpy(temp, dir_path[i]);
                               strcat(temp, filename);
                               if ((*filename != *dotdot))
                               {
                                       DOMX_DEBUG
                                           ("\n\t DCC Profiles copying into buffer => %s mpu_addr: %p",
                                           temp, buffer);
                                       pFile = fopen(temp, "rb");
                                       if (pFile == NULL)
                                       {
                                               DOMX_ERROR("File open error");
                                               ret = -1;
                                       } else
                                       {
                                               fseek(pFile, 0, SEEK_END);
                                               lSize = ftell(pFile);
                                               rewind(pFile);
                                               /* buffer is not NULL then copy all the DCC profiles into buffer
                                                  else return the size of the DCC directory */
                                               if (buffer)
                                               {
                                                       // copy file into the buffer:
                                                       result =
                                                           fread(buffer, 1,
                                                           lSize, pFile);
                                                       if (result != (size_t) lSize)
                                                       {
                                                               DOMX_ERROR
                                                                   ("fread: Reading error");
                                                               ret = -1;
                                                       }
                                                       buffer =
                                                           buffer + lSize;
                                               }
                                               /* getting the size of the total dcc files available in FS */
                                               dcc_buf_size =
                                                   dcc_buf_size + lSize;
                                               // terminate
                                               fclose(pFile);
                                       }
                               }
                       }
                       closedir(d);
               }
       }
       if (ret == 0)
               ret = dcc_buf_size;

       DOMX_EXIT("return %d", ret);
       return ret;
}

/* ===========================================================================*/
/**
 * @name DCC_Deinit()
 * @brief
 * @param hComponent: OMX_HANDLETYPE
 * @return void
 * @sa TBD
 *
 */
/* ===========================================================================*/
void DCC_DeInit(OMX_HANDLETYPE hComponent)
{
       OMX_S16 status;
       MEMPLUGIN_BUFFER_PARAMS sDccBuff_params;
       MEMPLUGIN_BUFFER_PROPERTIES sDccBuff_prop;
       PROXY_COMPONENT_PRIVATE *pComponentPrivate;
       OMX_COMPONENTTYPE *pHandle = NULL;

       DOMX_ENTER("ENTER");
       pHandle = (OMX_COMPONENTTYPE *) hComponent;
       pComponentPrivate = (PROXY_COMPONENT_PRIVATE *)pHandle->pComponentPrivate;
       if (sDccBuffer.pBufferHandle)
       {
               MEMPLUGIN_BUFFER_PARAMS_INIT(sDccBuff_params);
               sDccBuff_prop.sBuffer_accessor.pBufferHandle = sDccBuffer.pBufferHandle;
               sDccBuff_prop.sBuffer_accessor.pBufferMappedAddress = sDccBuffer.pBufferMappedAddress;
               sDccBuff_prop.sBuffer_accessor.pRegBufferHandle = sDccBuffer.pRegBufferHandle;
               sDccBuff_params.nWidth = dccbuf_size;
               MemPlugin_Free(pComponentPrivate->pMemPluginHandle,pComponentPrivate->nMemmgrClientDesc,&sDccBuff_params,&sDccBuff_prop);
               sDccBuffer.pBufferHandle = NULL;
               sDccBuffer.bufferFd = -1;
               sDccBuffer.pBufferMappedAddress = NULL;
       }

       DOMX_EXIT("EXIT");
}
#endif


/*===============================================================*/
/** @fn Cam_Setup : This function is called when the the OMX Camera library is
 *                  loaded. It creates a mutex, which is used during DCC_Init()
 */
/*===============================================================*/
void __attribute__ ((constructor)) Cam_Setup(void)
{
	TIMM_OSAL_ERRORTYPE eError = TIMM_OSAL_ERR_NONE;

	eError = TIMM_OSAL_MutexCreate(&cam_mutex);
	if (eError != TIMM_OSAL_ERR_NONE)
	{
		TIMM_OSAL_Error("Creation of default mutex failed");
	}
}


/*===============================================================*/
/** @fn Cam_Destroy : This function is called when the the OMX Camera library is
 *                    unloaded. It destroys the mutex which was created by
 *                    Core_Setup().
 *
 */
/*===============================================================*/
void __attribute__ ((destructor)) Cam_Destroy(void)
{
	TIMM_OSAL_ERRORTYPE eError = TIMM_OSAL_ERR_NONE;

	eError = TIMM_OSAL_MutexDelete(cam_mutex);
	if (eError != TIMM_OSAL_ERR_NONE)
	{
		TIMM_OSAL_Error("Destruction of default mutex failed");
	}
}
