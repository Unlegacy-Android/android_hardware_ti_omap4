/*
 * aqhostiface.h
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
**                            Module HostInterface                            **
**                            ~~~~~~~~~~~~~~~~~~~~                            **
*******************************************************************************/

/* Register AQHiClockControl **
** ~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Clock control register. */

#define AQHiClockControlRegAddrs                                          0x0000
#define AQ_HI_CLOCK_CONTROL_Address                                      0x00000
#define AQ_HI_CLOCK_CONTROL_MSB                                               15
#define AQ_HI_CLOCK_CONTROL_LSB                                                0
#define AQ_HI_CLOCK_CONTROL_BLK                                                0
#define AQ_HI_CLOCK_CONTROL_Count                                              1
#define AQ_HI_CLOCK_CONTROL_FieldMask                                 0x000A17FE
#define AQ_HI_CLOCK_CONTROL_ReadMask                                  0x000A17FE
#define AQ_HI_CLOCK_CONTROL_WriteMask                                 0x000817FE
#define AQ_HI_CLOCK_CONTROL_ResetValue                                0x00000100

/* Disable 2D clock. */
#define AQ_HI_CLOCK_CONTROL_CLK2D_DIS                                      1 : 1
#define AQ_HI_CLOCK_CONTROL_CLK2D_DIS_End                                      1
#define AQ_HI_CLOCK_CONTROL_CLK2D_DIS_Start                                    1
#define AQ_HI_CLOCK_CONTROL_CLK2D_DIS_Type                                   U01

#define AQ_HI_CLOCK_CONTROL_FSCALE_VAL                                     8 : 2
#define AQ_HI_CLOCK_CONTROL_FSCALE_VAL_End                                     8
#define AQ_HI_CLOCK_CONTROL_FSCALE_VAL_Start                                   2
#define AQ_HI_CLOCK_CONTROL_FSCALE_VAL_Type                                  U07

#define AQ_HI_CLOCK_CONTROL_FSCALE_CMD_LOAD                                9 : 9
#define AQ_HI_CLOCK_CONTROL_FSCALE_CMD_LOAD_End                                9
#define AQ_HI_CLOCK_CONTROL_FSCALE_CMD_LOAD_Start                              9
#define AQ_HI_CLOCK_CONTROL_FSCALE_CMD_LOAD_Type                             U01

/* Disables clock gating for rams. */
#define AQ_HI_CLOCK_CONTROL_DISABLE_RAM_CLOCK_GATING                     10 : 10
#define AQ_HI_CLOCK_CONTROL_DISABLE_RAM_CLOCK_GATING_End                      10
#define AQ_HI_CLOCK_CONTROL_DISABLE_RAM_CLOCK_GATING_Start                    10
#define AQ_HI_CLOCK_CONTROL_DISABLE_RAM_CLOCK_GATING_Type                    U01

/* Soft resets the IP. */
#define AQ_HI_CLOCK_CONTROL_SOFT_RESET                                   12 : 12
#define AQ_HI_CLOCK_CONTROL_SOFT_RESET_End                                    12
#define AQ_HI_CLOCK_CONTROL_SOFT_RESET_Start                                  12
#define AQ_HI_CLOCK_CONTROL_SOFT_RESET_Type                                  U01

/* 2D pipe is idle. */
#define AQ_HI_CLOCK_CONTROL_IDLE2_D                                      17 : 17
#define AQ_HI_CLOCK_CONTROL_IDLE2_D_End                                       17
#define AQ_HI_CLOCK_CONTROL_IDLE2_D_Start                                     17
#define AQ_HI_CLOCK_CONTROL_IDLE2_D_Type                                     U01

/* Isolate GPU bit */
#define AQ_HI_CLOCK_CONTROL_ISOLATE_GPU                                  19 : 19
#define AQ_HI_CLOCK_CONTROL_ISOLATE_GPU_End                                   19
#define AQ_HI_CLOCK_CONTROL_ISOLATE_GPU_Start                                 19
#define AQ_HI_CLOCK_CONTROL_ISOLATE_GPU_Type                                 U01

