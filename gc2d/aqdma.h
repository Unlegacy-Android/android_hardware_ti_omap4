/*
 * aqdma.h
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
**                               ~~~~~~~~~~~~~~                               **
**                               Module DmaUnit                               **
**                               ~~~~~~~~~~~~~~                               **
*******************************************************************************/


/* Register AQCmdBufferAddr **
** ~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Base address for the command buffer.  The address must be 64-bit aligned   **
** and it is always physical.  To use addresses above 0x8000_0000, program    **
** AQMemoryFE with the appropriate offset.  Also, this register cannot be     **
** read.  To check the value of the current fetch address use                 **
** AQFEDebugCurCmdAdr. Since this is a write only register is has no reset    **
** value.                                                                     */

#define AQCmdBufferAddrRegAddrs                                           0x0195
#define AQ_CMD_BUFFER_ADDR_Address                                       0x00654
#define AQ_CMD_BUFFER_ADDR_MSB                                                15
#define AQ_CMD_BUFFER_ADDR_LSB                                                 0
#define AQ_CMD_BUFFER_ADDR_BLK                                                 0
#define AQ_CMD_BUFFER_ADDR_Count                                               1
#define AQ_CMD_BUFFER_ADDR_FieldMask                                  0xFFFFFFFF
#define AQ_CMD_BUFFER_ADDR_ReadMask                                   0x00000000
#define AQ_CMD_BUFFER_ADDR_WriteMask                                  0xFFFFFFFC
#define AQ_CMD_BUFFER_ADDR_ResetValue                                 0x00000000

/* Programmers should always write 0 to this bit */
#define AQ_CMD_BUFFER_ADDR_TYPE                                          31 : 31
#define AQ_CMD_BUFFER_ADDR_TYPE_End                                           31
#define AQ_CMD_BUFFER_ADDR_TYPE_Start                                         31
#define AQ_CMD_BUFFER_ADDR_TYPE_Type                                         U01
#define   AQ_CMD_BUFFER_ADDR_TYPE_SYSTEM                                     0x0
#define   AQ_CMD_BUFFER_ADDR_TYPE_VIRTUAL_SYSTEM                             0x1

#define AQ_CMD_BUFFER_ADDR_ADDRESS                                        30 : 0
#define AQ_CMD_BUFFER_ADDR_ADDRESS_End                                        30
#define AQ_CMD_BUFFER_ADDR_ADDRESS_Start                                       0
#define AQ_CMD_BUFFER_ADDR_ADDRESS_Type                                      U31

/* Register AQCmdBufferCtrl **
** ~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Since this is a write only register is has no reset value. */

#define AQCmdBufferCtrlRegAddrs                                           0x0196
#define AQ_CMD_BUFFER_CTRL_Address                                       0x00658
#define AQ_CMD_BUFFER_CTRL_MSB                                                15
#define AQ_CMD_BUFFER_CTRL_LSB                                                 0
#define AQ_CMD_BUFFER_CTRL_BLK                                                 0
#define AQ_CMD_BUFFER_CTRL_Count                                               1
#define AQ_CMD_BUFFER_CTRL_FieldMask                                  0x0001FFFF
#define AQ_CMD_BUFFER_CTRL_ReadMask                                   0x00010000
#define AQ_CMD_BUFFER_CTRL_WriteMask                                  0x0001FFFF
#define AQ_CMD_BUFFER_CTRL_ResetValue                                 0x00000000

/* Number of 64-bit words to fetch from the command buffer. */
#define AQ_CMD_BUFFER_CTRL_PREFETCH                                       15 : 0
#define AQ_CMD_BUFFER_CTRL_PREFETCH_End                                       15
#define AQ_CMD_BUFFER_CTRL_PREFETCH_Start                                      0
#define AQ_CMD_BUFFER_CTRL_PREFETCH_Type                                     U16

/* Enable the command parser. */
#define AQ_CMD_BUFFER_CTRL_ENABLE                                        16 : 16
#define AQ_CMD_BUFFER_CTRL_ENABLE_End                                         16
#define AQ_CMD_BUFFER_CTRL_ENABLE_Start                                       16
#define AQ_CMD_BUFFER_CTRL_ENABLE_Type                                       U01
#define   AQ_CMD_BUFFER_CTRL_ENABLE_DISABLE                                  0x0
#define   AQ_CMD_BUFFER_CTRL_ENABLE_ENABLE                                   0x1

/* Register AQFEStatus **
** ~~~~~~~~~~~~~~~~~~~ */
#define AQFEStatusRegAddrs                                                0x0197
#define AQFE_STATUS_Address                                              0x0065C
#define AQFE_STATUS_MSB                                                       15
#define AQFE_STATUS_LSB                                                        0
#define AQFE_STATUS_BLK                                                        0
#define AQFE_STATUS_Count                                                      1
#define AQFE_STATUS_FieldMask                                         0x00000001
#define AQFE_STATUS_ReadMask                                          0x00000001
#define AQFE_STATUS_WriteMask                                         0x00000000
#define AQFE_STATUS_ResetValue                                        0x00000000

