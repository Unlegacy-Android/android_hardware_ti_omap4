/*
 * Copyright (C) Texas Instruments - http://www.ti.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NV12_resize.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "NV12_resize"

#define STRIDE 4096

/*==========================================================================
* Function Name  : VT_resizeFrame_Video_opt2_lp
*
* Description    : Resize a yuv frame.
*
* Input(s)       : input_img_ptr        -> Input Image Structure
*                : output_img_ptr       -> Output Image Structure
*
* Value Returned : bool                 -> FALSE on error TRUE on success
* NOTE:
*            Not tested for crop funtionallity.
*            faster version.
============================================================================*/
bool
VT_resizeFrame_Video_opt2_lp(
        structConvImage* i_img_ptr,      /* Points to the input image            */
        structConvImage* o_img_ptr       /* Points to the output image           */
        ) {
    LOG_FUNCTION_NAME;

    uint16_t row,col;
    uint32_t resizeFactorX;
    uint32_t resizeFactorY;

    uint16_t x, y;

    uint8_t* ptr8;
    uint8_t *ptr8Cb, *ptr8Cr;

    uint16_t xf, yf;
    uint8_t* inImgPtrY;
    uint8_t* inImgPtrU;
    uint8_t* inImgPtrV;
    uint32_t codx, cody;
    uint16_t idx,idy, idxC;

    if ( i_img_ptr->uWidth == o_img_ptr->uWidth ) {
        if ( i_img_ptr->uHeight == o_img_ptr->uHeight ) {
            CAMHAL_LOGV("************************f(i_img_ptr->uHeight == o_img_ptr->uHeight) are same *********************\n");
            CAMHAL_LOGV("************************(i_img_ptr->width == %d" , i_img_ptr->uWidth );
            CAMHAL_LOGV("************************(i_img_ptr->uHeight == %d" , i_img_ptr->uHeight );
            CAMHAL_LOGV("************************(o_img_ptr->width == %d" ,o_img_ptr->uWidth );
            CAMHAL_LOGV("************************(o_img_ptr->uHeight == %d" , o_img_ptr->uHeight );
        }
    }

    if ( !i_img_ptr || !i_img_ptr->imgPtr || !o_img_ptr || !o_img_ptr->imgPtr ) {
        CAMHAL_LOGE("Image Point NULL");
        return false;
    }

    inImgPtrY = (uint8_t *) i_img_ptr->imgPtr + i_img_ptr->uOffset;
    inImgPtrU = (uint8_t *) i_img_ptr->clrPtr + i_img_ptr->uOffset / 2;
    inImgPtrV = (uint8_t*)inImgPtrU + 1;

    codx = o_img_ptr->uWidth;
    cody = o_img_ptr->uHeight;
    idx = i_img_ptr->uWidth;
    idy = i_img_ptr->uHeight;

    /* make sure valid input size */
    if ( idx < 1 || idy < 1 || i_img_ptr->uStride < 1 ) {
        CAMHAL_LOGE("idx or idy less then 1 idx = %d idy = %d stride = %d", idx, idy, i_img_ptr->uStride);
        return false;
    }

    resizeFactorX = ((idx - 1) << 9) / codx;
    resizeFactorY = ((idy - 1) << 9) / cody;

    ptr8 = (uint8_t*)o_img_ptr->imgPtr + 0*o_img_ptr->uWidth;

    ////////////////////////////for Y//////////////////////////
    for ( row = 0; row < cody; row++ ) {
        uint8_t *pu8Yrow1 = NULL;
        uint8_t *pu8Yrow2 = NULL;
        y  = (uint16_t) ((uint32_t) (row * resizeFactorY) >> 9);
        yf = (uint8_t)  ((uint32_t)((row * resizeFactorY) >> 6) & 0x7);
        pu8Yrow1 = inImgPtrY + (y) * i_img_ptr->uStride;
        pu8Yrow2 = pu8Yrow1 + i_img_ptr->uStride;

        for ( col = 0; col < codx; col++ ) {
            uint8_t in11, in12, in21, in22;
            uint8_t *pu8ptr1 = NULL;
            uint8_t *pu8ptr2 = NULL;
            uint8_t w;
            uint16_t accum_1;
            //uint32_t accum_W;

            x  = (uint16_t) ((uint32_t)  (col * resizeFactorX) >> 9);
            xf = (uint8_t)  ((uint32_t) ((col * resizeFactorX) >> 6) & 0x7);

            //accum_W = 0;
            accum_1 =  0;

            pu8ptr1 = pu8Yrow1 + (x);
            pu8ptr2 = pu8Yrow2 + (x);

            /* A pixel */
            //in = *(inImgPtrY + (y) * idx + (x));
            in11 = *(pu8ptr1);

            w = bWeights[xf][yf][0];
            accum_1 = (w * in11);
            //accum_W += (w);

            /* B pixel */
            //in = *(inImgPtrY + (y) * idx + (x + 1));
            in12 = *(pu8ptr1 + 1);
            w = bWeights[xf][yf][1];
            accum_1 += (w * in12);
            //accum_W += (w);

            /* C pixel */
            //in = *(inImgPtrY + (y + 1) * idx + (x));
            in21 = *(pu8ptr2);
            w = bWeights[xf][yf][3];
            accum_1 += (w * in21);
            //accum_W += (w);

            /* D pixel */
            //in = *(inImgPtrY + (y + 1) * idx + (x + 1));
            in22 = *(pu8ptr2 + 1);
            w = bWeights[xf][yf][2];
            accum_1 += (w * in22);
            //accum_W += (w);

            /* divide by sum of the weights */
            //accum_1 /= (accum_W);
            //accum_1 = (accum_1 / 64);
            accum_1 = (accum_1 >> 6);
            *ptr8 = (uint8_t)accum_1 ;

            ptr8++;
        }
        ptr8 = ptr8 + (o_img_ptr->uStride - codx);
    }
    ////////////////////////////for Y//////////////////////////

    ///////////////////////////////for Cb-Cr//////////////////////

    ptr8Cb = (uint8_t*)o_img_ptr->clrPtr + 0*o_img_ptr->uWidth;

    ptr8Cr = (uint8_t*)(ptr8Cb + 1);

    idxC = (idx >> 1);
    for ( row = 0; row < (cody >> 1); row++ ) {
        uint8_t *pu8Cbr1 = NULL;
        uint8_t *pu8Cbr2 = NULL;
        uint8_t *pu8Crr1 = NULL;
        uint8_t *pu8Crr2 = NULL;

        y  = (uint16_t) ((uint32_t) (row * resizeFactorY) >> 9);
        yf = (uint8_t)  ((uint32_t)((row * resizeFactorY) >> 6) & 0x7);

        pu8Cbr1 = inImgPtrU + (y) * i_img_ptr->uStride;
        pu8Cbr2 = pu8Cbr1 + i_img_ptr->uStride;
        pu8Crr1 = inImgPtrV + (y) * i_img_ptr->uStride;
        pu8Crr2 = pu8Crr1 + i_img_ptr->uStride;

        for ( col = 0; col < (codx >> 1); col++ ) {
            uint8_t in11, in12, in21, in22;
            uint8_t *pu8Cbc1 = NULL;
            uint8_t *pu8Cbc2 = NULL;
            uint8_t *pu8Crc1 = NULL;
            uint8_t *pu8Crc2 = NULL;

            uint8_t w;
            uint16_t accum_1Cb, accum_1Cr;
            //uint32_t accum_WCb, accum_WCr;

            x  = (uint16_t) ((uint32_t)  (col * resizeFactorX) >> 9);
            xf = (uint8_t)  ((uint32_t) ((col * resizeFactorX) >> 6) & 0x7);

            //accum_WCb = accum_WCr =  0;
            accum_1Cb = accum_1Cr =  0;

            pu8Cbc1 = pu8Cbr1 + (x * 2);
            pu8Cbc2 = pu8Cbr2 + (x * 2);
            pu8Crc1 = pu8Crr1 + (x * 2);
            pu8Crc2 = pu8Crr2 + (x * 2);

            /* A pixel */
            w = bWeights[xf][yf][0];

            in11 = *(pu8Cbc1);
            accum_1Cb = (w * in11);
            //accum_WCb += (w);

            in11 = *(pu8Crc1);
            accum_1Cr = (w * in11);
            //accum_WCr += (w);

            /* B pixel */
            w = bWeights[xf][yf][1];

            in12 = *(pu8Cbc1 + 2);
            accum_1Cb += (w * in12);
            //accum_WCb += (w);

            in12 = *(pu8Crc1 + 2);
            accum_1Cr += (w * in12);
            //accum_WCr += (w);

            /* C pixel */
            w = bWeights[xf][yf][3];

            in21 = *(pu8Cbc2);
            accum_1Cb += (w * in21);
            //accum_WCb += (w);

            in21 = *(pu8Crc2);
            accum_1Cr += (w * in21);
            //accum_WCr += (w);

            /* D pixel */
            w = bWeights[xf][yf][2];

            in22 = *(pu8Cbc2 + 2);
            accum_1Cb += (w * in22);
            //accum_WCb += (w);

            in22 = *(pu8Crc2 + 2);
            accum_1Cr += (w * in22);
            //accum_WCr += (w);

            /* divide by sum of the weights */
            //accum_1Cb /= (accum_WCb);
            accum_1Cb = (accum_1Cb >> 6);
            *ptr8Cb = (uint8_t)accum_1Cb ;

            accum_1Cr = (accum_1Cr >> 6);
            *ptr8Cr = (uint8_t)accum_1Cr ;

            ptr8Cb++;
            ptr8Cr++;

            ptr8Cb++;
            ptr8Cr++;
        }
        ptr8Cb = ptr8Cb + (o_img_ptr->uStride - codx);
        ptr8Cr = ptr8Cr + (o_img_ptr->uStride - codx);
    }
    ///////////////////For Cb- Cr////////////////////////////////////////

    CAMHAL_LOGV("success");
    return true;
}
