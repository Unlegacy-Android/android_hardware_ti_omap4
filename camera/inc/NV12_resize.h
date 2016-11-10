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

#ifndef NV12_RESIZE_H_
#define NV12_RESIZE_H_

#include <sys/types.h>
#include "Common.h"

const uint8_t bWeights[8][8][4] = {
  {{64, 0, 0, 0}, {56, 0, 0, 8}, {48, 0, 0,16}, {40, 0, 0,24},
   {32, 0, 0,32}, {24, 0, 0,40}, {16, 0, 0,48}, { 8, 0, 0,56}},

  {{56, 8, 0, 0}, {49, 7, 1, 7}, {42, 6, 2,14}, {35, 5, 3,21},
   {28, 4, 4,28}, {21, 3, 5,35}, {14, 2, 6,42}, { 7, 1, 7,49}},

  {{48,16, 0, 0}, {42,14, 2, 6}, {36,12,4 ,12}, {30,10,6 ,18},
   {24, 8, 8,24}, {18, 6,10,30}, {12,4 ,12,36}, { 6, 2,14,42}},

  {{40,24,0 ,0 }, {35,21, 3, 5}, {30,18, 6,10}, {25,15, 9,15},
   {20,12,12,20}, {15, 9,15,25}, {10, 6,18,30}, { 5, 3,21,35}},

  {{32,32, 0,0 }, {28,28, 4, 4}, {24,24, 8, 8}, {20,20,12,12},
   {16,16,16,16}, {12,12,20,20}, { 8, 8,24,24}, { 4, 4,28,28}},

  {{24,40,0 ,0 }, {21,35, 5, 3}, {18,30,10, 6}, {15,25,15, 9},
   {12,20,20,12}, { 9,15,25,15}, { 6,10,30,18}, { 3, 5,35,21}},

  {{16,48, 0,0 }, {14,42, 6, 2}, {12,36,12, 4}, {10,30,18, 6},
   {8 ,24,24,8 }, { 6,18,30,10}, { 4,12,36,12}, { 2, 6,42,14}},

  {{ 8,56, 0,0 }, { 7,49, 7, 1}, { 6,42,14, 2}, { 5,35,21, 3},
   { 4,28,28,4 }, { 3,21,35, 5}, { 2,14,42, 6}, { 1,7 ,49, 7}}
};

/* This structure defines the format of an image */
typedef struct {
    int32_t  uWidth;
    int32_t  uHeight;
    int32_t  uStride;
    uint8_t* imgPtr;
    uint8_t* clrPtr;
    int32_t  uOffset;
} structConvImage;

typedef struct IC_crop_struct {
    uint32_t x;       /* x pos of rectangle */
    uint32_t y;       /* y pos of rectangle */
    uint32_t uWidth;  /* dx of rectangle    */
    uint32_t uHeight; /* dy of rectangle    */
} IC_rect_type;

/*==========================================================================
* Function Name  : VT_resizeFrame_Video_opt2_lp
*
* Description    : Resize a yuv frame.
*
* Input(s)       : input_img_ptr        -> Input Image Structure
*                : output_img_ptr       -> Output Image Structure
*                : cropout              -> crop structure
*
* Value Returned : bool                 -> FALSE on error TRUE on success
* NOTE:
*            Not tested for crop funtionallity.
*            faster version.
============================================================================*/
bool
VT_resizeFrame_Video_opt2_lp(
        structConvImage* i_img_ptr, /* Points to the input image            */
        structConvImage* o_img_ptr, /* Points to the output image           */
        IC_rect_type*  cropout      /* how much to resize to in final image */
        );

#endif //#define NV12_RESIZE_H_