/* Status of the command parser. 0 --> Idle 1 --> Busy */
#define AQFE_STATUS_COMMAND_DATA                                           0 : 0
#define AQFE_STATUS_COMMAND_DATA_End                                           0
#define AQFE_STATUS_COMMAND_DATA_Start                                         0
#define AQFE_STATUS_COMMAND_DATA_Type                                        U01
#define   AQFE_STATUS_COMMAND_DATA_IDLE                                      0x0
#define   AQFE_STATUS_COMMAND_DATA_BUSY                                      0x1


/* Register gcregFEDETimeout **
** ~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Timeout counter for DE in the number of clocks. When the are no DE         **
** commands for the specified number of clocks, a 2D PE cache flush state     **
** will be automatically generated by FE. When set to zero (default), timeout **
** counter is disabled.                                                       */

#define gcregFEDETimeoutRegAddrs                                          0x019C
#define GCREG_FEDE_TIMEOUT_Address                                       0x00670
#define GCREG_FEDE_TIMEOUT_MSB                                                15
#define GCREG_FEDE_TIMEOUT_LSB                                                 0
#define GCREG_FEDE_TIMEOUT_BLK                                                 0
#define GCREG_FEDE_TIMEOUT_Count                                               1
#define GCREG_FEDE_TIMEOUT_FieldMask                                  0xFFFFFFFF
#define GCREG_FEDE_TIMEOUT_ReadMask                                   0xFFFFFFFF
#define GCREG_FEDE_TIMEOUT_WriteMask                                  0xFFFFFFFF
#define GCREG_FEDE_TIMEOUT_ResetValue                                 0x00000000

/* Preset the timer to 5ms assuming core clock is 200MHz. */
#define GCREG_FEDE_TIMEOUT_COUNTER                                        31 : 0
#define GCREG_FEDE_TIMEOUT_COUNTER_End                                        31
#define GCREG_FEDE_TIMEOUT_COUNTER_Start                                       0
#define GCREG_FEDE_TIMEOUT_COUNTER_Type                                      U32

/* Register AQFEDebugState **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* Reserved. */

#define AQFEDebugStateRegAddrs                                            0x0198
#define AQFE_DEBUG_STATE_Address                                         0x00660
#define AQFE_DEBUG_STATE_MSB                                                  15
#define AQFE_DEBUG_STATE_LSB                                                   0
#define AQFE_DEBUG_STATE_BLK                                                   0
#define AQFE_DEBUG_STATE_Count                                                 1
#define AQFE_DEBUG_STATE_FieldMask                                    0x0003FF1F
#define AQFE_DEBUG_STATE_ReadMask                                     0x0003FF1F
#define AQFE_DEBUG_STATE_WriteMask                                    0x00000000
#define AQFE_DEBUG_STATE_ResetValue                                   0x00000000

#define AQFE_DEBUG_STATE_CMD_STATE                                         4 : 0
#define AQFE_DEBUG_STATE_CMD_STATE_End                                         4
#define AQFE_DEBUG_STATE_CMD_STATE_Start                                       0
#define AQFE_DEBUG_STATE_CMD_STATE_Type                                      U05

#define AQFE_DEBUG_STATE_CMD_DMA_STATE                                     9 : 8
#define AQFE_DEBUG_STATE_CMD_DMA_STATE_End                                     9
#define AQFE_DEBUG_STATE_CMD_DMA_STATE_Start                                   8
#define AQFE_DEBUG_STATE_CMD_DMA_STATE_Type                                  U02

#define AQFE_DEBUG_STATE_CMD_FETCH_STATE                                 11 : 10
#define AQFE_DEBUG_STATE_CMD_FETCH_STATE_End                                  11
#define AQFE_DEBUG_STATE_CMD_FETCH_STATE_Start                                10
#define AQFE_DEBUG_STATE_CMD_FETCH_STATE_Type                                U02

#define AQFE_DEBUG_STATE_REQ_DMA_STATE                                   13 : 12
#define AQFE_DEBUG_STATE_REQ_DMA_STATE_End                                    13
#define AQFE_DEBUG_STATE_REQ_DMA_STATE_Start                                  12
#define AQFE_DEBUG_STATE_REQ_DMA_STATE_Type                                  U02

#define AQFE_DEBUG_STATE_CAL_STATE                                       15 : 14
#define AQFE_DEBUG_STATE_CAL_STATE_End                                        15
#define AQFE_DEBUG_STATE_CAL_STATE_Start                                      14
#define AQFE_DEBUG_STATE_CAL_STATE_Type                                      U02

