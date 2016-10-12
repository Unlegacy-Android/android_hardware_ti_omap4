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
 *  @file  omx_proxy_vc1enc.c
 *         This file contains methods that provides the functionality for
 *         the OpenMAX1.1 DOMX Framework Proxy component.
 *********************************************************************************************
 This is the proxy specific wrapper that passes the component name to the generic proxy init()
 The proxy wrapper also does some runtime/static time onfig on per proxy basis
 This is a thin wrapper that is called when componentiit() of the proxy is called
 static OMX_ERRORTYPE PROXY_Wrapper_init(OMX_HANDLETYPE hComponent, OMX_PTR pAppData);
 this layer gets called first whenever a proxy's get handle is called
 ************************************************************************************************
 *  @path WTSD_DucatiMMSW\omx\omx_il_1_x\omx_proxy_component\src
 *
 *  @rev 1.0
 */

/*==============================================================
 * ! Revision History
 * ! ============================
 *
 * ! 20-JUNE-2012 : x0078587@ti.com Initial Version
 * ================================================================*/

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
#include "omx_proxy_video_encoder.h"

#include <MetadataBufferType.h>
#ifdef  ENABLE_GRALLOC_BUFFERS
#include "native_handle.h"
#include <hal_public.h>
#include <VideoMetadata.h>
#endif

#include <stdlib.h>
#include <cutils/properties.h>

#define COMPONENT_NAME "OMX.TI.DUCATI1.VIDEO.VC1E"
/* needs to be specific for every configuration wrapper */

#define OMX_VC1E_INPUT_PORT 0
#define LINUX_PAGE_SIZE 4096

#ifdef ANDROID_QUIRK_CHANGE_PORT_VALUES

OMX_ERRORTYPE LOCAL_PROXY_VC1E_GetParameter(OMX_IN OMX_HANDLETYPE hComponent,
                                            OMX_IN OMX_INDEXTYPE nParamIndex, OMX_INOUT OMX_PTR pParamStruct);

OMX_ERRORTYPE LOCAL_PROXY_VC1E_SetParameter(OMX_IN OMX_HANDLETYPE hComponent,
                                            OMX_IN OMX_INDEXTYPE nParamIndex, OMX_INOUT OMX_PTR pParamStruct);

#endif


#define OMX_INIT_STRUCT(_s_, _name_)    \
    memset(&(_s_), 0x0, sizeof(_name_));         \
    (_s_).nSize = sizeof(_name_);               \
    (_s_).nVersion.s.nVersionMajor = 0x1;    \
    (_s_).nVersion.s.nVersionMinor = 0x1;     \
    (_s_).nVersion.s.nRevision = 0x0;            \
    (_s_).nVersion.s.nStep = 0x0


/* Params needed for Dynamic Frame Rate Control*/
#define FRAME_RATE_THRESHOLD 1 /* Change in Frame rate to configure the encoder */
OMX_U32      nFrameRateThreshold = 0; /* Frame Rate threshold for every frame rate update */
OMX_U32      nPortFrameRate = 0; /* Port FPS initially set to the Encoder */
OMX_U32      nFrameCounter = 0; /* Number of input frames recieved since last framerate calculation */
OMX_TICKS    nVideoTime = 0; /* Video duration since last framerate calculation */
OMX_TICKS    nLastFrameRateUpdateTime = 0; /*Time stamp at last frame rate update */


#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
/* Opaque color format requires below quirks to be enabled
 * ENABLE_GRALLOC_BUFFERS
 * ANDROID_QUIRCK_CHANGE_PORT_VALUES
 */
#define OMX_VC1VE_NUM_INTERNAL_BUF (8)

#define COLORCONVERT_MAX_SUB_BUFFERS (3)

#define COLORCONVERT_BUFTYPE_VIRTUAL (0x0)
#define COLORCONVERT_BUFTYPE_ION     (0x1)
#define COLORCONVERT_BUFTYPE_GRALLOCOPAQUE (0x2)

int COLORCONVERT_open(void * *hCC, PROXY_COMPONENT_PRIVATE *pCompPrv);
int COLORCONVERT_PlatformOpaqueToNV12(void *hCC, void *pSrc[],
                                      void *pDst[], int nWidth,
                                      int nHeight, int nStride,
                                      int nSrcBufType, int nDstBufType);
int COLORCONVERT_close(void *hCC, PROXY_COMPONENT_PRIVATE *pCompPrv);
static int COLORCONVERT_AllocateBuffer(OMX_HANDLETYPE hComponent, OMX_U32 nStride);
static OMX_ERRORTYPE LOCAL_PROXY_VC1E_AllocateBuffer(OMX_IN OMX_HANDLETYPE hComponent,
                                                     OMX_INOUT OMX_BUFFERHEADERTYPE * *ppBufferHdr, OMX_IN OMX_U32 nPortIndex,
                                                     OMX_IN OMX_PTR pAppPrivate, OMX_IN OMX_U32 nSizeBytes);

static OMX_ERRORTYPE LOCAL_PROXY_VC1E_FreeBuffer(OMX_IN OMX_HANDLETYPE hComponent,
                                                 OMX_IN OMX_U32 nPortIndex, OMX_IN OMX_BUFFERHEADERTYPE *pBufferHdr);

static OMX_ERRORTYPE LOCAL_PROXY_VC1E_ComponentDeInit(OMX_HANDLETYPE hComponent);

extern RPC_OMX_ERRORTYPE RPC_RegisterBuffer(OMX_HANDLETYPE hRPCCtx, int fd1, int fd2,
				     OMX_PTR *handle1, OMX_PTR *handle2,
				     PROXY_BUFFER_TYPE proxyBufferType);
extern RPC_OMX_ERRORTYPE RPC_UnRegisterBuffer(OMX_HANDLETYPE hRPCCtx, OMX_PTR handle1, OMX_PTR handle2, PROXY_BUFFER_TYPE proxyBufferType);
#endif


OMX_ERRORTYPE LOCAL_PROXY_VC1E_GetExtensionIndex(OMX_IN OMX_HANDLETYPE hComponent,
                                                 OMX_IN OMX_STRING cParameterName, OMX_OUT OMX_INDEXTYPE *pIndexType);

OMX_ERRORTYPE LOCAL_PROXY_VC1E_EmptyThisBuffer(OMX_HANDLETYPE hComponent,
                                               OMX_BUFFERHEADERTYPE *pBufferHdr);

/* ===========================================================================*/
/**
 * @name OMX_ConfigureDynamicFrameRate()
 * @brief This function is used to dynamically change
           the frame rate of the encoder to obtain target frame rate.
 * @param hComponent : pointer to the OMX Component.
 * @param pBufferHdr : buffer header to be configured.
 * @return OMX_ErrorNone = Successful
 *
 */