/* Register AQHiIdle **
** ~~~~~~~~~~~~~~~~~ */

/* Idle status register. */

#define AQHiIdleRegAddrs                                                  0x0001
#define AQ_HI_IDLE_Address                                               0x00004
#define AQ_HI_IDLE_MSB                                                        15
#define AQ_HI_IDLE_LSB                                                         0
#define AQ_HI_IDLE_BLK                                                         0
#define AQ_HI_IDLE_Count                                                       1
#define AQ_HI_IDLE_FieldMask                                          0x80000007
#define AQ_HI_IDLE_ReadMask                                           0x80000007
#define AQ_HI_IDLE_WriteMask                                          0x00000000
#define AQ_HI_IDLE_ResetValue                                         0x00000007

/* FE is idle. */
#define AQ_HI_IDLE_IDLE_FE                                                 0 : 0
#define AQ_HI_IDLE_IDLE_FE_End                                                 0
#define AQ_HI_IDLE_IDLE_FE_Start                                               0
#define AQ_HI_IDLE_IDLE_FE_Type                                              U01

/* DE is idle. */
#define AQ_HI_IDLE_IDLE_DE                                                 1 : 1
#define AQ_HI_IDLE_IDLE_DE_End                                                 1
#define AQ_HI_IDLE_IDLE_DE_Start                                               1
#define AQ_HI_IDLE_IDLE_DE_Type                                              U01

/* PE is idle. */
#define AQ_HI_IDLE_IDLE_PE                                                 2 : 2
#define AQ_HI_IDLE_IDLE_PE_End                                                 2
#define AQ_HI_IDLE_IDLE_PE_Start                                               2
#define AQ_HI_IDLE_IDLE_PE_Type                                              U01

/* AXI is in low power mode. */
#define AQ_HI_IDLE_AXI_LP                                                31 : 31
#define AQ_HI_IDLE_AXI_LP_End                                                 31
#define AQ_HI_IDLE_AXI_LP_Start                                               31
#define AQ_HI_IDLE_AXI_LP_Type                                               U01

/* Register AQAxiConfig **
** ~~~~~~~~~~~~~~~~~~~~ */
#define AQAxiConfigRegAddrs                                               0x0002
#define AQ_AXI_CONFIG_Address                                            0x00008
#define AQ_AXI_CONFIG_MSB                                                     15
#define AQ_AXI_CONFIG_LSB                                                      0
#define AQ_AXI_CONFIG_BLK                                                      0
#define AQ_AXI_CONFIG_Count                                                    1
#define AQ_AXI_CONFIG_FieldMask                                       0x0000FFFF
#define AQ_AXI_CONFIG_ReadMask                                        0x0000FFFF
#define AQ_AXI_CONFIG_WriteMask                                       0x0000FFFF
#define AQ_AXI_CONFIG_ResetValue                                      0x00000000

#define AQ_AXI_CONFIG_AWID                                                 3 : 0
#define AQ_AXI_CONFIG_AWID_End                                                 3
#define AQ_AXI_CONFIG_AWID_Start                                               0
#define AQ_AXI_CONFIG_AWID_Type                                              U04

#define AQ_AXI_CONFIG_ARID                                                 7 : 4
#define AQ_AXI_CONFIG_ARID_End                                                 7
#define AQ_AXI_CONFIG_ARID_Start                                               4
#define AQ_AXI_CONFIG_ARID_Type                                              U04

#define AQ_AXI_CONFIG_AWCACHE                                             11 : 8
#define AQ_AXI_CONFIG_AWCACHE_End                                             11
#define AQ_AXI_CONFIG_AWCACHE_Start                                            8
#define AQ_AXI_CONFIG_AWCACHE_Type                                           U04

#define AQ_AXI_CONFIG_ARCACHE                                            15 : 12
#define AQ_AXI_CONFIG_ARCACHE_End                                             15
#define AQ_AXI_CONFIG_ARCACHE_Start                                           12
#define AQ_AXI_CONFIG_ARCACHE_Type                                           U04