#define AQFE_DEBUG_STATE_VE_REQ_STATE                                    17 : 16
#define AQFE_DEBUG_STATE_VE_REQ_STATE_End                                     17
#define AQFE_DEBUG_STATE_VE_REQ_STATE_Start                                   16
#define AQFE_DEBUG_STATE_VE_REQ_STATE_Type                                   U02

/* Register AQFEDebugCurCmdAdr **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* This is the command decoder address.  The address is always physical so    **
** the MSB should always be 0.  It has no reset value.                        */

#define AQFEDebugCurCmdAdrRegAddrs                                        0x0199
#define AQFE_DEBUG_CUR_CMD_ADR_Address                                   0x00664
#define AQFE_DEBUG_CUR_CMD_ADR_MSB                                            15
#define AQFE_DEBUG_CUR_CMD_ADR_LSB                                             0
#define AQFE_DEBUG_CUR_CMD_ADR_BLK                                             0
#define AQFE_DEBUG_CUR_CMD_ADR_Count                                           1
#define AQFE_DEBUG_CUR_CMD_ADR_FieldMask                              0xFFFFFFF8
#define AQFE_DEBUG_CUR_CMD_ADR_ReadMask                               0xFFFFFFF8
#define AQFE_DEBUG_CUR_CMD_ADR_WriteMask                              0x00000000
#define AQFE_DEBUG_CUR_CMD_ADR_ResetValue                             0x00000000

#define AQFE_DEBUG_CUR_CMD_ADR_CUR_CMD_ADR                                31 : 3
#define AQFE_DEBUG_CUR_CMD_ADR_CUR_CMD_ADR_End                                31
#define AQFE_DEBUG_CUR_CMD_ADR_CUR_CMD_ADR_Start                               3
#define AQFE_DEBUG_CUR_CMD_ADR_CUR_CMD_ADR_Type                              U29

/* Register AQFEDebugCmdLowReg **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Reserved.  No reset value. */

#define AQFEDebugCmdLowRegRegAddrs                                        0x019A
#define AQFE_DEBUG_CMD_LOW_REG_Address                                   0x00668
#define AQFE_DEBUG_CMD_LOW_REG_MSB                                            15
#define AQFE_DEBUG_CMD_LOW_REG_LSB                                             0
#define AQFE_DEBUG_CMD_LOW_REG_BLK                                             0
#define AQFE_DEBUG_CMD_LOW_REG_Count                                           1
#define AQFE_DEBUG_CMD_LOW_REG_FieldMask                              0xFFFFFFFF
#define AQFE_DEBUG_CMD_LOW_REG_ReadMask                               0xFFFFFFFF
#define AQFE_DEBUG_CMD_LOW_REG_WriteMask                              0x00000000
#define AQFE_DEBUG_CMD_LOW_REG_ResetValue                             0x00000000

/* Command register used by CmdState. */
#define AQFE_DEBUG_CMD_LOW_REG_CMD_LOW_REG                                31 : 0
#define AQFE_DEBUG_CMD_LOW_REG_CMD_LOW_REG_End                                31
#define AQFE_DEBUG_CMD_LOW_REG_CMD_LOW_REG_Start                               0
#define AQFE_DEBUG_CMD_LOW_REG_CMD_LOW_REG_Type                              U32

/* Register AQFEDebugCmdHiReg **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Reserved.  No reset value. */

#define AQFEDebugCmdHiRegRegAddrs                                         0x019B
#define AQFE_DEBUG_CMD_HI_REG_Address                                    0x0066C
#define AQFE_DEBUG_CMD_HI_REG_MSB                                             15
#define AQFE_DEBUG_CMD_HI_REG_LSB                                              0
#define AQFE_DEBUG_CMD_HI_REG_BLK                                              0
#define AQFE_DEBUG_CMD_HI_REG_Count                                            1
#define AQFE_DEBUG_CMD_HI_REG_FieldMask                               0xFFFFFFFF
#define AQFE_DEBUG_CMD_HI_REG_ReadMask                                0xFFFFFFFF
#define AQFE_DEBUG_CMD_HI_REG_WriteMask                               0x00000000
#define AQFE_DEBUG_CMD_HI_REG_ResetValue                              0x00000000

/* Command register used by CmdState. */
#define AQFE_DEBUG_CMD_HI_REG_CMD_HI_REG                                  31 : 0
#define AQFE_DEBUG_CMD_HI_REG_CMD_HI_REG_End                                  31
#define AQFE_DEBUG_CMD_HI_REG_CMD_HI_REG_Start                                 0
#define AQFE_DEBUG_CMD_HI_REG_CMD_HI_REG_Type                                U32
