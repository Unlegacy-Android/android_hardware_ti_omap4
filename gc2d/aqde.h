/*
 * aqde.h
 *
 * Copyright (C) 2010-2011 Vivante Corporation.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*******************************************************************************
**                            ~~~~~~~~~~~~~~~~~~~~                            **
**                            Module DrawingEngine                            **
**                            ~~~~~~~~~~~~~~~~~~~~                            **
*******************************************************************************/

/* Register AQDESrcAddress **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source surface. */

#define AQDESrcAddressRegAddrs                                            0x0480
#define AQDE_SRC_ADDRESS_Address                                         0x01200
#define AQDE_SRC_ADDRESS_MSB                                                  15
#define AQDE_SRC_ADDRESS_LSB                                                   0
#define AQDE_SRC_ADDRESS_BLK                                                   0
#define AQDE_SRC_ADDRESS_Count                                                 1
#define AQDE_SRC_ADDRESS_FieldMask                                    0xFFFFFFFF
#define AQDE_SRC_ADDRESS_ReadMask                                     0xFFFFFFFC
#define AQDE_SRC_ADDRESS_WriteMask                                    0xFFFFFFFC
#define AQDE_SRC_ADDRESS_ResetValue                                   0x00000000

#define AQDE_SRC_ADDRESS_TYPE                                            31 : 31
#define AQDE_SRC_ADDRESS_TYPE_End                                             31
#define AQDE_SRC_ADDRESS_TYPE_Start                                           31
#define AQDE_SRC_ADDRESS_TYPE_Type                                           U01
#define   AQDE_SRC_ADDRESS_TYPE_SYSTEM                                       0x0
#define   AQDE_SRC_ADDRESS_TYPE_VIRTUAL_SYSTEM                               0x1

#define AQDE_SRC_ADDRESS_ADDRESS                                          30 : 0
#define AQDE_SRC_ADDRESS_ADDRESS_End                                          30
#define AQDE_SRC_ADDRESS_ADDRESS_Start                                         0
#define AQDE_SRC_ADDRESS_ADDRESS_Type                                        U31

/* Register AQDESrcStride **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source surface in bytes. To calculate the stride multiply    **
** the surface width in pixels (8-pixel aligned) by the number of bytes per   **
** pixel.                                                                     */

#define AQDESrcStrideRegAddrs                                             0x0481
#define AQDE_SRC_STRIDE_Address                                          0x01204
#define AQDE_SRC_STRIDE_MSB                                                   15
#define AQDE_SRC_STRIDE_LSB                                                    0
#define AQDE_SRC_STRIDE_BLK                                                    0
#define AQDE_SRC_STRIDE_Count                                                  1
#define AQDE_SRC_STRIDE_FieldMask                                     0x0003FFFF
#define AQDE_SRC_STRIDE_ReadMask                                      0x0003FFFC
#define AQDE_SRC_STRIDE_WriteMask                                     0x0003FFFC
#define AQDE_SRC_STRIDE_ResetValue                                    0x00000000

#define AQDE_SRC_STRIDE_STRIDE                                            17 : 0
#define AQDE_SRC_STRIDE_STRIDE_End                                            17
#define AQDE_SRC_STRIDE_STRIDE_Start                                           0
#define AQDE_SRC_STRIDE_STRIDE_Type                                          U18

/* Register AQDESrcRotationConfig **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 90 degree rotation configuration for the source surface. Width field       **
** specifies the width of the surface in pixels.                              */

#define AQDESrcRotationConfigRegAddrs                                     0x0482
#define AQDE_SRC_ROTATION_CONFIG_Address                                 0x01208
#define AQDE_SRC_ROTATION_CONFIG_MSB                                          15
#define AQDE_SRC_ROTATION_CONFIG_LSB                                           0
#define AQDE_SRC_ROTATION_CONFIG_BLK                                           0
#define AQDE_SRC_ROTATION_CONFIG_Count                                         1
#define AQDE_SRC_ROTATION_CONFIG_FieldMask                            0x0001FFFF
#define AQDE_SRC_ROTATION_CONFIG_ReadMask                             0x0001FFFF
#define AQDE_SRC_ROTATION_CONFIG_WriteMask                            0x0001FFFF
#define AQDE_SRC_ROTATION_CONFIG_ResetValue                           0x00000000

#define AQDE_SRC_ROTATION_CONFIG_WIDTH                                    15 : 0
#define AQDE_SRC_ROTATION_CONFIG_WIDTH_End                                    15
#define AQDE_SRC_ROTATION_CONFIG_WIDTH_Start                                   0
#define AQDE_SRC_ROTATION_CONFIG_WIDTH_Type                                  U16

#define AQDE_SRC_ROTATION_CONFIG_ROTATION                                16 : 16
#define AQDE_SRC_ROTATION_CONFIG_ROTATION_End                                 16
#define AQDE_SRC_ROTATION_CONFIG_ROTATION_Start                               16
#define AQDE_SRC_ROTATION_CONFIG_ROTATION_Type                               U01
#define   AQDE_SRC_ROTATION_CONFIG_ROTATION_NORMAL                           0x0
#define   AQDE_SRC_ROTATION_CONFIG_ROTATION_ROTATED                          0x1

/* Register AQDESrcConfig **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* Source surface configuration register. */

#define AQDESrcConfigRegAddrs                                             0x0483
#define AQDE_SRC_CONFIG_Address                                          0x0120C
#define AQDE_SRC_CONFIG_MSB                                                   15
#define AQDE_SRC_CONFIG_LSB                                                    0
#define AQDE_SRC_CONFIG_BLK                                                    0
#define AQDE_SRC_CONFIG_Count                                                  1
#define AQDE_SRC_CONFIG_FieldMask                                     0xFF31B1FF
#define AQDE_SRC_CONFIG_ReadMask                                      0xFF31B1FF
#define AQDE_SRC_CONFIG_WriteMask                                     0xFF31B1FF
#define AQDE_SRC_CONFIG_ResetValue                                    0x00000000

/* Control source endianess. */
#define AQDE_SRC_CONFIG_ENDIAN_CONTROL                                   31 : 30
#define AQDE_SRC_CONFIG_ENDIAN_CONTROL_End                                    31
#define AQDE_SRC_CONFIG_ENDIAN_CONTROL_Start                                  30
#define AQDE_SRC_CONFIG_ENDIAN_CONTROL_Type                                  U02
#define   AQDE_SRC_CONFIG_ENDIAN_CONTROL_NO_SWAP                             0x0
#define   AQDE_SRC_CONFIG_ENDIAN_CONTROL_SWAP_WORD                           0x1
#define   AQDE_SRC_CONFIG_ENDIAN_CONTROL_SWAP_DWORD                          0x2

/* Disable 420 L2 cache  NOTE: the field is valid for chips with 420 L2 cache **
** defined.                                                                   */
#define AQDE_SRC_CONFIG_DISABLE420_L2_CACHE                              29 : 29
#define AQDE_SRC_CONFIG_DISABLE420_L2_CACHE_End                               29
#define AQDE_SRC_CONFIG_DISABLE420_L2_CACHE_Start                             29
#define AQDE_SRC_CONFIG_DISABLE420_L2_CACHE_Type                             U01
#define   AQDE_SRC_CONFIG_DISABLE420_L2_CACHE_ENABLED                        0x0
#define   AQDE_SRC_CONFIG_DISABLE420_L2_CACHE_DISABLED                       0x1

/* Defines the pixel format of the source surface.  NOTE: the field is valid  **
** for chips with 2DPE20 feature defined.                                     */
#define AQDE_SRC_CONFIG_SOURCE_FORMAT                                    28 : 24
#define AQDE_SRC_CONFIG_SOURCE_FORMAT_End                                     28
#define AQDE_SRC_CONFIG_SOURCE_FORMAT_Start                                   24
#define AQDE_SRC_CONFIG_SOURCE_FORMAT_Type                                   U05
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_X4R4G4B4                            0x00
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_A4R4G4B4                            0x01
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_X1R5G5B5                            0x02
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_A1R5G5B5                            0x03
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_R5G6B5                              0x04
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_X8R8G8B8                            0x05
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8                            0x06
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_YUY2                                0x07
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_UYVY                                0x08
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_INDEX8                              0x09
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_MONOCHROME                          0x0A
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_YV12                                0x0F
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_A8                                  0x10
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_NV12                                0x11
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_NV16                                0x12
#define   AQDE_SRC_CONFIG_SOURCE_FORMAT_RG16                                0x13

/* Color channel swizzles.  NOTE: the field is valid for chips with 2DPE20    **
** feature defined.                                                           */
#define AQDE_SRC_CONFIG_SWIZZLE                                          21 : 20
#define AQDE_SRC_CONFIG_SWIZZLE_End                                           21
#define AQDE_SRC_CONFIG_SWIZZLE_Start                                         20
#define AQDE_SRC_CONFIG_SWIZZLE_Type                                         U02
#define   AQDE_SRC_CONFIG_SWIZZLE_ARGB                                       0x0
#define   AQDE_SRC_CONFIG_SWIZZLE_RGBA                                       0x1
#define   AQDE_SRC_CONFIG_SWIZZLE_ABGR                                       0x2
#define   AQDE_SRC_CONFIG_SWIZZLE_BGRA                                       0x3

/* For chips with 2DPE20 feature defined this field is obsolete. For older    **
** chips where 2DPE20 feature is not defined this field determines the format **
** of AQDESrcColorFg and AQDESrcColorBg registers. If set, the values must be **
** set in A8R8G8B8 format, otherwise the values must be preconverted to the   **
** destination format.                                                        */
#define AQDE_SRC_CONFIG_COLOR_CONVERT                                    16 : 16
#define AQDE_SRC_CONFIG_COLOR_CONVERT_End                                     16
#define AQDE_SRC_CONFIG_COLOR_CONVERT_Start                                   16
#define AQDE_SRC_CONFIG_COLOR_CONVERT_Type                                   U01
#define   AQDE_SRC_CONFIG_COLOR_CONVERT_OFF                                  0x0
#define   AQDE_SRC_CONFIG_COLOR_CONVERT_ON                                   0x1

/* Mono expansion: if 0, transparency color will be 0, otherwise transparency **
** color will be 1.                                                           */
#define AQDE_SRC_CONFIG_MONO_TRANSPARENCY                                15 : 15
#define AQDE_SRC_CONFIG_MONO_TRANSPARENCY_End                                 15
#define AQDE_SRC_CONFIG_MONO_TRANSPARENCY_Start                               15
#define AQDE_SRC_CONFIG_MONO_TRANSPARENCY_Type                               U01
#define   AQDE_SRC_CONFIG_MONO_TRANSPARENCY_BACKGROUND                       0x0
#define   AQDE_SRC_CONFIG_MONO_TRANSPARENCY_FOREGROUND                       0x1

/* Mono expansion or masked blit: stream packing in pixels. Determines how    **
** many horizontal pixels are there per each 32-bit chunk. For example, if    **
** set to Packed8, each 32-bit chunk is 8-pixel wide, which also means that   **
** it defines 4 vertical lines of pixels.                                     */
#define AQDE_SRC_CONFIG_PACK                                             13 : 12
#define AQDE_SRC_CONFIG_PACK_End                                              13
#define AQDE_SRC_CONFIG_PACK_Start                                            12
#define AQDE_SRC_CONFIG_PACK_Type                                            U02
#define   AQDE_SRC_CONFIG_PACK_PACKED8                                       0x0
#define   AQDE_SRC_CONFIG_PACK_PACKED16                                      0x1
#define   AQDE_SRC_CONFIG_PACK_PACKED32                                      0x2
#define   AQDE_SRC_CONFIG_PACK_UNPACKED                                      0x3

/* Source data location: set to STREAM for mono expansion blits or masked     **
** blits. For mono expansion blits the complete bitmap comes from the command **
** stream. For masked blits the source data comes from the memory and the     **
** mask from the command stream.                                              */
#define AQDE_SRC_CONFIG_LOCATION                                           8 : 8
#define AQDE_SRC_CONFIG_LOCATION_End                                           8
#define AQDE_SRC_CONFIG_LOCATION_Start                                         8
#define AQDE_SRC_CONFIG_LOCATION_Type                                        U01
#define   AQDE_SRC_CONFIG_LOCATION_MEMORY                                    0x0
#define   AQDE_SRC_CONFIG_LOCATION_STREAM                                    0x1

/* Source linear/tiled address computation control. Reserved field for future **
** expansion. NOTE: the field is valid for chips with 2DPE20 feature defined. */
#define AQDE_SRC_CONFIG_TILED                                              7 : 7
#define AQDE_SRC_CONFIG_TILED_End                                              7
#define AQDE_SRC_CONFIG_TILED_Start                                            7
#define AQDE_SRC_CONFIG_TILED_Type                                           U01
#define   AQDE_SRC_CONFIG_TILED_DISABLED                                     0x0
#define   AQDE_SRC_CONFIG_TILED_ENABLED                                      0x1

/* If set to ABSOLUTE, the source coordinates are treated as absolute         **
** coordinates inside the source surface. If set to RELATIVE, the source      **
** coordinates are treated as the offsets from the destination coordinates    **
** with the source size equal to the size of the destination.                 */
#define AQDE_SRC_CONFIG_SRC_RELATIVE                                       6 : 6
#define AQDE_SRC_CONFIG_SRC_RELATIVE_End                                       6
#define AQDE_SRC_CONFIG_SRC_RELATIVE_Start                                     6
#define AQDE_SRC_CONFIG_SRC_RELATIVE_Type                                    U01
#define   AQDE_SRC_CONFIG_SRC_RELATIVE_ABSOLUTE                              0x0
#define   AQDE_SRC_CONFIG_SRC_RELATIVE_RELATIVE                              0x1

/* Source transparency configuration. If set to OPAQUE, the transparency will **
** be decided by the pattern mask if pattern is being used. If set to         **
** TRANSPARENT, each source pixel will be compared against AQDESrcColorBg     **
** register for color blits or MONO_TRANSPARENCY field of this register for   **
** mono expansion blits to determine whether the pixel is transparent or not. **
** If set to MASKED_MASK, the transparency is determined based on the mask    **
** bits for masked blits. If set to MASKED_PATTERN, the transparency will be  **
** decided by the pattern mask; this setting is functionally identical to     **
** OPAQUE. Once the transarency is decided, the value (0 for opaque, 1 for    **
** transparent) it is used to select foreground or background ROP code.       **
** NOTE :  the field is obsolete for chips with 2DPE20 feature defined. For   **
** those chips use Transparency field of AQPEConfig register.                 */
#define AQDE_SRC_CONFIG_TRANSPARENCY                                       5 : 4
#define AQDE_SRC_CONFIG_TRANSPARENCY_End                                       5
#define AQDE_SRC_CONFIG_TRANSPARENCY_Start                                     4
#define AQDE_SRC_CONFIG_TRANSPARENCY_Type                                    U02
#define   AQDE_SRC_CONFIG_TRANSPARENCY_OPAQUE                                0x0
#define   AQDE_SRC_CONFIG_TRANSPARENCY_TRANSPARENT                           0x1
#define   AQDE_SRC_CONFIG_TRANSPARENCY_MASKED_MASK                           0x2
#define   AQDE_SRC_CONFIG_TRANSPARENCY_MASKED_PATTERN                        0x3

/* Defines the pixel format of the source surface.  NOTE :  the field is      **
** obsolete for chips with 2DPE20 feature defined. For those chips use        **
** SourceFormat field.                                                        */
#define AQDE_SRC_CONFIG_FORMAT                                             3 : 0
#define AQDE_SRC_CONFIG_FORMAT_End                                             3
#define AQDE_SRC_CONFIG_FORMAT_Start                                           0
#define AQDE_SRC_CONFIG_FORMAT_Type                                          U04
#define   AQDE_SRC_CONFIG_FORMAT_X4R4G4B4                                    0x0
#define   AQDE_SRC_CONFIG_FORMAT_A4R4G4B4                                    0x1
#define   AQDE_SRC_CONFIG_FORMAT_X1R5G5B5                                    0x2
#define   AQDE_SRC_CONFIG_FORMAT_A1R5G5B5                                    0x3
#define   AQDE_SRC_CONFIG_FORMAT_R5G6B5                                      0x4
#define   AQDE_SRC_CONFIG_FORMAT_X8R8G8B8                                    0x5
#define   AQDE_SRC_CONFIG_FORMAT_A8R8G8B8                                    0x6
#define   AQDE_SRC_CONFIG_FORMAT_YUY2                                        0x7
#define   AQDE_SRC_CONFIG_FORMAT_UYVY                                        0x8
#define   AQDE_SRC_CONFIG_FORMAT_INDEX8                                      0x9
#define   AQDE_SRC_CONFIG_FORMAT_MONOCHROME                                  0xA
#define   AQDE_SRC_CONFIG_FORMAT_YV12                                        0xF

/* Register AQDESrcOrigin **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* Absolute or relative (see SRC_RELATIVE field of AQDESrcConfig register) X  **
** and Y coordinates in pixels of the top left corner of the source rectangle **
** within the source surface.                                                 */

#define AQDESrcOriginRegAddrs                                             0x0484
#define AQDE_SRC_ORIGIN_Address                                          0x01210
#define AQDE_SRC_ORIGIN_MSB                                                   15
#define AQDE_SRC_ORIGIN_LSB                                                    0
#define AQDE_SRC_ORIGIN_BLK                                                    0
#define AQDE_SRC_ORIGIN_Count                                                  1
#define AQDE_SRC_ORIGIN_FieldMask                                     0xFFFFFFFF
#define AQDE_SRC_ORIGIN_ReadMask                                      0xFFFFFFFF
#define AQDE_SRC_ORIGIN_WriteMask                                     0xFFFFFFFF
#define AQDE_SRC_ORIGIN_ResetValue                                    0x00000000

#define AQDE_SRC_ORIGIN_Y                                                31 : 16
#define AQDE_SRC_ORIGIN_Y_End                                                 31
#define AQDE_SRC_ORIGIN_Y_Start                                               16
#define AQDE_SRC_ORIGIN_Y_Type                                               U16

#define AQDE_SRC_ORIGIN_X                                                 15 : 0
#define AQDE_SRC_ORIGIN_X_End                                                 15
#define AQDE_SRC_ORIGIN_X_Start                                                0
#define AQDE_SRC_ORIGIN_X_Type                                               U16

/* Register AQDESrcSize **
** ~~~~~~~~~~~~~~~~~~~~ */

/* Width and height of the source rectangle in pixels. If the source is       **
** relative (see SRC_RELATIVE field of AQDESrcConfig register) or a regular   **
** bitblt is being performed without stretching, this register is ignored and **
** the source size is assumed to be the same as the destination.              */

#define AQDESrcSizeRegAddrs                                               0x0485
#define AQDE_SRC_SIZE_Address                                            0x01214
#define AQDE_SRC_SIZE_MSB                                                     15
#define AQDE_SRC_SIZE_LSB                                                      0
#define AQDE_SRC_SIZE_BLK                                                      0
#define AQDE_SRC_SIZE_Count                                                    1
#define AQDE_SRC_SIZE_FieldMask                                       0xFFFFFFFF
#define AQDE_SRC_SIZE_ReadMask                                        0xFFFFFFFF
#define AQDE_SRC_SIZE_WriteMask                                       0xFFFFFFFF
#define AQDE_SRC_SIZE_ResetValue                                      0x00000000

#define AQDE_SRC_SIZE_Y                                                  31 : 16
#define AQDE_SRC_SIZE_Y_End                                                   31
#define AQDE_SRC_SIZE_Y_Start                                                 16
#define AQDE_SRC_SIZE_Y_Type                                                 U16

#define AQDE_SRC_SIZE_X                                                   15 : 0
#define AQDE_SRC_SIZE_X_End                                                   15
#define AQDE_SRC_SIZE_X_Start                                                  0
#define AQDE_SRC_SIZE_X_Type                                                 U16

/* Register AQDESrcColorBg **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* In mono expansion defines the source color if the mono pixel is 0. For     **
** chips with 2DPE20 feature defined the color must be set in A8R8G8B8        **
** format, otherwise the format depends on the setting of ColorConvert field  **
** of AQDESrcConfig register.  In color blits defines the source transparency **
** color and must be of the same format as the source surface.                */

#define AQDESrcColorBgRegAddrs                                            0x0486
#define AQDE_SRC_COLOR_BG_Address                                        0x01218
#define AQDE_SRC_COLOR_BG_MSB                                                 15
#define AQDE_SRC_COLOR_BG_LSB                                                  0
#define AQDE_SRC_COLOR_BG_BLK                                                  0
#define AQDE_SRC_COLOR_BG_Count                                                1
#define AQDE_SRC_COLOR_BG_FieldMask                                   0xFFFFFFFF
#define AQDE_SRC_COLOR_BG_ReadMask                                    0xFFFFFFFF
#define AQDE_SRC_COLOR_BG_WriteMask                                   0xFFFFFFFF
#define AQDE_SRC_COLOR_BG_ResetValue                                  0x00000000

#define AQDE_SRC_COLOR_BG_ALPHA                                          31 : 24
#define AQDE_SRC_COLOR_BG_ALPHA_End                                           31
#define AQDE_SRC_COLOR_BG_ALPHA_Start                                         24
#define AQDE_SRC_COLOR_BG_ALPHA_Type                                         U08

#define AQDE_SRC_COLOR_BG_RED                                            23 : 16
#define AQDE_SRC_COLOR_BG_RED_End                                             23
#define AQDE_SRC_COLOR_BG_RED_Start                                           16
#define AQDE_SRC_COLOR_BG_RED_Type                                           U08

#define AQDE_SRC_COLOR_BG_GREEN                                           15 : 8
#define AQDE_SRC_COLOR_BG_GREEN_End                                           15
#define AQDE_SRC_COLOR_BG_GREEN_Start                                          8
#define AQDE_SRC_COLOR_BG_GREEN_Type                                         U08

#define AQDE_SRC_COLOR_BG_BLUE                                             7 : 0
#define AQDE_SRC_COLOR_BG_BLUE_End                                             7
#define AQDE_SRC_COLOR_BG_BLUE_Start                                           0
#define AQDE_SRC_COLOR_BG_BLUE_Type                                          U08

/* Register AQDESrcColorFg **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* In mono expansion defines the source color if the mono pixel is 1. For     **
** chips with 2DPE20 feature defined the color must be set in A8R8G8B8        **
** format, otherwise the format depends on the setting of ColorConvert field  **
** of AQDESrcConfig register.                                                 */

#define AQDESrcColorFgRegAddrs                                            0x0487
#define AQDE_SRC_COLOR_FG_Address                                        0x0121C
#define AQDE_SRC_COLOR_FG_MSB                                                 15
#define AQDE_SRC_COLOR_FG_LSB                                                  0
#define AQDE_SRC_COLOR_FG_BLK                                                  0
#define AQDE_SRC_COLOR_FG_Count                                                1
#define AQDE_SRC_COLOR_FG_FieldMask                                   0xFFFFFFFF
#define AQDE_SRC_COLOR_FG_ReadMask                                    0xFFFFFFFF
#define AQDE_SRC_COLOR_FG_WriteMask                                   0xFFFFFFFF
#define AQDE_SRC_COLOR_FG_ResetValue                                  0x00000000

#define AQDE_SRC_COLOR_FG_ALPHA                                          31 : 24
#define AQDE_SRC_COLOR_FG_ALPHA_End                                           31
#define AQDE_SRC_COLOR_FG_ALPHA_Start                                         24
#define AQDE_SRC_COLOR_FG_ALPHA_Type                                         U08

#define AQDE_SRC_COLOR_FG_RED                                            23 : 16
#define AQDE_SRC_COLOR_FG_RED_End                                             23
#define AQDE_SRC_COLOR_FG_RED_Start                                           16
#define AQDE_SRC_COLOR_FG_RED_Type                                           U08

#define AQDE_SRC_COLOR_FG_GREEN                                           15 : 8
#define AQDE_SRC_COLOR_FG_GREEN_End                                           15
#define AQDE_SRC_COLOR_FG_GREEN_Start                                          8
#define AQDE_SRC_COLOR_FG_GREEN_Type                                         U08

#define AQDE_SRC_COLOR_FG_BLUE                                             7 : 0
#define AQDE_SRC_COLOR_FG_BLUE_End                                             7
#define AQDE_SRC_COLOR_FG_BLUE_Start                                           0
#define AQDE_SRC_COLOR_FG_BLUE_Type                                          U08

/* Register AQDEStretchFactorLow **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEStretchFactorLowRegAddrs                                      0x0488
#define AQDE_STRETCH_FACTOR_LOW_Address                                  0x01220
#define AQDE_STRETCH_FACTOR_LOW_MSB                                           15
#define AQDE_STRETCH_FACTOR_LOW_LSB                                            0
#define AQDE_STRETCH_FACTOR_LOW_BLK                                            0
#define AQDE_STRETCH_FACTOR_LOW_Count                                          1
#define AQDE_STRETCH_FACTOR_LOW_FieldMask                             0x7FFFFFFF
#define AQDE_STRETCH_FACTOR_LOW_ReadMask                              0x7FFFFFFF
#define AQDE_STRETCH_FACTOR_LOW_WriteMask                             0x7FFFFFFF
#define AQDE_STRETCH_FACTOR_LOW_ResetValue                            0x00000000

/* Horizontal stretch factor in 15.16 fixed point format. The value is        **
** calculated using the following formula: factor = ((srcWidth - 1) << 16) /  **
** (dstWidth - 1). Stretch blit uses only the integer part of the value,      **
** while Filter blit uses all 31 bits.                                        */
#define AQDE_STRETCH_FACTOR_LOW_X                                         30 : 0
#define AQDE_STRETCH_FACTOR_LOW_X_End                                         30
#define AQDE_STRETCH_FACTOR_LOW_X_Start                                        0
#define AQDE_STRETCH_FACTOR_LOW_X_Type                                       U31

/* Register AQDEStretchFactorHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEStretchFactorHighRegAddrs                                     0x0489
#define AQDE_STRETCH_FACTOR_HIGH_Address                                 0x01224
#define AQDE_STRETCH_FACTOR_HIGH_MSB                                          15
#define AQDE_STRETCH_FACTOR_HIGH_LSB                                           0
#define AQDE_STRETCH_FACTOR_LOW_HIGH_BLK                                       0
#define AQDE_STRETCH_FACTOR_HIGH_Count                                         1
#define AQDE_STRETCH_FACTOR_HIGH_FieldMask                            0x7FFFFFFF
#define AQDE_STRETCH_FACTOR_HIGH_ReadMask                             0x7FFFFFFF
#define AQDE_STRETCH_FACTOR_HIGH_WriteMask                            0x7FFFFFFF
#define AQDE_STRETCH_FACTOR_HIGH_ResetValue                           0x00000000

/* Vertical stretch factor in 15.16 fixed point format. The value is          **
** calculated using the following formula: factor = ((srcHeight - 1) << 16) / **
** (dstHeight - 1). Stretch blit uses only the integer part of the value,     **
** while Filter blit uses all 31 bits.                                        */
#define AQDE_STRETCH_FACTOR_HIGH_Y                                        30 : 0
#define AQDE_STRETCH_FACTOR_HIGH_Y_End                                        30
#define AQDE_STRETCH_FACTOR_HIGH_Y_Start                                       0
#define AQDE_STRETCH_FACTOR_HIGH_Y_Type                                      U31

/* Register AQDEDestAddress **
** ~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the destination surface. */

#define AQDEDestAddressRegAddrs                                           0x048A
#define AQDE_DEST_ADDRESS_Address                                        0x01228
#define AQDE_DEST_ADDRESS_MSB                                                 15
#define AQDE_DEST_ADDRESS_LSB                                                  0
#define AQDE_DEST_ADDRESS_BLK                                                  0
#define AQDE_DEST_ADDRESS_Count                                                1
#define AQDE_DEST_ADDRESS_FieldMask                                   0xFFFFFFFF
#define AQDE_DEST_ADDRESS_ReadMask                                    0xFFFFFFFC
#define AQDE_DEST_ADDRESS_WriteMask                                   0xFFFFFFFC
#define AQDE_DEST_ADDRESS_ResetValue                                  0x00000000

#define AQDE_DEST_ADDRESS_TYPE                                           31 : 31
#define AQDE_DEST_ADDRESS_TYPE_End                                            31
#define AQDE_DEST_ADDRESS_TYPE_Start                                          31
#define AQDE_DEST_ADDRESS_TYPE_Type                                          U01
#define   AQDE_DEST_ADDRESS_TYPE_SYSTEM                                      0x0
#define   AQDE_DEST_ADDRESS_TYPE_VIRTUAL_SYSTEM                              0x1

#define AQDE_DEST_ADDRESS_ADDRESS                                         30 : 0
#define AQDE_DEST_ADDRESS_ADDRESS_End                                         30
#define AQDE_DEST_ADDRESS_ADDRESS_Start                                        0
#define AQDE_DEST_ADDRESS_ADDRESS_Type                                       U31

/* Register AQDEDestStride **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the destination surface in bytes. To calculate the stride        **
** multiply the surface width in pixels (8-pixel aligned) by the number of    **
** bytes per pixel.                                                           */

#define AQDEDestStrideRegAddrs                                            0x048B
#define AQDE_DEST_STRIDE_Address                                         0x0122C
#define AQDE_DEST_STRIDE_MSB                                                  15
#define AQDE_DEST_STRIDE_LSB                                                   0
#define AQDE_DEST_STRIDE_BLK                                                   0
#define AQDE_DEST_STRIDE_Count                                                 1
#define AQDE_DEST_STRIDE_FieldMask                                    0x0003FFFF
#define AQDE_DEST_STRIDE_ReadMask                                     0x0003FFFC
#define AQDE_DEST_STRIDE_WriteMask                                    0x0003FFFC
#define AQDE_DEST_STRIDE_ResetValue                                   0x00000000

#define AQDE_DEST_STRIDE_STRIDE                                           17 : 0
#define AQDE_DEST_STRIDE_STRIDE_End                                           17
#define AQDE_DEST_STRIDE_STRIDE_Start                                          0
#define AQDE_DEST_STRIDE_STRIDE_Type                                         U18

/* Register AQDEDestRotationConfig **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 90 degree rotation configuration for the destination surface. Width field  **
** specifies the width of the surface in pixels.                              */

#define AQDEDestRotationConfigRegAddrs                                    0x048C
#define AQDE_DEST_ROTATION_CONFIG_Address                                0x01230
#define AQDE_DEST_ROTATION_CONFIG_MSB                                         15
#define AQDE_DEST_ROTATION_CONFIG_LSB                                          0
#define AQDE_DEST_ROTATION_CONFIG_BLK                                          0
#define AQDE_DEST_ROTATION_CONFIG_Count                                        1
#define AQDE_DEST_ROTATION_CONFIG_FieldMask                           0x0001FFFF
#define AQDE_DEST_ROTATION_CONFIG_ReadMask                            0x0001FFFF
#define AQDE_DEST_ROTATION_CONFIG_WriteMask                           0x0001FFFF
#define AQDE_DEST_ROTATION_CONFIG_ResetValue                          0x00000000

#define AQDE_DEST_ROTATION_CONFIG_WIDTH                                   15 : 0
#define AQDE_DEST_ROTATION_CONFIG_WIDTH_End                                   15
#define AQDE_DEST_ROTATION_CONFIG_WIDTH_Start                                  0
#define AQDE_DEST_ROTATION_CONFIG_WIDTH_Type                                 U16

#define AQDE_DEST_ROTATION_CONFIG_ROTATION                               16 : 16
#define AQDE_DEST_ROTATION_CONFIG_ROTATION_End                                16
#define AQDE_DEST_ROTATION_CONFIG_ROTATION_Start                              16
#define AQDE_DEST_ROTATION_CONFIG_ROTATION_Type                              U01
#define   AQDE_DEST_ROTATION_CONFIG_ROTATION_NORMAL                          0x0
#define   AQDE_DEST_ROTATION_CONFIG_ROTATION_ROTATED                         0x1

/* Register AQDEDestConfig **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* Destination surface configuration register. */

#define AQDEDestConfigRegAddrs                                            0x048D
#define AQDE_DEST_CONFIG_Address                                         0x01234
#define AQDE_DEST_CONFIG_MSB                                                  15
#define AQDE_DEST_CONFIG_LSB                                                   0
#define AQDE_DEST_CONFIG_BLK                                                   0
#define AQDE_DEST_CONFIG_Count                                                 1
#define AQDE_DEST_CONFIG_FieldMask                                    0x0733F11F
#define AQDE_DEST_CONFIG_ReadMask                                     0x0733F11F
#define AQDE_DEST_CONFIG_WriteMask                                    0x0733F11F
#define AQDE_DEST_CONFIG_ResetValue                                   0x00000000

/* MinorTile. */
#define AQDE_DEST_CONFIG_MINOR_TILED                                     26 : 26
#define AQDE_DEST_CONFIG_MINOR_TILED_End                                      26
#define AQDE_DEST_CONFIG_MINOR_TILED_Start                                    26
#define AQDE_DEST_CONFIG_MINOR_TILED_Type                                    U01
#define   AQDE_DEST_CONFIG_MINOR_TILED_DISABLED                              0x0
#define   AQDE_DEST_CONFIG_MINOR_TILED_ENABLED                               0x1

/* Performance fix for de. */
#define AQDE_DEST_CONFIG_INTER_TILE_PER_FIX                              25 : 25
#define AQDE_DEST_CONFIG_INTER_TILE_PER_FIX_End                               25
#define AQDE_DEST_CONFIG_INTER_TILE_PER_FIX_Start                             25
#define AQDE_DEST_CONFIG_INTER_TILE_PER_FIX_Type                             U01
#define   AQDE_DEST_CONFIG_INTER_TILE_PER_FIX_DISABLED                       0x1
#define   AQDE_DEST_CONFIG_INTER_TILE_PER_FIX_ENABLED                        0x0

/* Control GDI Strecth Blit. */
#define AQDE_DEST_CONFIG_GDI_STRE                                        24 : 24
#define AQDE_DEST_CONFIG_GDI_STRE_End                                         24
#define AQDE_DEST_CONFIG_GDI_STRE_Start                                       24
#define AQDE_DEST_CONFIG_GDI_STRE_Type                                       U01
#define   AQDE_DEST_CONFIG_GDI_STRE_DISABLED                                 0x0
#define   AQDE_DEST_CONFIG_GDI_STRE_ENABLED                                  0x1

/* Control destination endianess. */
#define AQDE_DEST_CONFIG_ENDIAN_CONTROL                                  21 : 20
#define AQDE_DEST_CONFIG_ENDIAN_CONTROL_End                                   21
#define AQDE_DEST_CONFIG_ENDIAN_CONTROL_Start                                 20
#define AQDE_DEST_CONFIG_ENDIAN_CONTROL_Type                                 U02
#define   AQDE_DEST_CONFIG_ENDIAN_CONTROL_NO_SWAP                            0x0
#define   AQDE_DEST_CONFIG_ENDIAN_CONTROL_SWAP_WORD                          0x1
#define   AQDE_DEST_CONFIG_ENDIAN_CONTROL_SWAP_DWORD                         0x2

/* Color channel swizzles.  NOTE: the field is valid for chips with 2DPE20    **
** feature defined.                                                           */
#define AQDE_DEST_CONFIG_SWIZZLE                                         17 : 16
#define AQDE_DEST_CONFIG_SWIZZLE_End                                          17
#define AQDE_DEST_CONFIG_SWIZZLE_Start                                        16
#define AQDE_DEST_CONFIG_SWIZZLE_Type                                        U02
#define   AQDE_DEST_CONFIG_SWIZZLE_ARGB                                      0x0
#define   AQDE_DEST_CONFIG_SWIZZLE_RGBA                                      0x1
#define   AQDE_DEST_CONFIG_SWIZZLE_ABGR                                      0x2
#define   AQDE_DEST_CONFIG_SWIZZLE_BGRA                                      0x3

/* Determines the type of primitive to be rendered. BIT_BLT_REVERSED and      **
** INVALID_COMMAND values are defined for internal use and should not be      **
** used.                                                                      */
#define AQDE_DEST_CONFIG_COMMAND                                         15 : 12
#define AQDE_DEST_CONFIG_COMMAND_End                                          15
#define AQDE_DEST_CONFIG_COMMAND_Start                                        12
#define AQDE_DEST_CONFIG_COMMAND_Type                                        U04
#define   AQDE_DEST_CONFIG_COMMAND_CLEAR                                     0x0
#define   AQDE_DEST_CONFIG_COMMAND_LINE                                      0x1
#define   AQDE_DEST_CONFIG_COMMAND_BIT_BLT                                   0x2
#define   AQDE_DEST_CONFIG_COMMAND_BIT_BLT_REVERSED                          0x3
#define   AQDE_DEST_CONFIG_COMMAND_STRETCH_BLT                               0x4
#define   AQDE_DEST_CONFIG_COMMAND_HOR_FILTER_BLT                            0x5
#define   AQDE_DEST_CONFIG_COMMAND_VER_FILTER_BLT                            0x6
#define   AQDE_DEST_CONFIG_COMMAND_ONE_PASS_FILTER_BLT                       0x7
#define   AQDE_DEST_CONFIG_COMMAND_MULTI_SOURCE_BLT                          0x8

/* Destination linear/tiled address computation control. Reserved field for   **
** future expansion. NOTE: the field is valid for chips with 2DPE20 feature   **
** defined.                                                                   */
#define AQDE_DEST_CONFIG_TILED                                             8 : 8
#define AQDE_DEST_CONFIG_TILED_End                                             8
#define AQDE_DEST_CONFIG_TILED_Start                                           8
#define AQDE_DEST_CONFIG_TILED_Type                                          U01
#define   AQDE_DEST_CONFIG_TILED_DISABLED                                    0x0
#define   AQDE_DEST_CONFIG_TILED_ENABLED                                     0x1

/* Defines the pixel format of the destination surface. */
#define AQDE_DEST_CONFIG_FORMAT                                            4 : 0
#define AQDE_DEST_CONFIG_FORMAT_End                                            4
#define AQDE_DEST_CONFIG_FORMAT_Start                                          0
#define AQDE_DEST_CONFIG_FORMAT_Type                                         U05
#define   AQDE_DEST_CONFIG_FORMAT_X4R4G4B4                                  0x00
#define   AQDE_DEST_CONFIG_FORMAT_A4R4G4B4                                  0x01
#define   AQDE_DEST_CONFIG_FORMAT_X1R5G5B5                                  0x02
#define   AQDE_DEST_CONFIG_FORMAT_A1R5G5B5                                  0x03
#define   AQDE_DEST_CONFIG_FORMAT_R5G6B5                                    0x04
#define   AQDE_DEST_CONFIG_FORMAT_X8R8G8B8                                  0x05
#define   AQDE_DEST_CONFIG_FORMAT_A8R8G8B8                                  0x06
#define   AQDE_DEST_CONFIG_FORMAT_YUY2                                      0x07
#define   AQDE_DEST_CONFIG_FORMAT_UYVY                                      0x08
#define   AQDE_DEST_CONFIG_FORMAT_INDEX8                                    0x09
#define   AQDE_DEST_CONFIG_FORMAT_MONOCHROME                                0x0A
#define   AQDE_DEST_CONFIG_FORMAT_YV12                                      0x0F
#define   AQDE_DEST_CONFIG_FORMAT_A8                                        0x10
#define   AQDE_DEST_CONFIG_FORMAT_NV12                                      0x11
#define   AQDE_DEST_CONFIG_FORMAT_NV16                                      0x12
#define   AQDE_DEST_CONFIG_FORMAT_RG16                                      0x13

/* Register AQDEPatternAddress **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of 8x8 pattern for SOLID_COLOR patterns (see   **
** TYPE field in AQDEPatternConfig register).                                 */

#define AQDEPatternAddressRegAddrs                                        0x048E
#define AQDE_PATTERN_ADDRESS_Address                                     0x01238
#define AQDE_PATTERN_ADDRESS_MSB                                              15
#define AQDE_PATTERN_ADDRESS_LSB                                               0
#define AQDE_PATTERN_ADDRESS_BLK                                               0
#define AQDE_PATTERN_ADDRESS_Count                                             1
#define AQDE_PATTERN_ADDRESS_FieldMask                                0xFFFFFFFF
#define AQDE_PATTERN_ADDRESS_ReadMask                                 0xFFFFFFFC
#define AQDE_PATTERN_ADDRESS_WriteMask                                0xFFFFFFFC
#define AQDE_PATTERN_ADDRESS_ResetValue                               0x00000000

#define AQDE_PATTERN_ADDRESS_TYPE                                        31 : 31
#define AQDE_PATTERN_ADDRESS_TYPE_End                                         31
#define AQDE_PATTERN_ADDRESS_TYPE_Start                                       31
#define AQDE_PATTERN_ADDRESS_TYPE_Type                                       U01
#define   AQDE_PATTERN_ADDRESS_TYPE_SYSTEM                                   0x0
#define   AQDE_PATTERN_ADDRESS_TYPE_VIRTUAL_SYSTEM                           0x1

#define AQDE_PATTERN_ADDRESS_ADDRESS                                      30 : 0
#define AQDE_PATTERN_ADDRESS_ADDRESS_End                                      30
#define AQDE_PATTERN_ADDRESS_ADDRESS_Start                                     0
#define AQDE_PATTERN_ADDRESS_ADDRESS_Type                                    U31

/* Register AQDEPatternConfig **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Pattern configuration register. */

#define AQDEPatternConfigRegAddrs                                         0x048F
#define AQDE_PATTERN_CONFIG_Address                                      0x0123C
#define AQDE_PATTERN_CONFIG_MSB                                               15
#define AQDE_PATTERN_CONFIG_LSB                                                0
#define AQDE_PATTERN_CONFIG_BLK                                                0
#define AQDE_PATTERN_CONFIG_Count                                              1
#define AQDE_PATTERN_CONFIG_FieldMask                                 0xDF7703FF
#define AQDE_PATTERN_CONFIG_ReadMask                                  0xDF7703FF
#define AQDE_PATTERN_CONFIG_WriteMask                                 0xDF7703FF
#define AQDE_PATTERN_CONFIG_ResetValue                                0x00000000

/* Control pattern endianess. */
#define AQDE_PATTERN_CONFIG_ENDIAN_CONTROL                               31 : 30
#define AQDE_PATTERN_CONFIG_ENDIAN_CONTROL_End                                31
#define AQDE_PATTERN_CONFIG_ENDIAN_CONTROL_Start                              30
#define AQDE_PATTERN_CONFIG_ENDIAN_CONTROL_Type                              U02
#define   AQDE_PATTERN_CONFIG_ENDIAN_CONTROL_NO_SWAP                         0x0
#define   AQDE_PATTERN_CONFIG_ENDIAN_CONTROL_SWAP_WORD                       0x1
#define   AQDE_PATTERN_CONFIG_ENDIAN_CONTROL_SWAP_DWORD                      0x2

/* Defines the pixel format of the pattern and is used for PATTERN patterns   **
** (see TYPE field of this register).  NOTE: the field is valid for chips     **
** with 2DPE20 feature defined.                                               */
#define AQDE_PATTERN_CONFIG_PATTERN_FORMAT                               28 : 24
#define AQDE_PATTERN_CONFIG_PATTERN_FORMAT_End                                28
#define AQDE_PATTERN_CONFIG_PATTERN_FORMAT_Start                              24
#define AQDE_PATTERN_CONFIG_PATTERN_FORMAT_Type                              U05
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_X4R4G4B4                       0x00
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_A4R4G4B4                       0x01
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_X1R5G5B5                       0x02
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_A1R5G5B5                       0x03
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_R5G6B5                         0x04
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_X8R8G8B8                       0x05
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_A8R8G8B8                       0x06
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_YUY2                           0x07
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_UYVY                           0x08
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_INDEX8                         0x09
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_MONOCHROME                     0x0A
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_YV12                           0x0F
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_A8                             0x10
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_NV12                           0x11
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_NV16                           0x12
#define   AQDE_PATTERN_CONFIG_PATTERN_FORMAT_RG16                           0x13

/* Defines the vertical coordinate in pixels of the top left corner of 8x8    **
** pattern within 8x8 block.                                                  */
#define AQDE_PATTERN_CONFIG_ORIGIN_Y                                     22 : 20
#define AQDE_PATTERN_CONFIG_ORIGIN_Y_End                                      22
#define AQDE_PATTERN_CONFIG_ORIGIN_Y_Start                                    20
#define AQDE_PATTERN_CONFIG_ORIGIN_Y_Type                                    U03

/* Defines the horizontal coordinate in pixels of the top left corner of 8x8  **
** pattern within 8x8 block.                                                  */
#define AQDE_PATTERN_CONFIG_ORIGIN_X                                     18 : 16
#define AQDE_PATTERN_CONFIG_ORIGIN_X_End                                      18
#define AQDE_PATTERN_CONFIG_ORIGIN_X_Start                                    16
#define AQDE_PATTERN_CONFIG_ORIGIN_X_Type                                    U03

/* Color channel swizzles.  NOTE: the field is valid for chips with 2DPE20    **
** feature defined.                                                           */
#define AQDE_PATTERN_CONFIG_SWIZZLE                                        9 : 8
#define AQDE_PATTERN_CONFIG_SWIZZLE_End                                        9
#define AQDE_PATTERN_CONFIG_SWIZZLE_Start                                      8
#define AQDE_PATTERN_CONFIG_SWIZZLE_Type                                     U02
#define   AQDE_PATTERN_CONFIG_SWIZZLE_ARGB                                   0x0
#define   AQDE_PATTERN_CONFIG_SWIZZLE_RGBA                                   0x1
#define   AQDE_PATTERN_CONFIG_SWIZZLE_ABGR                                   0x2
#define   AQDE_PATTERN_CONFIG_SWIZZLE_BGRA                                   0x3

/* Defines what should be initialized. If DEFAULT or INIT_CONFIG are set,     **
** only pattern configuration will be modified. If INIT_PATTERN is set, the   **
** pattern cache will be reloaded using the current configuration. If         **
** INIT_ALL is set, first the configuration will be updated, then the pattern **
** cache will be reloaded based on the updated configuration.                 */
#define AQDE_PATTERN_CONFIG_INIT_TRIGGER                                   7 : 6
#define AQDE_PATTERN_CONFIG_INIT_TRIGGER_End                                   7
#define AQDE_PATTERN_CONFIG_INIT_TRIGGER_Start                                 6
#define AQDE_PATTERN_CONFIG_INIT_TRIGGER_Type                                U02
#define   AQDE_PATTERN_CONFIG_INIT_TRIGGER_DEFAULT                           0x0
#define   AQDE_PATTERN_CONFIG_INIT_TRIGGER_INIT_CONFIG                       0x1
#define   AQDE_PATTERN_CONFIG_INIT_TRIGGER_INIT_PATTERN                      0x2
#define   AQDE_PATTERN_CONFIG_INIT_TRIGGER_INIT_ALL                          0x3

/* For chips with 2DPE20 feature defined this field is obsolete. For older    **
** chips where 2DPE20 feature is not defined this field determines the format **
** of AQDEPatternFgColor and AQDEPatternBgColor registers. If set, the values **
** must be set in A8R8G8B8 format, otherwise the values must be preconverted  **
** to the final format.                                                       */
#define AQDE_PATTERN_CONFIG_COLOR_CONVERT                                  5 : 5
#define AQDE_PATTERN_CONFIG_COLOR_CONVERT_End                                  5
#define AQDE_PATTERN_CONFIG_COLOR_CONVERT_Start                                5
#define AQDE_PATTERN_CONFIG_COLOR_CONVERT_Type                               U01
#define   AQDE_PATTERN_CONFIG_COLOR_CONVERT_OFF                              0x0
#define   AQDE_PATTERN_CONFIG_COLOR_CONVERT_ON                               0x1

/* If set to SOLID_COLOR, the pattern color is defined by the                 **
** AQDEPatternFgColor register, the value of which could used straight or     **
** converted to destination format (see COLOR_CONVERT field of this           **
** register). If set to PATTERN and the pattern format is monochrome, the     **
** pattern colors are determined by the AQDEPatternFgColor and                **
** AQDEPatternBgColor register pair based on the pattern values from          **
** AQDEPatternLow and AQDEPatternHigh registers. If set to PATTERN and the    **
** pattern format is not monochrome, the pattern is loaded from memory        **
** starting from the address specified in AQDEPatternAddress register.        */
#define AQDE_PATTERN_CONFIG_TYPE                                           4 : 4
#define AQDE_PATTERN_CONFIG_TYPE_End                                           4
#define AQDE_PATTERN_CONFIG_TYPE_Start                                         4
#define AQDE_PATTERN_CONFIG_TYPE_Type                                        U01
#define   AQDE_PATTERN_CONFIG_TYPE_SOLID_COLOR                               0x0
#define   AQDE_PATTERN_CONFIG_TYPE_PATTERN                                   0x1

/* Defines the pixel format of the pattern and is used for PATTERN patterns   **
** (see TYPE field of this register). NOTE : the field is obsolete for chips  **
** with 2DPE20 feature defined. For those chips use PatternFormat field.      */
#define AQDE_PATTERN_CONFIG_FORMAT                                         3 : 0
#define AQDE_PATTERN_CONFIG_FORMAT_End                                         3
#define AQDE_PATTERN_CONFIG_FORMAT_Start                                       0
#define AQDE_PATTERN_CONFIG_FORMAT_Type                                      U04
#define   AQDE_PATTERN_CONFIG_FORMAT_X4R4G4B4                                0x0
#define   AQDE_PATTERN_CONFIG_FORMAT_A4R4G4B4                                0x1
#define   AQDE_PATTERN_CONFIG_FORMAT_X1R5G5B5                                0x2
#define   AQDE_PATTERN_CONFIG_FORMAT_A1R5G5B5                                0x3
#define   AQDE_PATTERN_CONFIG_FORMAT_R5G6B5                                  0x4
#define   AQDE_PATTERN_CONFIG_FORMAT_X8R8G8B8                                0x5
#define   AQDE_PATTERN_CONFIG_FORMAT_A8R8G8B8                                0x6
#define   AQDE_PATTERN_CONFIG_FORMAT_YUY2                                    0x7
#define   AQDE_PATTERN_CONFIG_FORMAT_UYVY                                    0x8
#define   AQDE_PATTERN_CONFIG_FORMAT_INDEX8                                  0x9
#define   AQDE_PATTERN_CONFIG_FORMAT_MONOCHROME                              0xA
#define   AQDE_PATTERN_CONFIG_FORMAT_YV12                                    0xF

/* Register AQDEPatternLow **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* This register defines the pattern value for monochrome patterns. Color     **
** values from the AQDEPatternFgColor and AQDEPatternBgColor register pair    **
** are used in conjunction with the value of this register to determine the   **
** final color. The pattern is 8x8 pixels and is defined row by row.          */

#define AQDEPatternLowRegAddrs                                            0x0490
#define AQDE_PATTERN_LOW_Address                                         0x01240
#define AQDE_PATTERN_LOW_MSB                                                  15
#define AQDE_PATTERN_LOW_LSB                                                   0
#define AQDE_PATTERN_LOW_BLK                                                   0
#define AQDE_PATTERN_LOW_Count                                                 1
#define AQDE_PATTERN_LOW_FieldMask                                    0xFFFFFFFF
#define AQDE_PATTERN_LOW_ReadMask                                     0xFFFFFFFF
#define AQDE_PATTERN_LOW_WriteMask                                    0xFFFFFFFF
#define AQDE_PATTERN_LOW_ResetValue                                   0x00000000

#define AQDE_PATTERN_LOW_ROW0                                              7 : 0
#define AQDE_PATTERN_LOW_ROW0_End                                              7
#define AQDE_PATTERN_LOW_ROW0_Start                                            0
#define AQDE_PATTERN_LOW_ROW0_Type                                           U08

#define AQDE_PATTERN_LOW_ROW1                                             15 : 8
#define AQDE_PATTERN_LOW_ROW1_End                                             15
#define AQDE_PATTERN_LOW_ROW1_Start                                            8
#define AQDE_PATTERN_LOW_ROW1_Type                                           U08

#define AQDE_PATTERN_LOW_ROW2                                            23 : 16
#define AQDE_PATTERN_LOW_ROW2_End                                             23
#define AQDE_PATTERN_LOW_ROW2_Start                                           16
#define AQDE_PATTERN_LOW_ROW2_Type                                           U08

#define AQDE_PATTERN_LOW_ROW3                                            31 : 24
#define AQDE_PATTERN_LOW_ROW3_End                                             31
#define AQDE_PATTERN_LOW_ROW3_Start                                           24
#define AQDE_PATTERN_LOW_ROW3_Type                                           U08

/* Register AQDEPatternHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEPatternHighRegAddrs                                           0x0491
#define AQDE_PATTERN_HIGH_Address                                        0x01244
#define AQDE_PATTERN_HIGH_MSB                                                 15
#define AQDE_PATTERN_HIGH_LSB                                                  0
#define AQDE_PATTERN_LOW_HIGH_BLK                                              0
#define AQDE_PATTERN_HIGH_Count                                                1
#define AQDE_PATTERN_HIGH_FieldMask                                   0xFFFFFFFF
#define AQDE_PATTERN_HIGH_ReadMask                                    0xFFFFFFFF
#define AQDE_PATTERN_HIGH_WriteMask                                   0xFFFFFFFF
#define AQDE_PATTERN_HIGH_ResetValue                                  0x00000000

#define AQDE_PATTERN_HIGH_ROW4                                             7 : 0
#define AQDE_PATTERN_HIGH_ROW4_End                                             7
#define AQDE_PATTERN_HIGH_ROW4_Start                                           0
#define AQDE_PATTERN_HIGH_ROW4_Type                                          U08

#define AQDE_PATTERN_HIGH_ROW5                                            15 : 8
#define AQDE_PATTERN_HIGH_ROW5_End                                            15
#define AQDE_PATTERN_HIGH_ROW5_Start                                           8
#define AQDE_PATTERN_HIGH_ROW5_Type                                          U08

#define AQDE_PATTERN_HIGH_ROW6                                           23 : 16
#define AQDE_PATTERN_HIGH_ROW6_End                                            23
#define AQDE_PATTERN_HIGH_ROW6_Start                                          16
#define AQDE_PATTERN_HIGH_ROW6_Type                                          U08

#define AQDE_PATTERN_HIGH_ROW7                                           31 : 24
#define AQDE_PATTERN_HIGH_ROW7_End                                            31
#define AQDE_PATTERN_HIGH_ROW7_Start                                          24
#define AQDE_PATTERN_HIGH_ROW7_Type                                          U08

/* Register AQDEPatternMaskLow **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Pattern mask is used only when the transparency is defined by pattern.     **
** Pattern mask is defined in rows, one bit per pixel. Each mask bit is used  **
** to select the ROP code to use for this particular pixel. If mask bit is 0, **
** the pixel is called transparent and background ROP is used, if the bit is  **
** 1, the pixel is called opaque and foreground ROP is used on it.            */

#define AQDEPatternMaskLowRegAddrs                                        0x0492
#define AQDE_PATTERN_MASK_LOW_Address                                    0x01248
#define AQDE_PATTERN_MASK_LOW_MSB                                             15
#define AQDE_PATTERN_MASK_LOW_LSB                                              0
#define AQDE_PATTERN_MASK_LOW_BLK                                              0
#define AQDE_PATTERN_MASK_LOW_Count                                            1
#define AQDE_PATTERN_MASK_LOW_FieldMask                               0xFFFFFFFF
#define AQDE_PATTERN_MASK_LOW_ReadMask                                0xFFFFFFFF
#define AQDE_PATTERN_MASK_LOW_WriteMask                               0xFFFFFFFF
#define AQDE_PATTERN_MASK_LOW_ResetValue                              0xFFFFFFFF

#define AQDE_PATTERN_MASK_LOW_ROW0                                         7 : 0
#define AQDE_PATTERN_MASK_LOW_ROW0_End                                         7
#define AQDE_PATTERN_MASK_LOW_ROW0_Start                                       0
#define AQDE_PATTERN_MASK_LOW_ROW0_Type                                      U08

#define AQDE_PATTERN_MASK_LOW_ROW1                                        15 : 8
#define AQDE_PATTERN_MASK_LOW_ROW1_End                                        15
#define AQDE_PATTERN_MASK_LOW_ROW1_Start                                       8
#define AQDE_PATTERN_MASK_LOW_ROW1_Type                                      U08

#define AQDE_PATTERN_MASK_LOW_ROW2                                       23 : 16
#define AQDE_PATTERN_MASK_LOW_ROW2_End                                        23
#define AQDE_PATTERN_MASK_LOW_ROW2_Start                                      16
#define AQDE_PATTERN_MASK_LOW_ROW2_Type                                      U08

#define AQDE_PATTERN_MASK_LOW_ROW3                                       31 : 24
#define AQDE_PATTERN_MASK_LOW_ROW3_End                                        31
#define AQDE_PATTERN_MASK_LOW_ROW3_Start                                      24
#define AQDE_PATTERN_MASK_LOW_ROW3_Type                                      U08

/* Register AQDEPatternMaskHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEPatternMaskHighRegAddrs                                       0x0493
#define AQDE_PATTERN_MASK_HIGH_Address                                   0x0124C
#define AQDE_PATTERN_MASK_HIGH_MSB                                            15
#define AQDE_PATTERN_MASK_HIGH_LSB                                             0
#define AQDE_PATTERN_MASK_LOW_HIGH_BLK                                         0
#define AQDE_PATTERN_MASK_HIGH_Count                                           1
#define AQDE_PATTERN_MASK_HIGH_FieldMask                              0xFFFFFFFF
#define AQDE_PATTERN_MASK_HIGH_ReadMask                               0xFFFFFFFF
#define AQDE_PATTERN_MASK_HIGH_WriteMask                              0xFFFFFFFF
#define AQDE_PATTERN_MASK_HIGH_ResetValue                             0xFFFFFFFF

#define AQDE_PATTERN_MASK_HIGH_ROW4                                        7 : 0
#define AQDE_PATTERN_MASK_HIGH_ROW4_End                                        7
#define AQDE_PATTERN_MASK_HIGH_ROW4_Start                                      0
#define AQDE_PATTERN_MASK_HIGH_ROW4_Type                                     U08

#define AQDE_PATTERN_MASK_HIGH_ROW5                                       15 : 8
#define AQDE_PATTERN_MASK_HIGH_ROW5_End                                       15
#define AQDE_PATTERN_MASK_HIGH_ROW5_Start                                      8
#define AQDE_PATTERN_MASK_HIGH_ROW5_Type                                     U08

#define AQDE_PATTERN_MASK_HIGH_ROW6                                      23 : 16
#define AQDE_PATTERN_MASK_HIGH_ROW6_End                                       23
#define AQDE_PATTERN_MASK_HIGH_ROW6_Start                                     16
#define AQDE_PATTERN_MASK_HIGH_ROW6_Type                                     U08

#define AQDE_PATTERN_MASK_HIGH_ROW7                                      31 : 24
#define AQDE_PATTERN_MASK_HIGH_ROW7_End                                       31
#define AQDE_PATTERN_MASK_HIGH_ROW7_Start                                     24
#define AQDE_PATTERN_MASK_HIGH_ROW7_Type                                     U08

/* Register AQDEPatternBgColor **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the background color for monochrome patterns. For chips with       **
** 2DPE20 feature defined the color must be set in A8R8G8B8 format, otherwise **
** the format depends on the setting of ColorConvert field of                 **
** AQDEPatternConfig register.                                                */

#define AQDEPatternBgColorRegAddrs                                        0x0494
#define AQDE_PATTERN_BG_COLOR_Address                                    0x01250
#define AQDE_PATTERN_BG_COLOR_MSB                                             15
#define AQDE_PATTERN_BG_COLOR_LSB                                              0
#define AQDE_PATTERN_BG_COLOR_BLK                                              0
#define AQDE_PATTERN_BG_COLOR_Count                                            1
#define AQDE_PATTERN_BG_COLOR_FieldMask                               0xFFFFFFFF
#define AQDE_PATTERN_BG_COLOR_ReadMask                                0xFFFFFFFF
#define AQDE_PATTERN_BG_COLOR_WriteMask                               0xFFFFFFFF
#define AQDE_PATTERN_BG_COLOR_ResetValue                              0x00000000

#define AQDE_PATTERN_BG_COLOR_ALPHA                                      31 : 24
#define AQDE_PATTERN_BG_COLOR_ALPHA_End                                       31
#define AQDE_PATTERN_BG_COLOR_ALPHA_Start                                     24
#define AQDE_PATTERN_BG_COLOR_ALPHA_Type                                     U08

#define AQDE_PATTERN_BG_COLOR_RED                                        23 : 16
#define AQDE_PATTERN_BG_COLOR_RED_End                                         23
#define AQDE_PATTERN_BG_COLOR_RED_Start                                       16
#define AQDE_PATTERN_BG_COLOR_RED_Type                                       U08

#define AQDE_PATTERN_BG_COLOR_GREEN                                       15 : 8
#define AQDE_PATTERN_BG_COLOR_GREEN_End                                       15
#define AQDE_PATTERN_BG_COLOR_GREEN_Start                                      8
#define AQDE_PATTERN_BG_COLOR_GREEN_Type                                     U08

#define AQDE_PATTERN_BG_COLOR_BLUE                                         7 : 0
#define AQDE_PATTERN_BG_COLOR_BLUE_End                                         7
#define AQDE_PATTERN_BG_COLOR_BLUE_Start                                       0
#define AQDE_PATTERN_BG_COLOR_BLUE_Type                                      U08

/* Register AQDEPatternFgColor **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the foreground color for monochrome patterns. For chips with       **
** 2DPE20 feature defined the color must be set in A8R8G8B8 format, otherwise **
** the format depends on the setting of ColorConvert field of                 **
** AQDEPatternConfig register.                                                */

#define AQDEPatternFgColorRegAddrs                                        0x0495
#define AQDE_PATTERN_FG_COLOR_Address                                    0x01254
#define AQDE_PATTERN_FG_COLOR_MSB                                             15
#define AQDE_PATTERN_FG_COLOR_LSB                                              0
#define AQDE_PATTERN_FG_COLOR_BLK                                              0
#define AQDE_PATTERN_FG_COLOR_Count                                            1
#define AQDE_PATTERN_FG_COLOR_FieldMask                               0xFFFFFFFF
#define AQDE_PATTERN_FG_COLOR_ReadMask                                0xFFFFFFFF
#define AQDE_PATTERN_FG_COLOR_WriteMask                               0xFFFFFFFF
#define AQDE_PATTERN_FG_COLOR_ResetValue                              0x00000000

#define AQDE_PATTERN_FG_COLOR_ALPHA                                      31 : 24
#define AQDE_PATTERN_FG_COLOR_ALPHA_End                                       31
#define AQDE_PATTERN_FG_COLOR_ALPHA_Start                                     24
#define AQDE_PATTERN_FG_COLOR_ALPHA_Type                                     U08

#define AQDE_PATTERN_FG_COLOR_RED                                        23 : 16
#define AQDE_PATTERN_FG_COLOR_RED_End                                         23
#define AQDE_PATTERN_FG_COLOR_RED_Start                                       16
#define AQDE_PATTERN_FG_COLOR_RED_Type                                       U08

#define AQDE_PATTERN_FG_COLOR_GREEN                                       15 : 8
#define AQDE_PATTERN_FG_COLOR_GREEN_End                                       15
#define AQDE_PATTERN_FG_COLOR_GREEN_Start                                      8
#define AQDE_PATTERN_FG_COLOR_GREEN_Type                                     U08

#define AQDE_PATTERN_FG_COLOR_BLUE                                         7 : 0
#define AQDE_PATTERN_FG_COLOR_BLUE_End                                         7
#define AQDE_PATTERN_FG_COLOR_BLUE_Start                                       0
#define AQDE_PATTERN_FG_COLOR_BLUE_Type                                      U08

/* Register AQDEFilterBlit **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* Filter blit configuration regisrter. This register MUST be programmed      **
** before AQDEFilterKernel.                                                   */

#define AQDEFilterBlitRegAddrs                                            0x0496
#define AQDE_FILTER_BLIT_Address                                         0x01258
#define AQDE_FILTER_BLIT_MSB                                                  15
#define AQDE_FILTER_BLIT_LSB                                                   0
#define AQDE_FILTER_BLIT_BLK                                                   0
#define AQDE_FILTER_BLIT_Count                                                 1
#define AQDE_FILTER_BLIT_FieldMask                                    0x000000FF
#define AQDE_FILTER_BLIT_ReadMask                                     0x000000FF
#define AQDE_FILTER_BLIT_WriteMask                                    0x000000FF
#define AQDE_FILTER_BLIT_ResetValue                                   0x00000000

/* If set, the horizontal blit will walk all the way to the left edge         **
** allowing to sample pixels to the left of the center which could be beyond  **
** the source edge. This assumes that there are enough valid pixels beyond    **
** the left edge to cover the size of the kernel. For example if the kernel   **
** size is 9, there should be at least 4 valid pixels beyond the edge. This   **
** mode is used for split frame rendering to prevent seams between the        **
** subframes.  NOTE :  this field is now obsolete.                            */
#define AQDE_FILTER_BLIT_IGNORE_LEFT_EDGE                                  7 : 7
#define AQDE_FILTER_BLIT_IGNORE_LEFT_EDGE_End                                  7
#define AQDE_FILTER_BLIT_IGNORE_LEFT_EDGE_Start                                7
#define AQDE_FILTER_BLIT_IGNORE_LEFT_EDGE_Type                               U01

/* The same as IGNORE_LEFT_EDGE field, but for the top edge in vertical blit. **
**  NOTE :  this field is now obsolete.                                       */
#define AQDE_FILTER_BLIT_IGNORE_TOP_EDGE                                   6 : 6
#define AQDE_FILTER_BLIT_IGNORE_TOP_EDGE_End                                   6
#define AQDE_FILTER_BLIT_IGNORE_TOP_EDGE_Start                                 6
#define AQDE_FILTER_BLIT_IGNORE_TOP_EDGE_Type                                U01

/* The same as IGNORE_LEFT_EDGE field, but for the right edge.  NOTE :  this  **
** field is now obsolete.                                                     */
#define AQDE_FILTER_BLIT_IGNORE_RIGHT_EDGE                                 5 : 5
#define AQDE_FILTER_BLIT_IGNORE_RIGHT_EDGE_End                                 5
#define AQDE_FILTER_BLIT_IGNORE_RIGHT_EDGE_Start                               5
#define AQDE_FILTER_BLIT_IGNORE_RIGHT_EDGE_Type                              U01

/* The same as IGNORE_LEFT_EDGE field, but for the bottom edge in vertical    **
** blit.  NOTE :  this field is now obsolete.                                 */
#define AQDE_FILTER_BLIT_IGNORE_BOTTOM_EDGE                                4 : 4
#define AQDE_FILTER_BLIT_IGNORE_BOTTOM_EDGE_End                                4
#define AQDE_FILTER_BLIT_IGNORE_BOTTOM_EDGE_Start                              4
#define AQDE_FILTER_BLIT_IGNORE_BOTTOM_EDGE_Type                             U01

/* The size of the kernel; determines number of source samples to be taken to **
** determine each destination pixel. Valid values are 1, 3, 5, 7, 9.          */
#define AQDE_FILTER_BLIT_KERNEL_SIZE                                       3 : 0
#define AQDE_FILTER_BLIT_KERNEL_SIZE_End                                       3
#define AQDE_FILTER_BLIT_KERNEL_SIZE_Start                                     0
#define AQDE_FILTER_BLIT_KERNEL_SIZE_Type                                    U04

/* Register AQDEFilterKernel (128 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Filter blit coefficient table. */

#define AQDEFilterKernelRegAddrs                                          0x0600
#define AQDE_FILTER_KERNEL_Address                                       0x01800
#define AQDE_FILTER_KERNEL_MSB                                                15
#define AQDE_FILTER_KERNEL_LSB                                                 7
#define AQDE_FILTER_KERNEL_BLK                                                 7
#define AQDE_FILTER_KERNEL_Count                                             128
#define AQDE_FILTER_KERNEL_FieldMask                                  0xFFFFFFFF
#define AQDE_FILTER_KERNEL_ReadMask                                   0xFFFFFFFF
#define AQDE_FILTER_KERNEL_WriteMask                                  0xFFFFFFFF
#define AQDE_FILTER_KERNEL_ResetValue                                 0x00000000

#define AQDE_FILTER_KERNEL_COEFFICIENT0                                   15 : 0
#define AQDE_FILTER_KERNEL_COEFFICIENT0_End                                   15
#define AQDE_FILTER_KERNEL_COEFFICIENT0_Start                                  0
#define AQDE_FILTER_KERNEL_COEFFICIENT0_Type                                 U16

#define AQDE_FILTER_KERNEL_COEFFICIENT1                                  31 : 16
#define AQDE_FILTER_KERNEL_COEFFICIENT1_End                                   31
#define AQDE_FILTER_KERNEL_COEFFICIENT1_Start                                 16
#define AQDE_FILTER_KERNEL_COEFFICIENT1_Type                                 U16

/* Register AQDEIndexColorTable (256 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 256 color entries for the indexed color mode. Colors are assumed to be in  **
** the destination format and no color conversion is done on the values.      */

#define AQDEIndexColorTableRegAddrs                                       0x0700
#define AQDE_INDEX_COLOR_TABLE_Address                                   0x01C00
#define AQDE_INDEX_COLOR_TABLE_MSB                                            15
#define AQDE_INDEX_COLOR_TABLE_LSB                                             8
#define AQDE_INDEX_COLOR_TABLE_BLK                                             8
#define AQDE_INDEX_COLOR_TABLE_Count                                         256
#define AQDE_INDEX_COLOR_TABLE_FieldMask                              0xFFFFFFFF
#define AQDE_INDEX_COLOR_TABLE_ReadMask                               0xFFFFFFFF
#define AQDE_INDEX_COLOR_TABLE_WriteMask                              0xFFFFFFFF
#define AQDE_INDEX_COLOR_TABLE_ResetValue                             0x00000000

#define AQDE_INDEX_COLOR_TABLE_ALPHA                                     31 : 24
#define AQDE_INDEX_COLOR_TABLE_ALPHA_End                                      31
#define AQDE_INDEX_COLOR_TABLE_ALPHA_Start                                    24
#define AQDE_INDEX_COLOR_TABLE_ALPHA_Type                                    U08

#define AQDE_INDEX_COLOR_TABLE_RED                                       23 : 16
#define AQDE_INDEX_COLOR_TABLE_RED_End                                        23
#define AQDE_INDEX_COLOR_TABLE_RED_Start                                      16
#define AQDE_INDEX_COLOR_TABLE_RED_Type                                      U08

#define AQDE_INDEX_COLOR_TABLE_GREEN                                      15 : 8
#define AQDE_INDEX_COLOR_TABLE_GREEN_End                                      15
#define AQDE_INDEX_COLOR_TABLE_GREEN_Start                                     8
#define AQDE_INDEX_COLOR_TABLE_GREEN_Type                                    U08

#define AQDE_INDEX_COLOR_TABLE_BLUE                                        7 : 0
#define AQDE_INDEX_COLOR_TABLE_BLUE_End                                        7
#define AQDE_INDEX_COLOR_TABLE_BLUE_Start                                      0
#define AQDE_INDEX_COLOR_TABLE_BLUE_Type                                     U08

/* Register AQDEIndexColorTable32 (256 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 256 color entries for the indexed color mode. Colors are assumed to be in  **
** the A8R8G8B8 format and no color conversion is done on the values. This    **
** register is used only with chips with PE20 feature available.              */

#define AQDEIndexColorTable32RegAddrs                                     0x0D00
#define AQDE_INDEX_COLOR_TABLE32_Address                                 0x03400
#define AQDE_INDEX_COLOR_TABLE32_MSB                                          15
#define AQDE_INDEX_COLOR_TABLE32_LSB                                           8
#define AQDE_INDEX_COLOR_TABLE32_BLK                                           8
#define AQDE_INDEX_COLOR_TABLE32_Count                                       256
#define AQDE_INDEX_COLOR_TABLE32_FieldMask                            0xFFFFFFFF
#define AQDE_INDEX_COLOR_TABLE32_ReadMask                             0xFFFFFFFF
#define AQDE_INDEX_COLOR_TABLE32_WriteMask                            0xFFFFFFFF
#define AQDE_INDEX_COLOR_TABLE32_ResetValue                           0x00000000

#define AQDE_INDEX_COLOR_TABLE32_ALPHA                                   31 : 24
#define AQDE_INDEX_COLOR_TABLE32_ALPHA_End                                    31
#define AQDE_INDEX_COLOR_TABLE32_ALPHA_Start                                  24
#define AQDE_INDEX_COLOR_TABLE32_ALPHA_Type                                  U08

#define AQDE_INDEX_COLOR_TABLE32_RED                                     23 : 16
#define AQDE_INDEX_COLOR_TABLE32_RED_End                                      23
#define AQDE_INDEX_COLOR_TABLE32_RED_Start                                    16
#define AQDE_INDEX_COLOR_TABLE32_RED_Type                                    U08

#define AQDE_INDEX_COLOR_TABLE32_GREEN                                    15 : 8
#define AQDE_INDEX_COLOR_TABLE32_GREEN_End                                    15
#define AQDE_INDEX_COLOR_TABLE32_GREEN_Start                                   8
#define AQDE_INDEX_COLOR_TABLE32_GREEN_Type                                  U08

#define AQDE_INDEX_COLOR_TABLE32_BLUE                                      7 : 0
#define AQDE_INDEX_COLOR_TABLE32_BLUE_End                                      7
#define AQDE_INDEX_COLOR_TABLE32_BLUE_Start                                    0
#define AQDE_INDEX_COLOR_TABLE32_BLUE_Type                                   U08

/* Register AQDERop **
** ~~~~~~~~~~~~~~~~ */

/* Raster operation foreground and background codes. Even though ROP is not   **
** used in CLEAR, HOR_FILTER_BLT, VER_FILTER_BLT and alpha-eanbled BIT_BLTs,  **
** ROP code still has to be programmed, because the engine makes the decision **
** whether source, destination and pattern are involved in the current        **
** operation and the correct decision is essential for the engine to complete **
** the operation as expected.                                                 */

#define AQDERopRegAddrs                                                   0x0497
#define AQDE_ROP_Address                                                 0x0125C
#define AQDE_ROP_MSB                                                          15
#define AQDE_ROP_LSB                                                           0
#define AQDE_ROP_BLK                                                           0
#define AQDE_ROP_Count                                                         1
#define AQDE_ROP_FieldMask                                            0x0030FFFF
#define AQDE_ROP_ReadMask                                             0x0030FFFF
#define AQDE_ROP_WriteMask                                            0x0030FFFF
#define AQDE_ROP_ResetValue                                           0x00000000

/* ROP type :  ROP2, ROP3 or ROP4 */
#define AQDE_ROP_TYPE                                                    21 : 20
#define AQDE_ROP_TYPE_End                                                     21
#define AQDE_ROP_TYPE_Start                                                   20
#define AQDE_ROP_TYPE_Type                                                   U02
#define   AQDE_ROP_TYPE_ROP2_PATTERN                                         0x0
#define   AQDE_ROP_TYPE_ROP2_SOURCE                                          0x1
#define   AQDE_ROP_TYPE_ROP3                                                 0x2
#define   AQDE_ROP_TYPE_ROP4                                                 0x3

/* Background ROP code is used for transparent pixels. */
#define AQDE_ROP_ROP_BG                                                   15 : 8
#define AQDE_ROP_ROP_BG_End                                                   15
#define AQDE_ROP_ROP_BG_Start                                                  8
#define AQDE_ROP_ROP_BG_Type                                                 U08

/* Background ROP code is used for opaque pixels. */
#define AQDE_ROP_ROP_FG                                                    7 : 0
#define AQDE_ROP_ROP_FG_End                                                    7
#define AQDE_ROP_ROP_FG_Start                                                  0
#define AQDE_ROP_ROP_FG_Type                                                 U08

/* Register AQDEClipTopLeft **
** ~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Top left corner of the clipping rectangle defined in pixels. Clipping is   **
** always on and everything beyond the clipping rectangle will be clipped     **
** out. Clipping is not used with filter blits.                               */

#define AQDEClipTopLeftRegAddrs                                           0x0498
#define AQDE_CLIP_TOP_LEFT_Address                                       0x01260
#define AQDE_CLIP_TOP_LEFT_MSB                                                15
#define AQDE_CLIP_TOP_LEFT_LSB                                                 0
#define AQDE_CLIP_TOP_LEFT_BLK                                                 0
#define AQDE_CLIP_TOP_LEFT_Count                                               1
#define AQDE_CLIP_TOP_LEFT_FieldMask                                  0x7FFF7FFF
#define AQDE_CLIP_TOP_LEFT_ReadMask                                   0x7FFF7FFF
#define AQDE_CLIP_TOP_LEFT_WriteMask                                  0x7FFF7FFF
#define AQDE_CLIP_TOP_LEFT_ResetValue                                 0x00000000

#define AQDE_CLIP_TOP_LEFT_Y                                             30 : 16
#define AQDE_CLIP_TOP_LEFT_Y_End                                              30
#define AQDE_CLIP_TOP_LEFT_Y_Start                                            16
#define AQDE_CLIP_TOP_LEFT_Y_Type                                            U15

#define AQDE_CLIP_TOP_LEFT_X                                              14 : 0
#define AQDE_CLIP_TOP_LEFT_X_End                                              14
#define AQDE_CLIP_TOP_LEFT_X_Start                                             0
#define AQDE_CLIP_TOP_LEFT_X_Type                                            U15

/* Register AQDEClipBottomRight **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Bottom right corner of the clipping rectangle defined in pixels. Clipping  **
** is always on and everything beyond the clipping rectangle will be clipped  **
** out. Clipping is not used with filter blits.                               */

#define AQDEClipBottomRightRegAddrs                                       0x0499
#define AQDE_CLIP_BOTTOM_RIGHT_Address                                   0x01264
#define AQDE_CLIP_BOTTOM_RIGHT_MSB                                            15
#define AQDE_CLIP_BOTTOM_RIGHT_LSB                                             0
#define AQDE_CLIP_BOTTOM_RIGHT_BLK                                             0
#define AQDE_CLIP_BOTTOM_RIGHT_Count                                           1
#define AQDE_CLIP_BOTTOM_RIGHT_FieldMask                              0x7FFF7FFF
#define AQDE_CLIP_BOTTOM_RIGHT_ReadMask                               0x7FFF7FFF
#define AQDE_CLIP_BOTTOM_RIGHT_WriteMask                              0x7FFF7FFF
#define AQDE_CLIP_BOTTOM_RIGHT_ResetValue                             0x00000000

#define AQDE_CLIP_BOTTOM_RIGHT_Y                                         30 : 16
#define AQDE_CLIP_BOTTOM_RIGHT_Y_End                                          30
#define AQDE_CLIP_BOTTOM_RIGHT_Y_Start                                        16
#define AQDE_CLIP_BOTTOM_RIGHT_Y_Type                                        U15

#define AQDE_CLIP_BOTTOM_RIGHT_X                                          14 : 0
#define AQDE_CLIP_BOTTOM_RIGHT_X_End                                          14
#define AQDE_CLIP_BOTTOM_RIGHT_X_Start                                         0
#define AQDE_CLIP_BOTTOM_RIGHT_X_Type                                        U15

/* Register AQDEClearByteMask **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEClearByteMaskRegAddrs                                         0x049A
#define AQDE_CLEAR_BYTE_MASK_Address                                     0x01268
#define AQDE_CLEAR_BYTE_MASK_MSB                                              15
#define AQDE_CLEAR_BYTE_MASK_LSB                                               0
#define AQDE_CLEAR_BYTE_MASK_BLK                                               0
#define AQDE_CLEAR_BYTE_MASK_Count                                             1
#define AQDE_CLEAR_BYTE_MASK_FieldMask                                0x000000FF
#define AQDE_CLEAR_BYTE_MASK_ReadMask                                 0x000000FF
#define AQDE_CLEAR_BYTE_MASK_WriteMask                                0x000000FF
#define AQDE_CLEAR_BYTE_MASK_ResetValue                               0x00000000

/* Byte mask for the clear command; defines which bytes to clear with value   **
** specified in AQDEClearPixelValueLow and AQDEClearPixelValueHigh registers. **
**  This field is now obsolete.                                               */
#define AQDE_CLEAR_BYTE_MASK_VALUE                                         7 : 0
#define AQDE_CLEAR_BYTE_MASK_VALUE_End                                         7
#define AQDE_CLEAR_BYTE_MASK_VALUE_Start                                       0
#define AQDE_CLEAR_BYTE_MASK_VALUE_Type                                      U08

/* Register AQDEClearPixelValueLow **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEClearPixelValueLowRegAddrs                                    0x049C
#define AQDE_CLEAR_PIXEL_VALUE_LOW_Address                               0x01270
#define AQDE_CLEAR_PIXEL_VALUE_LOW_MSB                                        15
#define AQDE_CLEAR_PIXEL_VALUE_LOW_LSB                                         0
#define AQDE_CLEAR_PIXEL_VALUE_LOW_BLK                                         0
#define AQDE_CLEAR_PIXEL_VALUE_LOW_Count                                       1
#define AQDE_CLEAR_PIXEL_VALUE_LOW_FieldMask                          0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE_LOW_ReadMask                           0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE_LOW_WriteMask                          0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE_LOW_ResetValue                         0x00000000

/* For chips with 2DPE20 feature defined only the lower 32 bits are used and  **
** must be set in A8R8G8B8 format. For older chips where 2DPE20 feature is    **
** not defined this field represents a 64-bit value that combines either two  **
** (for 32-bit destinations) or four (for 16-bit destinations) pixel values   **
** in destination format.                                                     */
#define AQDE_CLEAR_PIXEL_VALUE_LOW_VALUE                                  31 : 0
#define AQDE_CLEAR_PIXEL_VALUE_LOW_VALUE_End                                  31
#define AQDE_CLEAR_PIXEL_VALUE_LOW_VALUE_Start                                 0
#define AQDE_CLEAR_PIXEL_VALUE_LOW_VALUE_Type                                U32

/* Register AQDEClearPixelValueHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEClearPixelValueHighRegAddrs                                   0x049D
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_Address                              0x01274
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_MSB                                       15
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_LSB                                        0
#define AQDE_CLEAR_PIXEL_VALUE_LOW_HIGH_BLK                                    0
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_Count                                      1
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_FieldMask                         0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_ReadMask                          0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_WriteMask                         0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_ResetValue                        0x00000000

/* For chips with 2DPE20 feature defined only the lower 32 bits are used and  **
** must be set in A8R8G8B8 format. For older chips where 2DPE20 feature is    **
** not defined this field represents a 64-bit value that combines either two  **
** (for 32-bit destinations) or four (for 16-bit destinations) pixel values   **
** in destination format.                                                     */
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_VALUE                                 31 : 0
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_VALUE_End                                 31
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_VALUE_Start                                0
#define AQDE_CLEAR_PIXEL_VALUE_HIGH_VALUE_Type                               U32

/* Register AQDEConfig **
** ~~~~~~~~~~~~~~~~~~~ */
#define AQDEConfigRegAddrs                                                0x049B
#define AQDE_CONFIG_Address                                              0x0126C
#define AQDE_CONFIG_MSB                                                       15
#define AQDE_CONFIG_LSB                                                        0
#define AQDE_CONFIG_BLK                                                        0
#define AQDE_CONFIG_Count                                                      1
#define AQDE_CONFIG_FieldMask                                         0x00370031
#define AQDE_CONFIG_ReadMask                                          0x00370031
#define AQDE_CONFIG_WriteMask                                         0x00370031
#define AQDE_CONFIG_ResetValue                                        0x00000000

#define AQDE_CONFIG_MIRROR_BLT_MODE                                        5 : 4
#define AQDE_CONFIG_MIRROR_BLT_MODE_End                                        5
#define AQDE_CONFIG_MIRROR_BLT_MODE_Start                                      4
#define AQDE_CONFIG_MIRROR_BLT_MODE_Type                                     U02
#define   AQDE_CONFIG_MIRROR_BLT_MODE_NORMAL                                 0x0
#define   AQDE_CONFIG_MIRROR_BLT_MODE_HMIRROR                                0x1
#define   AQDE_CONFIG_MIRROR_BLT_MODE_VMIRROR                                0x2
#define   AQDE_CONFIG_MIRROR_BLT_MODE_FULL_MIRROR                            0x3

#define AQDE_CONFIG_MIRROR_BLT_ENABLE                                      0 : 0
#define AQDE_CONFIG_MIRROR_BLT_ENABLE_End                                      0
#define AQDE_CONFIG_MIRROR_BLT_ENABLE_Start                                    0
#define AQDE_CONFIG_MIRROR_BLT_ENABLE_Type                                   U01
#define   AQDE_CONFIG_MIRROR_BLT_ENABLE_OFF                                  0x0
#define   AQDE_CONFIG_MIRROR_BLT_ENABLE_ON                                   0x1

/* Source select for the old walkers. */
#define AQDE_CONFIG_SOURCE_SELECT                                        18 : 16
#define AQDE_CONFIG_SOURCE_SELECT_End                                         18
#define AQDE_CONFIG_SOURCE_SELECT_Start                                       16
#define AQDE_CONFIG_SOURCE_SELECT_Type                                       U03

/* Destination select for the old walkers. */
#define AQDE_CONFIG_DESTINATION_SELECT                                   21 : 20
#define AQDE_CONFIG_DESTINATION_SELECT_End                                    21
#define AQDE_CONFIG_DESTINATION_SELECT_Start                                  20
#define AQDE_CONFIG_DESTINATION_SELECT_Type                                  U02

/* Register AQDESrcOriginFraction **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Fraction for the source origin. Together with values in AQDESrcOrigin      **
** these values form signed 16.16 fixed point origin for the source           **
** rectangle. Fractions are only used in filter blit in split frame mode.     */

#define AQDESrcOriginFractionRegAddrs                                     0x049E
#define AQDE_SRC_ORIGIN_FRACTION_Address                                 0x01278
#define AQDE_SRC_ORIGIN_FRACTION_MSB                                          15
#define AQDE_SRC_ORIGIN_FRACTION_LSB                                           0
#define AQDE_SRC_ORIGIN_FRACTION_BLK                                           0
#define AQDE_SRC_ORIGIN_FRACTION_Count                                         1
#define AQDE_SRC_ORIGIN_FRACTION_FieldMask                            0xFFFFFFFF
#define AQDE_SRC_ORIGIN_FRACTION_ReadMask                             0xFFFFFFFF
#define AQDE_SRC_ORIGIN_FRACTION_WriteMask                            0xFFFFFFFF
#define AQDE_SRC_ORIGIN_FRACTION_ResetValue                           0x00000000

#define AQDE_SRC_ORIGIN_FRACTION_Y                                       31 : 16
#define AQDE_SRC_ORIGIN_FRACTION_Y_End                                        31
#define AQDE_SRC_ORIGIN_FRACTION_Y_Start                                      16
#define AQDE_SRC_ORIGIN_FRACTION_Y_Type                                      U16

#define AQDE_SRC_ORIGIN_FRACTION_X                                        15 : 0
#define AQDE_SRC_ORIGIN_FRACTION_X_End                                        15
#define AQDE_SRC_ORIGIN_FRACTION_X_Start                                       0
#define AQDE_SRC_ORIGIN_FRACTION_X_Type                                      U16

/* Register AQDEAlphaControl **
** ~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEAlphaControlRegAddrs                                          0x049F
#define AQDE_ALPHA_CONTROL_Address                                       0x0127C
#define AQDE_ALPHA_CONTROL_MSB                                                15
#define AQDE_ALPHA_CONTROL_LSB                                                 0
#define AQDE_ALPHA_CONTROL_BLK                                                 0
#define AQDE_ALPHA_CONTROL_Count                                               1
#define AQDE_ALPHA_CONTROL_FieldMask                                  0xFFFF0001
#define AQDE_ALPHA_CONTROL_ReadMask                                   0xFFFF0001
#define AQDE_ALPHA_CONTROL_WriteMask                                  0xFFFF0001
#define AQDE_ALPHA_CONTROL_ResetValue                                 0x00000000

#define AQDE_ALPHA_CONTROL_ENABLE                                          0 : 0
#define AQDE_ALPHA_CONTROL_ENABLE_End                                          0
#define AQDE_ALPHA_CONTROL_ENABLE_Start                                        0
#define AQDE_ALPHA_CONTROL_ENABLE_Type                                       U01
#define   AQDE_ALPHA_CONTROL_ENABLE_OFF                                      0x0
#define   AQDE_ALPHA_CONTROL_ENABLE_ON                                       0x1

/* Global source alpha value.  For chips with 2DPE20 feature defined this     **
** field is obsolete; AQDEGlobalSrcColor register should be used instead.     */
#define AQDE_ALPHA_CONTROL_SRC_VALUE                                     23 : 16
#define AQDE_ALPHA_CONTROL_SRC_VALUE_End                                      23
#define AQDE_ALPHA_CONTROL_SRC_VALUE_Start                                    16
#define AQDE_ALPHA_CONTROL_SRC_VALUE_Type                                    U08

/* Global destination alpha value.  For chips with 2DPE20 feature defined     **
** this field is obsolete; AQDEGlobalDestColor register should be used        **
** instead.                                                                   */
#define AQDE_ALPHA_CONTROL_DST_VALUE                                     31 : 24
#define AQDE_ALPHA_CONTROL_DST_VALUE_End                                      31
#define AQDE_ALPHA_CONTROL_DST_VALUE_Start                                    24
#define AQDE_ALPHA_CONTROL_DST_VALUE_Type                                    U08

/* Register AQDEAlphaModes **
** ~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDEAlphaModesRegAddrs                                            0x04A0
#define AQDE_ALPHA_MODES_Address                                         0x01280
#define AQDE_ALPHA_MODES_MSB                                                  15
#define AQDE_ALPHA_MODES_LSB                                                   0
#define AQDE_ALPHA_MODES_BLK                                                   0
#define AQDE_ALPHA_MODES_Count                                                 1
#define AQDE_ALPHA_MODES_FieldMask                                    0xFF113311
#define AQDE_ALPHA_MODES_ReadMask                                     0xFF113311
#define AQDE_ALPHA_MODES_WriteMask                                    0xFF113311
#define AQDE_ALPHA_MODES_ResetValue                                   0x00000000

#define AQDE_ALPHA_MODES_SRC_ALPHA_MODE                                    0 : 0
#define AQDE_ALPHA_MODES_SRC_ALPHA_MODE_End                                    0
#define AQDE_ALPHA_MODES_SRC_ALPHA_MODE_Start                                  0
#define AQDE_ALPHA_MODES_SRC_ALPHA_MODE_Type                                 U01
#define   AQDE_ALPHA_MODES_SRC_ALPHA_MODE_NORMAL                             0x0
#define   AQDE_ALPHA_MODES_SRC_ALPHA_MODE_INVERSED                           0x1

#define AQDE_ALPHA_MODES_DST_ALPHA_MODE                                    4 : 4
#define AQDE_ALPHA_MODES_DST_ALPHA_MODE_End                                    4
#define AQDE_ALPHA_MODES_DST_ALPHA_MODE_Start                                  4
#define AQDE_ALPHA_MODES_DST_ALPHA_MODE_Type                                 U01
#define   AQDE_ALPHA_MODES_DST_ALPHA_MODE_NORMAL                             0x0
#define   AQDE_ALPHA_MODES_DST_ALPHA_MODE_INVERSED                           0x1

#define AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE                             9 : 8
#define AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_End                             9
#define AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_Start                           8
#define AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_Type                          U02
#define   AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_NORMAL                      0x0
#define   AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_GLOBAL                      0x1
#define   AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_SCALED                      0x2

#define AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE                           13 : 12
#define AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_End                            13
#define AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_Start                          12
#define AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_Type                          U02
#define   AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_NORMAL                      0x0
#define   AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_GLOBAL                      0x1
#define   AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_SCALED                      0x2

/* NOTE :  for chips with 2DPE20 feature defined, AQDEColorMultiplyModes      **
** register should be used instead.                                           */
#define AQDE_ALPHA_MODES_SRC_COLOR_MODE                                  16 : 16
#define AQDE_ALPHA_MODES_SRC_COLOR_MODE_End                                   16
#define AQDE_ALPHA_MODES_SRC_COLOR_MODE_Start                                 16
#define AQDE_ALPHA_MODES_SRC_COLOR_MODE_Type                                 U01
#define   AQDE_ALPHA_MODES_SRC_COLOR_MODE_NORMAL                             0x0
#define   AQDE_ALPHA_MODES_SRC_COLOR_MODE_MULTIPLY                           0x1

/* NOTE :  for chips with 2DPE20 feature defined, AQDEColorMultiplyModes      **
** register should be used instead.                                           */
#define AQDE_ALPHA_MODES_DST_COLOR_MODE                                  20 : 20
#define AQDE_ALPHA_MODES_DST_COLOR_MODE_End                                   20
#define AQDE_ALPHA_MODES_DST_COLOR_MODE_Start                                 20
#define AQDE_ALPHA_MODES_DST_COLOR_MODE_Type                                 U01
#define   AQDE_ALPHA_MODES_DST_COLOR_MODE_NORMAL                             0x0
#define   AQDE_ALPHA_MODES_DST_COLOR_MODE_MULTIPLY                           0x1

#define AQDE_ALPHA_MODES_SRC_BLENDING_MODE                               26 : 24
#define AQDE_ALPHA_MODES_SRC_BLENDING_MODE_End                                26
#define AQDE_ALPHA_MODES_SRC_BLENDING_MODE_Start                              24
#define AQDE_ALPHA_MODES_SRC_BLENDING_MODE_Type                              U03
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_ZERO                            0x0
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_ONE                             0x1
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_NORMAL                          0x2
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_INVERSED                        0x3
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_COLOR                           0x4
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_COLOR_INVERSED                  0x5
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_SATURATED_ALPHA                 0x6
#define   AQDE_ALPHA_MODES_SRC_BLENDING_MODE_SATURATED_DEST_ALPHA            0x7

/* Src Blending factor is calculate from Src alpha. */
#define AQDE_ALPHA_MODES_SRC_ALPHA_FACTOR                                27 : 27
#define AQDE_ALPHA_MODES_SRC_ALPHA_FACTOR_End                                 27
#define AQDE_ALPHA_MODES_SRC_ALPHA_FACTOR_Start                               27
#define AQDE_ALPHA_MODES_SRC_ALPHA_FACTOR_Type                               U01
#define   AQDE_ALPHA_MODES_SRC_ALPHA_FACTOR_DISABLED                         0x0
#define   AQDE_ALPHA_MODES_SRC_ALPHA_FACTOR_ENABLED                          0x1

#define AQDE_ALPHA_MODES_DST_BLENDING_MODE                               30 : 28
#define AQDE_ALPHA_MODES_DST_BLENDING_MODE_End                                30
#define AQDE_ALPHA_MODES_DST_BLENDING_MODE_Start                              28
#define AQDE_ALPHA_MODES_DST_BLENDING_MODE_Type                              U03
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_ZERO                            0x0
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_ONE                             0x1
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_NORMAL                          0x2
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_INVERSED                        0x3
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_COLOR                           0x4
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_COLOR_INVERSED                  0x5
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_SATURATED_ALPHA                 0x6
#define   AQDE_ALPHA_MODES_DST_BLENDING_MODE_SATURATED_DEST_ALPHA            0x7

/* Dst Blending factor is calculate from Dst alpha. */
#define AQDE_ALPHA_MODES_DST_ALPHA_FACTOR                                31 : 31
#define AQDE_ALPHA_MODES_DST_ALPHA_FACTOR_End                                 31
#define AQDE_ALPHA_MODES_DST_ALPHA_FACTOR_Start                               31
#define AQDE_ALPHA_MODES_DST_ALPHA_FACTOR_Type                               U01
#define   AQDE_ALPHA_MODES_DST_ALPHA_FACTOR_DISABLED                         0x0
#define   AQDE_ALPHA_MODES_DST_ALPHA_FACTOR_ENABLED                          0x1

/* Register UPlaneAddress **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source U plane. */

#define UPlaneAddressRegAddrs                                             0x04A1
#define UPLANE_ADDRESS_Address                                           0x01284
#define UPLANE_ADDRESS_MSB                                                    15
#define UPLANE_ADDRESS_LSB                                                     0
#define UPLANE_ADDRESS_BLK                                                     0
#define UPLANE_ADDRESS_Count                                                   1
#define UPLANE_ADDRESS_FieldMask                                      0xFFFFFFFF
#define UPLANE_ADDRESS_ReadMask                                       0xFFFFFFFC
#define UPLANE_ADDRESS_WriteMask                                      0xFFFFFFFC
#define UPLANE_ADDRESS_ResetValue                                     0x00000000

#define UPLANE_ADDRESS_TYPE                                              31 : 31
#define UPLANE_ADDRESS_TYPE_End                                               31
#define UPLANE_ADDRESS_TYPE_Start                                             31
#define UPLANE_ADDRESS_TYPE_Type                                             U01
#define   UPLANE_ADDRESS_TYPE_SYSTEM                                         0x0
#define   UPLANE_ADDRESS_TYPE_VIRTUAL_SYSTEM                                 0x1

#define UPLANE_ADDRESS_ADDRESS                                            30 : 0
#define UPLANE_ADDRESS_ADDRESS_End                                            30
#define UPLANE_ADDRESS_ADDRESS_Start                                           0
#define UPLANE_ADDRESS_ADDRESS_Type                                          U31

/* Register UPlaneStride **
** ~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source U plane in bytes. */

#define UPlaneStrideRegAddrs                                              0x04A2
#define UPLANE_STRIDE_Address                                            0x01288
#define UPLANE_STRIDE_MSB                                                     15
#define UPLANE_STRIDE_LSB                                                      0
#define UPLANE_STRIDE_BLK                                                      0
#define UPLANE_STRIDE_Count                                                    1
#define UPLANE_STRIDE_FieldMask                                       0x0003FFFF
#define UPLANE_STRIDE_ReadMask                                        0x0003FFFC
#define UPLANE_STRIDE_WriteMask                                       0x0003FFFC
#define UPLANE_STRIDE_ResetValue                                      0x00000000

#define UPLANE_STRIDE_STRIDE                                              17 : 0
#define UPLANE_STRIDE_STRIDE_End                                              17
#define UPLANE_STRIDE_STRIDE_Start                                             0
#define UPLANE_STRIDE_STRIDE_Type                                            U18

/* Register VPlaneAddress **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source V plane. */

#define VPlaneAddressRegAddrs                                             0x04A3
#define VPLANE_ADDRESS_Address                                           0x0128C
#define VPLANE_ADDRESS_MSB                                                    15
#define VPLANE_ADDRESS_LSB                                                     0
#define VPLANE_ADDRESS_BLK                                                     0
#define VPLANE_ADDRESS_Count                                                   1
#define VPLANE_ADDRESS_FieldMask                                      0xFFFFFFFF
#define VPLANE_ADDRESS_ReadMask                                       0xFFFFFFFC
#define VPLANE_ADDRESS_WriteMask                                      0xFFFFFFFC
#define VPLANE_ADDRESS_ResetValue                                     0x00000000

#define VPLANE_ADDRESS_TYPE                                              31 : 31
#define VPLANE_ADDRESS_TYPE_End                                               31
#define VPLANE_ADDRESS_TYPE_Start                                             31
#define VPLANE_ADDRESS_TYPE_Type                                             U01
#define   VPLANE_ADDRESS_TYPE_SYSTEM                                         0x0
#define   VPLANE_ADDRESS_TYPE_VIRTUAL_SYSTEM                                 0x1

#define VPLANE_ADDRESS_ADDRESS                                            30 : 0
#define VPLANE_ADDRESS_ADDRESS_End                                            30
#define VPLANE_ADDRESS_ADDRESS_Start                                           0
#define VPLANE_ADDRESS_ADDRESS_Type                                          U31

/* Register VPlaneStride **
** ~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source V plane in bytes. */

#define VPlaneStrideRegAddrs                                              0x04A4
#define VPLANE_STRIDE_Address                                            0x01290
#define VPLANE_STRIDE_MSB                                                     15
#define VPLANE_STRIDE_LSB                                                      0
#define VPLANE_STRIDE_BLK                                                      0
#define VPLANE_STRIDE_Count                                                    1
#define VPLANE_STRIDE_FieldMask                                       0x0003FFFF
#define VPLANE_STRIDE_ReadMask                                        0x0003FFFC
#define VPLANE_STRIDE_WriteMask                                       0x0003FFFC
#define VPLANE_STRIDE_ResetValue                                      0x00000000

#define VPLANE_STRIDE_STRIDE                                              17 : 0
#define VPLANE_STRIDE_STRIDE_End                                              17
#define VPLANE_STRIDE_STRIDE_Start                                             0
#define VPLANE_STRIDE_STRIDE_Type                                            U18

/* Register AQVRSourceImageLow **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Bounding box of the source image. */

#define AQVRSourceImageLowRegAddrs                                        0x04A6
#define AQVR_SOURCE_IMAGE_LOW_Address                                    0x01298
#define AQVR_SOURCE_IMAGE_LOW_MSB                                             15
#define AQVR_SOURCE_IMAGE_LOW_LSB                                              0
#define AQVR_SOURCE_IMAGE_LOW_BLK                                              0
#define AQVR_SOURCE_IMAGE_LOW_Count                                            1
#define AQVR_SOURCE_IMAGE_LOW_FieldMask                               0xFFFFFFFF
#define AQVR_SOURCE_IMAGE_LOW_ReadMask                                0xFFFFFFFF
#define AQVR_SOURCE_IMAGE_LOW_WriteMask                               0xFFFFFFFF
#define AQVR_SOURCE_IMAGE_LOW_ResetValue                              0x00000000

#define AQVR_SOURCE_IMAGE_LOW_LEFT                                        15 : 0
#define AQVR_SOURCE_IMAGE_LOW_LEFT_End                                        15
#define AQVR_SOURCE_IMAGE_LOW_LEFT_Start                                       0
#define AQVR_SOURCE_IMAGE_LOW_LEFT_Type                                      U16

#define AQVR_SOURCE_IMAGE_LOW_TOP                                        31 : 16
#define AQVR_SOURCE_IMAGE_LOW_TOP_End                                         31
#define AQVR_SOURCE_IMAGE_LOW_TOP_Start                                       16
#define AQVR_SOURCE_IMAGE_LOW_TOP_Type                                       U16

/* Register AQVRSourceImageHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQVRSourceImageHighRegAddrs                                       0x04A7
#define AQVR_SOURCE_IMAGE_HIGH_Address                                   0x0129C
#define AQVR_SOURCE_IMAGE_HIGH_MSB                                            15
#define AQVR_SOURCE_IMAGE_HIGH_LSB                                             0
#define AQVR_SOURCE_IMAGE_LOW_HIGH_BLK                                         0
#define AQVR_SOURCE_IMAGE_HIGH_Count                                           1
#define AQVR_SOURCE_IMAGE_HIGH_FieldMask                              0xFFFFFFFF
#define AQVR_SOURCE_IMAGE_HIGH_ReadMask                               0xFFFFFFFF
#define AQVR_SOURCE_IMAGE_HIGH_WriteMask                              0xFFFFFFFF
#define AQVR_SOURCE_IMAGE_HIGH_ResetValue                             0x00000000

#define AQVR_SOURCE_IMAGE_HIGH_RIGHT                                      15 : 0
#define AQVR_SOURCE_IMAGE_HIGH_RIGHT_End                                      15
#define AQVR_SOURCE_IMAGE_HIGH_RIGHT_Start                                     0
#define AQVR_SOURCE_IMAGE_HIGH_RIGHT_Type                                    U16

#define AQVR_SOURCE_IMAGE_HIGH_BOTTOM                                    31 : 16
#define AQVR_SOURCE_IMAGE_HIGH_BOTTOM_End                                     31
#define AQVR_SOURCE_IMAGE_HIGH_BOTTOM_Start                                   16
#define AQVR_SOURCE_IMAGE_HIGH_BOTTOM_Type                                   U16

/* Register AQVRSourceOriginLow **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Fractional origin of the source window to be rendered within the source    **
** image.                                                                     */

#define AQVRSourceOriginLowRegAddrs                                       0x04A8
#define AQVR_SOURCE_ORIGIN_LOW_Address                                   0x012A0
#define AQVR_SOURCE_ORIGIN_LOW_MSB                                            15
#define AQVR_SOURCE_ORIGIN_LOW_LSB                                             0
#define AQVR_SOURCE_ORIGIN_LOW_BLK                                             0
#define AQVR_SOURCE_ORIGIN_LOW_Count                                           1
#define AQVR_SOURCE_ORIGIN_LOW_FieldMask                              0xFFFFFFFF
#define AQVR_SOURCE_ORIGIN_LOW_ReadMask                               0xFFFFFFFF
#define AQVR_SOURCE_ORIGIN_LOW_WriteMask                              0xFFFFFFFF
#define AQVR_SOURCE_ORIGIN_LOW_ResetValue                             0x00000000

#define AQVR_SOURCE_ORIGIN_LOW_X                                          31 : 0
#define AQVR_SOURCE_ORIGIN_LOW_X_End                                          31
#define AQVR_SOURCE_ORIGIN_LOW_X_Start                                         0
#define AQVR_SOURCE_ORIGIN_LOW_X_Type                                        U32

/* Register AQVRSourceOriginHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQVRSourceOriginHighRegAddrs                                      0x04A9
#define AQVR_SOURCE_ORIGIN_HIGH_Address                                  0x012A4
#define AQVR_SOURCE_ORIGIN_HIGH_MSB                                           15
#define AQVR_SOURCE_ORIGIN_HIGH_LSB                                            0
#define AQVR_SOURCE_ORIGIN_LOW_HIGH_BLK                                        0
#define AQVR_SOURCE_ORIGIN_HIGH_Count                                          1
#define AQVR_SOURCE_ORIGIN_HIGH_FieldMask                             0xFFFFFFFF
#define AQVR_SOURCE_ORIGIN_HIGH_ReadMask                              0xFFFFFFFF
#define AQVR_SOURCE_ORIGIN_HIGH_WriteMask                             0xFFFFFFFF
#define AQVR_SOURCE_ORIGIN_HIGH_ResetValue                            0x00000000

#define AQVR_SOURCE_ORIGIN_HIGH_Y                                         31 : 0
#define AQVR_SOURCE_ORIGIN_HIGH_Y_End                                         31
#define AQVR_SOURCE_ORIGIN_HIGH_Y_Start                                        0
#define AQVR_SOURCE_ORIGIN_HIGH_Y_Type                                       U32

/* Register AQVRTargetWindowLow **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Bounding box of the destination window to be rendered within the           **
** destination image.                                                         */

#define AQVRTargetWindowLowRegAddrs                                       0x04AA
#define AQVR_TARGET_WINDOW_LOW_Address                                   0x012A8
#define AQVR_TARGET_WINDOW_LOW_MSB                                            15
#define AQVR_TARGET_WINDOW_LOW_LSB                                             0
#define AQVR_TARGET_WINDOW_LOW_BLK                                             0
#define AQVR_TARGET_WINDOW_LOW_Count                                           1
#define AQVR_TARGET_WINDOW_LOW_FieldMask                              0xFFFFFFFF
#define AQVR_TARGET_WINDOW_LOW_ReadMask                               0xFFFFFFFF
#define AQVR_TARGET_WINDOW_LOW_WriteMask                              0xFFFFFFFF
#define AQVR_TARGET_WINDOW_LOW_ResetValue                             0x00000000

#define AQVR_TARGET_WINDOW_LOW_LEFT                                       15 : 0
#define AQVR_TARGET_WINDOW_LOW_LEFT_End                                       15
#define AQVR_TARGET_WINDOW_LOW_LEFT_Start                                      0
#define AQVR_TARGET_WINDOW_LOW_LEFT_Type                                     U16

#define AQVR_TARGET_WINDOW_LOW_TOP                                       31 : 16
#define AQVR_TARGET_WINDOW_LOW_TOP_End                                        31
#define AQVR_TARGET_WINDOW_LOW_TOP_Start                                      16
#define AQVR_TARGET_WINDOW_LOW_TOP_Type                                      U16

/* Register AQVRTargetWindowHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQVRTargetWindowHighRegAddrs                                      0x04AB
#define AQVR_TARGET_WINDOW_HIGH_Address                                  0x012AC
#define AQVR_TARGET_WINDOW_HIGH_MSB                                           15
#define AQVR_TARGET_WINDOW_HIGH_LSB                                            0
#define AQVR_TARGET_WINDOW_LOW_HIGH_BLK                                        0
#define AQVR_TARGET_WINDOW_HIGH_Count                                          1
#define AQVR_TARGET_WINDOW_HIGH_FieldMask                             0xFFFFFFFF
#define AQVR_TARGET_WINDOW_HIGH_ReadMask                              0xFFFFFFFF
#define AQVR_TARGET_WINDOW_HIGH_WriteMask                             0xFFFFFFFF
#define AQVR_TARGET_WINDOW_HIGH_ResetValue                            0x00000000

#define AQVR_TARGET_WINDOW_HIGH_RIGHT                                     15 : 0
#define AQVR_TARGET_WINDOW_HIGH_RIGHT_End                                     15
#define AQVR_TARGET_WINDOW_HIGH_RIGHT_Start                                    0
#define AQVR_TARGET_WINDOW_HIGH_RIGHT_Type                                   U16

#define AQVR_TARGET_WINDOW_HIGH_BOTTOM                                   31 : 16
#define AQVR_TARGET_WINDOW_HIGH_BOTTOM_End                                    31
#define AQVR_TARGET_WINDOW_HIGH_BOTTOM_Start                                  16
#define AQVR_TARGET_WINDOW_HIGH_BOTTOM_Type                                  U16

/* Register AQVRConfig **
** ~~~~~~~~~~~~~~~~~~~ */

/* Video Rasterizer kick-off register. */

#define AQVRConfigRegAddrs                                                0x04A5
#define AQVR_CONFIG_Address                                              0x01294
#define AQVR_CONFIG_MSB                                                       15
#define AQVR_CONFIG_LSB                                                        0
#define AQVR_CONFIG_BLK                                                        0
#define AQVR_CONFIG_Count                                                      1
#define AQVR_CONFIG_FieldMask                                         0x0000000B
#define AQVR_CONFIG_ReadMask                                          0x0000000B
#define AQVR_CONFIG_WriteMask                                         0x0000000B
#define AQVR_CONFIG_ResetValue                                        0x00000000

/* Kick-off command. */
#define AQVR_CONFIG_START                                                  1 : 0
#define AQVR_CONFIG_START_End                                                  1
#define AQVR_CONFIG_START_Start                                                0
#define AQVR_CONFIG_START_Type                                               U02
#define   AQVR_CONFIG_START_HORIZONTAL_BLIT                                  0x0
#define   AQVR_CONFIG_START_VERTICAL_BLIT                                    0x1
#define   AQVR_CONFIG_START_ONE_PASS_BLIT                                    0x2

#define AQVR_CONFIG_MASK_START                                             3 : 3
#define AQVR_CONFIG_MASK_START_End                                             3
#define AQVR_CONFIG_MASK_START_Start                                           3
#define AQVR_CONFIG_MASK_START_Type                                          U01
#define   AQVR_CONFIG_MASK_START_ENABLED                                     0x0
#define   AQVR_CONFIG_MASK_START_MASKED                                      0x1

/* Register AQPEConfig **
** ~~~~~~~~~~~~~~~~~~~ */

/* PE debug register. */

#define AQPEConfigRegAddrs                                                0x04AC
#define AQPE_CONFIG_Address                                              0x012B0
#define AQPE_CONFIG_MSB                                                       15
#define AQPE_CONFIG_LSB                                                        0
#define AQPE_CONFIG_BLK                                                        0
#define AQPE_CONFIG_Count                                                      1
#define AQPE_CONFIG_FieldMask                                         0x0000000B
#define AQPE_CONFIG_ReadMask                                          0x0000000B
#define AQPE_CONFIG_WriteMask                                         0x0000000B
#define AQPE_CONFIG_ResetValue                                        0x00000000

#define AQPE_CONFIG_DESTINATION_FETCH                                      1 : 0
#define AQPE_CONFIG_DESTINATION_FETCH_End                                      1
#define AQPE_CONFIG_DESTINATION_FETCH_Start                                    0
#define AQPE_CONFIG_DESTINATION_FETCH_Type                                   U02
#define   AQPE_CONFIG_DESTINATION_FETCH_DISABLE                              0x0
#define   AQPE_CONFIG_DESTINATION_FETCH_DEFAULT                              0x1
#define   AQPE_CONFIG_DESTINATION_FETCH_ALWAYS                               0x2

#define AQPE_CONFIG_MASK_DESTINATION_FETCH                                 3 : 3
#define AQPE_CONFIG_MASK_DESTINATION_FETCH_End                                 3
#define AQPE_CONFIG_MASK_DESTINATION_FETCH_Start                               3
#define AQPE_CONFIG_MASK_DESTINATION_FETCH_Type                              U01
#define   AQPE_CONFIG_MASK_DESTINATION_FETCH_ENABLED                         0x0
#define   AQPE_CONFIG_MASK_DESTINATION_FETCH_MASKED                          0x1

/* Register AQDEDstRotationHeight **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 180/270 degree rotation configuration for the destination surface. Height  **
** field specifies the height of the surface in pixels.                       */

#define AQDEDstRotationHeightRegAddrs                                     0x04AD
#define AQDE_DST_ROTATION_HEIGHT_Address                                 0x012B4
#define AQDE_DST_ROTATION_HEIGHT_MSB                                          15
#define AQDE_DST_ROTATION_HEIGHT_LSB                                           0
#define AQDE_DST_ROTATION_HEIGHT_BLK                                           0
#define AQDE_DST_ROTATION_HEIGHT_Count                                         1
#define AQDE_DST_ROTATION_HEIGHT_FieldMask                            0x0000FFFF
#define AQDE_DST_ROTATION_HEIGHT_ReadMask                             0x0000FFFF
#define AQDE_DST_ROTATION_HEIGHT_WriteMask                            0x0000FFFF
#define AQDE_DST_ROTATION_HEIGHT_ResetValue                           0x00000000

#define AQDE_DST_ROTATION_HEIGHT_HEIGHT                                   15 : 0
#define AQDE_DST_ROTATION_HEIGHT_HEIGHT_End                                   15
#define AQDE_DST_ROTATION_HEIGHT_HEIGHT_Start                                  0
#define AQDE_DST_ROTATION_HEIGHT_HEIGHT_Type                                 U16

/* Register AQDESrcRotationHeight **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 180/270 degree rotation configuration for the Source surface. Height field **
** specifies the height of the surface in pixels.                             */

#define AQDESrcRotationHeightRegAddrs                                     0x04AE
#define AQDE_SRC_ROTATION_HEIGHT_Address                                 0x012B8
#define AQDE_SRC_ROTATION_HEIGHT_MSB                                          15
#define AQDE_SRC_ROTATION_HEIGHT_LSB                                           0
#define AQDE_SRC_ROTATION_HEIGHT_BLK                                           0
#define AQDE_SRC_ROTATION_HEIGHT_Count                                         1
#define AQDE_SRC_ROTATION_HEIGHT_FieldMask                            0x0000FFFF
#define AQDE_SRC_ROTATION_HEIGHT_ReadMask                             0x0000FFFF
#define AQDE_SRC_ROTATION_HEIGHT_WriteMask                            0x0000FFFF
#define AQDE_SRC_ROTATION_HEIGHT_ResetValue                           0x00000000

#define AQDE_SRC_ROTATION_HEIGHT_HEIGHT                                   15 : 0
#define AQDE_SRC_ROTATION_HEIGHT_HEIGHT_End                                   15
#define AQDE_SRC_ROTATION_HEIGHT_HEIGHT_Start                                  0
#define AQDE_SRC_ROTATION_HEIGHT_HEIGHT_Type                                 U16

/* Register AQDERotAngle **
** ~~~~~~~~~~~~~~~~~~~~~ */

/* 0/90/180/270 degree rotation configuration for the Source surface. Height  **
** field specifies the height of the surface in pixels.                       */

#define AQDERotAngleRegAddrs                                              0x04AF
#define AQDE_ROT_ANGLE_Address                                           0x012BC
#define AQDE_ROT_ANGLE_MSB                                                    15
#define AQDE_ROT_ANGLE_LSB                                                     0
#define AQDE_ROT_ANGLE_BLK                                                     0
#define AQDE_ROT_ANGLE_Count                                                   1
#define AQDE_ROT_ANGLE_FieldMask                                      0x000BB33F
#define AQDE_ROT_ANGLE_ReadMask                                       0x000BB33F
#define AQDE_ROT_ANGLE_WriteMask                                      0x000BB33F
#define AQDE_ROT_ANGLE_ResetValue                                     0x00000000

#define AQDE_ROT_ANGLE_SRC                                                 2 : 0
#define AQDE_ROT_ANGLE_SRC_End                                                 2
#define AQDE_ROT_ANGLE_SRC_Start                                               0
#define AQDE_ROT_ANGLE_SRC_Type                                              U03
#define   AQDE_ROT_ANGLE_SRC_ROT0                                            0x0
#define   AQDE_ROT_ANGLE_SRC_FLIP_X                                          0x1
#define   AQDE_ROT_ANGLE_SRC_FLIP_Y                                          0x2
#define   AQDE_ROT_ANGLE_SRC_ROT90                                           0x4
#define   AQDE_ROT_ANGLE_SRC_ROT180                                          0x5
#define   AQDE_ROT_ANGLE_SRC_ROT270                                          0x6

#define AQDE_ROT_ANGLE_DST                                                 5 : 3
#define AQDE_ROT_ANGLE_DST_End                                                 5
#define AQDE_ROT_ANGLE_DST_Start                                               3
#define AQDE_ROT_ANGLE_DST_Type                                              U03
#define   AQDE_ROT_ANGLE_DST_ROT0                                            0x0
#define   AQDE_ROT_ANGLE_DST_FLIP_X                                          0x1
#define   AQDE_ROT_ANGLE_DST_FLIP_Y                                          0x2
#define   AQDE_ROT_ANGLE_DST_ROT90                                           0x4
#define   AQDE_ROT_ANGLE_DST_ROT180                                          0x5
#define   AQDE_ROT_ANGLE_DST_ROT270                                          0x6

#define AQDE_ROT_ANGLE_MASK_SRC                                            8 : 8
#define AQDE_ROT_ANGLE_MASK_SRC_End                                            8
#define AQDE_ROT_ANGLE_MASK_SRC_Start                                          8
#define AQDE_ROT_ANGLE_MASK_SRC_Type                                         U01
#define   AQDE_ROT_ANGLE_MASK_SRC_ENABLED                                    0x0
#define   AQDE_ROT_ANGLE_MASK_SRC_MASKED                                     0x1

#define AQDE_ROT_ANGLE_MASK_DST                                            9 : 9
#define AQDE_ROT_ANGLE_MASK_DST_End                                            9
#define AQDE_ROT_ANGLE_MASK_DST_Start                                          9
#define AQDE_ROT_ANGLE_MASK_DST_Type                                         U01
#define   AQDE_ROT_ANGLE_MASK_DST_ENABLED                                    0x0
#define   AQDE_ROT_ANGLE_MASK_DST_MASKED                                     0x1

#define AQDE_ROT_ANGLE_SRC_MIRROR                                        13 : 12
#define AQDE_ROT_ANGLE_SRC_MIRROR_End                                         13
#define AQDE_ROT_ANGLE_SRC_MIRROR_Start                                       12
#define AQDE_ROT_ANGLE_SRC_MIRROR_Type                                       U02
#define   AQDE_ROT_ANGLE_SRC_MIRROR_NONE                                     0x0
#define   AQDE_ROT_ANGLE_SRC_MIRROR_MIRROR_X                                 0x1
#define   AQDE_ROT_ANGLE_SRC_MIRROR_MIRROR_Y                                 0x2
#define   AQDE_ROT_ANGLE_SRC_MIRROR_MIRROR_XY                                0x3

#define AQDE_ROT_ANGLE_MASK_SRC_MIRROR                                   15 : 15
#define AQDE_ROT_ANGLE_MASK_SRC_MIRROR_End                                    15
#define AQDE_ROT_ANGLE_MASK_SRC_MIRROR_Start                                  15
#define AQDE_ROT_ANGLE_MASK_SRC_MIRROR_Type                                  U01
#define   AQDE_ROT_ANGLE_MASK_SRC_MIRROR_ENABLED                             0x0
#define   AQDE_ROT_ANGLE_MASK_SRC_MIRROR_MASKED                              0x1

#define AQDE_ROT_ANGLE_DST_MIRROR                                        17 : 16
#define AQDE_ROT_ANGLE_DST_MIRROR_End                                         17
#define AQDE_ROT_ANGLE_DST_MIRROR_Start                                       16
#define AQDE_ROT_ANGLE_DST_MIRROR_Type                                       U02
#define   AQDE_ROT_ANGLE_DST_MIRROR_NONE                                     0x0
#define   AQDE_ROT_ANGLE_DST_MIRROR_MIRROR_X                                 0x1
#define   AQDE_ROT_ANGLE_DST_MIRROR_MIRROR_Y                                 0x2
#define   AQDE_ROT_ANGLE_DST_MIRROR_MIRROR_XY                                0x3

#define AQDE_ROT_ANGLE_MASK_DST_MIRROR                                   19 : 19
#define AQDE_ROT_ANGLE_MASK_DST_MIRROR_End                                    19
#define AQDE_ROT_ANGLE_MASK_DST_MIRROR_Start                                  19
#define AQDE_ROT_ANGLE_MASK_DST_MIRROR_Type                                  U01
#define   AQDE_ROT_ANGLE_MASK_DST_MIRROR_ENABLED                             0x0
#define   AQDE_ROT_ANGLE_MASK_DST_MIRROR_MASKED                              0x1

/* Register AQDEClearPixelValue32 **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* For chips with 2DPE20 feature defined only the lower 32 bits are used and  **
** must be set in A8R8G8B8 format. For older chips where 2DPE20 feature is    **
** not defined this field represents a 64-bit value that combines either two  **
** (for 32-bit destinations) or four (for 16-bit destinations) pixel values   **
** in destination format.                                                     */

#define AQDEClearPixelValue32RegAddrs                                     0x04B0
#define AQDE_CLEAR_PIXEL_VALUE32_Address                                 0x012C0
#define AQDE_CLEAR_PIXEL_VALUE32_MSB                                          15
#define AQDE_CLEAR_PIXEL_VALUE32_LSB                                           0
#define AQDE_CLEAR_PIXEL_VALUE32_BLK                                           0
#define AQDE_CLEAR_PIXEL_VALUE32_Count                                         1
#define AQDE_CLEAR_PIXEL_VALUE32_FieldMask                            0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE32_ReadMask                             0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE32_WriteMask                            0xFFFFFFFF
#define AQDE_CLEAR_PIXEL_VALUE32_ResetValue                           0x00000000

#define AQDE_CLEAR_PIXEL_VALUE32_ALPHA                                   31 : 24
#define AQDE_CLEAR_PIXEL_VALUE32_ALPHA_End                                    31
#define AQDE_CLEAR_PIXEL_VALUE32_ALPHA_Start                                  24
#define AQDE_CLEAR_PIXEL_VALUE32_ALPHA_Type                                  U08

#define AQDE_CLEAR_PIXEL_VALUE32_RED                                     23 : 16
#define AQDE_CLEAR_PIXEL_VALUE32_RED_End                                      23
#define AQDE_CLEAR_PIXEL_VALUE32_RED_Start                                    16
#define AQDE_CLEAR_PIXEL_VALUE32_RED_Type                                    U08

#define AQDE_CLEAR_PIXEL_VALUE32_GREEN                                    15 : 8
#define AQDE_CLEAR_PIXEL_VALUE32_GREEN_End                                    15
#define AQDE_CLEAR_PIXEL_VALUE32_GREEN_Start                                   8
#define AQDE_CLEAR_PIXEL_VALUE32_GREEN_Type                                  U08

#define AQDE_CLEAR_PIXEL_VALUE32_BLUE                                      7 : 0
#define AQDE_CLEAR_PIXEL_VALUE32_BLUE_End                                      7
#define AQDE_CLEAR_PIXEL_VALUE32_BLUE_Start                                    0
#define AQDE_CLEAR_PIXEL_VALUE32_BLUE_Type                                   U08

/* Register AQDEDestColorKey **
** ~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the destination transparency color in destination format.  NOTE:   **
** the register is valid for chips with 2DPE20 feature defined.               */

#define AQDEDestColorKeyRegAddrs                                          0x04B1
#define AQDE_DEST_COLOR_KEY_Address                                      0x012C4
#define AQDE_DEST_COLOR_KEY_MSB                                               15
#define AQDE_DEST_COLOR_KEY_LSB                                                0
#define AQDE_DEST_COLOR_KEY_BLK                                                0
#define AQDE_DEST_COLOR_KEY_Count                                              1
#define AQDE_DEST_COLOR_KEY_FieldMask                                 0xFFFFFFFF
#define AQDE_DEST_COLOR_KEY_ReadMask                                  0xFFFFFFFF
#define AQDE_DEST_COLOR_KEY_WriteMask                                 0xFFFFFFFF
#define AQDE_DEST_COLOR_KEY_ResetValue                                0x00000000

#define AQDE_DEST_COLOR_KEY_ALPHA                                        31 : 24
#define AQDE_DEST_COLOR_KEY_ALPHA_End                                         31
#define AQDE_DEST_COLOR_KEY_ALPHA_Start                                       24
#define AQDE_DEST_COLOR_KEY_ALPHA_Type                                       U08

#define AQDE_DEST_COLOR_KEY_RED                                          23 : 16
#define AQDE_DEST_COLOR_KEY_RED_End                                           23
#define AQDE_DEST_COLOR_KEY_RED_Start                                         16
#define AQDE_DEST_COLOR_KEY_RED_Type                                         U08

#define AQDE_DEST_COLOR_KEY_GREEN                                         15 : 8
#define AQDE_DEST_COLOR_KEY_GREEN_End                                         15
#define AQDE_DEST_COLOR_KEY_GREEN_Start                                        8
#define AQDE_DEST_COLOR_KEY_GREEN_Type                                       U08

#define AQDE_DEST_COLOR_KEY_BLUE                                           7 : 0
#define AQDE_DEST_COLOR_KEY_BLUE_End                                           7
#define AQDE_DEST_COLOR_KEY_BLUE_Start                                         0
#define AQDE_DEST_COLOR_KEY_BLUE_Type                                        U08

/* Register AQDEGlobalSrcColor **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the global source color and alpha values.  NOTE: the register is   **
** valid for chips with 2DPE20 feature defined.                               */

#define AQDEGlobalSrcColorRegAddrs                                        0x04B2
#define AQDE_GLOBAL_SRC_COLOR_Address                                    0x012C8
#define AQDE_GLOBAL_SRC_COLOR_MSB                                             15
#define AQDE_GLOBAL_SRC_COLOR_LSB                                              0
#define AQDE_GLOBAL_SRC_COLOR_BLK                                              0
#define AQDE_GLOBAL_SRC_COLOR_Count                                            1
#define AQDE_GLOBAL_SRC_COLOR_FieldMask                               0xFFFFFFFF
#define AQDE_GLOBAL_SRC_COLOR_ReadMask                                0xFFFFFFFF
#define AQDE_GLOBAL_SRC_COLOR_WriteMask                               0xFFFFFFFF
#define AQDE_GLOBAL_SRC_COLOR_ResetValue                              0x00000000

#define AQDE_GLOBAL_SRC_COLOR_ALPHA                                      31 : 24
#define AQDE_GLOBAL_SRC_COLOR_ALPHA_End                                       31
#define AQDE_GLOBAL_SRC_COLOR_ALPHA_Start                                     24
#define AQDE_GLOBAL_SRC_COLOR_ALPHA_Type                                     U08

#define AQDE_GLOBAL_SRC_COLOR_RED                                        23 : 16
#define AQDE_GLOBAL_SRC_COLOR_RED_End                                         23
#define AQDE_GLOBAL_SRC_COLOR_RED_Start                                       16
#define AQDE_GLOBAL_SRC_COLOR_RED_Type                                       U08

#define AQDE_GLOBAL_SRC_COLOR_GREEN                                       15 : 8
#define AQDE_GLOBAL_SRC_COLOR_GREEN_End                                       15
#define AQDE_GLOBAL_SRC_COLOR_GREEN_Start                                      8
#define AQDE_GLOBAL_SRC_COLOR_GREEN_Type                                     U08

#define AQDE_GLOBAL_SRC_COLOR_BLUE                                         7 : 0
#define AQDE_GLOBAL_SRC_COLOR_BLUE_End                                         7
#define AQDE_GLOBAL_SRC_COLOR_BLUE_Start                                       0
#define AQDE_GLOBAL_SRC_COLOR_BLUE_Type                                      U08

/* Register AQDEGlobalDestColor **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the global destination color and alpha values.  NOTE: the register **
** is valid for chips with 2DPE20 feature defined.                            */

#define AQDEGlobalDestColorRegAddrs                                       0x04B3
#define AQDE_GLOBAL_DEST_COLOR_Address                                   0x012CC
#define AQDE_GLOBAL_DEST_COLOR_MSB                                            15
#define AQDE_GLOBAL_DEST_COLOR_LSB                                             0
#define AQDE_GLOBAL_DEST_COLOR_BLK                                             0
#define AQDE_GLOBAL_DEST_COLOR_Count                                           1
#define AQDE_GLOBAL_DEST_COLOR_FieldMask                              0xFFFFFFFF
#define AQDE_GLOBAL_DEST_COLOR_ReadMask                               0xFFFFFFFF
#define AQDE_GLOBAL_DEST_COLOR_WriteMask                              0xFFFFFFFF
#define AQDE_GLOBAL_DEST_COLOR_ResetValue                             0x00000000

#define AQDE_GLOBAL_DEST_COLOR_ALPHA                                     31 : 24
#define AQDE_GLOBAL_DEST_COLOR_ALPHA_End                                      31
#define AQDE_GLOBAL_DEST_COLOR_ALPHA_Start                                    24
#define AQDE_GLOBAL_DEST_COLOR_ALPHA_Type                                    U08

#define AQDE_GLOBAL_DEST_COLOR_RED                                       23 : 16
#define AQDE_GLOBAL_DEST_COLOR_RED_End                                        23
#define AQDE_GLOBAL_DEST_COLOR_RED_Start                                      16
#define AQDE_GLOBAL_DEST_COLOR_RED_Type                                      U08

#define AQDE_GLOBAL_DEST_COLOR_GREEN                                      15 : 8
#define AQDE_GLOBAL_DEST_COLOR_GREEN_End                                      15
#define AQDE_GLOBAL_DEST_COLOR_GREEN_Start                                     8
#define AQDE_GLOBAL_DEST_COLOR_GREEN_Type                                    U08

#define AQDE_GLOBAL_DEST_COLOR_BLUE                                        7 : 0
#define AQDE_GLOBAL_DEST_COLOR_BLUE_End                                        7
#define AQDE_GLOBAL_DEST_COLOR_BLUE_Start                                      0
#define AQDE_GLOBAL_DEST_COLOR_BLUE_Type                                     U08

/* Register AQDEColorMultiplyModes **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Color modes to multiply Source or Destination pixel color by alpha         **
** channel. Alpha can be from global color source or current pixel.           */

#define AQDEColorMultiplyModesRegAddrs                                    0x04B4
#define AQDE_COLOR_MULTIPLY_MODES_Address                                0x012D0
#define AQDE_COLOR_MULTIPLY_MODES_MSB                                         15
#define AQDE_COLOR_MULTIPLY_MODES_LSB                                          0
#define AQDE_COLOR_MULTIPLY_MODES_BLK                                          0
#define AQDE_COLOR_MULTIPLY_MODES_Count                                        1
#define AQDE_COLOR_MULTIPLY_MODES_FieldMask                           0x00100311
#define AQDE_COLOR_MULTIPLY_MODES_ReadMask                            0x00100311
#define AQDE_COLOR_MULTIPLY_MODES_WriteMask                           0x00100311
#define AQDE_COLOR_MULTIPLY_MODES_ResetValue                          0x00000000

#define AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY                          0 : 0
#define AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_End                          0
#define AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_Start                        0
#define AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_Type                       U01
#define   AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_DISABLE                  0x0
#define   AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_ENABLE                   0x1

#define AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY                          4 : 4
#define AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_End                          4
#define AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_Start                        4
#define AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_Type                       U01
#define   AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_DISABLE                  0x0
#define   AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_ENABLE                   0x1

#define AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY                   9 : 8
#define AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_End                   9
#define AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_Start                 8
#define AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_Type                U02
#define   AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_DISABLE           0x0
#define   AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_ALPHA             0x1
#define   AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_COLOR             0x2

#define AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY                         20 : 20
#define AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_End                          20
#define AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_Start                        20
#define AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_Type                        U01
#define   AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_DISABLE                   0x0
#define   AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_ENABLE                    0x1

/* Register AQPETransparency **
** ~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQPETransparencyRegAddrs                                          0x04B5
#define AQPE_TRANSPARENCY_Address                                        0x012D4
#define AQPE_TRANSPARENCY_MSB                                                 15
#define AQPE_TRANSPARENCY_LSB                                                  0
#define AQPE_TRANSPARENCY_BLK                                                  0
#define AQPE_TRANSPARENCY_Count                                                1
#define AQPE_TRANSPARENCY_FieldMask                                   0xB3331333
#define AQPE_TRANSPARENCY_ReadMask                                    0xB3331333
#define AQPE_TRANSPARENCY_WriteMask                                   0xB3331333
#define AQPE_TRANSPARENCY_ResetValue                                  0x00000000

/* Source transparency mode. NOTE :  the field is valid for chips with 2DPE20 **
** feature defined.                                                           */
#define AQPE_TRANSPARENCY_SOURCE                                           1 : 0
#define AQPE_TRANSPARENCY_SOURCE_End                                           1
#define AQPE_TRANSPARENCY_SOURCE_Start                                         0
#define AQPE_TRANSPARENCY_SOURCE_Type                                        U02
#define   AQPE_TRANSPARENCY_SOURCE_OPAQUE                                    0x0
#define   AQPE_TRANSPARENCY_SOURCE_MASK                                      0x1
#define   AQPE_TRANSPARENCY_SOURCE_KEY                                       0x2

/* Pattern transparency mode. KEY transparency mode is reserved.  NOTE :  the **
** field is valid for chips with 2DPE20 feature defined.                      */
#define AQPE_TRANSPARENCY_PATTERN                                          5 : 4
#define AQPE_TRANSPARENCY_PATTERN_End                                          5
#define AQPE_TRANSPARENCY_PATTERN_Start                                        4
#define AQPE_TRANSPARENCY_PATTERN_Type                                       U02
#define   AQPE_TRANSPARENCY_PATTERN_OPAQUE                                   0x0
#define   AQPE_TRANSPARENCY_PATTERN_MASK                                     0x1
#define   AQPE_TRANSPARENCY_PATTERN_KEY                                      0x2

/* Destination transparency mode. MASK transparency mode is reserved.  NOTE : **
** the field is valid for chips with 2DPE20 feature defined.                  */
#define AQPE_TRANSPARENCY_DESTINATION                                      9 : 8
#define AQPE_TRANSPARENCY_DESTINATION_End                                      9
#define AQPE_TRANSPARENCY_DESTINATION_Start                                    8
#define AQPE_TRANSPARENCY_DESTINATION_Type                                   U02
#define   AQPE_TRANSPARENCY_DESTINATION_OPAQUE                               0x0
#define   AQPE_TRANSPARENCY_DESTINATION_MASK                                 0x1
#define   AQPE_TRANSPARENCY_DESTINATION_KEY                                  0x2

/* Mask field for Source/Pattern/Destination fields. */
#define AQPE_TRANSPARENCY_MASK_TRANSPARENCY                              12 : 12
#define AQPE_TRANSPARENCY_MASK_TRANSPARENCY_End                               12
#define AQPE_TRANSPARENCY_MASK_TRANSPARENCY_Start                             12
#define AQPE_TRANSPARENCY_MASK_TRANSPARENCY_Type                             U01
#define   AQPE_TRANSPARENCY_MASK_TRANSPARENCY_ENABLED                        0x0
#define   AQPE_TRANSPARENCY_MASK_TRANSPARENCY_MASKED                         0x1

/* Source usage override.  NOTE :  the field is valid for chips with 2DPE20   **
** feature defined.                                                           */
#define AQPE_TRANSPARENCY_USE_SRC_OVERRIDE                               17 : 16
#define AQPE_TRANSPARENCY_USE_SRC_OVERRIDE_End                                17
#define AQPE_TRANSPARENCY_USE_SRC_OVERRIDE_Start                              16
#define AQPE_TRANSPARENCY_USE_SRC_OVERRIDE_Type                              U02
#define   AQPE_TRANSPARENCY_USE_SRC_OVERRIDE_DEFAULT                         0x0
#define   AQPE_TRANSPARENCY_USE_SRC_OVERRIDE_USE_ENABLE                      0x1
#define   AQPE_TRANSPARENCY_USE_SRC_OVERRIDE_USE_DISABLE                     0x2

/* Pattern usage override.  NOTE :  the field is valid for chips with 2DPE20  **
** feature defined.                                                           */
#define AQPE_TRANSPARENCY_USE_PAT_OVERRIDE                               21 : 20
#define AQPE_TRANSPARENCY_USE_PAT_OVERRIDE_End                                21
#define AQPE_TRANSPARENCY_USE_PAT_OVERRIDE_Start                              20
#define AQPE_TRANSPARENCY_USE_PAT_OVERRIDE_Type                              U02
#define   AQPE_TRANSPARENCY_USE_PAT_OVERRIDE_DEFAULT                         0x0
#define   AQPE_TRANSPARENCY_USE_PAT_OVERRIDE_USE_ENABLE                      0x1
#define   AQPE_TRANSPARENCY_USE_PAT_OVERRIDE_USE_DISABLE                     0x2

/* Destination usage override.  NOTE :  the field is valid for chips with     **
** 2DPE20 feature defined.                                                    */
#define AQPE_TRANSPARENCY_USE_DST_OVERRIDE                               25 : 24
#define AQPE_TRANSPARENCY_USE_DST_OVERRIDE_End                                25
#define AQPE_TRANSPARENCY_USE_DST_OVERRIDE_Start                              24
#define AQPE_TRANSPARENCY_USE_DST_OVERRIDE_Type                              U02
#define   AQPE_TRANSPARENCY_USE_DST_OVERRIDE_DEFAULT                         0x0
#define   AQPE_TRANSPARENCY_USE_DST_OVERRIDE_USE_ENABLE                      0x1
#define   AQPE_TRANSPARENCY_USE_DST_OVERRIDE_USE_DISABLE                     0x2

/* 2D resource usage override mask field. */
#define AQPE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE                         28 : 28
#define AQPE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_End                          28
#define AQPE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_Start                        28
#define AQPE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_Type                        U01
#define   AQPE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_ENABLED                   0x0
#define   AQPE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_MASKED                    0x1

/* DEB Color Key. */
#define AQPE_TRANSPARENCY_DFB_COLOR_KEY                                  29 : 29
#define AQPE_TRANSPARENCY_DFB_COLOR_KEY_End                                   29
#define AQPE_TRANSPARENCY_DFB_COLOR_KEY_Start                                 29
#define AQPE_TRANSPARENCY_DFB_COLOR_KEY_Type                                 U01
#define   AQPE_TRANSPARENCY_DFB_COLOR_KEY_DISABLED                           0x0
#define   AQPE_TRANSPARENCY_DFB_COLOR_KEY_ENABLED                            0x1

#define AQPE_TRANSPARENCY_MASK_DFB_COLOR_KEY                             31 : 31
#define AQPE_TRANSPARENCY_MASK_DFB_COLOR_KEY_End                              31
#define AQPE_TRANSPARENCY_MASK_DFB_COLOR_KEY_Start                            31
#define AQPE_TRANSPARENCY_MASK_DFB_COLOR_KEY_Type                            U01
#define   AQPE_TRANSPARENCY_MASK_DFB_COLOR_KEY_ENABLED                       0x0
#define   AQPE_TRANSPARENCY_MASK_DFB_COLOR_KEY_MASKED                        0x1

/* Register AQPEControl **
** ~~~~~~~~~~~~~~~~~~~~ */

/* General purpose control register. */

#define AQPEControlRegAddrs                                               0x04B6
#define AQPE_CONTROL_Address                                             0x012D8
#define AQPE_CONTROL_MSB                                                      15
#define AQPE_CONTROL_LSB                                                       0
#define AQPE_CONTROL_BLK                                                       0
#define AQPE_CONTROL_Count                                                     1
#define AQPE_CONTROL_FieldMask                                        0x00000999
#define AQPE_CONTROL_ReadMask                                         0x00000999
#define AQPE_CONTROL_WriteMask                                        0x00000999
#define AQPE_CONTROL_ResetValue                                       0x00000000

#define AQPE_CONTROL_YUV                                                   0 : 0
#define AQPE_CONTROL_YUV_End                                                   0
#define AQPE_CONTROL_YUV_Start                                                 0
#define AQPE_CONTROL_YUV_Type                                                U01
#define   AQPE_CONTROL_YUV_601                                               0x0
#define   AQPE_CONTROL_YUV_709                                               0x1

#define AQPE_CONTROL_MASK_YUV                                              3 : 3
#define AQPE_CONTROL_MASK_YUV_End                                              3
#define AQPE_CONTROL_MASK_YUV_Start                                            3
#define AQPE_CONTROL_MASK_YUV_Type                                           U01
#define   AQPE_CONTROL_MASK_YUV_ENABLED                                      0x0
#define   AQPE_CONTROL_MASK_YUV_MASKED                                       0x1

#define AQPE_CONTROL_UV_SWIZZLE                                            4 : 4
#define AQPE_CONTROL_UV_SWIZZLE_End                                            4
#define AQPE_CONTROL_UV_SWIZZLE_Start                                          4
#define AQPE_CONTROL_UV_SWIZZLE_Type                                         U01
#define   AQPE_CONTROL_UV_SWIZZLE_UV                                         0x0
#define   AQPE_CONTROL_UV_SWIZZLE_VU                                         0x1

#define AQPE_CONTROL_MASK_UV_SWIZZLE                                       7 : 7
#define AQPE_CONTROL_MASK_UV_SWIZZLE_End                                       7
#define AQPE_CONTROL_MASK_UV_SWIZZLE_Start                                     7
#define AQPE_CONTROL_MASK_UV_SWIZZLE_Type                                    U01
#define   AQPE_CONTROL_MASK_UV_SWIZZLE_ENABLED                               0x0
#define   AQPE_CONTROL_MASK_UV_SWIZZLE_MASKED                                0x1

/* YUV to RGB convert enable */
#define AQPE_CONTROL_YUVRGB                                                8 : 8
#define AQPE_CONTROL_YUVRGB_End                                                8
#define AQPE_CONTROL_YUVRGB_Start                                              8
#define AQPE_CONTROL_YUVRGB_Type                                             U01
#define   AQPE_CONTROL_YUVRGB_DISABLED                                       0x0
#define   AQPE_CONTROL_YUVRGB_ENABLED                                        0x1

#define AQPE_CONTROL_MASK_YUVRGB                                         11 : 11
#define AQPE_CONTROL_MASK_YUVRGB_End                                          11
#define AQPE_CONTROL_MASK_YUVRGB_Start                                        11
#define AQPE_CONTROL_MASK_YUVRGB_Type                                        U01
#define   AQPE_CONTROL_MASK_YUVRGB_ENABLED                                   0x0
#define   AQPE_CONTROL_MASK_YUVRGB_MASKED                                    0x1

/* Register AQDESrcColorKeyHigh **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the source transparency color in source format.  NOTE :  the       **
** register is valid for chips with 2DPE20 feature defined.                   */

#define AQDESrcColorKeyHighRegAddrs                                       0x04B7
#define AQDE_SRC_COLOR_KEY_HIGH_Address                                  0x012DC
#define AQDE_SRC_COLOR_KEY_HIGH_MSB                                           15
#define AQDE_SRC_COLOR_KEY_HIGH_LSB                                            0
#define AQDE_SRC_COLOR_KEY_HIGH_BLK                                            0
#define AQDE_SRC_COLOR_KEY_HIGH_Count                                          1
#define AQDE_SRC_COLOR_KEY_HIGH_FieldMask                             0xFFFFFFFF
#define AQDE_SRC_COLOR_KEY_HIGH_ReadMask                              0xFFFFFFFF
#define AQDE_SRC_COLOR_KEY_HIGH_WriteMask                             0xFFFFFFFF
#define AQDE_SRC_COLOR_KEY_HIGH_ResetValue                            0x00000000

#define AQDE_SRC_COLOR_KEY_HIGH_ALPHA                                    31 : 24
#define AQDE_SRC_COLOR_KEY_HIGH_ALPHA_End                                     31
#define AQDE_SRC_COLOR_KEY_HIGH_ALPHA_Start                                   24
#define AQDE_SRC_COLOR_KEY_HIGH_ALPHA_Type                                   U08

#define AQDE_SRC_COLOR_KEY_HIGH_RED                                      23 : 16
#define AQDE_SRC_COLOR_KEY_HIGH_RED_End                                       23
#define AQDE_SRC_COLOR_KEY_HIGH_RED_Start                                     16
#define AQDE_SRC_COLOR_KEY_HIGH_RED_Type                                     U08

#define AQDE_SRC_COLOR_KEY_HIGH_GREEN                                     15 : 8
#define AQDE_SRC_COLOR_KEY_HIGH_GREEN_End                                     15
#define AQDE_SRC_COLOR_KEY_HIGH_GREEN_Start                                    8
#define AQDE_SRC_COLOR_KEY_HIGH_GREEN_Type                                   U08

#define AQDE_SRC_COLOR_KEY_HIGH_BLUE                                       7 : 0
#define AQDE_SRC_COLOR_KEY_HIGH_BLUE_End                                       7
#define AQDE_SRC_COLOR_KEY_HIGH_BLUE_Start                                     0
#define AQDE_SRC_COLOR_KEY_HIGH_BLUE_Type                                    U08

/* Register AQDEDestColorKeyHigh **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the destination transparency color in destination format.  NOTE :  **
** the register is valid for chips with 2DPE20 feature defined.               */

#define AQDEDestColorKeyHighRegAddrs                                      0x04B8
#define AQDE_DEST_COLOR_KEY_HIGH_Address                                 0x012E0
#define AQDE_DEST_COLOR_KEY_HIGH_MSB                                          15
#define AQDE_DEST_COLOR_KEY_HIGH_LSB                                           0
#define AQDE_DEST_COLOR_KEY_HIGH_BLK                                           0
#define AQDE_DEST_COLOR_KEY_HIGH_Count                                         1
#define AQDE_DEST_COLOR_KEY_HIGH_FieldMask                            0xFFFFFFFF
#define AQDE_DEST_COLOR_KEY_HIGH_ReadMask                             0xFFFFFFFF
#define AQDE_DEST_COLOR_KEY_HIGH_WriteMask                            0xFFFFFFFF
#define AQDE_DEST_COLOR_KEY_HIGH_ResetValue                           0x00000000

#define AQDE_DEST_COLOR_KEY_HIGH_ALPHA                                   31 : 24
#define AQDE_DEST_COLOR_KEY_HIGH_ALPHA_End                                    31
#define AQDE_DEST_COLOR_KEY_HIGH_ALPHA_Start                                  24
#define AQDE_DEST_COLOR_KEY_HIGH_ALPHA_Type                                  U08

#define AQDE_DEST_COLOR_KEY_HIGH_RED                                     23 : 16
#define AQDE_DEST_COLOR_KEY_HIGH_RED_End                                      23
#define AQDE_DEST_COLOR_KEY_HIGH_RED_Start                                    16
#define AQDE_DEST_COLOR_KEY_HIGH_RED_Type                                    U08

#define AQDE_DEST_COLOR_KEY_HIGH_GREEN                                    15 : 8
#define AQDE_DEST_COLOR_KEY_HIGH_GREEN_End                                    15
#define AQDE_DEST_COLOR_KEY_HIGH_GREEN_Start                                   8
#define AQDE_DEST_COLOR_KEY_HIGH_GREEN_Type                                  U08

#define AQDE_DEST_COLOR_KEY_HIGH_BLUE                                      7 : 0
#define AQDE_DEST_COLOR_KEY_HIGH_BLUE_End                                      7
#define AQDE_DEST_COLOR_KEY_HIGH_BLUE_Start                                    0
#define AQDE_DEST_COLOR_KEY_HIGH_BLUE_Type                                   U08

/* Register AQVRConfigEx **
** ~~~~~~~~~~~~~~~~~~~~~ */

/* Video Rasterizer configuration register. */

#define AQVRConfigExRegAddrs                                              0x04B9
#define AQVR_CONFIG_EX_Address                                           0x012E4
#define AQVR_CONFIG_EX_MSB                                                    15
#define AQVR_CONFIG_EX_LSB                                                     0
#define AQVR_CONFIG_EX_BLK                                                     0
#define AQVR_CONFIG_EX_Count                                                   1
#define AQVR_CONFIG_EX_FieldMask                                      0x000001FB
#define AQVR_CONFIG_EX_ReadMask                                       0x000001FB
#define AQVR_CONFIG_EX_WriteMask                                      0x000001FB
#define AQVR_CONFIG_EX_ResetValue                                     0x00000000

/* Line width in pixels for vertical pass. */
#define AQVR_CONFIG_EX_VERTICAL_LINE_WIDTH                                 1 : 0
#define AQVR_CONFIG_EX_VERTICAL_LINE_WIDTH_End                                 1
#define AQVR_CONFIG_EX_VERTICAL_LINE_WIDTH_Start                               0
#define AQVR_CONFIG_EX_VERTICAL_LINE_WIDTH_Type                              U02
#define   AQVR_CONFIG_EX_VERTICAL_LINE_WIDTH_AUTO                            0x0
#define   AQVR_CONFIG_EX_VERTICAL_LINE_WIDTH_PIXELS16                        0x1
#define   AQVR_CONFIG_EX_VERTICAL_LINE_WIDTH_PIXELS32                        0x2

#define AQVR_CONFIG_EX_MASK_VERTICAL_LINE_WIDTH                            3 : 3
#define AQVR_CONFIG_EX_MASK_VERTICAL_LINE_WIDTH_End                            3
#define AQVR_CONFIG_EX_MASK_VERTICAL_LINE_WIDTH_Start                          3
#define AQVR_CONFIG_EX_MASK_VERTICAL_LINE_WIDTH_Type                         U01
#define   AQVR_CONFIG_EX_MASK_VERTICAL_LINE_WIDTH_ENABLED                    0x0
#define   AQVR_CONFIG_EX_MASK_VERTICAL_LINE_WIDTH_MASKED                     0x1

/* one pass filter tap. */
#define AQVR_CONFIG_EX_FILTER_TAP                                          7 : 4
#define AQVR_CONFIG_EX_FILTER_TAP_End                                          7
#define AQVR_CONFIG_EX_FILTER_TAP_Start                                        4
#define AQVR_CONFIG_EX_FILTER_TAP_Type                                       U04

#define AQVR_CONFIG_EX_MASK_FILTER_TAP                                     8 : 8
#define AQVR_CONFIG_EX_MASK_FILTER_TAP_End                                     8
#define AQVR_CONFIG_EX_MASK_FILTER_TAP_Start                                   8
#define AQVR_CONFIG_EX_MASK_FILTER_TAP_Type                                  U01
#define   AQVR_CONFIG_EX_MASK_FILTER_TAP_ENABLED                             0x0
#define   AQVR_CONFIG_EX_MASK_FILTER_TAP_MASKED                              0x1

/* Register AQPEDitherLow **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* PE dither register.  If you don't want dither, set all fields to their     **
** reste values.                                                              */

#define AQPEDitherLowRegAddrs                                             0x04BA
#define AQPE_DITHER_LOW_Address                                          0x012E8
#define AQPE_DITHER_LOW_MSB                                                   15
#define AQPE_DITHER_LOW_LSB                                                    0
#define AQPE_DITHER_LOW_BLK                                                    0
#define AQPE_DITHER_LOW_Count                                                  1
#define AQPE_DITHER_LOW_FieldMask                                     0xFFFFFFFF
#define AQPE_DITHER_LOW_ReadMask                                      0xFFFFFFFF
#define AQPE_DITHER_LOW_WriteMask                                     0xFFFFFFFF
#define AQPE_DITHER_LOW_ResetValue                                    0xFFFFFFFF

/* X,Y = 0,0 */
#define AQPE_DITHER_LOW_PIXEL_X0_Y0                                        3 : 0
#define AQPE_DITHER_LOW_PIXEL_X0_Y0_End                                        3
#define AQPE_DITHER_LOW_PIXEL_X0_Y0_Start                                      0
#define AQPE_DITHER_LOW_PIXEL_X0_Y0_Type                                     U04

/* X,Y = 1,0 */
#define AQPE_DITHER_LOW_PIXEL_X1_Y0                                        7 : 4
#define AQPE_DITHER_LOW_PIXEL_X1_Y0_End                                        7
#define AQPE_DITHER_LOW_PIXEL_X1_Y0_Start                                      4
#define AQPE_DITHER_LOW_PIXEL_X1_Y0_Type                                     U04

/* X,Y = 2,0 */
#define AQPE_DITHER_LOW_PIXEL_X2_Y0                                       11 : 8
#define AQPE_DITHER_LOW_PIXEL_X2_Y0_End                                       11
#define AQPE_DITHER_LOW_PIXEL_X2_Y0_Start                                      8
#define AQPE_DITHER_LOW_PIXEL_X2_Y0_Type                                     U04

/* X,Y = 3,0 */
#define AQPE_DITHER_LOW_PIXEL_X3_Y0                                      15 : 12
#define AQPE_DITHER_LOW_PIXEL_X3_Y0_End                                       15
#define AQPE_DITHER_LOW_PIXEL_X3_Y0_Start                                     12
#define AQPE_DITHER_LOW_PIXEL_X3_Y0_Type                                     U04

/* X,Y = 0,1 */
#define AQPE_DITHER_LOW_PIXEL_X0_Y1                                      19 : 16
#define AQPE_DITHER_LOW_PIXEL_X0_Y1_End                                       19
#define AQPE_DITHER_LOW_PIXEL_X0_Y1_Start                                     16
#define AQPE_DITHER_LOW_PIXEL_X0_Y1_Type                                     U04

/* X,Y = 1,1 */
#define AQPE_DITHER_LOW_PIXEL_X1_Y1                                      23 : 20
#define AQPE_DITHER_LOW_PIXEL_X1_Y1_End                                       23
#define AQPE_DITHER_LOW_PIXEL_X1_Y1_Start                                     20
#define AQPE_DITHER_LOW_PIXEL_X1_Y1_Type                                     U04

/* X,Y = 2,1 */
#define AQPE_DITHER_LOW_PIXEL_X2_Y1                                      27 : 24
#define AQPE_DITHER_LOW_PIXEL_X2_Y1_End                                       27
#define AQPE_DITHER_LOW_PIXEL_X2_Y1_Start                                     24
#define AQPE_DITHER_LOW_PIXEL_X2_Y1_Type                                     U04

/* X,Y = 3,1 */
#define AQPE_DITHER_LOW_PIXEL_X3_Y1                                      31 : 28
#define AQPE_DITHER_LOW_PIXEL_X3_Y1_End                                       31
#define AQPE_DITHER_LOW_PIXEL_X3_Y1_Start                                     28
#define AQPE_DITHER_LOW_PIXEL_X3_Y1_Type                                     U04

/* Register AQPEDitherHigh **
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQPEDitherHighRegAddrs                                            0x04BB
#define AQPE_DITHER_HIGH_Address                                         0x012EC
#define AQPE_DITHER_HIGH_MSB                                                  15
#define AQPE_DITHER_HIGH_LSB                                                   0
#define AQPE_DITHER_LOW_HIGH_BLK                                               0
#define AQPE_DITHER_HIGH_Count                                                 1
#define AQPE_DITHER_HIGH_FieldMask                                    0xFFFFFFFF
#define AQPE_DITHER_HIGH_ReadMask                                     0xFFFFFFFF
#define AQPE_DITHER_HIGH_WriteMask                                    0xFFFFFFFF
#define AQPE_DITHER_HIGH_ResetValue                                   0xFFFFFFFF

/* X,Y = 0,2 */
#define AQPE_DITHER_HIGH_PIXEL_X0_Y2                                       3 : 0
#define AQPE_DITHER_HIGH_PIXEL_X0_Y2_End                                       3
#define AQPE_DITHER_HIGH_PIXEL_X0_Y2_Start                                     0
#define AQPE_DITHER_HIGH_PIXEL_X0_Y2_Type                                    U04

/* X,Y = 1,2 */
#define AQPE_DITHER_HIGH_PIXEL_X1_Y2                                       7 : 4
#define AQPE_DITHER_HIGH_PIXEL_X1_Y2_End                                       7
#define AQPE_DITHER_HIGH_PIXEL_X1_Y2_Start                                     4
#define AQPE_DITHER_HIGH_PIXEL_X1_Y2_Type                                    U04

/* X,Y = 2,2 */
#define AQPE_DITHER_HIGH_PIXEL_X2_Y2                                      11 : 8
#define AQPE_DITHER_HIGH_PIXEL_X2_Y2_End                                      11
#define AQPE_DITHER_HIGH_PIXEL_X2_Y2_Start                                     8
#define AQPE_DITHER_HIGH_PIXEL_X2_Y2_Type                                    U04

/* X,Y = 0,3 */
#define AQPE_DITHER_HIGH_PIXEL_X3_Y2                                     15 : 12
#define AQPE_DITHER_HIGH_PIXEL_X3_Y2_End                                      15
#define AQPE_DITHER_HIGH_PIXEL_X3_Y2_Start                                    12
#define AQPE_DITHER_HIGH_PIXEL_X3_Y2_Type                                    U04

/* X,Y = 1,3 */
#define AQPE_DITHER_HIGH_PIXEL_X0_Y3                                     19 : 16
#define AQPE_DITHER_HIGH_PIXEL_X0_Y3_End                                      19
#define AQPE_DITHER_HIGH_PIXEL_X0_Y3_Start                                    16
#define AQPE_DITHER_HIGH_PIXEL_X0_Y3_Type                                    U04

/* X,Y = 2,3 */
#define AQPE_DITHER_HIGH_PIXEL_X1_Y3                                     23 : 20
#define AQPE_DITHER_HIGH_PIXEL_X1_Y3_End                                      23
#define AQPE_DITHER_HIGH_PIXEL_X1_Y3_Start                                    20
#define AQPE_DITHER_HIGH_PIXEL_X1_Y3_Type                                    U04

/* X,Y = 3,3 */
#define AQPE_DITHER_HIGH_PIXEL_X2_Y3                                     27 : 24
#define AQPE_DITHER_HIGH_PIXEL_X2_Y3_End                                      27
#define AQPE_DITHER_HIGH_PIXEL_X2_Y3_Start                                    24
#define AQPE_DITHER_HIGH_PIXEL_X2_Y3_Type                                    U04

/* X,Y = 3,2 */
#define AQPE_DITHER_HIGH_PIXEL_X3_Y3                                     31 : 28
#define AQPE_DITHER_HIGH_PIXEL_X3_Y3_End                                      31
#define AQPE_DITHER_HIGH_PIXEL_X3_Y3_Start                                    28
#define AQPE_DITHER_HIGH_PIXEL_X3_Y3_Type                                    U04

/* Register AQDEHoriFilterKernel (128 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* One Pass filter Filter blit hori coefficient table. */

#define AQDEHoriFilterKernelRegAddrs                                      0x0A00
#define AQDE_HORI_FILTER_KERNEL_Address                                  0x02800
#define AQDE_HORI_FILTER_KERNEL_MSB                                           15
#define AQDE_HORI_FILTER_KERNEL_LSB                                            7
#define AQDE_HORI_FILTER_KERNEL_BLK                                            7
#define AQDE_HORI_FILTER_KERNEL_Count                                        128
#define AQDE_HORI_FILTER_KERNEL_FieldMask                             0xFFFFFFFF
#define AQDE_HORI_FILTER_KERNEL_ReadMask                              0xFFFFFFFF
#define AQDE_HORI_FILTER_KERNEL_WriteMask                             0xFFFFFFFF
#define AQDE_HORI_FILTER_KERNEL_ResetValue                            0x00000000

#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT0                              15 : 0
#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT0_End                              15
#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT0_Start                             0
#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT0_Type                            U16

#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT1                             31 : 16
#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT1_End                              31
#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT1_Start                            16
#define AQDE_HORI_FILTER_KERNEL_COEFFICIENT1_Type                            U16

/* Register AQDEVertiFilterKernel (128 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* One Pass Filter blit vertical coefficient table. */

#define AQDEVertiFilterKernelRegAddrs                                     0x0A80
#define AQDE_VERTI_FILTER_KERNEL_Address                                 0x02A00
#define AQDE_VERTI_FILTER_KERNEL_MSB                                          15
#define AQDE_VERTI_FILTER_KERNEL_LSB                                           7
#define AQDE_VERTI_FILTER_KERNEL_BLK                                           7
#define AQDE_VERTI_FILTER_KERNEL_Count                                       128
#define AQDE_VERTI_FILTER_KERNEL_FieldMask                            0xFFFFFFFF
#define AQDE_VERTI_FILTER_KERNEL_ReadMask                             0xFFFFFFFF
#define AQDE_VERTI_FILTER_KERNEL_WriteMask                            0xFFFFFFFF
#define AQDE_VERTI_FILTER_KERNEL_ResetValue                           0x00000000

#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT0                             15 : 0
#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT0_End                             15
#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT0_Start                            0
#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT0_Type                           U16

#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT1                            31 : 16
#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT1_End                             31
#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT1_Start                           16
#define AQDE_VERTI_FILTER_KERNEL_COEFFICIENT1_Type                           U16

/* Register AQBWConfig **
** ~~~~~~~~~~~~~~~~~~~ */
#define AQBWConfigRegAddrs                                                0x04BC
#define AQBW_CONFIG_Address                                              0x012F0
#define AQBW_CONFIG_MSB                                                       15
#define AQBW_CONFIG_LSB                                                        0
#define AQBW_CONFIG_BLK                                                        0
#define AQBW_CONFIG_Count                                                      1
#define AQBW_CONFIG_FieldMask                                         0x00009999
#define AQBW_CONFIG_ReadMask                                          0x00009999
#define AQBW_CONFIG_WriteMask                                         0x00009999
#define AQBW_CONFIG_ResetValue                                        0x00000000

/* One Pass Filter Block Config. */
#define AQBW_CONFIG_BLOCK_CONFIG                                           0 : 0
#define AQBW_CONFIG_BLOCK_CONFIG_End                                           0
#define AQBW_CONFIG_BLOCK_CONFIG_Start                                         0
#define AQBW_CONFIG_BLOCK_CONFIG_Type                                        U01
#define   AQBW_CONFIG_BLOCK_CONFIG_AUTO                                      0x0
#define   AQBW_CONFIG_BLOCK_CONFIG_CUSTOMIZE                                 0x1

#define AQBW_CONFIG_MASK_BLOCK_CONFIG                                      3 : 3
#define AQBW_CONFIG_MASK_BLOCK_CONFIG_End                                      3
#define AQBW_CONFIG_MASK_BLOCK_CONFIG_Start                                    3
#define AQBW_CONFIG_MASK_BLOCK_CONFIG_Type                                   U01
#define   AQBW_CONFIG_MASK_BLOCK_CONFIG_ENABLED                              0x0
#define   AQBW_CONFIG_MASK_BLOCK_CONFIG_MASKED                               0x1

/* block walk direction in one pass filter blit. */
#define AQBW_CONFIG_BLOCK_WALK_DIRECTION                                   4 : 4
#define AQBW_CONFIG_BLOCK_WALK_DIRECTION_End                                   4
#define AQBW_CONFIG_BLOCK_WALK_DIRECTION_Start                                 4
#define AQBW_CONFIG_BLOCK_WALK_DIRECTION_Type                                U01
#define   AQBW_CONFIG_BLOCK_WALK_DIRECTION_RIGHT_BOTTOM                      0x0
#define   AQBW_CONFIG_BLOCK_WALK_DIRECTION_BOTTOM_RIGHT                      0x1

#define AQBW_CONFIG_MASK_BLOCK_WALK_DIRECTION                              7 : 7
#define AQBW_CONFIG_MASK_BLOCK_WALK_DIRECTION_End                              7
#define AQBW_CONFIG_MASK_BLOCK_WALK_DIRECTION_Start                            7
#define AQBW_CONFIG_MASK_BLOCK_WALK_DIRECTION_Type                           U01
#define   AQBW_CONFIG_MASK_BLOCK_WALK_DIRECTION_ENABLED                      0x0
#define   AQBW_CONFIG_MASK_BLOCK_WALK_DIRECTION_MASKED                       0x1

/* block walk direction in one pass filter blit. */
#define AQBW_CONFIG_TILE_WALK_DIRECTION                                    8 : 8
#define AQBW_CONFIG_TILE_WALK_DIRECTION_End                                    8
#define AQBW_CONFIG_TILE_WALK_DIRECTION_Start                                  8
#define AQBW_CONFIG_TILE_WALK_DIRECTION_Type                                 U01
#define   AQBW_CONFIG_TILE_WALK_DIRECTION_RIGHT_BOTTOM                       0x0
#define   AQBW_CONFIG_TILE_WALK_DIRECTION_BOTTOM_RIGHT                       0x1

#define AQBW_CONFIG_MASK_TILE_WALK_DIRECTION                             11 : 11
#define AQBW_CONFIG_MASK_TILE_WALK_DIRECTION_End                              11
#define AQBW_CONFIG_MASK_TILE_WALK_DIRECTION_Start                            11
#define AQBW_CONFIG_MASK_TILE_WALK_DIRECTION_Type                            U01
#define   AQBW_CONFIG_MASK_TILE_WALK_DIRECTION_ENABLED                       0x0
#define   AQBW_CONFIG_MASK_TILE_WALK_DIRECTION_MASKED                        0x1

/* block walk direction in one pass filter blit. */
#define AQBW_CONFIG_PIXEL_WALK_DIRECTION                                 12 : 12
#define AQBW_CONFIG_PIXEL_WALK_DIRECTION_End                                  12
#define AQBW_CONFIG_PIXEL_WALK_DIRECTION_Start                                12
#define AQBW_CONFIG_PIXEL_WALK_DIRECTION_Type                                U01
#define   AQBW_CONFIG_PIXEL_WALK_DIRECTION_RIGHT_BOTTOM                      0x0
#define   AQBW_CONFIG_PIXEL_WALK_DIRECTION_BOTTOM_RIGHT                      0x1

#define AQBW_CONFIG_MASK_PIXEL_WALK_DIRECTION                            15 : 15
#define AQBW_CONFIG_MASK_PIXEL_WALK_DIRECTION_End                             15
#define AQBW_CONFIG_MASK_PIXEL_WALK_DIRECTION_Start                           15
#define AQBW_CONFIG_MASK_PIXEL_WALK_DIRECTION_Type                           U01
#define   AQBW_CONFIG_MASK_PIXEL_WALK_DIRECTION_ENABLED                      0x0
#define   AQBW_CONFIG_MASK_PIXEL_WALK_DIRECTION_MASKED                       0x1

/* Register AQBWBlockSize **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* Walker Block size. */

#define AQBWBlockSizeRegAddrs                                             0x04BD
#define AQBW_BLOCK_SIZE_Address                                          0x012F4
#define AQBW_BLOCK_SIZE_MSB                                                   15
#define AQBW_BLOCK_SIZE_LSB                                                    0
#define AQBW_BLOCK_SIZE_BLK                                                    0
#define AQBW_BLOCK_SIZE_Count                                                  1
#define AQBW_BLOCK_SIZE_FieldMask                                     0xFFFFFFFF
#define AQBW_BLOCK_SIZE_ReadMask                                      0xFFFFFFFF
#define AQBW_BLOCK_SIZE_WriteMask                                     0xFFFFFFFF
#define AQBW_BLOCK_SIZE_ResetValue                                    0x00000000

#define AQBW_BLOCK_SIZE_WIDTH                                             15 : 0
#define AQBW_BLOCK_SIZE_WIDTH_End                                             15
#define AQBW_BLOCK_SIZE_WIDTH_Start                                            0
#define AQBW_BLOCK_SIZE_WIDTH_Type                                           U16

#define AQBW_BLOCK_SIZE_HEIGHT                                           31 : 16
#define AQBW_BLOCK_SIZE_HEIGHT_End                                            31
#define AQBW_BLOCK_SIZE_HEIGHT_Start                                          16
#define AQBW_BLOCK_SIZE_HEIGHT_Type                                          U16

/* Register AQBWTileSize **
** ~~~~~~~~~~~~~~~~~~~~~ */

/* Walker tile size. */

#define AQBWTileSizeRegAddrs                                              0x04BE
#define AQBW_TILE_SIZE_Address                                           0x012F8
#define AQBW_TILE_SIZE_MSB                                                    15
#define AQBW_TILE_SIZE_LSB                                                     0
#define AQBW_TILE_SIZE_BLK                                                     0
#define AQBW_TILE_SIZE_Count                                                   1
#define AQBW_TILE_SIZE_FieldMask                                      0xFFFFFFFF
#define AQBW_TILE_SIZE_ReadMask                                       0xFFFFFFFF
#define AQBW_TILE_SIZE_WriteMask                                      0xFFFFFFFF
#define AQBW_TILE_SIZE_ResetValue                                     0x00000000

#define AQBW_TILE_SIZE_WIDTH                                              15 : 0
#define AQBW_TILE_SIZE_WIDTH_End                                              15
#define AQBW_TILE_SIZE_WIDTH_Start                                             0
#define AQBW_TILE_SIZE_WIDTH_Type                                            U16

#define AQBW_TILE_SIZE_HEIGHT                                            31 : 16
#define AQBW_TILE_SIZE_HEIGHT_End                                             31
#define AQBW_TILE_SIZE_HEIGHT_Start                                           16
#define AQBW_TILE_SIZE_HEIGHT_Type                                           U16

/* Register AQBWBlockMask **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* Walker Block Mask. */

#define AQBWBlockMaskRegAddrs                                             0x04BF
#define AQBW_BLOCK_MASK_Address                                          0x012FC
#define AQBW_BLOCK_MASK_MSB                                                   15
#define AQBW_BLOCK_MASK_LSB                                                    0
#define AQBW_BLOCK_MASK_BLK                                                    0
#define AQBW_BLOCK_MASK_Count                                                  1
#define AQBW_BLOCK_MASK_FieldMask                                     0xFFFFFFFF
#define AQBW_BLOCK_MASK_ReadMask                                      0xFFFFFFFF
#define AQBW_BLOCK_MASK_WriteMask                                     0xFFFFFFFF
#define AQBW_BLOCK_MASK_ResetValue                                    0x00000000

#define AQBW_BLOCK_MASK_HORIZONTAL                                        15 : 0
#define AQBW_BLOCK_MASK_HORIZONTAL_End                                        15
#define AQBW_BLOCK_MASK_HORIZONTAL_Start                                       0
#define AQBW_BLOCK_MASK_HORIZONTAL_Type                                      U16

#define AQBW_BLOCK_MASK_VERTICAL                                         31 : 16
#define AQBW_BLOCK_MASK_VERTICAL_End                                          31
#define AQBW_BLOCK_MASK_VERTICAL_Start                                        16
#define AQBW_BLOCK_MASK_VERTICAL_Type                                        U16

/* Register AQDESrcExConfig **
** ~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQDESrcExConfigRegAddrs                                           0x04C0
#define AQDE_SRC_EX_CONFIG_Address                                       0x01300
#define AQDE_SRC_EX_CONFIG_MSB                                                15
#define AQDE_SRC_EX_CONFIG_LSB                                                 0
#define AQDE_SRC_EX_CONFIG_BLK                                                 0
#define AQDE_SRC_EX_CONFIG_Count                                               1
#define AQDE_SRC_EX_CONFIG_FieldMask                                  0x00000109
#define AQDE_SRC_EX_CONFIG_ReadMask                                   0x00000109
#define AQDE_SRC_EX_CONFIG_WriteMask                                  0x00000109
#define AQDE_SRC_EX_CONFIG_ResetValue                                 0x00000000

/* Source multi tiled address computation control. */
#define AQDE_SRC_EX_CONFIG_MULTI_TILED                                     0 : 0
#define AQDE_SRC_EX_CONFIG_MULTI_TILED_End                                     0
#define AQDE_SRC_EX_CONFIG_MULTI_TILED_Start                                   0
#define AQDE_SRC_EX_CONFIG_MULTI_TILED_Type                                  U01
#define   AQDE_SRC_EX_CONFIG_MULTI_TILED_DISABLED                            0x0
#define   AQDE_SRC_EX_CONFIG_MULTI_TILED_ENABLED                             0x1

/* Source super tiled address computation control. */
#define AQDE_SRC_EX_CONFIG_SUPER_TILED                                     3 : 3
#define AQDE_SRC_EX_CONFIG_SUPER_TILED_End                                     3
#define AQDE_SRC_EX_CONFIG_SUPER_TILED_Start                                   3
#define AQDE_SRC_EX_CONFIG_SUPER_TILED_Type                                  U01
#define   AQDE_SRC_EX_CONFIG_SUPER_TILED_DISABLED                            0x0
#define   AQDE_SRC_EX_CONFIG_SUPER_TILED_ENABLED                             0x1

/* Source super tiled address computation control. */
#define AQDE_SRC_EX_CONFIG_MINOR_TILED                                     8 : 8
#define AQDE_SRC_EX_CONFIG_MINOR_TILED_End                                     8
#define AQDE_SRC_EX_CONFIG_MINOR_TILED_Start                                   8
#define AQDE_SRC_EX_CONFIG_MINOR_TILED_Type                                  U01
#define   AQDE_SRC_EX_CONFIG_MINOR_TILED_DISABLED                            0x0
#define   AQDE_SRC_EX_CONFIG_MINOR_TILED_ENABLED                             0x1

/* Register AQDESrcExAddress **
** ~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source extra surface. */

#define AQDESrcExAddressRegAddrs                                          0x04C1
#define AQDE_SRC_EX_ADDRESS_Address                                      0x01304
#define AQDE_SRC_EX_ADDRESS_MSB                                               15
#define AQDE_SRC_EX_ADDRESS_LSB                                                0
#define AQDE_SRC_EX_ADDRESS_BLK                                                0
#define AQDE_SRC_EX_ADDRESS_Count                                              1
#define AQDE_SRC_EX_ADDRESS_FieldMask                                 0xFFFFFFFF
#define AQDE_SRC_EX_ADDRESS_ReadMask                                  0xFFFFFFFC
#define AQDE_SRC_EX_ADDRESS_WriteMask                                 0xFFFFFFFC
#define AQDE_SRC_EX_ADDRESS_ResetValue                                0x00000000

#define AQDE_SRC_EX_ADDRESS_TYPE                                         31 : 31
#define AQDE_SRC_EX_ADDRESS_TYPE_End                                          31
#define AQDE_SRC_EX_ADDRESS_TYPE_Start                                        31
#define AQDE_SRC_EX_ADDRESS_TYPE_Type                                        U01
#define   AQDE_SRC_EX_ADDRESS_TYPE_SYSTEM                                    0x0
#define   AQDE_SRC_EX_ADDRESS_TYPE_VIRTUAL_SYSTEM                            0x1

#define AQDE_SRC_EX_ADDRESS_ADDRESS                                       30 : 0
#define AQDE_SRC_EX_ADDRESS_ADDRESS_End                                       30
#define AQDE_SRC_EX_ADDRESS_ADDRESS_Start                                      0
#define AQDE_SRC_EX_ADDRESS_ADDRESS_Type                                     U31

/* Register gcregDEMultiSource **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* MutiSource control register. */

#define gcregDEMultiSourceRegAddrs                                        0x04C2
#define GCREG_DE_MULTI_SOURCE_Address                                    0x01308
#define GCREG_DE_MULTI_SOURCE_MSB                                             15
#define GCREG_DE_MULTI_SOURCE_LSB                                              0
#define GCREG_DE_MULTI_SOURCE_BLK                                              0
#define GCREG_DE_MULTI_SOURCE_Count                                            1
#define GCREG_DE_MULTI_SOURCE_FieldMask                               0x00070707
#define GCREG_DE_MULTI_SOURCE_ReadMask                                0x00070707
#define GCREG_DE_MULTI_SOURCE_WriteMask                               0x00070707
#define GCREG_DE_MULTI_SOURCE_ResetValue                              0x00000000

/* Number of source surfaces minus 1. */
#define GCREG_DE_MULTI_SOURCE_MAX_SOURCE                                   2 : 0
#define GCREG_DE_MULTI_SOURCE_MAX_SOURCE_End                                   2
#define GCREG_DE_MULTI_SOURCE_MAX_SOURCE_Start                                 0
#define GCREG_DE_MULTI_SOURCE_MAX_SOURCE_Type                                U03

/* Number of pixels for horizontal block walker. */
#define GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK                            10 : 8
#define GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_End                            10
#define GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_Start                           8
#define GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_Type                          U03
#define   GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_PIXEL16                     0x0
#define   GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_PIXEL32                     0x1
#define   GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_PIXEL64                     0x2
#define   GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_PIXEL128                    0x3
#define   GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_PIXEL256                    0x4
#define   GCREG_DE_MULTI_SOURCE_HORIZONTAL_BLOCK_PIXEL512                    0x5

/* Number of lines for vertical block walker. */
#define GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK                             18 : 16
#define GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_End                              18
#define GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_Start                            16
#define GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_Type                            U03
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE1                         0x0
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE2                         0x1
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE4                         0x2
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE8                         0x3
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE16                        0x4
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE32                        0x5
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE64                        0x6
#define   GCREG_DE_MULTI_SOURCE_VERTICAL_BLOCK_LINE128                       0x7

/* Register gcregDEYUVConversion **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Configure the YUV to YUV conversion. */

#define gcregDEYUVConversionRegAddrs                                      0x04C3
#define GCREG_DEYUV_CONVERSION_Address                                   0x0130C
#define GCREG_DEYUV_CONVERSION_MSB                                            15
#define GCREG_DEYUV_CONVERSION_LSB                                             0
#define GCREG_DEYUV_CONVERSION_BLK                                             0
#define GCREG_DEYUV_CONVERSION_Count                                           1
#define GCREG_DEYUV_CONVERSION_FieldMask                              0xFFFFFFFF
#define GCREG_DEYUV_CONVERSION_ReadMask                               0xFFFFFFFF
#define GCREG_DEYUV_CONVERSION_WriteMask                              0xFFFFFFFF
#define GCREG_DEYUV_CONVERSION_ResetValue                             0x00000000

/* Select the number of planes we need to process. */
#define GCREG_DEYUV_CONVERSION_ENABLE                                      1 : 0
#define GCREG_DEYUV_CONVERSION_ENABLE_End                                      1
#define GCREG_DEYUV_CONVERSION_ENABLE_Start                                    0
#define GCREG_DEYUV_CONVERSION_ENABLE_Type                                   U02
/* YUV to YUV conversion is turned off. */
#define   GCREG_DEYUV_CONVERSION_ENABLE_OFF                                  0x0
/* YUV to YUV conversion is writing to 1 plane. */
#define   GCREG_DEYUV_CONVERSION_ENABLE_PLANE1                               0x1
/* YUV to YUV conversion is writing to 2 planes. */
#define   GCREG_DEYUV_CONVERSION_ENABLE_PLANE2                               0x2
/* YUV to YUV conversion is writing to 3 planes. */
#define   GCREG_DEYUV_CONVERSION_ENABLE_PLANE3                               0x3

/* Number of channels to process - 1 for plane 1. */
#define GCREG_DEYUV_CONVERSION_PLANE1_COUNT                                3 : 2
#define GCREG_DEYUV_CONVERSION_PLANE1_COUNT_End                                3
#define GCREG_DEYUV_CONVERSION_PLANE1_COUNT_Start                              2
#define GCREG_DEYUV_CONVERSION_PLANE1_COUNT_Type                             U02

/* Number of channels to process - 1 for plane 2. */
#define GCREG_DEYUV_CONVERSION_PLANE2_COUNT                                5 : 4
#define GCREG_DEYUV_CONVERSION_PLANE2_COUNT_End                                5
#define GCREG_DEYUV_CONVERSION_PLANE2_COUNT_Start                              4
#define GCREG_DEYUV_CONVERSION_PLANE2_COUNT_Type                             U02

/* Number of channels to process - 1 for plane 3. */
#define GCREG_DEYUV_CONVERSION_PLANE3_COUNT                                7 : 6
#define GCREG_DEYUV_CONVERSION_PLANE3_COUNT_End                                7
#define GCREG_DEYUV_CONVERSION_PLANE3_COUNT_Start                              6
#define GCREG_DEYUV_CONVERSION_PLANE3_COUNT_Type                             U02

/* Select which color channel to pick for B channel for plane 1. */
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B                            9 : 8
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B_End                            9
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B_Start                          8
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_B_ALPHA                      0x3

/* Select which color channel to pick for G channel for plane 1. */
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G                          11 : 10
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G_End                           11
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G_Start                         10
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_G_ALPHA                      0x3

/* Select which color channel to pick for R channel for plane 1. */
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R                          13 : 12
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R_End                           13
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R_Start                         12
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_R_ALPHA                      0x3

/* Select which color channel to pick for A channel for plane 1. */
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A                          15 : 14
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A_End                           15
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A_Start                         14
#define GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE1_SWIZZLE_A_ALPHA                      0x3

/* Select which color channel to pick for B channel for plane 2. */
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B                          17 : 16
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B_End                           17
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B_Start                         16
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_B_ALPHA                      0x3

/* Select which color channel to pick for G channel for plane 2. */
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G                          19 : 18
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G_End                           19
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G_Start                         18
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_G_ALPHA                      0x3

/* Select which color channel to pick for R channel for plane 2. */
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R                          21 : 20
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R_End                           21
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R_Start                         20
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_R_ALPHA                      0x3

/* Select which color channel to pick for A channel for plane 2. */
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A                          23 : 22
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A_End                           23
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A_Start                         22
#define GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE2_SWIZZLE_A_ALPHA                      0x3

/* Select which color channel to pick for B channel for plane 3. */
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B                          25 : 24
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B_End                           25
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B_Start                         24
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_B_ALPHA                      0x3

/* Select which color channel to pick for G channel for plane 3. */
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G                          27 : 26
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G_End                           27
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G_Start                         26
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_G_ALPHA                      0x3

/* Select which color channel to pick for R channel for plane 3. */
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R                          29 : 28
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R_End                           29
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R_Start                         28
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_R_ALPHA                      0x3

/* Select which color channel to pick for A channel for plane 3. */
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A                          31 : 30
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A_End                           31
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A_Start                         30
#define GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A_Type                         U02
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A_BLUE                       0x0
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A_GREEN                      0x1
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A_RED                        0x2
#define   GCREG_DEYUV_CONVERSION_PLANE3_SWIZZLE_A_ALPHA                      0x3

/* Register gcregDEPlane2Address **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Address for plane 2 if gcregDEYUVConversion.Enable is set to Plane2 or     **
** Plane3.                                                                    */

#define gcregDEPlane2AddressRegAddrs                                      0x04C4
#define GCREG_DE_PLANE2_ADDRESS_Address                                  0x01310
#define GCREG_DE_PLANE2_ADDRESS_MSB                                           15
#define GCREG_DE_PLANE2_ADDRESS_LSB                                            0
#define GCREG_DE_PLANE2_ADDRESS_BLK                                            0
#define GCREG_DE_PLANE2_ADDRESS_Count                                          1
#define GCREG_DE_PLANE2_ADDRESS_FieldMask                             0xFFFFFFFF
#define GCREG_DE_PLANE2_ADDRESS_ReadMask                              0xFFFFFFFC
#define GCREG_DE_PLANE2_ADDRESS_WriteMask                             0xFFFFFFFC
#define GCREG_DE_PLANE2_ADDRESS_ResetValue                            0x00000000

#define GCREG_DE_PLANE2_ADDRESS_TYPE                                     31 : 31
#define GCREG_DE_PLANE2_ADDRESS_TYPE_End                                      31
#define GCREG_DE_PLANE2_ADDRESS_TYPE_Start                                    31
#define GCREG_DE_PLANE2_ADDRESS_TYPE_Type                                    U01
#define   GCREG_DE_PLANE2_ADDRESS_TYPE_SYSTEM                                0x0
#define   GCREG_DE_PLANE2_ADDRESS_TYPE_VIRTUAL_SYSTEM                        0x1

#define GCREG_DE_PLANE2_ADDRESS_ADDRESS                                   30 : 0
#define GCREG_DE_PLANE2_ADDRESS_ADDRESS_End                                   30
#define GCREG_DE_PLANE2_ADDRESS_ADDRESS_Start                                  0
#define GCREG_DE_PLANE2_ADDRESS_ADDRESS_Type                                 U31

/* Register gcregDEPlane2Stride **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride for plane 2 if gcregDEYUVConversion.Enable is set to Plane2 or      **
** Plane3.                                                                    */

#define gcregDEPlane2StrideRegAddrs                                       0x04C5
#define GCREG_DE_PLANE2_STRIDE_Address                                   0x01314
#define GCREG_DE_PLANE2_STRIDE_MSB                                            15
#define GCREG_DE_PLANE2_STRIDE_LSB                                             0
#define GCREG_DE_PLANE2_STRIDE_BLK                                             0
#define GCREG_DE_PLANE2_STRIDE_Count                                           1
#define GCREG_DE_PLANE2_STRIDE_FieldMask                              0x0003FFFF
#define GCREG_DE_PLANE2_STRIDE_ReadMask                               0x0003FFFC
#define GCREG_DE_PLANE2_STRIDE_WriteMask                              0x0003FFFC
#define GCREG_DE_PLANE2_STRIDE_ResetValue                             0x00000000

#define GCREG_DE_PLANE2_STRIDE_STRIDE                                     17 : 0
#define GCREG_DE_PLANE2_STRIDE_STRIDE_End                                     17
#define GCREG_DE_PLANE2_STRIDE_STRIDE_Start                                    0
#define GCREG_DE_PLANE2_STRIDE_STRIDE_Type                                   U18

/* Register gcregDEPlane3Address **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Address for plane 3 if gcregDEYUVConversion.Enable is set to Plane3. */

#define gcregDEPlane3AddressRegAddrs                                      0x04C6
#define GCREG_DE_PLANE3_ADDRESS_Address                                  0x01318
#define GCREG_DE_PLANE3_ADDRESS_MSB                                           15
#define GCREG_DE_PLANE3_ADDRESS_LSB                                            0
#define GCREG_DE_PLANE3_ADDRESS_BLK                                            0
#define GCREG_DE_PLANE3_ADDRESS_Count                                          1
#define GCREG_DE_PLANE3_ADDRESS_FieldMask                             0xFFFFFFFF
#define GCREG_DE_PLANE3_ADDRESS_ReadMask                              0xFFFFFFFC
#define GCREG_DE_PLANE3_ADDRESS_WriteMask                             0xFFFFFFFC
#define GCREG_DE_PLANE3_ADDRESS_ResetValue                            0x00000000

#define GCREG_DE_PLANE3_ADDRESS_TYPE                                     31 : 31
#define GCREG_DE_PLANE3_ADDRESS_TYPE_End                                      31
#define GCREG_DE_PLANE3_ADDRESS_TYPE_Start                                    31
#define GCREG_DE_PLANE3_ADDRESS_TYPE_Type                                    U01
#define   GCREG_DE_PLANE3_ADDRESS_TYPE_SYSTEM                                0x0
#define   GCREG_DE_PLANE3_ADDRESS_TYPE_VIRTUAL_SYSTEM                        0x1

#define GCREG_DE_PLANE3_ADDRESS_ADDRESS                                   30 : 0
#define GCREG_DE_PLANE3_ADDRESS_ADDRESS_End                                   30
#define GCREG_DE_PLANE3_ADDRESS_ADDRESS_Start                                  0
#define GCREG_DE_PLANE3_ADDRESS_ADDRESS_Type                                 U31

/* Register gcregDEPlane3Stride **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride for plane 3 if gcregDEYUVConversion.Enable is set to Plane3. */

#define gcregDEPlane3StrideRegAddrs                                       0x04C7
#define GCREG_DE_PLANE3_STRIDE_Address                                   0x0131C
#define GCREG_DE_PLANE3_STRIDE_MSB                                            15
#define GCREG_DE_PLANE3_STRIDE_LSB                                             0
#define GCREG_DE_PLANE3_STRIDE_BLK                                             0
#define GCREG_DE_PLANE3_STRIDE_Count                                           1
#define GCREG_DE_PLANE3_STRIDE_FieldMask                              0x0003FFFF
#define GCREG_DE_PLANE3_STRIDE_ReadMask                               0x0003FFFC
#define GCREG_DE_PLANE3_STRIDE_WriteMask                              0x0003FFFC
#define GCREG_DE_PLANE3_STRIDE_ResetValue                             0x00000000

#define GCREG_DE_PLANE3_STRIDE_STRIDE                                     17 : 0
#define GCREG_DE_PLANE3_STRIDE_STRIDE_End                                     17
#define GCREG_DE_PLANE3_STRIDE_STRIDE_Start                                    0
#define GCREG_DE_PLANE3_STRIDE_STRIDE_Type                                   U18

/* Register gcregDEStallDE **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stall de. */

#define gcregDEStallDERegAddrs                                            0x04C8
#define GCREG_DE_STALL_DE_Address                                        0x01320
#define GCREG_DE_STALL_DE_MSB                                                 15
#define GCREG_DE_STALL_DE_LSB                                                  0
#define GCREG_DE_STALL_DE_BLK                                                  0
#define GCREG_DE_STALL_DE_Count                                                1
#define GCREG_DE_STALL_DE_FieldMask                                   0x00000001
#define GCREG_DE_STALL_DE_ReadMask                                    0x00000001
#define GCREG_DE_STALL_DE_WriteMask                                   0x00000001
#define GCREG_DE_STALL_DE_ResetValue                                  0x00000000

/* Stall de enable. */
#define GCREG_DE_STALL_DE_ENABLE                                           0 : 0
#define GCREG_DE_STALL_DE_ENABLE_End                                           0
#define GCREG_DE_STALL_DE_ENABLE_Start                                         0
#define GCREG_DE_STALL_DE_ENABLE_Type                                        U01
#define   GCREG_DE_STALL_DE_ENABLE_DISABLED                                  0x0
#define   GCREG_DE_STALL_DE_ENABLE_ENABLED                                   0x1

/* Register gcregDEPatternColor (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Pattern Color. 32-bit Pattern Color. */

#define gcregDEPatternColorRegAddrs                                       0x04CC
#define GCREG_DE_PATTERN_COLOR_Address                                   0x01330
#define GCREG_DE_PATTERN_COLOR_MSB                                            15
#define GCREG_DE_PATTERN_COLOR_LSB                                             2
#define GCREG_DE_PATTERN_COLOR_BLK                                             2
#define GCREG_DE_PATTERN_COLOR_Count                                           4
#define GCREG_DE_PATTERN_COLOR_FieldMask                              0xFFFFFFFF
#define GCREG_DE_PATTERN_COLOR_ReadMask                               0xFFFFFFFF
#define GCREG_DE_PATTERN_COLOR_WriteMask                              0xFFFFFFFF
#define GCREG_DE_PATTERN_COLOR_ResetValue                             0x00000000

#define GCREG_DE_PATTERN_COLOR_ALPHA                                     31 : 24
#define GCREG_DE_PATTERN_COLOR_ALPHA_End                                      31
#define GCREG_DE_PATTERN_COLOR_ALPHA_Start                                    24
#define GCREG_DE_PATTERN_COLOR_ALPHA_Type                                    U08

#define GCREG_DE_PATTERN_COLOR_RED                                       23 : 16
#define GCREG_DE_PATTERN_COLOR_RED_End                                        23
#define GCREG_DE_PATTERN_COLOR_RED_Start                                      16
#define GCREG_DE_PATTERN_COLOR_RED_Type                                      U08

#define GCREG_DE_PATTERN_COLOR_GREEN                                      15 : 8
#define GCREG_DE_PATTERN_COLOR_GREEN_End                                      15
#define GCREG_DE_PATTERN_COLOR_GREEN_Start                                     8
#define GCREG_DE_PATTERN_COLOR_GREEN_Type                                    U08

#define GCREG_DE_PATTERN_COLOR_BLUE                                        7 : 0
#define GCREG_DE_PATTERN_COLOR_BLUE_End                                        7
#define GCREG_DE_PATTERN_COLOR_BLUE_Start                                      0
#define GCREG_DE_PATTERN_COLOR_BLUE_Type                                     U08

/*******************************************************************************
**                            ~~~~~~~~~~~~~~~~~~~~                            **
**                            Module DEMultiSource                            **
**                            ~~~~~~~~~~~~~~~~~~~~                            **
*******************************************************************************/

/* Register gcregDESrcAddress (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source surface. */

#define gcregDESrcAddressRegAddrs                                         0x4A00
#define GCREG_DE_SRC_ADDRESS_Address                                     0x12800
#define GCREG_DE_SRC_ADDRESS_MSB                                              15
#define GCREG_DE_SRC_ADDRESS_LSB                                               2
#define GCREG_DE_SRC_ADDRESS_BLK                                               0
#define GCREG_DE_SRC_ADDRESS_Count                                             4
#define GCREG_DE_SRC_ADDRESS_FieldMask                                0xFFFFFFFF
#define GCREG_DE_SRC_ADDRESS_ReadMask                                 0xFFFFFFFC
#define GCREG_DE_SRC_ADDRESS_WriteMask                                0xFFFFFFFC
#define GCREG_DE_SRC_ADDRESS_ResetValue                               0x00000000

#define GCREG_DE_SRC_ADDRESS_TYPE                                        31 : 31
#define GCREG_DE_SRC_ADDRESS_TYPE_End                                         31
#define GCREG_DE_SRC_ADDRESS_TYPE_Start                                       31
#define GCREG_DE_SRC_ADDRESS_TYPE_Type                                       U01
#define   GCREG_DE_SRC_ADDRESS_TYPE_SYSTEM                                   0x0
#define   GCREG_DE_SRC_ADDRESS_TYPE_VIRTUAL_SYSTEM                           0x1

#define GCREG_DE_SRC_ADDRESS_ADDRESS                                      30 : 0
#define GCREG_DE_SRC_ADDRESS_ADDRESS_End                                      30
#define GCREG_DE_SRC_ADDRESS_ADDRESS_Start                                     0
#define GCREG_DE_SRC_ADDRESS_ADDRESS_Type                                    U31

/* Register gcregDESrcStride (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source surface in bytes. To calculate the stride multiply    **
** the surface width in pixels by the number of  bytes per pixel.             */

#define gcregDESrcStrideRegAddrs                                          0x4A04
#define GCREG_DE_SRC_STRIDE_Address                                      0x12810
#define GCREG_DE_SRC_STRIDE_MSB                                               15
#define GCREG_DE_SRC_STRIDE_LSB                                                2
#define GCREG_DE_SRC_STRIDE_BLK                                                0
#define GCREG_DE_SRC_STRIDE_Count                                              4
#define GCREG_DE_SRC_STRIDE_FieldMask                                 0x0003FFFF
#define GCREG_DE_SRC_STRIDE_ReadMask                                  0x0003FFFC
#define GCREG_DE_SRC_STRIDE_WriteMask                                 0x0003FFFC
#define GCREG_DE_SRC_STRIDE_ResetValue                                0x00000000

#define GCREG_DE_SRC_STRIDE_STRIDE                                        17 : 0
#define GCREG_DE_SRC_STRIDE_STRIDE_End                                        17
#define GCREG_DE_SRC_STRIDE_STRIDE_Start                                       0
#define GCREG_DE_SRC_STRIDE_STRIDE_Type                                      U18

/* Register gcregDESrcRotationConfig (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 90 degree rotation configuration for the source surface. Width field       **
** specifies the width of the surface in pixels.                              */

#define gcregDESrcRotationConfigRegAddrs                                  0x4A08
#define GCREG_DE_SRC_ROTATION_CONFIG_Address                             0x12820
#define GCREG_DE_SRC_ROTATION_CONFIG_MSB                                      15
#define GCREG_DE_SRC_ROTATION_CONFIG_LSB                                       2
#define GCREG_DE_SRC_ROTATION_CONFIG_BLK                                       0
#define GCREG_DE_SRC_ROTATION_CONFIG_Count                                     4
#define GCREG_DE_SRC_ROTATION_CONFIG_FieldMask                        0x0001FFFF
#define GCREG_DE_SRC_ROTATION_CONFIG_ReadMask                         0x0001FFFF
#define GCREG_DE_SRC_ROTATION_CONFIG_WriteMask                        0x0001FFFF
#define GCREG_DE_SRC_ROTATION_CONFIG_ResetValue                       0x00000000

#define GCREG_DE_SRC_ROTATION_CONFIG_WIDTH                                15 : 0
#define GCREG_DE_SRC_ROTATION_CONFIG_WIDTH_End                                15
#define GCREG_DE_SRC_ROTATION_CONFIG_WIDTH_Start                               0
#define GCREG_DE_SRC_ROTATION_CONFIG_WIDTH_Type                              U16

#define GCREG_DE_SRC_ROTATION_CONFIG_ROTATION                            16 : 16
#define GCREG_DE_SRC_ROTATION_CONFIG_ROTATION_End                             16
#define GCREG_DE_SRC_ROTATION_CONFIG_ROTATION_Start                           16
#define GCREG_DE_SRC_ROTATION_CONFIG_ROTATION_Type                           U01
#define   GCREG_DE_SRC_ROTATION_CONFIG_ROTATION_NORMAL                       0x0
#define   GCREG_DE_SRC_ROTATION_CONFIG_ROTATION_ROTATED                      0x1

/* Register gcregDESrcConfig (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Source surface configuration register. */

#define gcregDESrcConfigRegAddrs                                          0x4A0C
#define GCREG_DE_SRC_CONFIG_Address                                      0x12830
#define GCREG_DE_SRC_CONFIG_MSB                                               15
#define GCREG_DE_SRC_CONFIG_LSB                                                2
#define GCREG_DE_SRC_CONFIG_BLK                                                0
#define GCREG_DE_SRC_CONFIG_Count                                              4
#define GCREG_DE_SRC_CONFIG_FieldMask                                 0xDF30B1C0
#define GCREG_DE_SRC_CONFIG_ReadMask                                  0xDF30B1C0
#define GCREG_DE_SRC_CONFIG_WriteMask                                 0xDF30B1C0
#define GCREG_DE_SRC_CONFIG_ResetValue                                0x00000000

/* Control source endianess. */
#define GCREG_DE_SRC_CONFIG_ENDIAN_CONTROL                               31 : 30
#define GCREG_DE_SRC_CONFIG_ENDIAN_CONTROL_End                                31
#define GCREG_DE_SRC_CONFIG_ENDIAN_CONTROL_Start                              30
#define GCREG_DE_SRC_CONFIG_ENDIAN_CONTROL_Type                              U02
#define   GCREG_DE_SRC_CONFIG_ENDIAN_CONTROL_NO_SWAP                         0x0
#define   GCREG_DE_SRC_CONFIG_ENDIAN_CONTROL_SWAP_WORD                       0x1
#define   GCREG_DE_SRC_CONFIG_ENDIAN_CONTROL_SWAP_DWORD                      0x2

/* Defines the pixel format of the source surface. */
#define GCREG_DE_SRC_CONFIG_SOURCE_FORMAT                                28 : 24
#define GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_End                                 28
#define GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_Start                               24
#define GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_Type                               U05
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_X4R4G4B4                        0x00
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A4R4G4B4                        0x01
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_X1R5G5B5                        0x02
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A1R5G5B5                        0x03
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_R5G6B5                          0x04
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_X8R8G8B8                        0x05
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8                        0x06
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_YUY2                            0x07
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_UYVY                            0x08
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_INDEX8                          0x09
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_MONOCHROME                      0x0A
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_YV12                            0x0F
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8                              0x10
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_NV12                            0x11
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_NV16                            0x12
#define   GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_RG16                            0x13

/* Color channel swizzles. */
#define GCREG_DE_SRC_CONFIG_SWIZZLE                                      21 : 20
#define GCREG_DE_SRC_CONFIG_SWIZZLE_End                                       21
#define GCREG_DE_SRC_CONFIG_SWIZZLE_Start                                     20
#define GCREG_DE_SRC_CONFIG_SWIZZLE_Type                                     U02
#define   GCREG_DE_SRC_CONFIG_SWIZZLE_ARGB                                   0x0
#define   GCREG_DE_SRC_CONFIG_SWIZZLE_RGBA                                   0x1
#define   GCREG_DE_SRC_CONFIG_SWIZZLE_ABGR                                   0x2
#define   GCREG_DE_SRC_CONFIG_SWIZZLE_BGRA                                   0x3

/* Mono expansion :if 0, transparency color will be 0, otherwise transparency **
** color will be 1.                                                           */
#define GCREG_DE_SRC_CONFIG_MONO_TRANSPARENCY                            15 : 15
#define GCREG_DE_SRC_CONFIG_MONO_TRANSPARENCY_End                             15
#define GCREG_DE_SRC_CONFIG_MONO_TRANSPARENCY_Start                           15
#define GCREG_DE_SRC_CONFIG_MONO_TRANSPARENCY_Type                           U01
#define   GCREG_DE_SRC_CONFIG_MONO_TRANSPARENCY_BACKGROUND                   0x0
#define   GCREG_DE_SRC_CONFIG_MONO_TRANSPARENCY_FOREGROUND                   0x1

/* Mono expansion or masked blit :  stream packing in pixels. Determines how  **
** many horizontal pixels are there per each 32-bit chunk. For example, if    **
** set to Packed8, each 32-bit chunk is 8-pixel wide, which also means that   **
** it defines 4 vertical lines of pixels.                                     */
#define GCREG_DE_SRC_CONFIG_PACK                                         13 : 12
#define GCREG_DE_SRC_CONFIG_PACK_End                                          13
#define GCREG_DE_SRC_CONFIG_PACK_Start                                        12
#define GCREG_DE_SRC_CONFIG_PACK_Type                                        U02
#define   GCREG_DE_SRC_CONFIG_PACK_PACKED8                                   0x0
#define   GCREG_DE_SRC_CONFIG_PACK_PACKED16                                  0x1
#define   GCREG_DE_SRC_CONFIG_PACK_PACKED32                                  0x2
#define   GCREG_DE_SRC_CONFIG_PACK_UNPACKED                                  0x3

/* Source data location :  set to STREAM for mono expansion blits or masked   **
** blits. For mono expansion blits the complete bitmap comes from the command **
** stream. For masked blits the source data comes from the memory and the     **
** mask from the command stream.                                              */
#define GCREG_DE_SRC_CONFIG_LOCATION                                       8 : 8
#define GCREG_DE_SRC_CONFIG_LOCATION_End                                       8
#define GCREG_DE_SRC_CONFIG_LOCATION_Start                                     8
#define GCREG_DE_SRC_CONFIG_LOCATION_Type                                    U01
#define   GCREG_DE_SRC_CONFIG_LOCATION_MEMORY                                0x0
#define   GCREG_DE_SRC_CONFIG_LOCATION_STREAM                                0x1

/* Source linear/tiled address computation control. */
#define GCREG_DE_SRC_CONFIG_TILED                                          7 : 7
#define GCREG_DE_SRC_CONFIG_TILED_End                                          7
#define GCREG_DE_SRC_CONFIG_TILED_Start                                        7
#define GCREG_DE_SRC_CONFIG_TILED_Type                                       U01
#define   GCREG_DE_SRC_CONFIG_TILED_DISABLED                                 0x0
#define   GCREG_DE_SRC_CONFIG_TILED_ENABLED                                  0x1

/* If set to ABSOLUTE, the source coordinates are treated as absolute         **
** coordinates inside the source surface. If set to RELATIVE, the source      **
** coordinates are treated as the offsets from the destination coordinates    **
** with the source size equal to the size of the destination.                 */
#define GCREG_DE_SRC_CONFIG_SRC_RELATIVE                                   6 : 6
#define GCREG_DE_SRC_CONFIG_SRC_RELATIVE_End                                   6
#define GCREG_DE_SRC_CONFIG_SRC_RELATIVE_Start                                 6
#define GCREG_DE_SRC_CONFIG_SRC_RELATIVE_Type                                U01
#define   GCREG_DE_SRC_CONFIG_SRC_RELATIVE_ABSOLUTE                          0x0
#define   GCREG_DE_SRC_CONFIG_SRC_RELATIVE_RELATIVE                          0x1

/* Register gcregDESrcOrigin (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Absolute or relative (see SRC_RELATIVE field of gcregDESrcConfig register) **
** X and Y coordinates in pixels of the top left corner of the source         **
** rectangle within the source surface.                                       */

#define gcregDESrcOriginRegAddrs                                          0x4A10
#define GCREG_DE_SRC_ORIGIN_Address                                      0x12840
#define GCREG_DE_SRC_ORIGIN_MSB                                               15
#define GCREG_DE_SRC_ORIGIN_LSB                                                2
#define GCREG_DE_SRC_ORIGIN_BLK                                                0
#define GCREG_DE_SRC_ORIGIN_Count                                              4
#define GCREG_DE_SRC_ORIGIN_FieldMask                                 0xFFFFFFFF
#define GCREG_DE_SRC_ORIGIN_ReadMask                                  0xFFFFFFFF
#define GCREG_DE_SRC_ORIGIN_WriteMask                                 0xFFFFFFFF
#define GCREG_DE_SRC_ORIGIN_ResetValue                                0x00000000

#define GCREG_DE_SRC_ORIGIN_Y                                            31 : 16
#define GCREG_DE_SRC_ORIGIN_Y_End                                             31
#define GCREG_DE_SRC_ORIGIN_Y_Start                                           16
#define GCREG_DE_SRC_ORIGIN_Y_Type                                           U16

#define GCREG_DE_SRC_ORIGIN_X                                             15 : 0
#define GCREG_DE_SRC_ORIGIN_X_End                                             15
#define GCREG_DE_SRC_ORIGIN_X_Start                                            0
#define GCREG_DE_SRC_ORIGIN_X_Type                                           U16

/* Register gcregDESrcSize (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Width and height of the source rectangle in pixels. If the source is       **
** relative (see SRC_RELATIVE field of gcregDESrcConfig register) or a        **
** regular bitblt is being performed without stretching, this register is     **
** ignored and the source size is assumed to be the same as the destination.  */

#define gcregDESrcSizeRegAddrs                                            0x4A14
#define GCREG_DE_SRC_SIZE_Address                                        0x12850
#define GCREG_DE_SRC_SIZE_MSB                                                 15
#define GCREG_DE_SRC_SIZE_LSB                                                  2
#define GCREG_DE_SRC_SIZE_BLK                                                  0
#define GCREG_DE_SRC_SIZE_Count                                                4
#define GCREG_DE_SRC_SIZE_FieldMask                                   0xFFFFFFFF
#define GCREG_DE_SRC_SIZE_ReadMask                                    0xFFFFFFFF
#define GCREG_DE_SRC_SIZE_WriteMask                                   0xFFFFFFFF
#define GCREG_DE_SRC_SIZE_ResetValue                                  0x00000000

#define GCREG_DE_SRC_SIZE_Y                                              31 : 16
#define GCREG_DE_SRC_SIZE_Y_End                                               31
#define GCREG_DE_SRC_SIZE_Y_Start                                             16
#define GCREG_DE_SRC_SIZE_Y_Type                                             U16

#define GCREG_DE_SRC_SIZE_X                                               15 : 0
#define GCREG_DE_SRC_SIZE_X_End                                               15
#define GCREG_DE_SRC_SIZE_X_Start                                              0
#define GCREG_DE_SRC_SIZE_X_Type                                             U16

/* Register gcregDESrcColorBg (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Select the color where source becomes transparent. It must be programmed   **
** in A8R8G8B8 format.                                                        */

#define gcregDESrcColorBgRegAddrs                                         0x4A18
#define GCREG_DE_SRC_COLOR_BG_Address                                    0x12860
#define GCREG_DE_SRC_COLOR_BG_MSB                                             15
#define GCREG_DE_SRC_COLOR_BG_LSB                                              2
#define GCREG_DE_SRC_COLOR_BG_BLK                                              0
#define GCREG_DE_SRC_COLOR_BG_Count                                            4
#define GCREG_DE_SRC_COLOR_BG_FieldMask                               0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_BG_ReadMask                                0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_BG_WriteMask                               0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_BG_ResetValue                              0x00000000

#define GCREG_DE_SRC_COLOR_BG_ALPHA                                      31 : 24
#define GCREG_DE_SRC_COLOR_BG_ALPHA_End                                       31
#define GCREG_DE_SRC_COLOR_BG_ALPHA_Start                                     24
#define GCREG_DE_SRC_COLOR_BG_ALPHA_Type                                     U08

#define GCREG_DE_SRC_COLOR_BG_RED                                        23 : 16
#define GCREG_DE_SRC_COLOR_BG_RED_End                                         23
#define GCREG_DE_SRC_COLOR_BG_RED_Start                                       16
#define GCREG_DE_SRC_COLOR_BG_RED_Type                                       U08

#define GCREG_DE_SRC_COLOR_BG_GREEN                                       15 : 8
#define GCREG_DE_SRC_COLOR_BG_GREEN_End                                       15
#define GCREG_DE_SRC_COLOR_BG_GREEN_Start                                      8
#define GCREG_DE_SRC_COLOR_BG_GREEN_Type                                     U08

#define GCREG_DE_SRC_COLOR_BG_BLUE                                         7 : 0
#define GCREG_DE_SRC_COLOR_BG_BLUE_End                                         7
#define GCREG_DE_SRC_COLOR_BG_BLUE_Start                                       0
#define GCREG_DE_SRC_COLOR_BG_BLUE_Type                                      U08

/* Register gcregDERop (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Raster operation foreground and background codes. Even though ROP is not   **
** used in CLEAR, HOR_FILTER_BLT, VER_FILTER_BLT and alpha-eanbled BIT_BLTs,  **
** ROP code still has to be programmed, because the engine makes the decision **
** whether source, destination and pattern are involved in the current        **
** operation and the correct decision is essential for the engine to complete **
** the operation as expected.                                                 */

#define gcregDERopRegAddrs                                                0x4A1C
#define GCREG_DE_ROP_Address                                             0x12870
#define GCREG_DE_ROP_MSB                                                      15
#define GCREG_DE_ROP_LSB                                                       2
#define GCREG_DE_ROP_BLK                                                       0
#define GCREG_DE_ROP_Count                                                     4
#define GCREG_DE_ROP_FieldMask                                        0x0030FFFF
#define GCREG_DE_ROP_ReadMask                                         0x0030FFFF
#define GCREG_DE_ROP_WriteMask                                        0x0030FFFF
#define GCREG_DE_ROP_ResetValue                                       0x00000000

/* ROP type :  ROP2, ROP3 or ROP4 */
#define GCREG_DE_ROP_TYPE                                                21 : 20
#define GCREG_DE_ROP_TYPE_End                                                 21
#define GCREG_DE_ROP_TYPE_Start                                               20
#define GCREG_DE_ROP_TYPE_Type                                               U02
#define   GCREG_DE_ROP_TYPE_ROP2_PATTERN                                     0x0
#define   GCREG_DE_ROP_TYPE_ROP2_SOURCE                                      0x1
#define   GCREG_DE_ROP_TYPE_ROP3                                             0x2
#define   GCREG_DE_ROP_TYPE_ROP4                                             0x3

/* Background ROP code is used for transparent pixels. */
#define GCREG_DE_ROP_ROP_BG                                               15 : 8
#define GCREG_DE_ROP_ROP_BG_End                                               15
#define GCREG_DE_ROP_ROP_BG_Start                                              8
#define GCREG_DE_ROP_ROP_BG_Type                                             U08

/* Background ROP code is used for opaque pixels. */
#define GCREG_DE_ROP_ROP_FG                                                7 : 0
#define GCREG_DE_ROP_ROP_FG_End                                                7
#define GCREG_DE_ROP_ROP_FG_Start                                              0
#define GCREG_DE_ROP_ROP_FG_Type                                             U08

/* Register gcregDEAlphaControl (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregDEAlphaControlRegAddrs                                       0x4A20
#define GCREG_DE_ALPHA_CONTROL_Address                                   0x12880
#define GCREG_DE_ALPHA_CONTROL_MSB                                            15
#define GCREG_DE_ALPHA_CONTROL_LSB                                             2
#define GCREG_DE_ALPHA_CONTROL_BLK                                             0
#define GCREG_DE_ALPHA_CONTROL_Count                                           4
#define GCREG_DE_ALPHA_CONTROL_FieldMask                              0x00000001
#define GCREG_DE_ALPHA_CONTROL_ReadMask                               0x00000001
#define GCREG_DE_ALPHA_CONTROL_WriteMask                              0x00000001
#define GCREG_DE_ALPHA_CONTROL_ResetValue                             0x00000000

#define GCREG_DE_ALPHA_CONTROL_ENABLE                                      0 : 0
#define GCREG_DE_ALPHA_CONTROL_ENABLE_End                                      0
#define GCREG_DE_ALPHA_CONTROL_ENABLE_Start                                    0
#define GCREG_DE_ALPHA_CONTROL_ENABLE_Type                                   U01
#define   GCREG_DE_ALPHA_CONTROL_ENABLE_OFF                                  0x0
#define   GCREG_DE_ALPHA_CONTROL_ENABLE_ON                                   0x1

/* Register gcregDEAlphaModes (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregDEAlphaModesRegAddrs                                         0x4A24
#define GCREG_DE_ALPHA_MODES_Address                                     0x12890
#define GCREG_DE_ALPHA_MODES_MSB                                              15
#define GCREG_DE_ALPHA_MODES_LSB                                               2
#define GCREG_DE_ALPHA_MODES_BLK                                               0
#define GCREG_DE_ALPHA_MODES_Count                                             4
#define GCREG_DE_ALPHA_MODES_FieldMask                                0xFF003311
#define GCREG_DE_ALPHA_MODES_ReadMask                                 0xFF003311
#define GCREG_DE_ALPHA_MODES_WriteMask                                0xFF003311
#define GCREG_DE_ALPHA_MODES_ResetValue                               0x00000000

#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_MODE                                0 : 0
#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_MODE_End                                0
#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_MODE_Start                              0
#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_MODE_Type                             U01
#define   GCREG_DE_ALPHA_MODES_SRC_ALPHA_MODE_NORMAL                         0x0
#define   GCREG_DE_ALPHA_MODES_SRC_ALPHA_MODE_INVERSED                       0x1

#define GCREG_DE_ALPHA_MODES_DST_ALPHA_MODE                                4 : 4
#define GCREG_DE_ALPHA_MODES_DST_ALPHA_MODE_End                                4
#define GCREG_DE_ALPHA_MODES_DST_ALPHA_MODE_Start                              4
#define GCREG_DE_ALPHA_MODES_DST_ALPHA_MODE_Type                             U01
#define   GCREG_DE_ALPHA_MODES_DST_ALPHA_MODE_NORMAL                         0x0
#define   GCREG_DE_ALPHA_MODES_DST_ALPHA_MODE_INVERSED                       0x1

#define GCREG_DE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE                         9 : 8
#define GCREG_DE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_End                         9
#define GCREG_DE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_Start                       8
#define GCREG_DE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_Type                      U02
#define   GCREG_DE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_NORMAL                  0x0
#define   GCREG_DE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_GLOBAL                  0x1
#define   GCREG_DE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_SCALED                  0x2

#define GCREG_DE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE                       13 : 12
#define GCREG_DE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_End                        13
#define GCREG_DE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_Start                      12
#define GCREG_DE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_Type                      U02
#define   GCREG_DE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_NORMAL                  0x0
#define   GCREG_DE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_GLOBAL                  0x1
#define   GCREG_DE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_SCALED                  0x2

#define GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE                           26 : 24
#define GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_End                            26
#define GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_Start                          24
#define GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_Type                          U03
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_ZERO                        0x0
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_ONE                         0x1
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_NORMAL                      0x2
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_INVERSED                    0x3
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_COLOR                       0x4
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_COLOR_INVERSED              0x5
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_SATURATED_ALPHA             0x6
#define   GCREG_DE_ALPHA_MODES_SRC_BLENDING_MODE_SATURATED_DEST_ALPHA        0x7

/* Src Blending factor is calculate from Src alpha. */
#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_FACTOR                            27 : 27
#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_FACTOR_End                             27
#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_FACTOR_Start                           27
#define GCREG_DE_ALPHA_MODES_SRC_ALPHA_FACTOR_Type                           U01
#define   GCREG_DE_ALPHA_MODES_SRC_ALPHA_FACTOR_DISABLED                     0x0
#define   GCREG_DE_ALPHA_MODES_SRC_ALPHA_FACTOR_ENABLED                      0x1

#define GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE                           30 : 28
#define GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_End                            30
#define GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_Start                          28
#define GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_Type                          U03
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_ZERO                        0x0
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_ONE                         0x1
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_NORMAL                      0x2
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_INVERSED                    0x3
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_COLOR                       0x4
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_COLOR_INVERSED              0x5
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_SATURATED_ALPHA             0x6
#define   GCREG_DE_ALPHA_MODES_DST_BLENDING_MODE_SATURATED_DEST_ALPHA        0x7

/* Dst Blending factor is calculate from Dst alpha. */
#define GCREG_DE_ALPHA_MODES_DST_ALPHA_FACTOR                            31 : 31
#define GCREG_DE_ALPHA_MODES_DST_ALPHA_FACTOR_End                             31
#define GCREG_DE_ALPHA_MODES_DST_ALPHA_FACTOR_Start                           31
#define GCREG_DE_ALPHA_MODES_DST_ALPHA_FACTOR_Type                           U01
#define   GCREG_DE_ALPHA_MODES_DST_ALPHA_FACTOR_DISABLED                     0x0
#define   GCREG_DE_ALPHA_MODES_DST_ALPHA_FACTOR_ENABLED                      0x1

/* Register gcregDEAddressU (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source U plane. */

#define gcregDEAddressURegAddrs                                           0x4A28
#define GCREG_DE_ADDRESS_U_Address                                       0x128A0
#define GCREG_DE_ADDRESS_U_MSB                                                15
#define GCREG_DE_ADDRESS_U_LSB                                                 2
#define GCREG_DE_ADDRESS_U_BLK                                                 0
#define GCREG_DE_ADDRESS_U_Count                                               4
#define GCREG_DE_ADDRESS_U_FieldMask                                  0xFFFFFFFF
#define GCREG_DE_ADDRESS_U_ReadMask                                   0xFFFFFFFC
#define GCREG_DE_ADDRESS_U_WriteMask                                  0xFFFFFFFC
#define GCREG_DE_ADDRESS_U_ResetValue                                 0x00000000

#define GCREG_DE_ADDRESS_U_TYPE                                          31 : 31
#define GCREG_DE_ADDRESS_U_TYPE_End                                           31
#define GCREG_DE_ADDRESS_U_TYPE_Start                                         31
#define GCREG_DE_ADDRESS_U_TYPE_Type                                         U01
#define   GCREG_DE_ADDRESS_U_TYPE_SYSTEM                                     0x0
#define   GCREG_DE_ADDRESS_U_TYPE_VIRTUAL_SYSTEM                             0x1

#define GCREG_DE_ADDRESS_U_ADDRESS                                        30 : 0
#define GCREG_DE_ADDRESS_U_ADDRESS_End                                        30
#define GCREG_DE_ADDRESS_U_ADDRESS_Start                                       0
#define GCREG_DE_ADDRESS_U_ADDRESS_Type                                      U31

/* Register gcregDEStrideU (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source U plane in bytes. */

#define gcregDEStrideURegAddrs                                            0x4A2C
#define GCREG_DE_STRIDE_U_Address                                        0x128B0
#define GCREG_DE_STRIDE_U_MSB                                                 15
#define GCREG_DE_STRIDE_U_LSB                                                  2
#define GCREG_DE_STRIDE_U_BLK                                                  0
#define GCREG_DE_STRIDE_U_Count                                                4
#define GCREG_DE_STRIDE_U_FieldMask                                   0x0003FFFF
#define GCREG_DE_STRIDE_U_ReadMask                                    0x0003FFFC
#define GCREG_DE_STRIDE_U_WriteMask                                   0x0003FFFC
#define GCREG_DE_STRIDE_U_ResetValue                                  0x00000000

#define GCREG_DE_STRIDE_U_STRIDE                                          17 : 0
#define GCREG_DE_STRIDE_U_STRIDE_End                                          17
#define GCREG_DE_STRIDE_U_STRIDE_Start                                         0
#define GCREG_DE_STRIDE_U_STRIDE_Type                                        U18

/* Register gcregDEAddressV (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source V plane. */

#define gcregDEAddressVRegAddrs                                           0x4A30
#define GCREG_DE_ADDRESS_V_Address                                       0x128C0
#define GCREG_DE_ADDRESS_V_MSB                                                15
#define GCREG_DE_ADDRESS_V_LSB                                                 2
#define GCREG_DE_ADDRESS_V_BLK                                                 0
#define GCREG_DE_ADDRESS_V_Count                                               4
#define GCREG_DE_ADDRESS_V_FieldMask                                  0xFFFFFFFF
#define GCREG_DE_ADDRESS_V_ReadMask                                   0xFFFFFFFC
#define GCREG_DE_ADDRESS_V_WriteMask                                  0xFFFFFFFC
#define GCREG_DE_ADDRESS_V_ResetValue                                 0x00000000

#define GCREG_DE_ADDRESS_V_TYPE                                          31 : 31
#define GCREG_DE_ADDRESS_V_TYPE_End                                           31
#define GCREG_DE_ADDRESS_V_TYPE_Start                                         31
#define GCREG_DE_ADDRESS_V_TYPE_Type                                         U01
#define   GCREG_DE_ADDRESS_V_TYPE_SYSTEM                                     0x0
#define   GCREG_DE_ADDRESS_V_TYPE_VIRTUAL_SYSTEM                             0x1

#define GCREG_DE_ADDRESS_V_ADDRESS                                        30 : 0
#define GCREG_DE_ADDRESS_V_ADDRESS_End                                        30
#define GCREG_DE_ADDRESS_V_ADDRESS_Start                                       0
#define GCREG_DE_ADDRESS_V_ADDRESS_Type                                      U31

/* Register gcregDEStrideV (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source V plane in bytes. */

#define gcregDEStrideVRegAddrs                                            0x4A34
#define GCREG_DE_STRIDE_V_Address                                        0x128D0
#define GCREG_DE_STRIDE_V_MSB                                                 15
#define GCREG_DE_STRIDE_V_LSB                                                  2
#define GCREG_DE_STRIDE_V_BLK                                                  0
#define GCREG_DE_STRIDE_V_Count                                                4
#define GCREG_DE_STRIDE_V_FieldMask                                   0x0003FFFF
#define GCREG_DE_STRIDE_V_ReadMask                                    0x0003FFFC
#define GCREG_DE_STRIDE_V_WriteMask                                   0x0003FFFC
#define GCREG_DE_STRIDE_V_ResetValue                                  0x00000000

#define GCREG_DE_STRIDE_V_STRIDE                                          17 : 0
#define GCREG_DE_STRIDE_V_STRIDE_End                                          17
#define GCREG_DE_STRIDE_V_STRIDE_Start                                         0
#define GCREG_DE_STRIDE_V_STRIDE_Type                                        U18

/* Register gcregDESrcRotationHeight (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 180/270 degree rotation configuration for the Source surface. Height field **
** specifies the height of the surface in pixels.                             */

#define gcregDESrcRotationHeightRegAddrs                                  0x4A38
#define GCREG_DE_SRC_ROTATION_HEIGHT_Address                             0x128E0
#define GCREG_DE_SRC_ROTATION_HEIGHT_MSB                                      15
#define GCREG_DE_SRC_ROTATION_HEIGHT_LSB                                       2
#define GCREG_DE_SRC_ROTATION_HEIGHT_BLK                                       0
#define GCREG_DE_SRC_ROTATION_HEIGHT_Count                                     4
#define GCREG_DE_SRC_ROTATION_HEIGHT_FieldMask                        0x0000FFFF
#define GCREG_DE_SRC_ROTATION_HEIGHT_ReadMask                         0x0000FFFF
#define GCREG_DE_SRC_ROTATION_HEIGHT_WriteMask                        0x0000FFFF
#define GCREG_DE_SRC_ROTATION_HEIGHT_ResetValue                       0x00000000

#define GCREG_DE_SRC_ROTATION_HEIGHT_HEIGHT                               15 : 0
#define GCREG_DE_SRC_ROTATION_HEIGHT_HEIGHT_End                               15
#define GCREG_DE_SRC_ROTATION_HEIGHT_HEIGHT_Start                              0
#define GCREG_DE_SRC_ROTATION_HEIGHT_HEIGHT_Type                             U16

/* Register gcregDERotAngle (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 0/90/180/270 degree rotation configuration for the Source surface. Height  **
** field specifies the height of the surface in pixels.                       */

#define gcregDERotAngleRegAddrs                                           0x4A3C
#define GCREG_DE_ROT_ANGLE_Address                                       0x128F0
#define GCREG_DE_ROT_ANGLE_MSB                                                15
#define GCREG_DE_ROT_ANGLE_LSB                                                 2
#define GCREG_DE_ROT_ANGLE_BLK                                                 0
#define GCREG_DE_ROT_ANGLE_Count                                               4
#define GCREG_DE_ROT_ANGLE_FieldMask                                  0x000BB33F
#define GCREG_DE_ROT_ANGLE_ReadMask                                   0x000BB33F
#define GCREG_DE_ROT_ANGLE_WriteMask                                  0x000BB33F
#define GCREG_DE_ROT_ANGLE_ResetValue                                 0x00000000

#define GCREG_DE_ROT_ANGLE_SRC                                             2 : 0
#define GCREG_DE_ROT_ANGLE_SRC_End                                             2
#define GCREG_DE_ROT_ANGLE_SRC_Start                                           0
#define GCREG_DE_ROT_ANGLE_SRC_Type                                          U03
#define   GCREG_DE_ROT_ANGLE_SRC_ROT0                                        0x0
#define   GCREG_DE_ROT_ANGLE_SRC_FLIP_X                                      0x1
#define   GCREG_DE_ROT_ANGLE_SRC_FLIP_Y                                      0x2
#define   GCREG_DE_ROT_ANGLE_SRC_ROT90                                       0x4
#define   GCREG_DE_ROT_ANGLE_SRC_ROT180                                      0x5
#define   GCREG_DE_ROT_ANGLE_SRC_ROT270                                      0x6

#define GCREG_DE_ROT_ANGLE_DST                                             5 : 3
#define GCREG_DE_ROT_ANGLE_DST_End                                             5
#define GCREG_DE_ROT_ANGLE_DST_Start                                           3
#define GCREG_DE_ROT_ANGLE_DST_Type                                          U03
#define   GCREG_DE_ROT_ANGLE_DST_ROT0                                        0x0
#define   GCREG_DE_ROT_ANGLE_DST_FLIP_X                                      0x1
#define   GCREG_DE_ROT_ANGLE_DST_FLIP_Y                                      0x2
#define   GCREG_DE_ROT_ANGLE_DST_ROT90                                       0x4
#define   GCREG_DE_ROT_ANGLE_DST_ROT180                                      0x5
#define   GCREG_DE_ROT_ANGLE_DST_ROT270                                      0x6

#define GCREG_DE_ROT_ANGLE_MASK_SRC                                        8 : 8
#define GCREG_DE_ROT_ANGLE_MASK_SRC_End                                        8
#define GCREG_DE_ROT_ANGLE_MASK_SRC_Start                                      8
#define GCREG_DE_ROT_ANGLE_MASK_SRC_Type                                     U01
#define   GCREG_DE_ROT_ANGLE_MASK_SRC_ENABLED                                0x0
#define   GCREG_DE_ROT_ANGLE_MASK_SRC_MASKED                                 0x1

#define GCREG_DE_ROT_ANGLE_MASK_DST                                        9 : 9
#define GCREG_DE_ROT_ANGLE_MASK_DST_End                                        9
#define GCREG_DE_ROT_ANGLE_MASK_DST_Start                                      9
#define GCREG_DE_ROT_ANGLE_MASK_DST_Type                                     U01
#define   GCREG_DE_ROT_ANGLE_MASK_DST_ENABLED                                0x0
#define   GCREG_DE_ROT_ANGLE_MASK_DST_MASKED                                 0x1

#define GCREG_DE_ROT_ANGLE_SRC_MIRROR                                    13 : 12
#define GCREG_DE_ROT_ANGLE_SRC_MIRROR_End                                     13
#define GCREG_DE_ROT_ANGLE_SRC_MIRROR_Start                                   12
#define GCREG_DE_ROT_ANGLE_SRC_MIRROR_Type                                   U02
#define   GCREG_DE_ROT_ANGLE_SRC_MIRROR_NONE                                 0x0
#define   GCREG_DE_ROT_ANGLE_SRC_MIRROR_MIRROR_X                             0x1
#define   GCREG_DE_ROT_ANGLE_SRC_MIRROR_MIRROR_Y                             0x2
#define   GCREG_DE_ROT_ANGLE_SRC_MIRROR_MIRROR_XY                            0x3

#define GCREG_DE_ROT_ANGLE_MASK_SRC_MIRROR                               15 : 15
#define GCREG_DE_ROT_ANGLE_MASK_SRC_MIRROR_End                                15
#define GCREG_DE_ROT_ANGLE_MASK_SRC_MIRROR_Start                              15
#define GCREG_DE_ROT_ANGLE_MASK_SRC_MIRROR_Type                              U01
#define   GCREG_DE_ROT_ANGLE_MASK_SRC_MIRROR_ENABLED                         0x0
#define   GCREG_DE_ROT_ANGLE_MASK_SRC_MIRROR_MASKED                          0x1

#define GCREG_DE_ROT_ANGLE_DST_MIRROR                                    17 : 16
#define GCREG_DE_ROT_ANGLE_DST_MIRROR_End                                     17
#define GCREG_DE_ROT_ANGLE_DST_MIRROR_Start                                   16
#define GCREG_DE_ROT_ANGLE_DST_MIRROR_Type                                   U02
#define   GCREG_DE_ROT_ANGLE_DST_MIRROR_NONE                                 0x0
#define   GCREG_DE_ROT_ANGLE_DST_MIRROR_MIRROR_X                             0x1
#define   GCREG_DE_ROT_ANGLE_DST_MIRROR_MIRROR_Y                             0x2
#define   GCREG_DE_ROT_ANGLE_DST_MIRROR_MIRROR_XY                            0x3

#define GCREG_DE_ROT_ANGLE_MASK_DST_MIRROR                               19 : 19
#define GCREG_DE_ROT_ANGLE_MASK_DST_MIRROR_End                                19
#define GCREG_DE_ROT_ANGLE_MASK_DST_MIRROR_Start                              19
#define GCREG_DE_ROT_ANGLE_MASK_DST_MIRROR_Type                              U01
#define   GCREG_DE_ROT_ANGLE_MASK_DST_MIRROR_ENABLED                         0x0
#define   GCREG_DE_ROT_ANGLE_MASK_DST_MIRROR_MASKED                          0x1

/* Register gcregDEGlobalSrcColor (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the global source color and alpha values. */

#define gcregDEGlobalSrcColorRegAddrs                                     0x4A40
#define GCREG_DE_GLOBAL_SRC_COLOR_Address                                0x12900
#define GCREG_DE_GLOBAL_SRC_COLOR_MSB                                         15
#define GCREG_DE_GLOBAL_SRC_COLOR_LSB                                          2
#define GCREG_DE_GLOBAL_SRC_COLOR_BLK                                          0
#define GCREG_DE_GLOBAL_SRC_COLOR_Count                                        4
#define GCREG_DE_GLOBAL_SRC_COLOR_FieldMask                           0xFFFFFFFF
#define GCREG_DE_GLOBAL_SRC_COLOR_ReadMask                            0xFFFFFFFF
#define GCREG_DE_GLOBAL_SRC_COLOR_WriteMask                           0xFFFFFFFF
#define GCREG_DE_GLOBAL_SRC_COLOR_ResetValue                          0x00000000

#define GCREG_DE_GLOBAL_SRC_COLOR_ALPHA                                  31 : 24
#define GCREG_DE_GLOBAL_SRC_COLOR_ALPHA_End                                   31
#define GCREG_DE_GLOBAL_SRC_COLOR_ALPHA_Start                                 24
#define GCREG_DE_GLOBAL_SRC_COLOR_ALPHA_Type                                 U08

#define GCREG_DE_GLOBAL_SRC_COLOR_RED                                    23 : 16
#define GCREG_DE_GLOBAL_SRC_COLOR_RED_End                                     23
#define GCREG_DE_GLOBAL_SRC_COLOR_RED_Start                                   16
#define GCREG_DE_GLOBAL_SRC_COLOR_RED_Type                                   U08

#define GCREG_DE_GLOBAL_SRC_COLOR_GREEN                                   15 : 8
#define GCREG_DE_GLOBAL_SRC_COLOR_GREEN_End                                   15
#define GCREG_DE_GLOBAL_SRC_COLOR_GREEN_Start                                  8
#define GCREG_DE_GLOBAL_SRC_COLOR_GREEN_Type                                 U08

#define GCREG_DE_GLOBAL_SRC_COLOR_BLUE                                     7 : 0
#define GCREG_DE_GLOBAL_SRC_COLOR_BLUE_End                                     7
#define GCREG_DE_GLOBAL_SRC_COLOR_BLUE_Start                                   0
#define GCREG_DE_GLOBAL_SRC_COLOR_BLUE_Type                                  U08

/* Register gcregDEGlobalDestColor (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the global destination color and alpha values. */

#define gcregDEGlobalDestColorRegAddrs                                    0x4A44
#define GCREG_DE_GLOBAL_DEST_COLOR_Address                               0x12910
#define GCREG_DE_GLOBAL_DEST_COLOR_MSB                                        15
#define GCREG_DE_GLOBAL_DEST_COLOR_LSB                                         2
#define GCREG_DE_GLOBAL_DEST_COLOR_BLK                                         0
#define GCREG_DE_GLOBAL_DEST_COLOR_Count                                       4
#define GCREG_DE_GLOBAL_DEST_COLOR_FieldMask                          0xFFFFFFFF
#define GCREG_DE_GLOBAL_DEST_COLOR_ReadMask                           0xFFFFFFFF
#define GCREG_DE_GLOBAL_DEST_COLOR_WriteMask                          0xFFFFFFFF
#define GCREG_DE_GLOBAL_DEST_COLOR_ResetValue                         0x00000000

#define GCREG_DE_GLOBAL_DEST_COLOR_ALPHA                                 31 : 24
#define GCREG_DE_GLOBAL_DEST_COLOR_ALPHA_End                                  31
#define GCREG_DE_GLOBAL_DEST_COLOR_ALPHA_Start                                24
#define GCREG_DE_GLOBAL_DEST_COLOR_ALPHA_Type                                U08

#define GCREG_DE_GLOBAL_DEST_COLOR_RED                                   23 : 16
#define GCREG_DE_GLOBAL_DEST_COLOR_RED_End                                    23
#define GCREG_DE_GLOBAL_DEST_COLOR_RED_Start                                  16
#define GCREG_DE_GLOBAL_DEST_COLOR_RED_Type                                  U08

#define GCREG_DE_GLOBAL_DEST_COLOR_GREEN                                  15 : 8
#define GCREG_DE_GLOBAL_DEST_COLOR_GREEN_End                                  15
#define GCREG_DE_GLOBAL_DEST_COLOR_GREEN_Start                                 8
#define GCREG_DE_GLOBAL_DEST_COLOR_GREEN_Type                                U08

#define GCREG_DE_GLOBAL_DEST_COLOR_BLUE                                    7 : 0
#define GCREG_DE_GLOBAL_DEST_COLOR_BLUE_End                                    7
#define GCREG_DE_GLOBAL_DEST_COLOR_BLUE_Start                                  0
#define GCREG_DE_GLOBAL_DEST_COLOR_BLUE_Type                                 U08

/* Register gcregDEColorMultiplyModes (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Color modes to multiply Source or Destination pixel color by alpha         **
** channel. Alpha can be from global color source or current pixel.           */

#define gcregDEColorMultiplyModesRegAddrs                                 0x4A48
#define GCREG_DE_COLOR_MULTIPLY_MODES_Address                            0x12920
#define GCREG_DE_COLOR_MULTIPLY_MODES_MSB                                     15
#define GCREG_DE_COLOR_MULTIPLY_MODES_LSB                                      2
#define GCREG_DE_COLOR_MULTIPLY_MODES_BLK                                      0
#define GCREG_DE_COLOR_MULTIPLY_MODES_Count                                    4
#define GCREG_DE_COLOR_MULTIPLY_MODES_FieldMask                       0x00100311
#define GCREG_DE_COLOR_MULTIPLY_MODES_ReadMask                        0x00100311
#define GCREG_DE_COLOR_MULTIPLY_MODES_WriteMask                       0x00100311
#define GCREG_DE_COLOR_MULTIPLY_MODES_ResetValue                      0x00000000

#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY                      0 : 0
#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_End                      0
#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_Start                    0
#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_Type                   U01
#define   GCREG_DE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_DISABLE              0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_ENABLE               0x1

#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY                      4 : 4
#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_End                      4
#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_Start                    4
#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_Type                   U01
#define   GCREG_DE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_DISABLE              0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_ENABLE               0x1

#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY               9 : 8
#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_End               9
#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_Start             8
#define GCREG_DE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_Type            U02
#define   GCREG_DE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_DISABLE       0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_ALPHA         0x1
#define   GCREG_DE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_COLOR         0x2

#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY                     20 : 20
#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_End                      20
#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_Start                    20
#define GCREG_DE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_Type                    U01
#define   GCREG_DE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_DISABLE               0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_ENABLE                0x1

/* Register gcregPETransparency (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregPETransparencyRegAddrs                                       0x4A4C
#define GCREG_PE_TRANSPARENCY_Address                                    0x12930
#define GCREG_PE_TRANSPARENCY_MSB                                             15
#define GCREG_PE_TRANSPARENCY_LSB                                              2
#define GCREG_PE_TRANSPARENCY_BLK                                              0
#define GCREG_PE_TRANSPARENCY_Count                                            4
#define GCREG_PE_TRANSPARENCY_FieldMask                               0xB3331333
#define GCREG_PE_TRANSPARENCY_ReadMask                                0xB3331333
#define GCREG_PE_TRANSPARENCY_WriteMask                               0xB3331333
#define GCREG_PE_TRANSPARENCY_ResetValue                              0x00000000

/* Source transparency mode. */
#define GCREG_PE_TRANSPARENCY_SOURCE                                       1 : 0
#define GCREG_PE_TRANSPARENCY_SOURCE_End                                       1
#define GCREG_PE_TRANSPARENCY_SOURCE_Start                                     0
#define GCREG_PE_TRANSPARENCY_SOURCE_Type                                    U02
#define   GCREG_PE_TRANSPARENCY_SOURCE_OPAQUE                                0x0
#define   GCREG_PE_TRANSPARENCY_SOURCE_MASK                                  0x1
#define   GCREG_PE_TRANSPARENCY_SOURCE_KEY                                   0x2

/* Pattern transparency mode. KEY transparency mode is reserved. */
#define GCREG_PE_TRANSPARENCY_PATTERN                                      5 : 4
#define GCREG_PE_TRANSPARENCY_PATTERN_End                                      5
#define GCREG_PE_TRANSPARENCY_PATTERN_Start                                    4
#define GCREG_PE_TRANSPARENCY_PATTERN_Type                                   U02
#define   GCREG_PE_TRANSPARENCY_PATTERN_OPAQUE                               0x0
#define   GCREG_PE_TRANSPARENCY_PATTERN_MASK                                 0x1
#define   GCREG_PE_TRANSPARENCY_PATTERN_KEY                                  0x2

/* Destination transparency mode. MASK transparency mode is reserved. */
#define GCREG_PE_TRANSPARENCY_DESTINATION                                  9 : 8
#define GCREG_PE_TRANSPARENCY_DESTINATION_End                                  9
#define GCREG_PE_TRANSPARENCY_DESTINATION_Start                                8
#define GCREG_PE_TRANSPARENCY_DESTINATION_Type                               U02
#define   GCREG_PE_TRANSPARENCY_DESTINATION_OPAQUE                           0x0
#define   GCREG_PE_TRANSPARENCY_DESTINATION_MASK                             0x1
#define   GCREG_PE_TRANSPARENCY_DESTINATION_KEY                              0x2

/* Mask field for Source/Pattern/Destination fields. */
#define GCREG_PE_TRANSPARENCY_MASK_TRANSPARENCY                          12 : 12
#define GCREG_PE_TRANSPARENCY_MASK_TRANSPARENCY_End                           12
#define GCREG_PE_TRANSPARENCY_MASK_TRANSPARENCY_Start                         12
#define GCREG_PE_TRANSPARENCY_MASK_TRANSPARENCY_Type                         U01
#define   GCREG_PE_TRANSPARENCY_MASK_TRANSPARENCY_ENABLED                    0x0
#define   GCREG_PE_TRANSPARENCY_MASK_TRANSPARENCY_MASKED                     0x1

/* Source usage override. */
#define GCREG_PE_TRANSPARENCY_USE_SRC_OVERRIDE                           17 : 16
#define GCREG_PE_TRANSPARENCY_USE_SRC_OVERRIDE_End                            17
#define GCREG_PE_TRANSPARENCY_USE_SRC_OVERRIDE_Start                          16
#define GCREG_PE_TRANSPARENCY_USE_SRC_OVERRIDE_Type                          U02
#define   GCREG_PE_TRANSPARENCY_USE_SRC_OVERRIDE_DEFAULT                     0x0
#define   GCREG_PE_TRANSPARENCY_USE_SRC_OVERRIDE_USE_ENABLE                  0x1
#define   GCREG_PE_TRANSPARENCY_USE_SRC_OVERRIDE_USE_DISABLE                 0x2

/* Pattern usage override. */
#define GCREG_PE_TRANSPARENCY_USE_PAT_OVERRIDE                           21 : 20
#define GCREG_PE_TRANSPARENCY_USE_PAT_OVERRIDE_End                            21
#define GCREG_PE_TRANSPARENCY_USE_PAT_OVERRIDE_Start                          20
#define GCREG_PE_TRANSPARENCY_USE_PAT_OVERRIDE_Type                          U02
#define   GCREG_PE_TRANSPARENCY_USE_PAT_OVERRIDE_DEFAULT                     0x0
#define   GCREG_PE_TRANSPARENCY_USE_PAT_OVERRIDE_USE_ENABLE                  0x1
#define   GCREG_PE_TRANSPARENCY_USE_PAT_OVERRIDE_USE_DISABLE                 0x2

/* Destination usage override. */
#define GCREG_PE_TRANSPARENCY_USE_DST_OVERRIDE                           25 : 24
#define GCREG_PE_TRANSPARENCY_USE_DST_OVERRIDE_End                            25
#define GCREG_PE_TRANSPARENCY_USE_DST_OVERRIDE_Start                          24
#define GCREG_PE_TRANSPARENCY_USE_DST_OVERRIDE_Type                          U02
#define   GCREG_PE_TRANSPARENCY_USE_DST_OVERRIDE_DEFAULT                     0x0
#define   GCREG_PE_TRANSPARENCY_USE_DST_OVERRIDE_USE_ENABLE                  0x1
#define   GCREG_PE_TRANSPARENCY_USE_DST_OVERRIDE_USE_DISABLE                 0x2

/* 2D resource usage override mask field. */
#define GCREG_PE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE                     28 : 28
#define GCREG_PE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_End                      28
#define GCREG_PE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_Start                    28
#define GCREG_PE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_Type                    U01
#define   GCREG_PE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_ENABLED               0x0
#define   GCREG_PE_TRANSPARENCY_MASK_RESOURCE_OVERRIDE_MASKED                0x1

/* DFB Color Key. */
#define GCREG_PE_TRANSPARENCY_DFB_COLOR_KEY                              29 : 29
#define GCREG_PE_TRANSPARENCY_DFB_COLOR_KEY_End                               29
#define GCREG_PE_TRANSPARENCY_DFB_COLOR_KEY_Start                             29
#define GCREG_PE_TRANSPARENCY_DFB_COLOR_KEY_Type                             U01
#define   GCREG_PE_TRANSPARENCY_DFB_COLOR_KEY_DISABLED                       0x0
#define   GCREG_PE_TRANSPARENCY_DFB_COLOR_KEY_ENABLED                        0x1

#define GCREG_PE_TRANSPARENCY_MASK_DFB_COLOR_KEY                         31 : 31
#define GCREG_PE_TRANSPARENCY_MASK_DFB_COLOR_KEY_End                          31
#define GCREG_PE_TRANSPARENCY_MASK_DFB_COLOR_KEY_Start                        31
#define GCREG_PE_TRANSPARENCY_MASK_DFB_COLOR_KEY_Type                        U01
#define   GCREG_PE_TRANSPARENCY_MASK_DFB_COLOR_KEY_ENABLED                   0x0
#define   GCREG_PE_TRANSPARENCY_MASK_DFB_COLOR_KEY_MASKED                    0x1

/* Register gcregPEControl (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* General purpose control register. */

#define gcregPEControlRegAddrs                                            0x4A50
#define GCREG_PE_CONTROL_Address                                         0x12940
#define GCREG_PE_CONTROL_MSB                                                  15
#define GCREG_PE_CONTROL_LSB                                                   2
#define GCREG_PE_CONTROL_BLK                                                   0
#define GCREG_PE_CONTROL_Count                                                 4
#define GCREG_PE_CONTROL_FieldMask                                    0x00000999
#define GCREG_PE_CONTROL_ReadMask                                     0x00000999
#define GCREG_PE_CONTROL_WriteMask                                    0x00000999
#define GCREG_PE_CONTROL_ResetValue                                   0x00000000

#define GCREG_PE_CONTROL_YUV                                               0 : 0
#define GCREG_PE_CONTROL_YUV_End                                               0
#define GCREG_PE_CONTROL_YUV_Start                                             0
#define GCREG_PE_CONTROL_YUV_Type                                            U01
#define   GCREG_PE_CONTROL_YUV_601                                           0x0
#define   GCREG_PE_CONTROL_YUV_709                                           0x1

#define GCREG_PE_CONTROL_MASK_YUV                                          3 : 3
#define GCREG_PE_CONTROL_MASK_YUV_End                                          3
#define GCREG_PE_CONTROL_MASK_YUV_Start                                        3
#define GCREG_PE_CONTROL_MASK_YUV_Type                                       U01
#define   GCREG_PE_CONTROL_MASK_YUV_ENABLED                                  0x0
#define   GCREG_PE_CONTROL_MASK_YUV_MASKED                                   0x1

#define GCREG_PE_CONTROL_UV_SWIZZLE                                        4 : 4
#define GCREG_PE_CONTROL_UV_SWIZZLE_End                                        4
#define GCREG_PE_CONTROL_UV_SWIZZLE_Start                                      4
#define GCREG_PE_CONTROL_UV_SWIZZLE_Type                                     U01
#define   GCREG_PE_CONTROL_UV_SWIZZLE_UV                                     0x0
#define   GCREG_PE_CONTROL_UV_SWIZZLE_VU                                     0x1

#define GCREG_PE_CONTROL_MASK_UV_SWIZZLE                                   7 : 7
#define GCREG_PE_CONTROL_MASK_UV_SWIZZLE_End                                   7
#define GCREG_PE_CONTROL_MASK_UV_SWIZZLE_Start                                 7
#define GCREG_PE_CONTROL_MASK_UV_SWIZZLE_Type                                U01
#define   GCREG_PE_CONTROL_MASK_UV_SWIZZLE_ENABLED                           0x0
#define   GCREG_PE_CONTROL_MASK_UV_SWIZZLE_MASKED                            0x1

/* YUV to RGB convert enable */
#define GCREG_PE_CONTROL_YUVRGB                                            8 : 8
#define GCREG_PE_CONTROL_YUVRGB_End                                            8
#define GCREG_PE_CONTROL_YUVRGB_Start                                          8
#define GCREG_PE_CONTROL_YUVRGB_Type                                         U01
#define   GCREG_PE_CONTROL_YUVRGB_DISABLED                                   0x0
#define   GCREG_PE_CONTROL_YUVRGB_ENABLED                                    0x1

#define GCREG_PE_CONTROL_MASK_YUVRGB                                     11 : 11
#define GCREG_PE_CONTROL_MASK_YUVRGB_End                                      11
#define GCREG_PE_CONTROL_MASK_YUVRGB_Start                                    11
#define GCREG_PE_CONTROL_MASK_YUVRGB_Type                                    U01
#define   GCREG_PE_CONTROL_MASK_YUVRGB_ENABLED                               0x0
#define   GCREG_PE_CONTROL_MASK_YUVRGB_MASKED                                0x1

/* Register gcregDESrcColorKeyHigh (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the source transparency color in source format. */

#define gcregDESrcColorKeyHighRegAddrs                                    0x4A54
#define GCREG_DE_SRC_COLOR_KEY_HIGH_Address                              0x12950
#define GCREG_DE_SRC_COLOR_KEY_HIGH_MSB                                       15
#define GCREG_DE_SRC_COLOR_KEY_HIGH_LSB                                        2
#define GCREG_DE_SRC_COLOR_KEY_HIGH_BLK                                        0
#define GCREG_DE_SRC_COLOR_KEY_HIGH_Count                                      4
#define GCREG_DE_SRC_COLOR_KEY_HIGH_FieldMask                         0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_KEY_HIGH_ReadMask                          0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_KEY_HIGH_WriteMask                         0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_KEY_HIGH_ResetValue                        0x00000000

#define GCREG_DE_SRC_COLOR_KEY_HIGH_ALPHA                                31 : 24
#define GCREG_DE_SRC_COLOR_KEY_HIGH_ALPHA_End                                 31
#define GCREG_DE_SRC_COLOR_KEY_HIGH_ALPHA_Start                               24
#define GCREG_DE_SRC_COLOR_KEY_HIGH_ALPHA_Type                               U08

#define GCREG_DE_SRC_COLOR_KEY_HIGH_RED                                  23 : 16
#define GCREG_DE_SRC_COLOR_KEY_HIGH_RED_End                                   23
#define GCREG_DE_SRC_COLOR_KEY_HIGH_RED_Start                                 16
#define GCREG_DE_SRC_COLOR_KEY_HIGH_RED_Type                                 U08

#define GCREG_DE_SRC_COLOR_KEY_HIGH_GREEN                                 15 : 8
#define GCREG_DE_SRC_COLOR_KEY_HIGH_GREEN_End                                 15
#define GCREG_DE_SRC_COLOR_KEY_HIGH_GREEN_Start                                8
#define GCREG_DE_SRC_COLOR_KEY_HIGH_GREEN_Type                               U08

#define GCREG_DE_SRC_COLOR_KEY_HIGH_BLUE                                   7 : 0
#define GCREG_DE_SRC_COLOR_KEY_HIGH_BLUE_End                                   7
#define GCREG_DE_SRC_COLOR_KEY_HIGH_BLUE_Start                                 0
#define GCREG_DE_SRC_COLOR_KEY_HIGH_BLUE_Type                                U08

/* Register gcregDESrcExConfig (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregDESrcExConfigRegAddrs                                        0x4A58
#define GCREG_DE_SRC_EX_CONFIG_Address                                   0x12960
#define GCREG_DE_SRC_EX_CONFIG_MSB                                            15
#define GCREG_DE_SRC_EX_CONFIG_LSB                                             2
#define GCREG_DE_SRC_EX_CONFIG_BLK                                             0
#define GCREG_DE_SRC_EX_CONFIG_Count                                           4
#define GCREG_DE_SRC_EX_CONFIG_FieldMask                              0x00000109
#define GCREG_DE_SRC_EX_CONFIG_ReadMask                               0x00000109
#define GCREG_DE_SRC_EX_CONFIG_WriteMask                              0x00000109
#define GCREG_DE_SRC_EX_CONFIG_ResetValue                             0x00000000

/* Source multi tiled address computation control. */
#define GCREG_DE_SRC_EX_CONFIG_MULTI_TILED                                 0 : 0
#define GCREG_DE_SRC_EX_CONFIG_MULTI_TILED_End                                 0
#define GCREG_DE_SRC_EX_CONFIG_MULTI_TILED_Start                               0
#define GCREG_DE_SRC_EX_CONFIG_MULTI_TILED_Type                              U01
#define   GCREG_DE_SRC_EX_CONFIG_MULTI_TILED_DISABLED                        0x0
#define   GCREG_DE_SRC_EX_CONFIG_MULTI_TILED_ENABLED                         0x1

/* Source super tiled address computation control. */
#define GCREG_DE_SRC_EX_CONFIG_SUPER_TILED                                 3 : 3
#define GCREG_DE_SRC_EX_CONFIG_SUPER_TILED_End                                 3
#define GCREG_DE_SRC_EX_CONFIG_SUPER_TILED_Start                               3
#define GCREG_DE_SRC_EX_CONFIG_SUPER_TILED_Type                              U01
#define   GCREG_DE_SRC_EX_CONFIG_SUPER_TILED_DISABLED                        0x0
#define   GCREG_DE_SRC_EX_CONFIG_SUPER_TILED_ENABLED                         0x1

/* Source super tiled address computation control. */
#define GCREG_DE_SRC_EX_CONFIG_MINOR_TILED                                 8 : 8
#define GCREG_DE_SRC_EX_CONFIG_MINOR_TILED_End                                 8
#define GCREG_DE_SRC_EX_CONFIG_MINOR_TILED_Start                               8
#define GCREG_DE_SRC_EX_CONFIG_MINOR_TILED_Type                              U01
#define   GCREG_DE_SRC_EX_CONFIG_MINOR_TILED_DISABLED                        0x0
#define   GCREG_DE_SRC_EX_CONFIG_MINOR_TILED_ENABLED                         0x1

/* Register gcregDESrcExAddress (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source extra surface. */

#define gcregDESrcExAddressRegAddrs                                       0x4A5C
#define GCREG_DE_SRC_EX_ADDRESS_Address                                  0x12970
#define GCREG_DE_SRC_EX_ADDRESS_MSB                                           15
#define GCREG_DE_SRC_EX_ADDRESS_LSB                                            2
#define GCREG_DE_SRC_EX_ADDRESS_BLK                                            0
#define GCREG_DE_SRC_EX_ADDRESS_Count                                          4
#define GCREG_DE_SRC_EX_ADDRESS_FieldMask                             0xFFFFFFFF
#define GCREG_DE_SRC_EX_ADDRESS_ReadMask                              0xFFFFFFFC
#define GCREG_DE_SRC_EX_ADDRESS_WriteMask                             0xFFFFFFFC
#define GCREG_DE_SRC_EX_ADDRESS_ResetValue                            0x00000000

#define GCREG_DE_SRC_EX_ADDRESS_TYPE                                     31 : 31
#define GCREG_DE_SRC_EX_ADDRESS_TYPE_End                                      31
#define GCREG_DE_SRC_EX_ADDRESS_TYPE_Start                                    31
#define GCREG_DE_SRC_EX_ADDRESS_TYPE_Type                                    U01
#define   GCREG_DE_SRC_EX_ADDRESS_TYPE_SYSTEM                                0x0
#define   GCREG_DE_SRC_EX_ADDRESS_TYPE_VIRTUAL_SYSTEM                        0x1

#define GCREG_DE_SRC_EX_ADDRESS_ADDRESS                                   30 : 0
#define GCREG_DE_SRC_EX_ADDRESS_ADDRESS_End                                   30
#define GCREG_DE_SRC_EX_ADDRESS_ADDRESS_Start                                  0
#define GCREG_DE_SRC_EX_ADDRESS_ADDRESS_Type                                 U31

/*******************************************************************************
**                           ~~~~~~~~~~~~~~~~~~~~~~                           **
**                           Module DEMultiSourceEx                           **
**                           ~~~~~~~~~~~~~~~~~~~~~~                           **
*******************************************************************************/

/* Register gcregDESrcAddressEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source surface. */

#define gcregDESrcAddressExRegAddrs                                       0x4A80
#define GCREG_DE_SRC_ADDRESS_EX_Address                                  0x12A00
#define GCREG_DE_SRC_ADDRESS_EX_MSB                                           15
#define GCREG_DE_SRC_ADDRESS_EX_LSB                                            3
#define GCREG_DE_SRC_ADDRESS_EX_BLK                                            0
#define GCREG_DE_SRC_ADDRESS_EX_Count                                          8
#define GCREG_DE_SRC_ADDRESS_EX_FieldMask                             0xFFFFFFFF
#define GCREG_DE_SRC_ADDRESS_EX_ReadMask                              0xFFFFFFFC
#define GCREG_DE_SRC_ADDRESS_EX_WriteMask                             0xFFFFFFFC
#define GCREG_DE_SRC_ADDRESS_EX_ResetValue                            0x00000000

#define GCREG_DE_SRC_ADDRESS_EX_TYPE                                     31 : 31
#define GCREG_DE_SRC_ADDRESS_EX_TYPE_End                                      31
#define GCREG_DE_SRC_ADDRESS_EX_TYPE_Start                                    31
#define GCREG_DE_SRC_ADDRESS_EX_TYPE_Type                                    U01
#define   GCREG_DE_SRC_ADDRESS_EX_TYPE_SYSTEM                                0x0
#define   GCREG_DE_SRC_ADDRESS_EX_TYPE_VIRTUAL_SYSTEM                        0x1

#define GCREG_DE_SRC_ADDRESS_EX_ADDRESS                                   30 : 0
#define GCREG_DE_SRC_ADDRESS_EX_ADDRESS_End                                   30
#define GCREG_DE_SRC_ADDRESS_EX_ADDRESS_Start                                  0
#define GCREG_DE_SRC_ADDRESS_EX_ADDRESS_Type                                 U31

/* Register gcregDESrcStrideEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source surface in bytes. To calculate the stride multiply    **
** the surface width in pixels by the number of  bytes per pixel.             */

#define gcregDESrcStrideExRegAddrs                                        0x4A88
#define GCREG_DE_SRC_STRIDE_EX_Address                                   0x12A20
#define GCREG_DE_SRC_STRIDE_EX_MSB                                            15
#define GCREG_DE_SRC_STRIDE_EX_LSB                                             3
#define GCREG_DE_SRC_STRIDE_EX_BLK                                             0
#define GCREG_DE_SRC_STRIDE_EX_Count                                           8
#define GCREG_DE_SRC_STRIDE_EX_FieldMask                              0x0003FFFF
#define GCREG_DE_SRC_STRIDE_EX_ReadMask                               0x0003FFFC
#define GCREG_DE_SRC_STRIDE_EX_WriteMask                              0x0003FFFC
#define GCREG_DE_SRC_STRIDE_EX_ResetValue                             0x00000000

#define GCREG_DE_SRC_STRIDE_EX_STRIDE                                     17 : 0
#define GCREG_DE_SRC_STRIDE_EX_STRIDE_End                                     17
#define GCREG_DE_SRC_STRIDE_EX_STRIDE_Start                                    0
#define GCREG_DE_SRC_STRIDE_EX_STRIDE_Type                                   U18

/* Register gcregDESrcRotationConfigEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 90 degree rotation configuration for the source surface. Width field       **
** specifies the width of the surface in pixels.                              */

#define gcregDESrcRotationConfigExRegAddrs                                0x4A90
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_Address                          0x12A40
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_MSB                                   15
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_LSB                                    3
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_BLK                                    0
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_Count                                  8
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_FieldMask                     0x0001FFFF
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_ReadMask                      0x0001FFFF
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_WriteMask                     0x0001FFFF
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_ResetValue                    0x00000000

#define GCREG_DE_SRC_ROTATION_CONFIG_EX_WIDTH                             15 : 0
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_WIDTH_End                             15
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_WIDTH_Start                            0
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_WIDTH_Type                           U16

#define GCREG_DE_SRC_ROTATION_CONFIG_EX_ROTATION                         16 : 16
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_ROTATION_End                          16
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_ROTATION_Start                        16
#define GCREG_DE_SRC_ROTATION_CONFIG_EX_ROTATION_Type                        U01
#define   GCREG_DE_SRC_ROTATION_CONFIG_EX_ROTATION_NORMAL                    0x0
#define   GCREG_DE_SRC_ROTATION_CONFIG_EX_ROTATION_ROTATED                   0x1

/* Register gcregDESrcConfigEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Source surface configuration register. */

#define gcregDESrcConfigExRegAddrs                                        0x4A98
#define GCREG_DE_SRC_CONFIG_EX_Address                                   0x12A60
#define GCREG_DE_SRC_CONFIG_EX_MSB                                            15
#define GCREG_DE_SRC_CONFIG_EX_LSB                                             3
#define GCREG_DE_SRC_CONFIG_EX_BLK                                             0
#define GCREG_DE_SRC_CONFIG_EX_Count                                           8
#define GCREG_DE_SRC_CONFIG_EX_FieldMask                              0xDF30B1C0
#define GCREG_DE_SRC_CONFIG_EX_ReadMask                               0xDF30B1C0
#define GCREG_DE_SRC_CONFIG_EX_WriteMask                              0xDF30B1C0
#define GCREG_DE_SRC_CONFIG_EX_ResetValue                             0x00000000

/* Control source endianess. */
#define GCREG_DE_SRC_CONFIG_EX_ENDIAN_CONTROL                            31 : 30
#define GCREG_DE_SRC_CONFIG_EX_ENDIAN_CONTROL_End                             31
#define GCREG_DE_SRC_CONFIG_EX_ENDIAN_CONTROL_Start                           30
#define GCREG_DE_SRC_CONFIG_EX_ENDIAN_CONTROL_Type                           U02
#define   GCREG_DE_SRC_CONFIG_EX_ENDIAN_CONTROL_NO_SWAP                      0x0
#define   GCREG_DE_SRC_CONFIG_EX_ENDIAN_CONTROL_SWAP_WORD                    0x1
#define   GCREG_DE_SRC_CONFIG_EX_ENDIAN_CONTROL_SWAP_DWORD                   0x2

/* Defines the pixel format of the source surface. */
#define GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT                             28 : 24
#define GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_End                              28
#define GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_Start                            24
#define GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_Type                            U05
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_X4R4G4B4                     0x00
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_A4R4G4B4                     0x01
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_X1R5G5B5                     0x02
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_A1R5G5B5                     0x03
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_R5G6B5                       0x04
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_X8R8G8B8                     0x05
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_A8R8G8B8                     0x06
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_YUY2                         0x07
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_UYVY                         0x08
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_INDEX8                       0x09
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_MONOCHROME                   0x0A
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_YV12                         0x0F
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_A8                           0x10
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_NV12                         0x11
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_NV16                         0x12
#define   GCREG_DE_SRC_CONFIG_EX_SOURCE_FORMAT_RG16                         0x13

/* Color channel swizzles. */
#define GCREG_DE_SRC_CONFIG_EX_SWIZZLE                                   21 : 20
#define GCREG_DE_SRC_CONFIG_EX_SWIZZLE_End                                    21
#define GCREG_DE_SRC_CONFIG_EX_SWIZZLE_Start                                  20
#define GCREG_DE_SRC_CONFIG_EX_SWIZZLE_Type                                  U02
#define   GCREG_DE_SRC_CONFIG_EX_SWIZZLE_ARGB                                0x0
#define   GCREG_DE_SRC_CONFIG_EX_SWIZZLE_RGBA                                0x1
#define   GCREG_DE_SRC_CONFIG_EX_SWIZZLE_ABGR                                0x2
#define   GCREG_DE_SRC_CONFIG_EX_SWIZZLE_BGRA                                0x3

/* Mono expansion :if 0, transparency color will be 0, otherwise transparency **
** color will be 1.                                                           */
#define GCREG_DE_SRC_CONFIG_EX_MONO_TRANSPARENCY                         15 : 15
#define GCREG_DE_SRC_CONFIG_EX_MONO_TRANSPARENCY_End                          15
#define GCREG_DE_SRC_CONFIG_EX_MONO_TRANSPARENCY_Start                        15
#define GCREG_DE_SRC_CONFIG_EX_MONO_TRANSPARENCY_Type                        U01
#define   GCREG_DE_SRC_CONFIG_EX_MONO_TRANSPARENCY_BACKGROUND                0x0
#define   GCREG_DE_SRC_CONFIG_EX_MONO_TRANSPARENCY_FOREGROUND                0x1

/* Mono expansion or masked blit :  stream packing in pixels. Determines how  **
** many horizontal pixels are there per each 32-bit chunk. For example, if    **
** set to Packed8, each 32-bit chunk is 8-pixel wide, which also means that   **
** it defines 4 vertical lines of pixels.                                     */
#define GCREG_DE_SRC_CONFIG_EX_PACK                                      13 : 12
#define GCREG_DE_SRC_CONFIG_EX_PACK_End                                       13
#define GCREG_DE_SRC_CONFIG_EX_PACK_Start                                     12
#define GCREG_DE_SRC_CONFIG_EX_PACK_Type                                     U02
#define   GCREG_DE_SRC_CONFIG_EX_PACK_PACKED8                                0x0
#define   GCREG_DE_SRC_CONFIG_EX_PACK_PACKED16                               0x1
#define   GCREG_DE_SRC_CONFIG_EX_PACK_PACKED32                               0x2
#define   GCREG_DE_SRC_CONFIG_EX_PACK_UNPACKED                               0x3

/* Source data location :  set to STREAM for mono expansion blits or masked   **
** blits. For mono expansion blits the complete bitmap comes from the command **
** stream. For masked blits the source data comes from the memory and the     **
** mask from the command stream.                                              */
#define GCREG_DE_SRC_CONFIG_EX_LOCATION                                    8 : 8
#define GCREG_DE_SRC_CONFIG_EX_LOCATION_End                                    8
#define GCREG_DE_SRC_CONFIG_EX_LOCATION_Start                                  8
#define GCREG_DE_SRC_CONFIG_EX_LOCATION_Type                                 U01
#define   GCREG_DE_SRC_CONFIG_EX_LOCATION_MEMORY                             0x0
#define   GCREG_DE_SRC_CONFIG_EX_LOCATION_STREAM                             0x1

/* Source linear/tiled address computation control. */
#define GCREG_DE_SRC_CONFIG_EX_TILED                                       7 : 7
#define GCREG_DE_SRC_CONFIG_EX_TILED_End                                       7
#define GCREG_DE_SRC_CONFIG_EX_TILED_Start                                     7
#define GCREG_DE_SRC_CONFIG_EX_TILED_Type                                    U01
#define   GCREG_DE_SRC_CONFIG_EX_TILED_DISABLED                              0x0
#define   GCREG_DE_SRC_CONFIG_EX_TILED_ENABLED                               0x1

/* If set to ABSOLUTE, the source coordinates are treated as absolute         **
** coordinates inside the source surface. If set to RELATIVE, the source      **
** coordinates are treated as the offsets from the destination coordinates    **
** with the source size equal to the size of the destination.                 */
#define GCREG_DE_SRC_CONFIG_EX_SRC_RELATIVE                                6 : 6
#define GCREG_DE_SRC_CONFIG_EX_SRC_RELATIVE_End                                6
#define GCREG_DE_SRC_CONFIG_EX_SRC_RELATIVE_Start                              6
#define GCREG_DE_SRC_CONFIG_EX_SRC_RELATIVE_Type                             U01
#define   GCREG_DE_SRC_CONFIG_EX_SRC_RELATIVE_ABSOLUTE                       0x0
#define   GCREG_DE_SRC_CONFIG_EX_SRC_RELATIVE_RELATIVE                       0x1

/* Register gcregDESrcOriginEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Absolute or relative (see SRC_RELATIVE field of gcregDESrcConfig register) **
** X and Y coordinates in pixels of the top left corner of the source         **
** rectangle within the source surface.                                       */

#define gcregDESrcOriginExRegAddrs                                        0x4AA0
#define GCREG_DE_SRC_ORIGIN_EX_Address                                   0x12A80
#define GCREG_DE_SRC_ORIGIN_EX_MSB                                            15
#define GCREG_DE_SRC_ORIGIN_EX_LSB                                             3
#define GCREG_DE_SRC_ORIGIN_EX_BLK                                             0
#define GCREG_DE_SRC_ORIGIN_EX_Count                                           8
#define GCREG_DE_SRC_ORIGIN_EX_FieldMask                              0xFFFFFFFF
#define GCREG_DE_SRC_ORIGIN_EX_ReadMask                               0xFFFFFFFF
#define GCREG_DE_SRC_ORIGIN_EX_WriteMask                              0xFFFFFFFF
#define GCREG_DE_SRC_ORIGIN_EX_ResetValue                             0x00000000

#define GCREG_DE_SRC_ORIGIN_EX_Y                                         31 : 16
#define GCREG_DE_SRC_ORIGIN_EX_Y_End                                          31
#define GCREG_DE_SRC_ORIGIN_EX_Y_Start                                        16
#define GCREG_DE_SRC_ORIGIN_EX_Y_Type                                        U16

#define GCREG_DE_SRC_ORIGIN_EX_X                                          15 : 0
#define GCREG_DE_SRC_ORIGIN_EX_X_End                                          15
#define GCREG_DE_SRC_ORIGIN_EX_X_Start                                         0
#define GCREG_DE_SRC_ORIGIN_EX_X_Type                                        U16

/* Register gcregDESrcSizeEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Width and height of the source rectangle in pixels. If the source is       **
** relative (see SRC_RELATIVE field of gcregDESrcConfig register) or a        **
** regular bitblt is being performed without stretching, this register is     **
** ignored and the source size is assumed to be the same as the destination.  */

#define gcregDESrcSizeExRegAddrs                                          0x4AA8
#define GCREG_DE_SRC_SIZE_EX_Address                                     0x12AA0
#define GCREG_DE_SRC_SIZE_EX_MSB                                              15
#define GCREG_DE_SRC_SIZE_EX_LSB                                               3
#define GCREG_DE_SRC_SIZE_EX_BLK                                               0
#define GCREG_DE_SRC_SIZE_EX_Count                                             8
#define GCREG_DE_SRC_SIZE_EX_FieldMask                                0xFFFFFFFF
#define GCREG_DE_SRC_SIZE_EX_ReadMask                                 0xFFFFFFFF
#define GCREG_DE_SRC_SIZE_EX_WriteMask                                0xFFFFFFFF
#define GCREG_DE_SRC_SIZE_EX_ResetValue                               0x00000000

#define GCREG_DE_SRC_SIZE_EX_Y                                           31 : 16
#define GCREG_DE_SRC_SIZE_EX_Y_End                                            31
#define GCREG_DE_SRC_SIZE_EX_Y_Start                                          16
#define GCREG_DE_SRC_SIZE_EX_Y_Type                                          U16

#define GCREG_DE_SRC_SIZE_EX_X                                            15 : 0
#define GCREG_DE_SRC_SIZE_EX_X_End                                            15
#define GCREG_DE_SRC_SIZE_EX_X_Start                                           0
#define GCREG_DE_SRC_SIZE_EX_X_Type                                          U16

/* Register gcregDESrcColorBgEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Select the color where source becomes transparent. It must be programmed   **
** in A8R8G8B8 format.                                                        */

#define gcregDESrcColorBgExRegAddrs                                       0x4AB0
#define GCREG_DE_SRC_COLOR_BG_EX_Address                                 0x12AC0
#define GCREG_DE_SRC_COLOR_BG_EX_MSB                                          15
#define GCREG_DE_SRC_COLOR_BG_EX_LSB                                           3
#define GCREG_DE_SRC_COLOR_BG_EX_BLK                                           0
#define GCREG_DE_SRC_COLOR_BG_EX_Count                                         8
#define GCREG_DE_SRC_COLOR_BG_EX_FieldMask                            0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_BG_EX_ReadMask                             0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_BG_EX_WriteMask                            0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_BG_EX_ResetValue                           0x00000000

#define GCREG_DE_SRC_COLOR_BG_EX_ALPHA                                   31 : 24
#define GCREG_DE_SRC_COLOR_BG_EX_ALPHA_End                                    31
#define GCREG_DE_SRC_COLOR_BG_EX_ALPHA_Start                                  24
#define GCREG_DE_SRC_COLOR_BG_EX_ALPHA_Type                                  U08

#define GCREG_DE_SRC_COLOR_BG_EX_RED                                     23 : 16
#define GCREG_DE_SRC_COLOR_BG_EX_RED_End                                      23
#define GCREG_DE_SRC_COLOR_BG_EX_RED_Start                                    16
#define GCREG_DE_SRC_COLOR_BG_EX_RED_Type                                    U08

#define GCREG_DE_SRC_COLOR_BG_EX_GREEN                                    15 : 8
#define GCREG_DE_SRC_COLOR_BG_EX_GREEN_End                                    15
#define GCREG_DE_SRC_COLOR_BG_EX_GREEN_Start                                   8
#define GCREG_DE_SRC_COLOR_BG_EX_GREEN_Type                                  U08

#define GCREG_DE_SRC_COLOR_BG_EX_BLUE                                      7 : 0
#define GCREG_DE_SRC_COLOR_BG_EX_BLUE_End                                      7
#define GCREG_DE_SRC_COLOR_BG_EX_BLUE_Start                                    0
#define GCREG_DE_SRC_COLOR_BG_EX_BLUE_Type                                   U08

/* Register gcregDERopEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Raster operation foreground and background codes. Even though ROP is not   **
** used in CLEAR, HOR_FILTER_BLT, VER_FILTER_BLT and alpha-eanbled BIT_BLTs,  **
** ROP code still has to be programmed, because the engine makes the decision **
** whether source, destination and pattern are involved in the current        **
** operation and the correct decision is essential for the engine to complete **
** the operation as expected.                                                 */

#define gcregDERopExRegAddrs                                              0x4AB8
#define GCREG_DE_ROP_EX_Address                                          0x12AE0
#define GCREG_DE_ROP_EX_MSB                                                   15
#define GCREG_DE_ROP_EX_LSB                                                    3
#define GCREG_DE_ROP_EX_BLK                                                    0
#define GCREG_DE_ROP_EX_Count                                                  8
#define GCREG_DE_ROP_EX_FieldMask                                     0x0030FFFF
#define GCREG_DE_ROP_EX_ReadMask                                      0x0030FFFF
#define GCREG_DE_ROP_EX_WriteMask                                     0x0030FFFF
#define GCREG_DE_ROP_EX_ResetValue                                    0x00000000

/* ROP type :  ROP2, ROP3 or ROP4 */
#define GCREG_DE_ROP_EX_TYPE                                             21 : 20
#define GCREG_DE_ROP_EX_TYPE_End                                              21
#define GCREG_DE_ROP_EX_TYPE_Start                                            20
#define GCREG_DE_ROP_EX_TYPE_Type                                            U02
#define   GCREG_DE_ROP_EX_TYPE_ROP2_PATTERN                                  0x0
#define   GCREG_DE_ROP_EX_TYPE_ROP2_SOURCE                                   0x1
#define   GCREG_DE_ROP_EX_TYPE_ROP3                                          0x2
#define   GCREG_DE_ROP_EX_TYPE_ROP4                                          0x3

/* Background ROP code is used for transparent pixels. */
#define GCREG_DE_ROP_EX_ROP_BG                                            15 : 8
#define GCREG_DE_ROP_EX_ROP_BG_End                                            15
#define GCREG_DE_ROP_EX_ROP_BG_Start                                           8
#define GCREG_DE_ROP_EX_ROP_BG_Type                                          U08

/* Background ROP code is used for opaque pixels. */
#define GCREG_DE_ROP_EX_ROP_FG                                             7 : 0
#define GCREG_DE_ROP_EX_ROP_FG_End                                             7
#define GCREG_DE_ROP_EX_ROP_FG_Start                                           0
#define GCREG_DE_ROP_EX_ROP_FG_Type                                          U08

/* Register gcregDEAlphaControlEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregDEAlphaControlExRegAddrs                                     0x4AC0
#define GCREG_DE_ALPHA_CONTROL_EX_Address                                0x12B00
#define GCREG_DE_ALPHA_CONTROL_EX_MSB                                         15
#define GCREG_DE_ALPHA_CONTROL_EX_LSB                                          3
#define GCREG_DE_ALPHA_CONTROL_EX_BLK                                          0
#define GCREG_DE_ALPHA_CONTROL_EX_Count                                        8
#define GCREG_DE_ALPHA_CONTROL_EX_FieldMask                           0x00000001
#define GCREG_DE_ALPHA_CONTROL_EX_ReadMask                            0x00000001
#define GCREG_DE_ALPHA_CONTROL_EX_WriteMask                           0x00000001
#define GCREG_DE_ALPHA_CONTROL_EX_ResetValue                          0x00000000

#define GCREG_DE_ALPHA_CONTROL_EX_ENABLE                                   0 : 0
#define GCREG_DE_ALPHA_CONTROL_EX_ENABLE_End                                   0
#define GCREG_DE_ALPHA_CONTROL_EX_ENABLE_Start                                 0
#define GCREG_DE_ALPHA_CONTROL_EX_ENABLE_Type                                U01
#define   GCREG_DE_ALPHA_CONTROL_EX_ENABLE_OFF                               0x0
#define   GCREG_DE_ALPHA_CONTROL_EX_ENABLE_ON                                0x1

/* Register gcregDEAlphaModesEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregDEAlphaModesExRegAddrs                                       0x4AC8
#define GCREG_DE_ALPHA_MODES_EX_Address                                  0x12B20
#define GCREG_DE_ALPHA_MODES_EX_MSB                                           15
#define GCREG_DE_ALPHA_MODES_EX_LSB                                            3
#define GCREG_DE_ALPHA_MODES_EX_BLK                                            0
#define GCREG_DE_ALPHA_MODES_EX_Count                                          8
#define GCREG_DE_ALPHA_MODES_EX_FieldMask                             0xFF003311
#define GCREG_DE_ALPHA_MODES_EX_ReadMask                              0xFF003311
#define GCREG_DE_ALPHA_MODES_EX_WriteMask                             0xFF003311
#define GCREG_DE_ALPHA_MODES_EX_ResetValue                            0x00000000

#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_MODE                             0 : 0
#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_MODE_End                             0
#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_MODE_Start                           0
#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_MODE_Type                          U01
#define   GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_MODE_NORMAL                      0x0
#define   GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_MODE_INVERSED                    0x1

#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_MODE                             4 : 4
#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_MODE_End                             4
#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_MODE_Start                           4
#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_MODE_Type                          U01
#define   GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_MODE_NORMAL                      0x0
#define   GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_MODE_INVERSED                    0x1

#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_SRC_ALPHA_MODE                      9 : 8
#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_SRC_ALPHA_MODE_End                      9
#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_SRC_ALPHA_MODE_Start                    8
#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_SRC_ALPHA_MODE_Type                   U02
#define   GCREG_DE_ALPHA_MODES_EX_GLOBAL_SRC_ALPHA_MODE_NORMAL               0x0
#define   GCREG_DE_ALPHA_MODES_EX_GLOBAL_SRC_ALPHA_MODE_GLOBAL               0x1
#define   GCREG_DE_ALPHA_MODES_EX_GLOBAL_SRC_ALPHA_MODE_SCALED               0x2

#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_DST_ALPHA_MODE                    13 : 12
#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_DST_ALPHA_MODE_End                     13
#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_DST_ALPHA_MODE_Start                   12
#define GCREG_DE_ALPHA_MODES_EX_GLOBAL_DST_ALPHA_MODE_Type                   U02
#define   GCREG_DE_ALPHA_MODES_EX_GLOBAL_DST_ALPHA_MODE_NORMAL               0x0
#define   GCREG_DE_ALPHA_MODES_EX_GLOBAL_DST_ALPHA_MODE_GLOBAL               0x1
#define   GCREG_DE_ALPHA_MODES_EX_GLOBAL_DST_ALPHA_MODE_SCALED               0x2

#define GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE                        26 : 24
#define GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_End                         26
#define GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_Start                       24
#define GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_Type                       U03
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_ZERO                     0x0
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_ONE                      0x1
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_NORMAL                   0x2
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_INVERSED                 0x3
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_COLOR                    0x4
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_COLOR_INVERSED           0x5
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_SATURATED_ALPHA          0x6
#define   GCREG_DE_ALPHA_MODES_EX_SRC_BLENDING_MODE_SATURATED_DEST_ALPHA     0x7

/* Src Blending factor is calculate from Src alpha. */
#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_FACTOR                         27 : 27
#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_FACTOR_End                          27
#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_FACTOR_Start                        27
#define GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_FACTOR_Type                        U01
#define   GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_FACTOR_DISABLED                  0x0
#define   GCREG_DE_ALPHA_MODES_EX_SRC_ALPHA_FACTOR_ENABLED                   0x1

#define GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE                        30 : 28
#define GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_End                         30
#define GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_Start                       28
#define GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_Type                       U03
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_ZERO                     0x0
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_ONE                      0x1
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_NORMAL                   0x2
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_INVERSED                 0x3
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_COLOR                    0x4
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_COLOR_INVERSED           0x5
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_SATURATED_ALPHA          0x6
#define   GCREG_DE_ALPHA_MODES_EX_DST_BLENDING_MODE_SATURATED_DEST_ALPHA     0x7

/* Dst Blending factor is calculate from Dst alpha. */
#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_FACTOR                         31 : 31
#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_FACTOR_End                          31
#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_FACTOR_Start                        31
#define GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_FACTOR_Type                        U01
#define   GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_FACTOR_DISABLED                  0x0
#define   GCREG_DE_ALPHA_MODES_EX_DST_ALPHA_FACTOR_ENABLED                   0x1

/* Register gcregDEAddressUEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source U plane. */

#define gcregDEAddressUExRegAddrs                                         0x4AD0
#define GCREG_DE_ADDRESS_UEX_Address                                     0x12B40
#define GCREG_DE_ADDRESS_UEX_MSB                                              15
#define GCREG_DE_ADDRESS_UEX_LSB                                               3
#define GCREG_DE_ADDRESS_UEX_BLK                                               0
#define GCREG_DE_ADDRESS_UEX_Count                                             8
#define GCREG_DE_ADDRESS_UEX_FieldMask                                0xFFFFFFFF
#define GCREG_DE_ADDRESS_UEX_ReadMask                                 0xFFFFFFFC
#define GCREG_DE_ADDRESS_UEX_WriteMask                                0xFFFFFFFC
#define GCREG_DE_ADDRESS_UEX_ResetValue                               0x00000000

#define GCREG_DE_ADDRESS_UEX_TYPE                                        31 : 31
#define GCREG_DE_ADDRESS_UEX_TYPE_End                                         31
#define GCREG_DE_ADDRESS_UEX_TYPE_Start                                       31
#define GCREG_DE_ADDRESS_UEX_TYPE_Type                                       U01
#define   GCREG_DE_ADDRESS_UEX_TYPE_SYSTEM                                   0x0
#define   GCREG_DE_ADDRESS_UEX_TYPE_VIRTUAL_SYSTEM                           0x1

#define GCREG_DE_ADDRESS_UEX_ADDRESS                                      30 : 0
#define GCREG_DE_ADDRESS_UEX_ADDRESS_End                                      30
#define GCREG_DE_ADDRESS_UEX_ADDRESS_Start                                     0
#define GCREG_DE_ADDRESS_UEX_ADDRESS_Type                                    U31

/* Register gcregDEStrideUEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source U plane in bytes. */

#define gcregDEStrideUExRegAddrs                                          0x4AD8
#define GCREG_DE_STRIDE_UEX_Address                                      0x12B60
#define GCREG_DE_STRIDE_UEX_MSB                                               15
#define GCREG_DE_STRIDE_UEX_LSB                                                3
#define GCREG_DE_STRIDE_UEX_BLK                                                0
#define GCREG_DE_STRIDE_UEX_Count                                              8
#define GCREG_DE_STRIDE_UEX_FieldMask                                 0x0003FFFF
#define GCREG_DE_STRIDE_UEX_ReadMask                                  0x0003FFFC
#define GCREG_DE_STRIDE_UEX_WriteMask                                 0x0003FFFC
#define GCREG_DE_STRIDE_UEX_ResetValue                                0x00000000

#define GCREG_DE_STRIDE_UEX_STRIDE                                        17 : 0
#define GCREG_DE_STRIDE_UEX_STRIDE_End                                        17
#define GCREG_DE_STRIDE_UEX_STRIDE_Start                                       0
#define GCREG_DE_STRIDE_UEX_STRIDE_Type                                      U18

/* Register gcregDEAddressVEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source V plane. */

#define gcregDEAddressVExRegAddrs                                         0x4AE0
#define GCREG_DE_ADDRESS_VEX_Address                                     0x12B80
#define GCREG_DE_ADDRESS_VEX_MSB                                              15
#define GCREG_DE_ADDRESS_VEX_LSB                                               3
#define GCREG_DE_ADDRESS_VEX_BLK                                               0
#define GCREG_DE_ADDRESS_VEX_Count                                             8
#define GCREG_DE_ADDRESS_VEX_FieldMask                                0xFFFFFFFF
#define GCREG_DE_ADDRESS_VEX_ReadMask                                 0xFFFFFFFC
#define GCREG_DE_ADDRESS_VEX_WriteMask                                0xFFFFFFFC
#define GCREG_DE_ADDRESS_VEX_ResetValue                               0x00000000

#define GCREG_DE_ADDRESS_VEX_TYPE                                        31 : 31
#define GCREG_DE_ADDRESS_VEX_TYPE_End                                         31
#define GCREG_DE_ADDRESS_VEX_TYPE_Start                                       31
#define GCREG_DE_ADDRESS_VEX_TYPE_Type                                       U01
#define   GCREG_DE_ADDRESS_VEX_TYPE_SYSTEM                                   0x0
#define   GCREG_DE_ADDRESS_VEX_TYPE_VIRTUAL_SYSTEM                           0x1

#define GCREG_DE_ADDRESS_VEX_ADDRESS                                      30 : 0
#define GCREG_DE_ADDRESS_VEX_ADDRESS_End                                      30
#define GCREG_DE_ADDRESS_VEX_ADDRESS_Start                                     0
#define GCREG_DE_ADDRESS_VEX_ADDRESS_Type                                    U31

/* Register gcregDEStrideVEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stride of the source V plane in bytes. */

#define gcregDEStrideVExRegAddrs                                          0x4AE8
#define GCREG_DE_STRIDE_VEX_Address                                      0x12BA0
#define GCREG_DE_STRIDE_VEX_MSB                                               15
#define GCREG_DE_STRIDE_VEX_LSB                                                3
#define GCREG_DE_STRIDE_VEX_BLK                                                0
#define GCREG_DE_STRIDE_VEX_Count                                              8
#define GCREG_DE_STRIDE_VEX_FieldMask                                 0x0003FFFF
#define GCREG_DE_STRIDE_VEX_ReadMask                                  0x0003FFFC
#define GCREG_DE_STRIDE_VEX_WriteMask                                 0x0003FFFC
#define GCREG_DE_STRIDE_VEX_ResetValue                                0x00000000

#define GCREG_DE_STRIDE_VEX_STRIDE                                        17 : 0
#define GCREG_DE_STRIDE_VEX_STRIDE_End                                        17
#define GCREG_DE_STRIDE_VEX_STRIDE_Start                                       0
#define GCREG_DE_STRIDE_VEX_STRIDE_Type                                      U18

/* Register gcregDESrcRotationHeightEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 180/270 degree rotation configuration for the Source surface. Height field **
** specifies the height of the surface in pixels.                             */

#define gcregDESrcRotationHeightExRegAddrs                                0x4AF0
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_Address                          0x12BC0
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_MSB                                   15
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_LSB                                    3
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_BLK                                    0
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_Count                                  8
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_FieldMask                     0x0000FFFF
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_ReadMask                      0x0000FFFF
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_WriteMask                     0x0000FFFF
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_ResetValue                    0x00000000

#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_HEIGHT                            15 : 0
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_HEIGHT_End                            15
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_HEIGHT_Start                           0
#define GCREG_DE_SRC_ROTATION_HEIGHT_EX_HEIGHT_Type                          U16

/* Register gcregDERotAngleEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 0/90/180/270 degree rotation configuration for the Source surface. Height  **
** field specifies the height of the surface in pixels.                       */

#define gcregDERotAngleExRegAddrs                                         0x4AF8
#define GCREG_DE_ROT_ANGLE_EX_Address                                    0x12BE0
#define GCREG_DE_ROT_ANGLE_EX_MSB                                             15
#define GCREG_DE_ROT_ANGLE_EX_LSB                                              3
#define GCREG_DE_ROT_ANGLE_EX_BLK                                              0
#define GCREG_DE_ROT_ANGLE_EX_Count                                            8
#define GCREG_DE_ROT_ANGLE_EX_FieldMask                               0x000BB33F
#define GCREG_DE_ROT_ANGLE_EX_ReadMask                                0x000BB33F
#define GCREG_DE_ROT_ANGLE_EX_WriteMask                               0x000BB33F
#define GCREG_DE_ROT_ANGLE_EX_ResetValue                              0x00000000

#define GCREG_DE_ROT_ANGLE_EX_SRC                                          2 : 0
#define GCREG_DE_ROT_ANGLE_EX_SRC_End                                          2
#define GCREG_DE_ROT_ANGLE_EX_SRC_Start                                        0
#define GCREG_DE_ROT_ANGLE_EX_SRC_Type                                       U03
#define   GCREG_DE_ROT_ANGLE_EX_SRC_ROT0                                     0x0
#define   GCREG_DE_ROT_ANGLE_EX_SRC_FLIP_X                                   0x1
#define   GCREG_DE_ROT_ANGLE_EX_SRC_FLIP_Y                                   0x2
#define   GCREG_DE_ROT_ANGLE_EX_SRC_ROT90                                    0x4
#define   GCREG_DE_ROT_ANGLE_EX_SRC_ROT180                                   0x5
#define   GCREG_DE_ROT_ANGLE_EX_SRC_ROT270                                   0x6

#define GCREG_DE_ROT_ANGLE_EX_DST                                          5 : 3
#define GCREG_DE_ROT_ANGLE_EX_DST_End                                          5
#define GCREG_DE_ROT_ANGLE_EX_DST_Start                                        3
#define GCREG_DE_ROT_ANGLE_EX_DST_Type                                       U03
#define   GCREG_DE_ROT_ANGLE_EX_DST_ROT0                                     0x0
#define   GCREG_DE_ROT_ANGLE_EX_DST_FLIP_X                                   0x1
#define   GCREG_DE_ROT_ANGLE_EX_DST_FLIP_Y                                   0x2
#define   GCREG_DE_ROT_ANGLE_EX_DST_ROT90                                    0x4
#define   GCREG_DE_ROT_ANGLE_EX_DST_ROT180                                   0x5
#define   GCREG_DE_ROT_ANGLE_EX_DST_ROT270                                   0x6

#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC                                     8 : 8
#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC_End                                     8
#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC_Start                                   8
#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC_Type                                  U01
#define   GCREG_DE_ROT_ANGLE_EX_MASK_SRC_ENABLED                             0x0
#define   GCREG_DE_ROT_ANGLE_EX_MASK_SRC_MASKED                              0x1

#define GCREG_DE_ROT_ANGLE_EX_MASK_DST                                     9 : 9
#define GCREG_DE_ROT_ANGLE_EX_MASK_DST_End                                     9
#define GCREG_DE_ROT_ANGLE_EX_MASK_DST_Start                                   9
#define GCREG_DE_ROT_ANGLE_EX_MASK_DST_Type                                  U01
#define   GCREG_DE_ROT_ANGLE_EX_MASK_DST_ENABLED                             0x0
#define   GCREG_DE_ROT_ANGLE_EX_MASK_DST_MASKED                              0x1

#define GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR                                 13 : 12
#define GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR_End                                  13
#define GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR_Start                                12
#define GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR_Type                                U02
#define   GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR_NONE                              0x0
#define   GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR_MIRROR_X                          0x1
#define   GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR_MIRROR_Y                          0x2
#define   GCREG_DE_ROT_ANGLE_EX_SRC_MIRROR_MIRROR_XY                         0x3

#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC_MIRROR                            15 : 15
#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC_MIRROR_End                             15
#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC_MIRROR_Start                           15
#define GCREG_DE_ROT_ANGLE_EX_MASK_SRC_MIRROR_Type                           U01
#define   GCREG_DE_ROT_ANGLE_EX_MASK_SRC_MIRROR_ENABLED                      0x0
#define   GCREG_DE_ROT_ANGLE_EX_MASK_SRC_MIRROR_MASKED                       0x1

#define GCREG_DE_ROT_ANGLE_EX_DST_MIRROR                                 17 : 16
#define GCREG_DE_ROT_ANGLE_EX_DST_MIRROR_End                                  17
#define GCREG_DE_ROT_ANGLE_EX_DST_MIRROR_Start                                16
#define GCREG_DE_ROT_ANGLE_EX_DST_MIRROR_Type                                U02
#define   GCREG_DE_ROT_ANGLE_EX_DST_MIRROR_NONE                              0x0
#define   GCREG_DE_ROT_ANGLE_EX_DST_MIRROR_MIRROR_X                          0x1
#define   GCREG_DE_ROT_ANGLE_EX_DST_MIRROR_MIRROR_Y                          0x2
#define   GCREG_DE_ROT_ANGLE_EX_DST_MIRROR_MIRROR_XY                         0x3

#define GCREG_DE_ROT_ANGLE_EX_MASK_DST_MIRROR                            19 : 19
#define GCREG_DE_ROT_ANGLE_EX_MASK_DST_MIRROR_End                             19
#define GCREG_DE_ROT_ANGLE_EX_MASK_DST_MIRROR_Start                           19
#define GCREG_DE_ROT_ANGLE_EX_MASK_DST_MIRROR_Type                           U01
#define   GCREG_DE_ROT_ANGLE_EX_MASK_DST_MIRROR_ENABLED                      0x0
#define   GCREG_DE_ROT_ANGLE_EX_MASK_DST_MIRROR_MASKED                       0x1

/* Register gcregDEGlobalSrcColorEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the global source color and alpha values. */

#define gcregDEGlobalSrcColorExRegAddrs                                   0x4B00
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_Address                             0x12C00
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_MSB                                      15
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_LSB                                       3
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_BLK                                       0
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_Count                                     8
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_FieldMask                        0xFFFFFFFF
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_ReadMask                         0xFFFFFFFF
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_WriteMask                        0xFFFFFFFF
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_ResetValue                       0x00000000

#define GCREG_DE_GLOBAL_SRC_COLOR_EX_ALPHA                               31 : 24
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_ALPHA_End                                31
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_ALPHA_Start                              24
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_ALPHA_Type                              U08

#define GCREG_DE_GLOBAL_SRC_COLOR_EX_RED                                 23 : 16
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_RED_End                                  23
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_RED_Start                                16
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_RED_Type                                U08

#define GCREG_DE_GLOBAL_SRC_COLOR_EX_GREEN                                15 : 8
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_GREEN_End                                15
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_GREEN_Start                               8
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_GREEN_Type                              U08

#define GCREG_DE_GLOBAL_SRC_COLOR_EX_BLUE                                  7 : 0
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_BLUE_End                                  7
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_BLUE_Start                                0
#define GCREG_DE_GLOBAL_SRC_COLOR_EX_BLUE_Type                               U08

/* Register gcregDEGlobalDestColorEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the global destination color and alpha values. */

#define gcregDEGlobalDestColorExRegAddrs                                  0x4B08
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_Address                            0x12C20
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_MSB                                     15
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_LSB                                      3
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_BLK                                      0
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_Count                                    8
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_FieldMask                       0xFFFFFFFF
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_ReadMask                        0xFFFFFFFF
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_WriteMask                       0xFFFFFFFF
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_ResetValue                      0x00000000

#define GCREG_DE_GLOBAL_DEST_COLOR_EX_ALPHA                              31 : 24
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_ALPHA_End                               31
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_ALPHA_Start                             24
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_ALPHA_Type                             U08

#define GCREG_DE_GLOBAL_DEST_COLOR_EX_RED                                23 : 16
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_RED_End                                 23
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_RED_Start                               16
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_RED_Type                               U08

#define GCREG_DE_GLOBAL_DEST_COLOR_EX_GREEN                               15 : 8
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_GREEN_End                               15
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_GREEN_Start                              8
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_GREEN_Type                             U08

#define GCREG_DE_GLOBAL_DEST_COLOR_EX_BLUE                                 7 : 0
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_BLUE_End                                 7
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_BLUE_Start                               0
#define GCREG_DE_GLOBAL_DEST_COLOR_EX_BLUE_Type                              U08

/* Register gcregDEColorMultiplyModesEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Color modes to multiply Source or Destination pixel color by alpha         **
** channel. Alpha can be from global color source or current pixel.           */

#define gcregDEColorMultiplyModesExRegAddrs                               0x4B10
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_Address                         0x12C40
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_MSB                                  15
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_LSB                                   3
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_BLK                                   0
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_Count                                 8
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_FieldMask                    0x00100311
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_ReadMask                     0x00100311
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_WriteMask                    0x00100311
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_ResetValue                   0x00000000

#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_PREMULTIPLY                   0 : 0
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_PREMULTIPLY_End                   0
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_PREMULTIPLY_Start                 0
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_PREMULTIPLY_Type                U01
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_PREMULTIPLY_DISABLE           0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_PREMULTIPLY_ENABLE            0x1

#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_PREMULTIPLY                   4 : 4
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_PREMULTIPLY_End                   4
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_PREMULTIPLY_Start                 4
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_PREMULTIPLY_Type                U01
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_PREMULTIPLY_DISABLE           0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_PREMULTIPLY_ENABLE            0x1

#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_GLOBAL_PREMULTIPLY            9 : 8
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_GLOBAL_PREMULTIPLY_End            9
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_GLOBAL_PREMULTIPLY_Start          8
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_GLOBAL_PREMULTIPLY_Type         U02
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_GLOBAL_PREMULTIPLY_DISABLE    0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_GLOBAL_PREMULTIPLY_ALPHA      0x1
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_SRC_GLOBAL_PREMULTIPLY_COLOR      0x2

#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_DEMULTIPLY                  20 : 20
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_DEMULTIPLY_End                   20
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_DEMULTIPLY_Start                 20
#define GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_DEMULTIPLY_Type                 U01
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_DEMULTIPLY_DISABLE            0x0
#define   GCREG_DE_COLOR_MULTIPLY_MODES_EX_DST_DEMULTIPLY_ENABLE             0x1

/* Register gcregPETransparencyEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregPETransparencyExRegAddrs                                     0x4B18
#define GCREG_PE_TRANSPARENCY_EX_Address                                 0x12C60
#define GCREG_PE_TRANSPARENCY_EX_MSB                                          15
#define GCREG_PE_TRANSPARENCY_EX_LSB                                           3
#define GCREG_PE_TRANSPARENCY_EX_BLK                                           0
#define GCREG_PE_TRANSPARENCY_EX_Count                                         8
#define GCREG_PE_TRANSPARENCY_EX_FieldMask                            0xB3331333
#define GCREG_PE_TRANSPARENCY_EX_ReadMask                             0xB3331333
#define GCREG_PE_TRANSPARENCY_EX_WriteMask                            0xB3331333
#define GCREG_PE_TRANSPARENCY_EX_ResetValue                           0x00000000

/* Source transparency mode. */
#define GCREG_PE_TRANSPARENCY_EX_SOURCE                                    1 : 0
#define GCREG_PE_TRANSPARENCY_EX_SOURCE_End                                    1
#define GCREG_PE_TRANSPARENCY_EX_SOURCE_Start                                  0
#define GCREG_PE_TRANSPARENCY_EX_SOURCE_Type                                 U02
#define   GCREG_PE_TRANSPARENCY_EX_SOURCE_OPAQUE                             0x0
#define   GCREG_PE_TRANSPARENCY_EX_SOURCE_MASK                               0x1
#define   GCREG_PE_TRANSPARENCY_EX_SOURCE_KEY                                0x2

/* Pattern transparency mode. KEY transparency mode is reserved. */
#define GCREG_PE_TRANSPARENCY_EX_PATTERN                                   5 : 4
#define GCREG_PE_TRANSPARENCY_EX_PATTERN_End                                   5
#define GCREG_PE_TRANSPARENCY_EX_PATTERN_Start                                 4
#define GCREG_PE_TRANSPARENCY_EX_PATTERN_Type                                U02
#define   GCREG_PE_TRANSPARENCY_EX_PATTERN_OPAQUE                            0x0
#define   GCREG_PE_TRANSPARENCY_EX_PATTERN_MASK                              0x1
#define   GCREG_PE_TRANSPARENCY_EX_PATTERN_KEY                               0x2

/* Destination transparency mode. MASK transparency mode is reserved. */
#define GCREG_PE_TRANSPARENCY_EX_DESTINATION                               9 : 8
#define GCREG_PE_TRANSPARENCY_EX_DESTINATION_End                               9
#define GCREG_PE_TRANSPARENCY_EX_DESTINATION_Start                             8
#define GCREG_PE_TRANSPARENCY_EX_DESTINATION_Type                            U02
#define   GCREG_PE_TRANSPARENCY_EX_DESTINATION_OPAQUE                        0x0
#define   GCREG_PE_TRANSPARENCY_EX_DESTINATION_MASK                          0x1
#define   GCREG_PE_TRANSPARENCY_EX_DESTINATION_KEY                           0x2

/* Mask field for Source/Pattern/Destination fields. */
#define GCREG_PE_TRANSPARENCY_EX_MASK_TRANSPARENCY                       12 : 12
#define GCREG_PE_TRANSPARENCY_EX_MASK_TRANSPARENCY_End                        12
#define GCREG_PE_TRANSPARENCY_EX_MASK_TRANSPARENCY_Start                      12
#define GCREG_PE_TRANSPARENCY_EX_MASK_TRANSPARENCY_Type                      U01
#define   GCREG_PE_TRANSPARENCY_EX_MASK_TRANSPARENCY_ENABLED                 0x0
#define   GCREG_PE_TRANSPARENCY_EX_MASK_TRANSPARENCY_MASKED                  0x1

/* Source usage override. */
#define GCREG_PE_TRANSPARENCY_EX_USE_SRC_OVERRIDE                        17 : 16
#define GCREG_PE_TRANSPARENCY_EX_USE_SRC_OVERRIDE_End                         17
#define GCREG_PE_TRANSPARENCY_EX_USE_SRC_OVERRIDE_Start                       16
#define GCREG_PE_TRANSPARENCY_EX_USE_SRC_OVERRIDE_Type                       U02
#define   GCREG_PE_TRANSPARENCY_EX_USE_SRC_OVERRIDE_DEFAULT                  0x0
#define   GCREG_PE_TRANSPARENCY_EX_USE_SRC_OVERRIDE_USE_ENABLE               0x1
#define   GCREG_PE_TRANSPARENCY_EX_USE_SRC_OVERRIDE_USE_DISABLE              0x2

/* Pattern usage override. */
#define GCREG_PE_TRANSPARENCY_EX_USE_PAT_OVERRIDE                        21 : 20
#define GCREG_PE_TRANSPARENCY_EX_USE_PAT_OVERRIDE_End                         21
#define GCREG_PE_TRANSPARENCY_EX_USE_PAT_OVERRIDE_Start                       20
#define GCREG_PE_TRANSPARENCY_EX_USE_PAT_OVERRIDE_Type                       U02
#define   GCREG_PE_TRANSPARENCY_EX_USE_PAT_OVERRIDE_DEFAULT                  0x0
#define   GCREG_PE_TRANSPARENCY_EX_USE_PAT_OVERRIDE_USE_ENABLE               0x1
#define   GCREG_PE_TRANSPARENCY_EX_USE_PAT_OVERRIDE_USE_DISABLE              0x2

/* Destination usage override. */
#define GCREG_PE_TRANSPARENCY_EX_USE_DST_OVERRIDE                        25 : 24
#define GCREG_PE_TRANSPARENCY_EX_USE_DST_OVERRIDE_End                         25
#define GCREG_PE_TRANSPARENCY_EX_USE_DST_OVERRIDE_Start                       24
#define GCREG_PE_TRANSPARENCY_EX_USE_DST_OVERRIDE_Type                       U02
#define   GCREG_PE_TRANSPARENCY_EX_USE_DST_OVERRIDE_DEFAULT                  0x0
#define   GCREG_PE_TRANSPARENCY_EX_USE_DST_OVERRIDE_USE_ENABLE               0x1
#define   GCREG_PE_TRANSPARENCY_EX_USE_DST_OVERRIDE_USE_DISABLE              0x2

/* 2D resource usage override mask field. */
#define GCREG_PE_TRANSPARENCY_EX_MASK_RESOURCE_OVERRIDE                  28 : 28
#define GCREG_PE_TRANSPARENCY_EX_MASK_RESOURCE_OVERRIDE_End                   28
#define GCREG_PE_TRANSPARENCY_EX_MASK_RESOURCE_OVERRIDE_Start                 28
#define GCREG_PE_TRANSPARENCY_EX_MASK_RESOURCE_OVERRIDE_Type                 U01
#define   GCREG_PE_TRANSPARENCY_EX_MASK_RESOURCE_OVERRIDE_ENABLED            0x0
#define   GCREG_PE_TRANSPARENCY_EX_MASK_RESOURCE_OVERRIDE_MASKED             0x1

/* DFB Color Key. */
#define GCREG_PE_TRANSPARENCY_EX_DFB_COLOR_KEY                           29 : 29
#define GCREG_PE_TRANSPARENCY_EX_DFB_COLOR_KEY_End                            29
#define GCREG_PE_TRANSPARENCY_EX_DFB_COLOR_KEY_Start                          29
#define GCREG_PE_TRANSPARENCY_EX_DFB_COLOR_KEY_Type                          U01
#define   GCREG_PE_TRANSPARENCY_EX_DFB_COLOR_KEY_DISABLED                    0x0
#define   GCREG_PE_TRANSPARENCY_EX_DFB_COLOR_KEY_ENABLED                     0x1

#define GCREG_PE_TRANSPARENCY_EX_MASK_DFB_COLOR_KEY                      31 : 31
#define GCREG_PE_TRANSPARENCY_EX_MASK_DFB_COLOR_KEY_End                       31
#define GCREG_PE_TRANSPARENCY_EX_MASK_DFB_COLOR_KEY_Start                     31
#define GCREG_PE_TRANSPARENCY_EX_MASK_DFB_COLOR_KEY_Type                     U01
#define   GCREG_PE_TRANSPARENCY_EX_MASK_DFB_COLOR_KEY_ENABLED                0x0
#define   GCREG_PE_TRANSPARENCY_EX_MASK_DFB_COLOR_KEY_MASKED                 0x1

/* Register gcregPEControlEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* General purpose control register. */

#define gcregPEControlExRegAddrs                                          0x4B20
#define GCREG_PE_CONTROL_EX_Address                                      0x12C80
#define GCREG_PE_CONTROL_EX_MSB                                               15
#define GCREG_PE_CONTROL_EX_LSB                                                3
#define GCREG_PE_CONTROL_EX_BLK                                                0
#define GCREG_PE_CONTROL_EX_Count                                              8
#define GCREG_PE_CONTROL_EX_FieldMask                                 0x00000999
#define GCREG_PE_CONTROL_EX_ReadMask                                  0x00000999
#define GCREG_PE_CONTROL_EX_WriteMask                                 0x00000999
#define GCREG_PE_CONTROL_EX_ResetValue                                0x00000000

#define GCREG_PE_CONTROL_EX_YUV                                            0 : 0
#define GCREG_PE_CONTROL_EX_YUV_End                                            0
#define GCREG_PE_CONTROL_EX_YUV_Start                                          0
#define GCREG_PE_CONTROL_EX_YUV_Type                                         U01
#define   GCREG_PE_CONTROL_EX_YUV_601                                        0x0
#define   GCREG_PE_CONTROL_EX_YUV_709                                        0x1

#define GCREG_PE_CONTROL_EX_MASK_YUV                                       3 : 3
#define GCREG_PE_CONTROL_EX_MASK_YUV_End                                       3
#define GCREG_PE_CONTROL_EX_MASK_YUV_Start                                     3
#define GCREG_PE_CONTROL_EX_MASK_YUV_Type                                    U01
#define   GCREG_PE_CONTROL_EX_MASK_YUV_ENABLED                               0x0
#define   GCREG_PE_CONTROL_EX_MASK_YUV_MASKED                                0x1

#define GCREG_PE_CONTROL_EX_UV_SWIZZLE                                     4 : 4
#define GCREG_PE_CONTROL_EX_UV_SWIZZLE_End                                     4
#define GCREG_PE_CONTROL_EX_UV_SWIZZLE_Start                                   4
#define GCREG_PE_CONTROL_EX_UV_SWIZZLE_Type                                  U01
#define   GCREG_PE_CONTROL_EX_UV_SWIZZLE_UV                                  0x0
#define   GCREG_PE_CONTROL_EX_UV_SWIZZLE_VU                                  0x1

#define GCREG_PE_CONTROL_EX_MASK_UV_SWIZZLE                                7 : 7
#define GCREG_PE_CONTROL_EX_MASK_UV_SWIZZLE_End                                7
#define GCREG_PE_CONTROL_EX_MASK_UV_SWIZZLE_Start                              7
#define GCREG_PE_CONTROL_EX_MASK_UV_SWIZZLE_Type                             U01
#define   GCREG_PE_CONTROL_EX_MASK_UV_SWIZZLE_ENABLED                        0x0
#define   GCREG_PE_CONTROL_EX_MASK_UV_SWIZZLE_MASKED                         0x1

/* YUV to RGB convert enable */
#define GCREG_PE_CONTROL_EX_YUVRGB                                         8 : 8
#define GCREG_PE_CONTROL_EX_YUVRGB_End                                         8
#define GCREG_PE_CONTROL_EX_YUVRGB_Start                                       8
#define GCREG_PE_CONTROL_EX_YUVRGB_Type                                      U01
#define   GCREG_PE_CONTROL_EX_YUVRGB_DISABLED                                0x0
#define   GCREG_PE_CONTROL_EX_YUVRGB_ENABLED                                 0x1

#define GCREG_PE_CONTROL_EX_MASK_YUVRGB                                  11 : 11
#define GCREG_PE_CONTROL_EX_MASK_YUVRGB_End                                   11
#define GCREG_PE_CONTROL_EX_MASK_YUVRGB_Start                                 11
#define GCREG_PE_CONTROL_EX_MASK_YUVRGB_Type                                 U01
#define   GCREG_PE_CONTROL_EX_MASK_YUVRGB_ENABLED                            0x0
#define   GCREG_PE_CONTROL_EX_MASK_YUVRGB_MASKED                             0x1

/* Register gcregDESrcColorKeyHighEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Defines the source transparency color in source format. */

#define gcregDESrcColorKeyHighExRegAddrs                                  0x4B28
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_Address                           0x12CA0
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_MSB                                    15
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_LSB                                     3
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_BLK                                     0
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_Count                                   8
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_FieldMask                      0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_ReadMask                       0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_WriteMask                      0xFFFFFFFF
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_ResetValue                     0x00000000

#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_ALPHA                             31 : 24
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_ALPHA_End                              31
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_ALPHA_Start                            24
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_ALPHA_Type                            U08

#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_RED                               23 : 16
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_RED_End                                23
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_RED_Start                              16
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_RED_Type                              U08

#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_GREEN                              15 : 8
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_GREEN_End                              15
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_GREEN_Start                             8
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_GREEN_Type                            U08

#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_BLUE                                7 : 0
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_BLUE_End                                7
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_BLUE_Start                              0
#define GCREG_DE_SRC_COLOR_KEY_HIGH_EX_BLUE_Type                             U08

/* Register gcregDESrcExConfigEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcregDESrcExConfigExRegAddrs                                      0x4B30
#define GCREG_DE_SRC_EX_CONFIG_EX_Address                                0x12CC0
#define GCREG_DE_SRC_EX_CONFIG_EX_MSB                                         15
#define GCREG_DE_SRC_EX_CONFIG_EX_LSB                                          3
#define GCREG_DE_SRC_EX_CONFIG_EX_BLK                                          0
#define GCREG_DE_SRC_EX_CONFIG_EX_Count                                        8
#define GCREG_DE_SRC_EX_CONFIG_EX_FieldMask                           0x00000109
#define GCREG_DE_SRC_EX_CONFIG_EX_ReadMask                            0x00000109
#define GCREG_DE_SRC_EX_CONFIG_EX_WriteMask                           0x00000109
#define GCREG_DE_SRC_EX_CONFIG_EX_ResetValue                          0x00000000

/* Source multi tiled address computation control. */
#define GCREG_DE_SRC_EX_CONFIG_EX_MULTI_TILED                              0 : 0
#define GCREG_DE_SRC_EX_CONFIG_EX_MULTI_TILED_End                              0
#define GCREG_DE_SRC_EX_CONFIG_EX_MULTI_TILED_Start                            0
#define GCREG_DE_SRC_EX_CONFIG_EX_MULTI_TILED_Type                           U01
#define   GCREG_DE_SRC_EX_CONFIG_EX_MULTI_TILED_DISABLED                     0x0
#define   GCREG_DE_SRC_EX_CONFIG_EX_MULTI_TILED_ENABLED                      0x1

/* Source super tiled address computation control. */
#define GCREG_DE_SRC_EX_CONFIG_EX_SUPER_TILED                              3 : 3
#define GCREG_DE_SRC_EX_CONFIG_EX_SUPER_TILED_End                              3
#define GCREG_DE_SRC_EX_CONFIG_EX_SUPER_TILED_Start                            3
#define GCREG_DE_SRC_EX_CONFIG_EX_SUPER_TILED_Type                           U01
#define   GCREG_DE_SRC_EX_CONFIG_EX_SUPER_TILED_DISABLED                     0x0
#define   GCREG_DE_SRC_EX_CONFIG_EX_SUPER_TILED_ENABLED                      0x1

/* Source super tiled address computation control. */
#define GCREG_DE_SRC_EX_CONFIG_EX_MINOR_TILED                              8 : 8
#define GCREG_DE_SRC_EX_CONFIG_EX_MINOR_TILED_End                              8
#define GCREG_DE_SRC_EX_CONFIG_EX_MINOR_TILED_Start                            8
#define GCREG_DE_SRC_EX_CONFIG_EX_MINOR_TILED_Type                           U01
#define   GCREG_DE_SRC_EX_CONFIG_EX_MINOR_TILED_DISABLED                     0x0
#define   GCREG_DE_SRC_EX_CONFIG_EX_MINOR_TILED_ENABLED                      0x1

/* Register gcregDESrcExAddressEx (8 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 32-bit aligned base address of the source extra surface. */

#define gcregDESrcExAddressExRegAddrs                                     0x4B38
#define GCREG_DE_SRC_EX_ADDRESS_EX_Address                               0x12CE0
#define GCREG_DE_SRC_EX_ADDRESS_EX_MSB                                        15
#define GCREG_DE_SRC_EX_ADDRESS_EX_LSB                                         3
#define GCREG_DE_SRC_EX_ADDRESS_EX_BLK                                         0
#define GCREG_DE_SRC_EX_ADDRESS_EX_Count                                       8
#define GCREG_DE_SRC_EX_ADDRESS_EX_FieldMask                          0xFFFFFFFF
#define GCREG_DE_SRC_EX_ADDRESS_EX_ReadMask                           0xFFFFFFFC
#define GCREG_DE_SRC_EX_ADDRESS_EX_WriteMask                          0xFFFFFFFC
#define GCREG_DE_SRC_EX_ADDRESS_EX_ResetValue                         0x00000000

#define GCREG_DE_SRC_EX_ADDRESS_EX_TYPE                                  31 : 31
#define GCREG_DE_SRC_EX_ADDRESS_EX_TYPE_End                                   31
#define GCREG_DE_SRC_EX_ADDRESS_EX_TYPE_Start                                 31
#define GCREG_DE_SRC_EX_ADDRESS_EX_TYPE_Type                                 U01
#define   GCREG_DE_SRC_EX_ADDRESS_EX_TYPE_SYSTEM                             0x0
#define   GCREG_DE_SRC_EX_ADDRESS_EX_TYPE_VIRTUAL_SYSTEM                     0x1

#define GCREG_DE_SRC_EX_ADDRESS_EX_ADDRESS                                30 : 0
#define GCREG_DE_SRC_EX_ADDRESS_EX_ADDRESS_End                                30
#define GCREG_DE_SRC_EX_ADDRESS_EX_ADDRESS_Start                               0
#define GCREG_DE_SRC_EX_ADDRESS_EX_ADDRESS_Type                              U31

/*******************************************************************************
**                                ~~~~~~~~~~~~~                               **
**                                Command DE2PE                               **
**                                ~~~~~~~~~~~~~                               **
*******************************************************************************/

/* Offset Command
** ~~~~~~~~~~~~~~ */

#define DE2PE_COMMAND_PIXEL                                                0 : 0
#define DE2PE_COMMAND_PIXEL_End                                                0
#define DE2PE_COMMAND_PIXEL_Start                                              0
#define DE2PE_COMMAND_PIXEL_Type                                             U01
#define   DE2PE_COMMAND_PIXEL_INVALID                                        0x0
#define   DE2PE_COMMAND_PIXEL_VALID                                          0x1
#define   DE2PE_COMMAND_PIXEL_OPAQUE                                         0x0
#define   DE2PE_COMMAND_PIXEL_TRANSPARENT                                    0x1

/*******************************************************************************
**                           ~~~~~~~~~~~~~~~~~~~~~~~                          **
**                           Command AQDrawingEngine                          **
**                           ~~~~~~~~~~~~~~~~~~~~~~~                          **
*******************************************************************************/

/* Offset Format
** ~~~~~~~~~~~~~ */

#define AQ_DRAWING_ENGINE_FORMAT_SUB_SAMPLE_MODE_YUV                     12 : 12
#define AQ_DRAWING_ENGINE_FORMAT_SUB_SAMPLE_MODE_YUV_End                      12
#define AQ_DRAWING_ENGINE_FORMAT_SUB_SAMPLE_MODE_YUV_Start                    12
#define AQ_DRAWING_ENGINE_FORMAT_SUB_SAMPLE_MODE_YUV_Type                    U01
#define   AQ_DRAWING_ENGINE_FORMAT_SUB_SAMPLE_MODE_YUV_MODE422               0x0
#define   AQ_DRAWING_ENGINE_FORMAT_SUB_SAMPLE_MODE_YUV_MODE420               0x1

#define AQ_DRAWING_ENGINE_FORMAT_SWIZZLE                                   9 : 8
#define AQ_DRAWING_ENGINE_FORMAT_SWIZZLE_End                                   9
#define AQ_DRAWING_ENGINE_FORMAT_SWIZZLE_Start                                 8
#define AQ_DRAWING_ENGINE_FORMAT_SWIZZLE_Type                                U02
#define   AQ_DRAWING_ENGINE_FORMAT_SWIZZLE_ARGB                              0x0
#define   AQ_DRAWING_ENGINE_FORMAT_SWIZZLE_RGBA                              0x1
#define   AQ_DRAWING_ENGINE_FORMAT_SWIZZLE_ABGR                              0x2
#define   AQ_DRAWING_ENGINE_FORMAT_SWIZZLE_BGRA                              0x3

#define AQ_DRAWING_ENGINE_FORMAT_FORMAT                                    4 : 0
#define AQ_DRAWING_ENGINE_FORMAT_FORMAT_End                                    4
#define AQ_DRAWING_ENGINE_FORMAT_FORMAT_Start                                  0
#define AQ_DRAWING_ENGINE_FORMAT_FORMAT_Type                                 U05
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_X4R4G4B4                          0x00
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_A4R4G4B4                          0x01
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_X1R5G5B5                          0x02
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_A1R5G5B5                          0x03
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_R5G6B5                            0x04
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_X8R8G8B8                          0x05
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_A8R8G8B8                          0x06
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_YUY2                              0x07
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_UYVY                              0x08
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_INDEX8                            0x09
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_MONOCHROME                        0x0A
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_YV12                              0x0F
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_A8                                0x10
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_NV12                              0x11
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_NV16                              0x12
#define   AQ_DRAWING_ENGINE_FORMAT_FORMAT_RG16                              0x13

/* Offset AlphaBlending
** ~~~~~~~~~~~~~~~~~~~~ */

#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_ALPHA_MODE                        0 : 0
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_ALPHA_MODE_End                        0
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_ALPHA_MODE_Start                      0
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_ALPHA_MODE_Type                     U01
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_ALPHA_MODE_NORMAL                 0x0
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_ALPHA_MODE_INVERSED               0x1

#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_GLOBAL_ALPHA_MODE                 5 : 4
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_GLOBAL_ALPHA_MODE_End                 5
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_GLOBAL_ALPHA_MODE_Start               4
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_GLOBAL_ALPHA_MODE_Type              U02
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_GLOBAL_ALPHA_MODE_NORMAL          0x0
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_GLOBAL_ALPHA_MODE_GLOBAL          0x1
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_GLOBAL_ALPHA_MODE_SCALED          0x2

#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_COLOR_MODE                      13 : 12
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_COLOR_MODE_End                       13
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_COLOR_MODE_Start                     12
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_COLOR_MODE_Type                     U02
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_COLOR_MODE_NORMAL                 0x0
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_COLOR_MODE_MULTIPLY               0x1

#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE                   18 : 16
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_End                    18
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_Start                  16
#define AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_Type                  U03
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_ZERO                0x0
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_ONE                 0x1
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_NORMAL              0x2
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_INVERSED            0x3
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_COLOR               0x4
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_COLOR_INVERSED      0x5
#define   AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_SATURATED_ALPHA     0x6
#define  AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_SATURATED_DEST_ALPHA 0x7

/* Offset ResourceUsage
** ~~~~~~~~~~~~~~~~~~~~ */

#define AQ_DRAWING_ENGINE_RESOURCE_USAGE_OVERRIDE                          1 : 0
#define AQ_DRAWING_ENGINE_RESOURCE_USAGE_OVERRIDE_End                          1
#define AQ_DRAWING_ENGINE_RESOURCE_USAGE_OVERRIDE_Start                        0
#define AQ_DRAWING_ENGINE_RESOURCE_USAGE_OVERRIDE_Type                       U02
#define   AQ_DRAWING_ENGINE_RESOURCE_USAGE_OVERRIDE_DEFAULT                  0x0
#define   AQ_DRAWING_ENGINE_RESOURCE_USAGE_OVERRIDE_USE_ENABLE               0x1
#define   AQ_DRAWING_ENGINE_RESOURCE_USAGE_OVERRIDE_USE_DISABLE              0x2