/* Register AQAxiStatus **
** ~~~~~~~~~~~~~~~~~~~~ */
#define AQAxiStatusRegAddrs                                               0x0003
#define AQ_AXI_STATUS_Address                                            0x0000C
#define AQ_AXI_STATUS_MSB                                                     15
#define AQ_AXI_STATUS_LSB                                                      0
#define AQ_AXI_STATUS_BLK                                                      0
#define AQ_AXI_STATUS_Count                                                    1
#define AQ_AXI_STATUS_FieldMask                                       0x000003FF
#define AQ_AXI_STATUS_ReadMask                                        0x000003FF
#define AQ_AXI_STATUS_WriteMask                                       0x00000000
#define AQ_AXI_STATUS_ResetValue                                      0x00000000

#define AQ_AXI_STATUS_DET_RD_ERR                                           9 : 9
#define AQ_AXI_STATUS_DET_RD_ERR_End                                           9
#define AQ_AXI_STATUS_DET_RD_ERR_Start                                         9
#define AQ_AXI_STATUS_DET_RD_ERR_Type                                        U01

#define AQ_AXI_STATUS_DET_WR_ERR                                           8 : 8
#define AQ_AXI_STATUS_DET_WR_ERR_End                                           8
#define AQ_AXI_STATUS_DET_WR_ERR_Start                                         8
#define AQ_AXI_STATUS_DET_WR_ERR_Type                                        U01

#define AQ_AXI_STATUS_RD_ERR_ID                                            7 : 4
#define AQ_AXI_STATUS_RD_ERR_ID_End                                            7
#define AQ_AXI_STATUS_RD_ERR_ID_Start                                          4
#define AQ_AXI_STATUS_RD_ERR_ID_Type                                         U04

#define AQ_AXI_STATUS_WR_ERR_ID                                            3 : 0
#define AQ_AXI_STATUS_WR_ERR_ID_End                                            3
#define AQ_AXI_STATUS_WR_ERR_ID_Start                                          0
#define AQ_AXI_STATUS_WR_ERR_ID_Type                                         U04

/* Register AQIntrAcknowledge **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Interrupt acknowledge register.  Each bit represents a corresponding event **
** being triggered.  Reading frmo this register clears the outstanding        **
** interrupt.                                                                 */

#define AQIntrAcknowledgeRegAddrs                                         0x0004
#define AQ_INTR_ACKNOWLEDGE_Address                                      0x00010
#define AQ_INTR_ACKNOWLEDGE_MSB                                               15
#define AQ_INTR_ACKNOWLEDGE_LSB                                                0
#define AQ_INTR_ACKNOWLEDGE_BLK                                                0
#define AQ_INTR_ACKNOWLEDGE_Count                                              1
#define AQ_INTR_ACKNOWLEDGE_FieldMask                                 0xFFFFFFFF
#define AQ_INTR_ACKNOWLEDGE_ReadMask                                  0xFFFFFFFF
#define AQ_INTR_ACKNOWLEDGE_WriteMask                                 0x00000000
#define AQ_INTR_ACKNOWLEDGE_ResetValue                                0x00000000

#define AQ_INTR_ACKNOWLEDGE_INTR_VEC                                      31 : 0
#define AQ_INTR_ACKNOWLEDGE_INTR_VEC_End                                      31
#define AQ_INTR_ACKNOWLEDGE_INTR_VEC_Start                                     0
#define AQ_INTR_ACKNOWLEDGE_INTR_VEC_Type                                    U32

/* Register AQIntrEnbl **
** ~~~~~~~~~~~~~~~~~~~ */

/* Interrupt enable register.  Each bit enables a corresponding event. */

#define AQIntrEnblRegAddrs                                                0x0005
#define AQ_INTR_ENBL_Address                                             0x00014
#define AQ_INTR_ENBL_MSB                                                      15
#define AQ_INTR_ENBL_LSB                                                       0
#define AQ_INTR_ENBL_BLK                                                       0
#define AQ_INTR_ENBL_Count                                                     1
#define AQ_INTR_ENBL_FieldMask                                        0xFFFFFFFF
#define AQ_INTR_ENBL_ReadMask                                         0xFFFFFFFF
#define AQ_INTR_ENBL_WriteMask                                        0xFFFFFFFF
#define AQ_INTR_ENBL_ResetValue                                       0x00000000