/* ===========================================================================*/
static OMX_ERRORTYPE OMX_ConfigureDynamicFrameRate(OMX_HANDLETYPE hComponent,
                                                   OMX_BUFFERHEADERTYPE *pBufferHdr)
{
    OMX_ERRORTYPE               eError = OMX_ErrorNone;
    OMX_U32                     nTargetFrameRate = 0; /* Target Frame Rate to be provided to Encoder */
    OMX_U32                     nCurrentFrameRate = 0; /* Current Frame Rate currently set  in Encoder */
    OMX_CONFIG_FRAMERATETYPE    tFrameRate;
    OMX_COMPONENTTYPE          *pHandle;

    DOMX_ENTER("%s hComponent = %p, pBufferHdr = %p", __FUNCTION__, hComponent, pBufferHdr);

    if( hComponent == NULL ) {
        DOMX_ERROR("Component is invalid/ not present ");
        eError = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pHandle = (OMX_COMPONENTTYPE *) hComponent;

    /* Initialise the OMX structures */
    OMX_INIT_STRUCT(tFrameRate, OMX_CONFIG_FRAMERATETYPE);

    /* Intialise nLastFrameRateUpdateTime for the 1st frame */
    if((!nFrameCounter) && (!nLastFrameRateUpdateTime)) {
        nLastFrameRateUpdateTime = pBufferHdr->nTimeStamp;
    }

    /* Increment the Frame Counter and Calculate Frame Rate*/
    nFrameCounter++;
    nVideoTime = pBufferHdr->nTimeStamp - nLastFrameRateUpdateTime;

    if( nVideoTime < 0 ) {
        eError = OMX_ErrorBadParameter;
        goto EXIT;
    }

    /*Get Port Frame Rate if not read yet*/
    if( !nFrameRateThreshold ) {
        tFrameRate.nPortIndex = OMX_VC1E_INPUT_PORT; /* As per ducati support-set for input port */

        /* Read Current FrameRate */
        eError = pHandle->GetConfig(hComponent, OMX_IndexConfigVideoFramerate, &tFrameRate);
        if( eError != OMX_ErrorNone ) {
            DOMX_ERROR("pHandle->GetConfig OMX_IndexConfigVideoFramerate eError :0x%x \n", eError);
        }
        nFrameRateThreshold = tFrameRate.xEncodeFramerate >> 16;
        nPortFrameRate = nFrameRateThreshold;
        DOMX_DEBUG(" Port Frame Rate is %d ", nPortFrameRate);
    }
    nCurrentFrameRate = nFrameRateThreshold;

    /* If Number of frames is less than the Threshold
      *  Frame Rate udpate is not necessary
      */
    if( nFrameCounter < nFrameRateThreshold ) {
        DOMX_EXIT(" Threshold not reached, no update necessary");
        eError = OMX_ErrorNone;
        goto EXIT;
    }

    /*Calculate the new target Frame Rate*/
    if( nVideoTime != 0 ) {
        nTargetFrameRate = nFrameCounter * OMX_TICKS_PER_SECOND / nVideoTime;
    }

    /* For 1080p  record, max FPS supported by Codec for advanced profile is 30.
      * When Dynamic Frame Rate is enabled, there might be scenario when FPS
      * calculated is more than 30. Hence adding the check so that Dynamic Frame
      * Rate set is never greater than the port FPS initially set.
      */
    if( nTargetFrameRate > nPortFrameRate ) {
        DOMX_DEBUG("Frame Rate Calculated is more than initial port set Frame Rate");
        nTargetFrameRate = nPortFrameRate;
    }

    /* Difference in Frame Rate is more than Threshold - Only then update Frame Rate*/
    if((((OMX_S32)nTargetFrameRate) - ((OMX_S32) nCurrentFrameRate) >= FRAME_RATE_THRESHOLD) ||
       (((OMX_S32) nCurrentFrameRate) - ((OMX_S32)nTargetFrameRate) >= FRAME_RATE_THRESHOLD)) {

        /* Now Send the new Frame Rate */
        tFrameRate.nPortIndex = OMX_VC1E_INPUT_PORT; /* As per ducati support-set for input port */
        tFrameRate.xEncodeFramerate = (OMX_U32)(nTargetFrameRate * (1 << 16));
        eError = pHandle->SetConfig(hComponent, OMX_IndexConfigVideoFramerate, &tFrameRate);
        if( eError != OMX_ErrorNone ) {
            DOMX_ERROR(" Error while configuring Dynamic Frame Rate,Error info = %d", eError);
            goto EXIT;
        } else {
            DOMX_DEBUG("Dynamic Frame Rate configuration successful \n");
        }
        nFrameRateThreshold = nTargetFrameRate; /*Update the threshold */
    }

    /* reset all params */
    nFrameCounter = 0;
    nVideoTime = 0;
    nLastFrameRateUpdateTime = pBufferHdr->nTimeStamp;
    eError = OMX_ErrorNone;

EXIT:
    DOMX_EXIT("%s eError: %d", __FUNCTION__, eError);
    return (eError);
}

static OMX_ERRORTYPE ComponentPrivateEmptyThisBuffer(OMX_HANDLETYPE hComponent,
                                                     OMX_BUFFERHEADERTYPE *pBufferHdr)
{
    OMX_ERRORTYPE    eError = OMX_ErrorNone;
    OMX_COMPONENTTYPE *hComp = (OMX_COMPONENTTYPE *) hComponent;
	PROXY_COMPONENT_PRIVATE *pCompPrv;
	PROXY_assert(hComponent != NULL, OMX_ErrorInsufficientResources,"Null component handle received in EmptyThisBuffer");
	pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
	PROXY_assert(pCompPrv != NULL, OMX_ErrorInsufficientResources,"Pointer to Null component private structure received in EmptyThisBuffer");
        if(pCompPrv->proxyPortBuffers[0].proxyBufferType == EncoderMetadataPointers) {
		OMX_U32 *pTempBuffer;
		OMX_U32 nMetadataBufferType;
		pTempBuffer = (OMX_U32 *) (pBufferHdr->pBuffer);
		if(pTempBuffer == NULL) {
	        eError = OMX_ErrorBadParameter;
			DOMX_ERROR("Null meta data buffer supplied - Cannot find metadata type");
			goto EXIT;
	        }
		nMetadataBufferType = *pTempBuffer;
		if(nMetadataBufferType == CAMERA_METADATA_BUFFER_TYPE) {
			eError = OMX_ConfigureDynamicFrameRate(hComponent, pBufferHdr);
			if( eError != OMX_ErrorNone)
				DOMX_ERROR(" Error while configuring FrameRate Dynamically.Error  info = %d - Non Fatal Error",eError);
		}
	}

    DOMX_DEBUG("Redirection from ComponentPricateEmptyThisBuffer to PROXY_EmptyThisBuffer");
EXIT:
        if( eError != OMX_ErrorNone) {
		DOMX_EXIT("%s: exiting with error 0x%x - Non Fatal",__FUNCTION__,eError);
        } else {
               DOMX_EXIT("%s: dynamic frame rate config successful",__FUNCTION__);
        }
    return (LOCAL_PROXY_VC1E_EmptyThisBuffer(hComponent, pBufferHdr));
}

/* ===========================================================================*/
/**
 * @name OMX_ComponentInit()
 * @brief This function is used to
 *           Initializes the Component Specific Datastructures
 * @param hComponent  : pointer to the OMX Component.
 * @return OMX_ErrorNone = Successful
 *
 */
/* ===========================================================================*/
OMX_ERRORTYPE OMX_ComponentInit(OMX_HANDLETYPE hComponent)
{
    OMX_ERRORTYPE              eError = OMX_ErrorNone;
    OMX_COMPONENTTYPE         *pHandle = NULL;
    PROXY_COMPONENT_PRIVATE   *pComponentPrivate = NULL;

    pHandle = (OMX_COMPONENTTYPE *) hComponent;
    OMX_TI_PARAM_ENHANCEDPORTRECONFIG    tParamStruct;
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    TIMM_OSAL_ERRORTYPE       eOSALStatus = TIMM_OSAL_ERR_NONE;
    OMX_PROXY_ENCODER_PRIVATE   *pProxy = NULL;
#endif
    char       value[OMX_MAX_STRINGNAME_SIZE];
    OMX_U32    mEnableVFR = 1; /* Flag used to enable/disable VFR for Encoder */
    property_get("debug.vfr.enable", value, " 1");
    mEnableVFR = atoi(value);

    DOMX_ENTER("");

    DOMX_DEBUG("Component name provided is %s", COMPONENT_NAME);

    pHandle->pComponentPrivate =
        (PROXY_COMPONENT_PRIVATE *)
        TIMM_OSAL_Malloc(sizeof(PROXY_COMPONENT_PRIVATE), TIMM_OSAL_TRUE,
                         0, TIMMOSAL_MEM_SEGMENT_INT);

    PROXY_assert(pHandle->pComponentPrivate != NULL,
                 OMX_ErrorInsufficientResources,
                 "ERROR IN ALLOCATING PROXY COMPONENT PRIVATE STRUCTURE");

    pComponentPrivate =
        (PROXY_COMPONENT_PRIVATE *) pHandle->pComponentPrivate;

    TIMM_OSAL_Memset(pComponentPrivate, 0,
                     sizeof(PROXY_COMPONENT_PRIVATE));

    pComponentPrivate->cCompName =
        TIMM_OSAL_Malloc(MAX_COMPONENT_NAME_LENGTH * sizeof(OMX_U8),
                         TIMM_OSAL_TRUE, 0, TIMMOSAL_MEM_SEGMENT_INT);

    PROXY_assert(pComponentPrivate->cCompName != NULL,
                 OMX_ErrorInsufficientResources,
                 " Error in Allocating space for proxy component table");

#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    pComponentPrivate->pCompProxyPrv =
        (OMX_PROXY_ENCODER_PRIVATE *)
        TIMM_OSAL_Malloc(sizeof(OMX_PROXY_ENCODER_PRIVATE), TIMM_OSAL_TRUE,
                         0, TIMMOSAL_MEM_SEGMENT_INT);

    PROXY_assert(pComponentPrivate->pCompProxyPrv != NULL,
                 OMX_ErrorInsufficientResources,
                 " Could not allocate proxy component private");

    TIMM_OSAL_Memset(pComponentPrivate->pCompProxyPrv, 0,
                     sizeof(OMX_PROXY_ENCODER_PRIVATE));

    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pComponentPrivate->pCompProxyPrv;

    /* Create Pipe of for encoder input buffers */
    eOSALStatus = TIMM_OSAL_CreatePipe(&pProxy->hBufPipe, sizeof(OMX_U32),
                                       OMX_VC1VE_NUM_INTERNAL_BUF, 1);
    PROXY_assert(eOSALStatus == TIMM_OSAL_ERR_NONE,
                 OMX_ErrorInsufficientResources,
                 "Pipe creation failed");
#endif

    // Copying component Name - this will be picked up in the proxy common
    PROXY_assert(strlen(COMPONENT_NAME) + 1 < MAX_COMPONENT_NAME_LENGTH,
                 OMX_ErrorInvalidComponentName,
                 "Length of component name is longer than the max allowed");
    TIMM_OSAL_Memcpy(pComponentPrivate->cCompName, COMPONENT_NAME,
                     strlen(COMPONENT_NAME) + 1);

    eError = OMX_ProxyCommonInit(hComponent);   // Calling Proxy Common Init()
#ifdef ANDROID_QUIRK_CHANGE_PORT_VALUES
    pHandle->SetParameter = LOCAL_PROXY_VC1E_SetParameter;
    pHandle->GetParameter = LOCAL_PROXY_VC1E_GetParameter;
#endif
    pComponentPrivate->IsLoadedState = OMX_TRUE;
    pHandle->EmptyThisBuffer = LOCAL_PROXY_VC1E_EmptyThisBuffer;
    pHandle->GetExtensionIndex = LOCAL_PROXY_VC1E_GetExtensionIndex;

#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    pHandle->ComponentDeInit = LOCAL_PROXY_VC1E_ComponentDeInit;
    pHandle->FreeBuffer = LOCAL_PROXY_VC1E_FreeBuffer;
    pHandle->AllocateBuffer = LOCAL_PROXY_VC1E_AllocateBuffer;
#endif

    if( mEnableVFR ) {
        pHandle->EmptyThisBuffer = ComponentPrivateEmptyThisBuffer;
    }

EXIT:
    if( eError != OMX_ErrorNone ) {
        DOMX_DEBUG("Error in Initializing Proxy");

#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
        if( pProxy->hBufPipe != NULL ) {
            TIMM_OSAL_DeletePipe(pProxy->hBufPipe);
            pProxy->hBufPipe = NULL;
        }

        if( pComponentPrivate->pCompProxyPrv != NULL ) {
            TIMM_OSAL_Free(pComponentPrivate->pCompProxyPrv);
            pComponentPrivate->pCompProxyPrv = NULL;
            pProxy = NULL;
        }
#endif
        if( pComponentPrivate->cCompName != NULL ) {
            TIMM_OSAL_Free(pComponentPrivate->cCompName);
            pComponentPrivate->cCompName = NULL;
        }
        if( pComponentPrivate != NULL ) {
            TIMM_OSAL_Free(pComponentPrivate);
            pComponentPrivate = NULL;
        }
    }
    return (eError);
}

#ifdef  ANDROID_QUIRK_CHANGE_PORT_VALUES

/* ===========================================================================*/
/**
 * @name PROXY_VC1E_GetParameter()
 * @brief This fuction sends the parameter stucture to the component to
 *    get the values of requested parameter by application.
 * @param [in] hComponent  : pointer to the OMX Component.
 * @param [in] nParamIndex : Index of the parameter to get
 * @param [in] pParamStruct: pointer to the paramter structure
 * @return OMX_ErrorNone = Successful
 *
 */
/* ===========================================================================*/
OMX_ERRORTYPE LOCAL_PROXY_VC1E_GetParameter(OMX_IN OMX_HANDLETYPE hComponent,
                                            OMX_IN OMX_INDEXTYPE nParamIndex, OMX_INOUT OMX_PTR pParamStruct)
{
    OMX_ERRORTYPE                     eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE          *pCompPrv = NULL;
    OMX_COMPONENTTYPE                *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_PARAM_PORTDEFINITIONTYPE     *pPortDef = NULL;
    OMX_VIDEO_PARAM_PORTFORMATTYPE   *pPortParam = NULL;

#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    OMX_PROXY_ENCODER_PRIVATE   *pProxy = NULL;
#endif

    PROXY_require((pParamStruct != NULL), OMX_ErrorBadParameter, NULL);
    PROXY_assert((hComp->pComponentPrivate != NULL),
                 OMX_ErrorBadParameter, NULL);

    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;
#endif

    DOMX_ENTER
        ("hComponent = %p, pCompPrv = %p, nParamIndex = %d, pParamStruct = %p",
        hComponent, pCompPrv, nParamIndex, pParamStruct);

    eError = PROXY_GetParameter(hComponent, nParamIndex, pParamStruct);

    if( nParamIndex == OMX_IndexParamPortDefinition ) {
        pPortDef = (OMX_PARAM_PORTDEFINITIONTYPE *)pParamStruct;

        if( pPortDef->format.video.eColorFormat == OMX_COLOR_FormatYUV420PackedSemiPlanar ) {
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
            if( pProxy->bAndroidOpaqueFormat == OMX_TRUE ) {
                pPortDef->format.video.eColorFormat = OMX_COLOR_FormatAndroidOpaque;
            } else
#endif
            {
                pPortDef->format.video.eColorFormat = OMX_TI_COLOR_FormatYUV420PackedSemiPlanar;
            }
        }

        if( pPortDef->nPortIndex == OMX_VC1E_INPUT_PORT ) {
            if( pCompPrv->proxyPortBuffers[OMX_VC1E_INPUT_PORT].proxyBufferType == EncoderMetadataPointers ) {
                pPortDef->nBufferSize = sizeof(video_metadata_t);
            }
        }
    } else if( nParamIndex == OMX_IndexParamVideoPortFormat ) {
        pPortParam = (OMX_VIDEO_PARAM_PORTFORMATTYPE *)pParamStruct;

        if((eError == OMX_ErrorNone) &&
           (pPortParam->eColorFormat == OMX_COLOR_FormatYUV420PackedSemiPlanar)) {
            pPortParam->eColorFormat = OMX_TI_COLOR_FormatYUV420PackedSemiPlanar;
        }
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
        else if((eError == OMX_ErrorNoMore) &&
                (pPortParam->nIndex == 1)) {
            /* HACK:Remote OMX-VC1E supports only 1 color format (index 0). The
             * OMX_COLOR_FormatAndroidOpaque is supported only at the proxy.
             * Call GetParameter() to fill in defaults for parameters and
             * override color format and index for the additional
             * OMX_COLOR_FormatAndroidOpaque support*/
            pPortParam->nIndex = 0;
            eError = PROXY_GetParameter(hComponent, nParamIndex, pParamStruct);
            pPortParam->nIndex = 1;
            pPortParam->eColorFormat = OMX_COLOR_FormatAndroidOpaque;
            eError = OMX_ErrorNone;
        }
#endif
    } else if( nParamIndex == OMX_TI_IndexComponentHandle ) {
        OMX_TI_COMPONENT_HANDLE   *pCompHandle = pParamStruct;
        pCompHandle->pHandle = hComponent;
        eError = OMX_ErrorNone;
    }

    PROXY_assert((eError == OMX_ErrorNone) || (eError == OMX_ErrorNoMore),
                 eError, " Error in Proxy GetParameter");

EXIT:
    DOMX_EXIT("eError: %d", eError);
    return (eError);
}

/* ===========================================================================*/
/**
 * @name PROXY_VC1E_SetParameter()
 * @brief This fuction sends the parameter stucture to the component to
 *    set the values as as requested by application.
 * @param [in] hComponent  : pointer to the OMX Component.
 * @param [in] nIndex      : Index of the parameter to be set
 * @param [in] pParamStruct: pointer to the parameter structure to be set
 * @return OMX_ErrorNone = Successful
 *
 */
/* ===========================================================================*/
OMX_ERRORTYPE LOCAL_PROXY_VC1E_SetParameter(OMX_IN OMX_HANDLETYPE hComponent,
                                            OMX_IN OMX_INDEXTYPE nParamIndex, OMX_IN OMX_PTR pParamStruct)
{
    OMX_ERRORTYPE                             eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE                  *pCompPrv = NULL;
    OMX_COMPONENTTYPE                        *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_PARAM_PORTDEFINITIONTYPE             *pPortDef = NULL;
    OMX_VIDEO_PARAM_PORTFORMATTYPE           *pPortParams = NULL;
    OMX_VIDEO_STOREMETADATAINBUFFERSPARAMS   *pStoreMetaData = NULL;
    OMX_TI_PARAM_BUFFERPREANNOUNCE            tParamSetNPA;
    OMX_PARAM_PORTDEFINITIONTYPE              sPortDef;

#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    OMX_PROXY_ENCODER_PRIVATE   *pProxy = NULL;
#endif

    DOMX_ENTER
        ("hComponent = %p, pCompPrv = %p, nParamIndex = %d, pParamStruct = %p",
        hComponent, pCompPrv, nParamIndex, pParamStruct);

    PROXY_require((pParamStruct != NULL), OMX_ErrorBadParameter, NULL);
    PROXY_require((hComp->pComponentPrivate != NULL),
                  OMX_ErrorBadParameter, NULL);

    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;
#endif

    if( nParamIndex == OMX_IndexParamPortDefinition ) {
        pPortDef = (OMX_PARAM_PORTDEFINITIONTYPE *)pParamStruct;

        if( pPortDef->format.video.eColorFormat == OMX_TI_COLOR_FormatYUV420PackedSemiPlanar ) {
            pPortDef->format.video.eColorFormat = OMX_COLOR_FormatYUV420PackedSemiPlanar;
        }
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
        else if( pPortDef->format.video.eColorFormat == OMX_COLOR_FormatAndroidOpaque ) {
            if( COLORCONVERT_open(&pProxy->hCC, pCompPrv) != 0 ) {
                PROXY_assert(0, OMX_ErrorInsufficientResources,
                             "Failed to open Color converting service");
            }
            pProxy->bAndroidOpaqueFormat = OMX_TRUE;
            pPortDef->format.video.eColorFormat = OMX_COLOR_FormatYUV420PackedSemiPlanar;
        }
#endif
    } else if( nParamIndex == OMX_IndexParamVideoPortFormat ) {
        pPortParams = (OMX_VIDEO_PARAM_PORTFORMATTYPE *)pParamStruct;

        if( pPortParams->eColorFormat == OMX_TI_COLOR_FormatYUV420PackedSemiPlanar ) {
            pPortParams->eColorFormat = OMX_COLOR_FormatYUV420PackedSemiPlanar;
        }
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
        else if( pPortParams->eColorFormat == OMX_COLOR_FormatAndroidOpaque ) {
            if( COLORCONVERT_open(&pProxy->hCC, pCompPrv) != 0 ) {
                PROXY_assert(0, OMX_ErrorInsufficientResources,
                             "Failed to open Color converting service");
            }
            pProxy->bAndroidOpaqueFormat = OMX_TRUE;
            pPortParams->eColorFormat = OMX_COLOR_FormatYUV420PackedSemiPlanar;
        }
#endif
    } else if( nParamIndex == (OMX_INDEXTYPE) OMX_TI_IndexEncoderStoreMetadatInBuffers ) {
        pStoreMetaData = (OMX_VIDEO_STOREMETADATAINBUFFERSPARAMS *) pParamStruct;

        DOMX_DEBUG("Moving to Metadatamode");
        if( pStoreMetaData->nPortIndex == OMX_VC1E_INPUT_PORT && pStoreMetaData->bStoreMetaData == OMX_TRUE ) {
            OMX_INIT_STRUCT(tParamSetNPA, OMX_TI_PARAM_BUFFERPREANNOUNCE);
            tParamSetNPA.nPortIndex = OMX_VC1E_INPUT_PORT;
            tParamSetNPA.bEnabled = OMX_FALSE;
            //Call NPA on OMX encoder on ducati.
            PROXY_SetParameter(hComponent, (unsigned int)OMX_TI_IndexParamBufferPreAnnouncement, &tParamSetNPA);
            pCompPrv->proxyPortBuffers[pStoreMetaData->nPortIndex].proxyBufferType = EncoderMetadataPointers;
            DOMX_DEBUG("Moving to Metadatamode done");

            /*Initializing Structure */
            OMX_INIT_STRUCT(sPortDef, OMX_PARAM_PORTDEFINITIONTYPE);
            sPortDef.nPortIndex = OMX_VC1E_INPUT_PORT;

            eError = PROXY_GetParameter(hComponent, OMX_IndexParamPortDefinition, &sPortDef);
            PROXY_assert(eError == OMX_ErrorNone, eError, " Error in Proxy GetParameter for Port Def");

            sPortDef.format.video.nStride = LINUX_PAGE_SIZE;

            eError = PROXY_SetParameter(hComponent, OMX_IndexParamPortDefinition, &sPortDef);

            PROXY_assert(eError == OMX_ErrorNone, eError, " Error in Proxy SetParameter for Port Def");
        }
        goto EXIT;
    }

    eError = PROXY_SetParameter(hComponent, nParamIndex, pParamStruct);
    PROXY_assert(eError == OMX_ErrorNone,
                 eError, " Error in Proxy SetParameter");

EXIT:
    DOMX_EXIT("eError: %d", eError);
    return (eError);
}

#endif


/* ===========================================================================*/
/**
 * @name PROXY_GetExtensionIndex()
 * @brief This function is used to return the
 *          extended index value based on a string parameter
 * @param [in] hComponent  : pointer to the OMX Component.
 * @param [in] cParameterName : Name of Parameter
 * @param [out] pIndexType : Index Type to be returned
 * @return OMX_ErrorNone = Successful
 * @sa TBD
 *
 */
/* ===========================================================================*/
OMX_ERRORTYPE LOCAL_PROXY_VC1E_GetExtensionIndex(OMX_IN OMX_HANDLETYPE hComponent,
                                                 OMX_IN OMX_STRING cParameterName, OMX_OUT OMX_INDEXTYPE *pIndexType)
{
    OMX_ERRORTYPE              eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE   *pCompPrv = NULL;
    OMX_COMPONENTTYPE         *hComp = hComponent;

    PROXY_require((hComp->pComponentPrivate != NULL),
                  OMX_ErrorBadParameter, NULL);
    PROXY_require(cParameterName != NULL, OMX_ErrorBadParameter, NULL);
    PROXY_require(pIndexType != NULL, OMX_ErrorBadParameter, NULL);

    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;

    DOMX_ENTER("%s hComponent = %p, pCompPrv = %p, cParameterName = %s",
               __FUNCTION__, hComponent, pCompPrv, cParameterName);

    // Check for NULL Parameters
    PROXY_require((cParameterName != NULL && pIndexType != NULL),
                  OMX_ErrorBadParameter, NULL);

    // Ensure that String length is not greater than Max allowed length
    PROXY_require(strlen(cParameterName) <= 127, OMX_ErrorBadParameter, NULL);

    if( strcmp(cParameterName, "OMX.google.android.index.storeMetaDataInBuffers") == 0 ) {
        // If Index type is 2D Buffer Allocated Dimension
        *pIndexType = (OMX_INDEXTYPE) OMX_TI_IndexEncoderStoreMetadatInBuffers;
        goto EXIT;
    }

    eError = PROXY_GetExtensionIndex(hComponent, cParameterName, pIndexType);

EXIT:
    DOMX_EXIT("%s eError: %d", __FUNCTION__, eError);
    return (eError);
}

/* ===========================================================================*/
/**
 * @name PROXY_VC1E_EmptyThisBuffer()
 * @brief This function is used to send the input frame to the OMX encoder
 *           component for processing.
 * @param hComponent  : pointer to the OMX Component.
 * @param pBufferHdr  : header of buffer to be read.
 * @return OMX_ErrorNone = Successful
 * @sa TBD
 *
 */
/* ===========================================================================*/
OMX_ERRORTYPE LOCAL_PROXY_VC1E_EmptyThisBuffer(OMX_HANDLETYPE hComponent,
                                               OMX_BUFFERHEADERTYPE *pBufferHdr)
{

    OMX_ERRORTYPE                   eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE        *pCompPrv;
    OMX_COMPONENTTYPE              *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_PTR                         pBufferOrig = NULL;
    OMX_U32                         nStride = 0, nNumLines = 0;
    OMX_PARAM_PORTDEFINITIONTYPE    tParamStruct;
    OMX_U32                         nFilledLen, nAllocLen;

#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    OMX_PROXY_ENCODER_PRIVATE   *pProxy = NULL;
    TIMM_OSAL_ERRORTYPE       eOSALStatus = TIMM_OSAL_ERR_NONE;
    OMX_U32                   nBufIndex = 0, nSize=0, nRet=0;
#endif
#ifdef ENABLE_GRALLOC_BUFFERS
    OMX_PTR                pAuxBuf0 = NULL, pAuxBuf1 = NULL;
    RPC_OMX_ERRORTYPE      eRPCError = RPC_OMX_ErrorNone;
    OMX_ERRORTYPE          eCompReturn = OMX_ErrorNone;
    IMG_native_handle_t   *pGrallocHandle=NULL;
#endif

    DOMX_ENTER("%s hComponent = %p, pBufferHdr = %p", __FUNCTION__, hComponent, pBufferHdr);

    PROXY_require(pBufferHdr != NULL, OMX_ErrorBadParameter, NULL);
    PROXY_require(hComp->pComponentPrivate != NULL, OMX_ErrorBadParameter,
                  NULL);
    PROXY_CHK_VERSION(pBufferHdr, OMX_BUFFERHEADERTYPE);

    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;
#endif

    OMX_INIT_STRUCT(tParamStruct, OMX_PARAM_PORTDEFINITIONTYPE);
    tParamStruct.nPortIndex = OMX_VC1E_INPUT_PORT;

    eError = PROXY_GetParameter(hComponent, OMX_IndexParamPortDefinition, &tParamStruct);
    PROXY_require(eError == OMX_ErrorNone, OMX_ErrorBadParameter, "Error is Get Parameter for port def");
    nFilledLen = pBufferHdr->nFilledLen;
    nAllocLen = pBufferHdr->nAllocLen;
    if( nFilledLen != 0 ) {
        pBufferHdr->nFilledLen = tParamStruct.nBufferSize;
    }
    pBufferHdr->nAllocLen =  tParamStruct.nBufferSize;

    DOMX_DEBUG
        ("%s hComponent=%p, pCompPrv=%p, nFilledLen=%d, nOffset=%d, nFlags=%08x",
        __FUNCTION__, hComponent, pCompPrv, pBufferHdr->nFilledLen,
        pBufferHdr->nOffset, pBufferHdr->nFlags);

    if( pCompPrv->proxyPortBuffers[OMX_VC1E_INPUT_PORT].proxyBufferType == EncoderMetadataPointers ) {
        OMX_U32   *pTempBuffer;
        OMX_U32    nMetadataBufferType;
        DOMX_DEBUG("Passing meta data to encoder");

        pBufferOrig = pBufferHdr->pBuffer;

        pTempBuffer = (OMX_U32 *) (pBufferHdr->pBuffer);
        nMetadataBufferType = *pTempBuffer;

        if( nMetadataBufferType == CAMERA_METADATA_BUFFER_TYPE ) {
#ifdef ENABLE_GRALLOC_BUFFERS
            video_metadata_t   *pVideoMetadataBuffer;
            DOMX_DEBUG("MetadataBufferType is CAMERA_METADATA_BUFFER_TYPE");

            pVideoMetadataBuffer = (video_metadata_t *) ((OMX_U32 *)(pBufferHdr->pBuffer));
            pGrallocHandle = (IMG_native_handle_t *) (pVideoMetadataBuffer->pHandle);
            DOMX_DEBUG("Grallloc buffer recieved in metadata buffer 0x%x", pGrallocHandle);
            if( pGrallocHandle->iFormat != HAL_PIXEL_FORMAT_TI_NV12 && pProxy->gralloc_handle[0] == NULL ) {
                DOMX_DEBUG("Allocating NV12 buffers internally within DOMX actual count: %d", pCompPrv->nAllocatedBuffers);
                pProxy->nCurBufIndex = 0;

                while((unsigned) pProxy->nCurBufIndex < pCompPrv->nAllocatedBuffers ) {
                    eError = COLORCONVERT_AllocateBuffer(hComponent, nStride);
                    PROXY_require(eError == OMX_ErrorNone, eError, "Error allocating buffers for color conversion");
                    pProxy->nCurBufIndex++;
                }
            }
            pBufferHdr->pBuffer = (OMX_U8 *)(pGrallocHandle->fd[0]);
            ((OMX_TI_PLATFORMPRIVATE *) pBufferHdr->pPlatformPrivate)->
            pAuxBuf1 = (OMX_PTR) pGrallocHandle->fd[1];
            DOMX_DEBUG("%s Gralloc=0x%x, Y-fd=%d, UV-fd=%d", __FUNCTION__, pGrallocHandle,
                       pGrallocHandle->fd[0], pGrallocHandle->fd[1]);

#ifndef ANDROID_API_N_OR_LATER
            pBufferHdr->nOffset = pVideoMetadataBuffer->offset;
#endif
#endif
        } else if( nMetadataBufferType == kMetadataBufferTypeGrallocSource ) {
#ifdef ENABLE_GRALLOC_BUFFERS
            buffer_handle_t    tBufHandle;
            DOMX_DEBUG("MetadataBufferType is kMetadataBufferTypeGrallocSource");

            pTempBuffer++;
            tBufHandle =  *((buffer_handle_t *)pTempBuffer);
            pGrallocHandle = (IMG_native_handle_t *) tBufHandle;
            DOMX_DEBUG("Grallloc buffer recieved in metadata buffer 0x%x", pGrallocHandle);
            if( pGrallocHandle->iFormat != HAL_PIXEL_FORMAT_TI_NV12 && pProxy->gralloc_handle[0] == NULL ) {
                DOMX_DEBUG("Allocating NV12 buffers internally within DOMX actual count: %d", pCompPrv->nAllocatedBuffers);
                pProxy->nCurBufIndex = 0;

                while((unsigned) pProxy->nCurBufIndex < pCompPrv->nAllocatedBuffers ) {
                    eError = COLORCONVERT_AllocateBuffer(hComponent, nStride);
                    PROXY_require(eError == OMX_ErrorNone, eError, "Error allocating buffers for color conversion");
                    pProxy->nCurBufIndex++;
                }
            }

            pBufferHdr->pBuffer = (OMX_U8 *)(pGrallocHandle->fd[0]);
            ((OMX_TI_PLATFORMPRIVATE *) pBufferHdr->pPlatformPrivate)->
            pAuxBuf1 = (OMX_PTR) pGrallocHandle->fd[1];
            DOMX_DEBUG("%s Gralloc=0x%x, Y-fd=%d, UV-fd=%d", __FUNCTION__, pGrallocHandle,
                       pGrallocHandle->fd[0], pGrallocHandle->fd[1]);
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
            if( pProxy->bAndroidOpaqueFormat && pGrallocHandle->iFormat != HAL_PIXEL_FORMAT_TI_NV12 ) {
                /* Dequeue NV12 buffer for encoder */
                eOSALStatus = TIMM_OSAL_ReadFromPipe(pProxy->hBufPipe, &nBufIndex,
                                                     sizeof(OMX_PTR), (TIMM_OSAL_U32 *)(&nSize),
                                                     TIMM_OSAL_SUSPEND);
                PROXY_assert(eOSALStatus == TIMM_OSAL_ERR_NONE, OMX_ErrorBadParameter, NULL);

                if( nFilledLen != 0 ) {
                    /* Get NV12 data after colorconv*/
                    nRet = COLORCONVERT_PlatformOpaqueToNV12(pProxy->hCC, (void * *) &pGrallocHandle, (void * *) &pProxy->gralloc_handle[nBufIndex],
                                                             pGrallocHandle->iWidth,
                                                             pGrallocHandle->iHeight,
                                                             4096, COLORCONVERT_BUFTYPE_GRALLOCOPAQUE,
                                                             COLORCONVERT_BUFTYPE_GRALLOCOPAQUE);

                    if( nRet != 0 ) {
                        eOSALStatus = TIMM_OSAL_WriteToPipe(pProxy->hBufPipe, (void *) &nBufIndex,
                                                            sizeof(OMX_U32), TIMM_OSAL_SUSPEND);
                        PROXY_assert(0, OMX_ErrorBadParameter, "Color conversion routine failed");
                    }
                }

                /* Update pBufferHdr with NV12 buffers for OMX component */
                pBufferHdr->pBuffer= (OMX_U8 *)(pProxy->gralloc_handle[nBufIndex]->fd[0]);
                ((OMX_TI_PLATFORMPRIVATE *) pBufferHdr->pPlatformPrivate)->pAuxBuf1 = (OMX_PTR)(pProxy->gralloc_handle[nBufIndex]->fd[1]);
            }
#endif
#endif
        } else {
            DOMX_ERROR("MetadataBufferType is unknow. Returning 'OMX_ErrorBadParameter'");
            eError = OMX_ErrorBadParameter;
            goto EXIT; //need to restore lenght fields in pBufferHdr
        }
#ifdef ENABLE_GRALLOC_BUFFERS
        eRPCError = RPC_RegisterBuffer(pCompPrv->hRemoteComp, (int)pBufferHdr->pBuffer, -1,
                                       &pAuxBuf0, &pAuxBuf1,
                                       GrallocPointers);
        PROXY_checkRpcError();
        if( pAuxBuf0 ) {
            pBufferHdr->pBuffer = pAuxBuf0;
        }
        if( pAuxBuf1 ) {
            ((OMX_TI_PLATFORMPRIVATE *) pBufferHdr->pPlatformPrivate)->pAuxBuf1 = pAuxBuf1;
        }
#endif
    }

    eError = PROXY_EmptyThisBuffer(hComponent, pBufferHdr);
#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
    if( pProxy->bAndroidOpaqueFormat
#ifdef ENABLE_GRALLOC_BUFFERS
        && pGrallocHandle != NULL && pGrallocHandle->iFormat != HAL_PIXEL_FORMAT_TI_NV12
#endif
        ) {
        /*Write buffer to end of pipe for re-circulation for future ETB()*/
        eOSALStatus = TIMM_OSAL_WriteToPipe(pProxy->hBufPipe, (void *) &nBufIndex,
                                            sizeof(OMX_U32), TIMM_OSAL_SUSPEND);
        PROXY_assert(eOSALStatus == TIMM_OSAL_ERR_NONE, OMX_ErrorBadParameter, "Pipe write failed");
    }
#endif

EXIT:
    if( pBufferHdr != NULL && pCompPrv->proxyPortBuffers[pBufferHdr->nInputPortIndex].proxyBufferType == EncoderMetadataPointers ) {
        pBufferHdr->pBuffer = pBufferOrig;
        pBufferHdr->nFilledLen = nFilledLen;
        pBufferHdr->nAllocLen = nAllocLen;
#ifdef ENABLE_GRALLOC_BUFFERS
        RPC_UnRegisterBuffer(pCompPrv->hRemoteComp, pAuxBuf0, pAuxBuf1, GrallocPointers);
#endif
    }
    DOMX_EXIT("%s eError: %d", __FUNCTION__, eError);
    return (eError);
}

#ifdef ANDROID_CUSTOM_OPAQUECOLORFORMAT
/* ===========================================================================*/
/**
 * @name LOCAL_PROXY_VC1E_AllocateBuffer()
 * @brief
 * @param hComponent  : pointer to the OMX Component.
 * @param nPortIndex  : port where buffer need to be allocated.
 * @return OMX_ErrorNone = Successful
 * @sa TBD
 *
 */
/* ===========================================================================*/
static OMX_ERRORTYPE LOCAL_PROXY_VC1E_AllocateBuffer(OMX_HANDLETYPE hComponent,
                                                     OMX_BUFFERHEADERTYPE * *ppBufferHdr, OMX_U32 nPortIndex,
                                                     OMX_PTR pAppPrivate, OMX_U32 nSizeBytes)
{
    OMX_ERRORTYPE              eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE   *pCompPrv = NULL;
    OMX_COMPONENTTYPE         *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_PROXY_ENCODER_PRIVATE    *pProxy = NULL;
    TIMM_OSAL_ERRORTYPE        eOSALStatus = TIMM_OSAL_ERR_NONE;
    int                        err, nStride;

    DOMX_ENTER
        ("hComponent = %p, pCompPrv = %p, nPortIndex = %d, pAppPrivate = %p ,nSizeBytes = %d",
        hComponent, pCompPrv, nPortIndex, pAppPrivate, nSizeBytes);
    PROXY_require(hComp->pComponentPrivate != NULL, OMX_ErrorBadParameter,
                  NULL);
    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;


    eError = PROXY_AllocateBuffer(hComponent, ppBufferHdr, nPortIndex,
                                  pAppPrivate, nSizeBytes);
EXIT:
    DOMX_EXIT("%s eError: %d", __FUNCTION__, eError);
    return (eError);
}

/* ===========================================================================*/
/**
 * @name LOCAL_PROXY_VC1E_FreeBuffer()
 * @brief This function is used to free all the buffers that were allocated
 *          and sent to component though use_buffer call.
 * @param hComponent  : pointer to the OMX Component.
 * @param nPortIndex  : Port where buffer needs to be freed
 * @param pBufferHdr  : Buffer header
 * @return OMX_ErrorNone = Successful
 *
 */
/* ===========================================================================*/
static OMX_ERRORTYPE LOCAL_PROXY_VC1E_FreeBuffer(OMX_IN OMX_HANDLETYPE hComponent,
                                                 OMX_IN OMX_U32 nPortIndex, OMX_IN OMX_BUFFERHEADERTYPE *pBufferHdr)
{
    OMX_ERRORTYPE              eError = OMX_ErrorNone;
    OMX_COMPONENTTYPE         *hComp = (OMX_COMPONENTTYPE *) hComponent;
    PROXY_COMPONENT_PRIVATE   *pCompPrv = NULL;
    OMX_U32                    nBufIndex, nSize, nCount=0;
    OMX_PROXY_ENCODER_PRIVATE    *pProxy = NULL;

    DOMX_ENTER("%s hComponent = %p, nPortIndex = %d, pBufferHdr = %p",
               __FUNCTION__, hComponent, nPortIndex, pBufferHdr);

    PROXY_require(hComp->pComponentPrivate != NULL, OMX_ErrorBadParameter,
                  NULL);
    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;

    if((nPortIndex == OMX_VC1E_INPUT_PORT) &&
       (pProxy->bAndroidOpaqueFormat) && (pProxy->gralloc_handle[0] != NULL)) {
        pProxy->nCurBufIndex--;
        PROXY_require(pProxy->nCurBufIndex >= 0,
                      OMX_ErrorBadParameter, "Buffer index underflow");

        if( pProxy->gralloc_handle[pProxy->nCurBufIndex] ) {
            pProxy->mAllocDev->free(pProxy->mAllocDev, (buffer_handle_t)(pProxy->gralloc_handle[pProxy->nCurBufIndex]));
            pProxy->gralloc_handle[pProxy->nCurBufIndex] = NULL;
        }

        /*Clear the Bufindex pipe by dummy reads*/
        TIMM_OSAL_GetPipeReadyMessageCount(pProxy->hBufPipe, (TIMM_OSAL_U32 *)&nCount);
        if( nCount ) {
            TIMM_OSAL_ReadFromPipe(pProxy->hBufPipe, &nBufIndex,
                                   sizeof(OMX_PTR), (TIMM_OSAL_U32 *)&nSize, TIMM_OSAL_NO_SUSPEND);
        }
    }

    eError = PROXY_FreeBuffer(hComponent, nPortIndex, pBufferHdr);

EXIT:
    DOMX_EXIT("%s eError: %d", __FUNCTION__, eError);
    return (eError);
}

/* ===========================================================================*/
/**
 * @name COLORCONVERT_AllocateBuffer()
 * @brief Allocating gralloc buffers for color conversion
 * @param hComponent  : pointer to the OMX Component.
 * @param nStride     : Stride of the frame.
 * @return OMX_ErrorNone = Successful
 *
 */
/* ===========================================================================*/
int COLORCONVERT_AllocateBuffer(OMX_HANDLETYPE hComponent, OMX_U32 nStride)
{
    OMX_CONFIG_RECTTYPE        tParam;
    TIMM_OSAL_ERRORTYPE        eOSALStatus = TIMM_OSAL_ERR_NONE;
    OMX_U32                    err;
    OMX_ERRORTYPE              eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE   *pCompPrv = NULL;
    OMX_PROXY_ENCODER_PRIVATE    *pProxy = NULL;
    OMX_COMPONENTTYPE         *hComp = (OMX_COMPONENTTYPE *) hComponent;

    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;

    OMX_INIT_STRUCT(tParam, OMX_CONFIG_RECTTYPE);
    tParam.nPortIndex = OMX_VC1E_INPUT_PORT;
    eError = PROXY_GetParameter(hComponent, (OMX_INDEXTYPE)OMX_TI_IndexParam2DBufferAllocDimension, &tParam);
    PROXY_assert(eError == OMX_ErrorNone, eError, " Error in Proxy GetParameter");
    err = pProxy->mAllocDev->alloc(pProxy->mAllocDev, (int) tParam.nWidth, (int) tParam.nHeight,
                                   (int) HAL_PIXEL_FORMAT_TI_NV12, (int) GRALLOC_USAGE_HW_RENDER,
                                   (buffer_handle_t *)(&(pProxy->gralloc_handle[pProxy->nCurBufIndex])), (int *) &nStride);
    PROXY_assert(!err, err, " Error in allocating Gralloc buffers");
    eOSALStatus = TIMM_OSAL_WriteToPipe(pProxy->hBufPipe, (void *) &pProxy->nCurBufIndex, sizeof(OMX_U32), TIMM_OSAL_SUSPEND);
    PROXY_assert(eOSALStatus == TIMM_OSAL_ERR_NONE, OMX_ErrorBadParameter, "Pipe write failed");

EXIT:
    return (eError);
}

/* ===========================================================================*/
/**
 * @name PROXY_VC1E_ComponentDeInit()
 * @brief This function is used as a proxy to deinitalize the component which
 *          means to free any resources allocated at component
 * @param hComponent  : pointer to the OMX Component.
 * @return OMX_ErrorNone = Successful
 *
 */
/* ===========================================================================*/
OMX_ERRORTYPE LOCAL_PROXY_VC1E_ComponentDeInit(OMX_HANDLETYPE hComponent)
{
    OMX_ERRORTYPE              eError = OMX_ErrorNone;
    PROXY_COMPONENT_PRIVATE   *pCompPrv;
    OMX_COMPONENTTYPE         *hComp = (OMX_COMPONENTTYPE *) hComponent;
    OMX_PROXY_ENCODER_PRIVATE    *pProxy = NULL;
    TIMM_OSAL_ERRORTYPE        eOSALStatus = TIMM_OSAL_ERR_NONE;
    OMX_U32                    i;

    DOMX_ENTER("%s hComponent = %p", __FUNCTION__, hComponent);

    PROXY_require(hComp->pComponentPrivate != NULL, OMX_ErrorBadParameter,
                  NULL);
    pCompPrv = (PROXY_COMPONENT_PRIVATE *) hComp->pComponentPrivate;
    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;

    if( pProxy->hBufPipe != NULL ) {
        eOSALStatus = TIMM_OSAL_DeletePipe(pProxy->hBufPipe);
        pProxy->hBufPipe = NULL;

        if( eOSALStatus != TIMM_OSAL_ERR_NONE ) {
            DOMX_ERROR("Pipe deletion failed");
        }
    }

    if( pProxy->bAndroidOpaqueFormat == OMX_TRUE ) {
        /* Cleanup internal buffers in pipe if not freed on FreeBuffer */
        for( i=0; i < OMX_VC1VE_NUM_INTERNAL_BUF; i++ ) {
            if( pProxy->gralloc_handle[i] ) {
                pProxy->mAllocDev->free(pProxy->mAllocDev, (buffer_handle_t)(pProxy->gralloc_handle[i]));
                pProxy->gralloc_handle[i] = NULL;
            }
        }

        COLORCONVERT_close(pProxy->hCC, pCompPrv);
        pProxy->bAndroidOpaqueFormat = OMX_FALSE;

        if( pCompPrv->pCompProxyPrv != NULL ) {
            TIMM_OSAL_Free(pCompPrv->pCompProxyPrv);
            pCompPrv->pCompProxyPrv = NULL;
        }
    }

    eError = PROXY_ComponentDeInit(hComponent);
EXIT:
    DOMX_EXIT("eError: %d", eError);
    return (eError);
}

/* ===========================================================================*/
/**
 * @name COLORCONVERT_open()
 * @brief This function opens the color conversion module.
 * @param void
 * @return OMX_ErrorNone = Successful
 * @sa TBD
 *
 */
/* ===========================================================================*/
int COLORCONVERT_open(void * *hCC, PROXY_COMPONENT_PRIVATE *pCompPrv)
{
    int                       nErr = -1;
    hw_module_t const        *module = NULL;
    OMX_PROXY_ENCODER_PRIVATE   *pProxy = NULL;

    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;
    nErr = hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &module);

    if( nErr == 0 ) {
        *hCC = (void *) ((IMG_gralloc_module_public_t const *)module);
    } else {
        DOMX_ERROR("FATAL: gralloc api hw_get_module() returned error: Can't find \
                %s module err = %x", GRALLOC_HARDWARE_MODULE_ID, nErr);
    }

    gralloc_open(module, &(pProxy->mAllocDev));

    return (nErr);
}