#define AQ_INTR_ENBL_INTR_ENBL_VEC                                        31 : 0
#define AQ_INTR_ENBL_INTR_ENBL_VEC_End                                        31
#define AQ_INTR_ENBL_INTR_ENBL_VEC_Start                                       0
#define AQ_INTR_ENBL_INTR_ENBL_VEC_Type                                      U32

/* Register gcGpOut0 **
** ~~~~~~~~~~~~~~~~~ */

/* General Purpose output register0. R/W but not connected to anywhere */

#define gcGpOut0RegAddrs                                                  0x0019
#define GC_GP_OUT0_Address                                               0x00064
#define GC_GP_OUT0_MSB                                                        15
#define GC_GP_OUT0_LSB                                                         0
#define GC_GP_OUT0_BLK                                                         0
#define GC_GP_OUT0_Count                                                       1
#define GC_GP_OUT0_FieldMask                                          0xFFFFFFFF
#define GC_GP_OUT0_ReadMask                                           0xFFFFFFFF
#define GC_GP_OUT0_WriteMask                                          0xFFFFFFFF
#define GC_GP_OUT0_ResetValue                                         0x00000000

#define GC_GP_OUT0_COUNT                                                  31 : 0
#define GC_GP_OUT0_COUNT_End                                                  31
#define GC_GP_OUT0_COUNT_Start                                                 0
#define GC_GP_OUT0_COUNT_Type                                                U32

/* Register gcTotalCycles **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* Total cycles. This register is a free running counter.  It can be reset by **
** writing 0 to it.                                                           */

#define gcTotalCyclesRegAddrs                                             0x001E
#define GC_TOTAL_CYCLES_Address                                          0x00078
#define GC_TOTAL_CYCLES_MSB                                                   15
#define GC_TOTAL_CYCLES_LSB                                                    0
#define GC_TOTAL_CYCLES_BLK                                                    0
#define GC_TOTAL_CYCLES_Count                                                  1
#define GC_TOTAL_CYCLES_FieldMask                                     0xFFFFFFFF
#define GC_TOTAL_CYCLES_ReadMask                                      0xFFFFFFFF
#define GC_TOTAL_CYCLES_WriteMask                                     0xFFFFFFFF
#define GC_TOTAL_CYCLES_ResetValue                                    0x00000000

#define GC_TOTAL_CYCLES_CYCLES                                            31 : 0
#define GC_TOTAL_CYCLES_CYCLES_End                                            31
#define GC_TOTAL_CYCLES_CYCLES_Start                                           0
#define GC_TOTAL_CYCLES_CYCLES_Type                                          U32

/* Register gcTotalIdleCycles **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Total cycles where the GPU is idle. It is reset when  gcTotalCycles        **
** register is written to. It looks at all the  blocks but FE when            **
** determining the IP is idle.                                                */

#define gcTotalIdleCyclesRegAddrs                                         0x001F
#define GC_TOTAL_IDLE_CYCLES_Address                                     0x0007C
#define GC_TOTAL_IDLE_CYCLES_MSB                                              15
#define GC_TOTAL_IDLE_CYCLES_LSB                                               0
#define GC_TOTAL_IDLE_CYCLES_BLK                                               0
#define GC_TOTAL_IDLE_CYCLES_Count                                             1
#define GC_TOTAL_IDLE_CYCLES_FieldMask                                0xFFFFFFFF
#define GC_TOTAL_IDLE_CYCLES_ReadMask                                 0xFFFFFFFF
#define GC_TOTAL_IDLE_CYCLES_WriteMask                                0xFFFFFFFF
#define GC_TOTAL_IDLE_CYCLES_ResetValue                               0x00000000

#define GC_TOTAL_IDLE_CYCLES_CYCLES                                       31 : 0
#define GC_TOTAL_IDLE_CYCLES_CYCLES_End                                       31
#define GC_TOTAL_IDLE_CYCLES_CYCLES_Start                                      0
#define GC_TOTAL_IDLE_CYCLES_CYCLES_Type                                     U32