/* ===========================================================================*/
/**
 * @name COLORCONVERT_PlatformOpaqueToNV12()
 * @brief  This function is used to get NV12 data after color conversion
 * @param void
 * @return OMX_ErrorNone = Successful
 * @sa TBD
 *
 */
/* ===========================================================================*/
int COLORCONVERT_PlatformOpaqueToNV12(void *hCC,
                                      void *pSrc[COLORCONVERT_MAX_SUB_BUFFERS],
                                      void *pDst[COLORCONVERT_MAX_SUB_BUFFERS],
                                      int nWidth, int nHeight, __unused int nStride,
                                      int nSrcBufType, int nDstBufType)
{
    IMG_gralloc_module_public_t const   *module = hCC;
    int                                  nErr = -1;

    if((nSrcBufType == COLORCONVERT_BUFTYPE_GRALLOCOPAQUE) && (nDstBufType == COLORCONVERT_BUFTYPE_VIRTUAL)) {
        nErr = module->Blit(module, pSrc[0], pDst, HAL_PIXEL_FORMAT_TI_NV12);
    } else if((nSrcBufType == COLORCONVERT_BUFTYPE_GRALLOCOPAQUE) && (nDstBufType == COLORCONVERT_BUFTYPE_GRALLOCOPAQUE)) {
        nErr = module->Blit2(module, pSrc[0], pDst[0], nWidth, nHeight, 0, 0);
    }

    return (nErr);
}

/* ===========================================================================*/
/**
 * @name COLORCONVERT_open()
 * @brief This function closes the color conversion module.
 * @param void
 * @return OMX_ErrorNone = Successful
 * @sa TBD
 *
 */
/* ===========================================================================*/
int COLORCONVERT_close(__unused void *hCC, PROXY_COMPONENT_PRIVATE *pCompPrv)
{
    OMX_PROXY_ENCODER_PRIVATE   *pProxy = NULL;

    pProxy = (OMX_PROXY_ENCODER_PRIVATE *) pCompPrv->pCompProxyPrv;
    if( pProxy && pProxy->mAllocDev ) {
        gralloc_close(pProxy->mAllocDev);
    }
    return (0);
}

#endif
