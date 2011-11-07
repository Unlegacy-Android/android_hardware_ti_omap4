/*
 * aqcmd.h
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
**                                ~~~~~~~~~~~~~                               **
**                                Module Tokens                               **
**                                ~~~~~~~~~~~~~                               **
*******************************************************************************/

/* Register AQStall **
** ~~~~~~~~~~~~~~~~ */

/* Reserved for GC series of products. */

#define AQStallRegAddrs                                                   0x0F00
#define AQ_STALL_Address                                                 0x03C00
#define AQ_STALL_MSB                                                          15
#define AQ_STALL_LSB                                                           0
#define AQ_STALL_BLK                                                           0
#define AQ_STALL_Count                                                         1
#define AQ_STALL_FieldMask                                            0xC0001F1F
#define AQ_STALL_ReadMask                                             0xC0001F1F
#define AQ_STALL_WriteMask                                            0xC0001F1F
#define AQ_STALL_ResetValue                                           0x00000000

#define AQ_STALL_FLIP0                                                   30 : 30
#define AQ_STALL_FLIP0_End                                                    30
#define AQ_STALL_FLIP0_Start                                                  30
#define AQ_STALL_FLIP0_Type                                                  U01

#define AQ_STALL_FLIP1                                                   31 : 31
#define AQ_STALL_FLIP1_End                                                    31
#define AQ_STALL_FLIP1_Start                                                  31
#define AQ_STALL_FLIP1_Type                                                  U01

#define AQ_STALL_SOURCE                                                    4 : 0
#define AQ_STALL_SOURCE_End                                                    4
#define AQ_STALL_SOURCE_Start                                                  0
#define AQ_STALL_SOURCE_Type                                                 U05
#define   AQ_STALL_SOURCE_FRONT_END                                         0x01
#define   AQ_STALL_SOURCE_PIXEL_ENGINE                                      0x07
#define   AQ_STALL_SOURCE_DRAWING_ENGINE                                    0x0B

#define AQ_STALL_DESTINATION                                              12 : 8
#define AQ_STALL_DESTINATION_End                                              12
#define AQ_STALL_DESTINATION_Start                                             8
#define AQ_STALL_DESTINATION_Type                                            U05
#define   AQ_STALL_DESTINATION_FRONT_END                                    0x01
#define   AQ_STALL_DESTINATION_PIXEL_ENGINE                                 0x07
#define   AQ_STALL_DESTINATION_DRAWING_ENGINE                               0x0B


/* Register AQTrigger **
** ~~~~~~~~~~~~~~~~~~ */

/* Reserved for GC series of products. */

#define AQTriggerRegAddrs                                                 0x0F02
#define AQ_TRIGGER_Address                                               0x03C08
#define AQ_TRIGGER_MSB                                                        15
#define AQ_TRIGGER_LSB                                                         0
#define AQ_TRIGGER_BLK                                                         0
#define AQ_TRIGGER_Count                                                       1
#define AQ_TRIGGER_FieldMask                                          0x000F1F1F
#define AQ_TRIGGER_ReadMask                                           0x000F1F1F
#define AQ_TRIGGER_WriteMask                                          0x000F1F1F
#define AQ_TRIGGER_ResetValue                                         0x00000000

#define AQ_TRIGGER_ID                                                    19 : 16
#define AQ_TRIGGER_ID_End                                                     19
#define AQ_TRIGGER_ID_Start                                                   16
#define AQ_TRIGGER_ID_Type                                                   U04

#define AQ_TRIGGER_SOURCE                                                  4 : 0
#define AQ_TRIGGER_SOURCE_End                                                  4
#define AQ_TRIGGER_SOURCE_Start                                                0
#define AQ_TRIGGER_SOURCE_Type                                               U05
#define   AQ_TRIGGER_SOURCE_FRONT_END                                       0x01
#define   AQ_TRIGGER_SOURCE_PIXEL_ENGINE                                    0x07
#define   AQ_TRIGGER_SOURCE_DRAWING_ENGINE                                  0x0B

#define AQ_TRIGGER_DESTINATION                                            12 : 8
#define AQ_TRIGGER_DESTINATION_End                                            12
#define AQ_TRIGGER_DESTINATION_Start                                           8
#define AQ_TRIGGER_DESTINATION_Type                                          U05
#define   AQ_TRIGGER_DESTINATION_FRONT_END                                  0x01
#define   AQ_TRIGGER_DESTINATION_PIXEL_ENGINE                               0x07
#define   AQ_TRIGGER_DESTINATION_DRAWING_ENGINE                             0x0B

/*******************************************************************************
**                         ~~~~~~~~~~~~~~~~~~~~~~~~~~                         **
**                         Command AQCommandLoadState                         **
**                         ~~~~~~~~~~~~~~~~~~~~~~~~~~                         **
*******************************************************************************/

#define AQCommandLoadStateCmdAddrs                                        0x0F03
#define AQ_COMMAND_LOAD_STATE_Address                                    0x03C0C
#define AQ_COMMAND_LOAD_STATE_Count                                            1

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define AQ_COMMAND_LOAD_STATE_COMMAND_Index                                    0
#define AQ_COMMAND_LOAD_STATE_COMMAND_CmdAddrs                            0x0F03

/* When enabled, convert 16.16 fixed point into 32-bit floating point. */
#define AQ_COMMAND_LOAD_STATE_COMMAND_FLOAT                              26 : 26
#define AQ_COMMAND_LOAD_STATE_COMMAND_FLOAT_End                               26
#define AQ_COMMAND_LOAD_STATE_COMMAND_FLOAT_Start                             26
#define AQ_COMMAND_LOAD_STATE_COMMAND_FLOAT_Type                             U01
#define   AQ_COMMAND_LOAD_STATE_COMMAND_FLOAT_NORMAL                         0x0
#define   AQ_COMMAND_LOAD_STATE_COMMAND_FLOAT_FIXED16_DOT16                  0x1

/* Number of states. 0 = 1024. */
#define AQ_COMMAND_LOAD_STATE_COMMAND_COUNT                              25 : 16
#define AQ_COMMAND_LOAD_STATE_COMMAND_COUNT_End                               25
#define AQ_COMMAND_LOAD_STATE_COMMAND_COUNT_Start                             16
#define AQ_COMMAND_LOAD_STATE_COMMAND_COUNT_Type                             U10

/* Starting state address. */
#define AQ_COMMAND_LOAD_STATE_COMMAND_ADDRESS                             15 : 0
#define AQ_COMMAND_LOAD_STATE_COMMAND_ADDRESS_End                             15
#define AQ_COMMAND_LOAD_STATE_COMMAND_ADDRESS_Start                            0
#define AQ_COMMAND_LOAD_STATE_COMMAND_ADDRESS_Type                           U16

#define AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE                             31 : 27
#define AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_End                              31
#define AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_Start                            27
#define AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_Type                            U05
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_LOAD_STATE                   0x01
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_END                          0x02
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_NOP                          0x03
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_START_DE                     0x04
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_WAIT                         0x07
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_LINK                         0x08
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_STALL                        0x09
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_CALL                         0x0A
#define   AQ_COMMAND_LOAD_STATE_COMMAND_OPCODE_RETURN                       0x0B

/*******************************************************************************
**                            ~~~~~~~~~~~~~~~~~~~~                            **
**                            Command AQCommandEnd                            **
**                            ~~~~~~~~~~~~~~~~~~~~                            **
*******************************************************************************/

#define AQCommandEndCmdAddrs                                              0x0F04
#define AQ_COMMAND_END_Address                                           0x03C10
#define AQ_COMMAND_END_Count                                                   1

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define AQ_COMMAND_END_COMMAND_Index                                           0
#define AQ_COMMAND_END_COMMAND_CmdAddrs                                   0x0F04

/* Send event when END is completed. */
#define AQ_COMMAND_END_COMMAND_EVENT_ENABLE                                8 : 8
#define AQ_COMMAND_END_COMMAND_EVENT_ENABLE_End                                8
#define AQ_COMMAND_END_COMMAND_EVENT_ENABLE_Start                              8
#define AQ_COMMAND_END_COMMAND_EVENT_ENABLE_Type                             U01

/* Event ID to be send. */
#define AQ_COMMAND_END_COMMAND_EVENT_ID                                    4 : 0
#define AQ_COMMAND_END_COMMAND_EVENT_ID_End                                    4
#define AQ_COMMAND_END_COMMAND_EVENT_ID_Start                                  0
#define AQ_COMMAND_END_COMMAND_EVENT_ID_Type                                 U05

#define AQ_COMMAND_END_COMMAND_OPCODE                                    31 : 27
#define AQ_COMMAND_END_COMMAND_OPCODE_End                                     31
#define AQ_COMMAND_END_COMMAND_OPCODE_Start                                   27
#define AQ_COMMAND_END_COMMAND_OPCODE_Type                                   U05
#define   AQ_COMMAND_END_COMMAND_OPCODE_LOAD_STATE                          0x01
#define   AQ_COMMAND_END_COMMAND_OPCODE_END                                 0x02
#define   AQ_COMMAND_END_COMMAND_OPCODE_NOP                                 0x03
#define   AQ_COMMAND_END_COMMAND_OPCODE_START_DE                            0x04
#define   AQ_COMMAND_END_COMMAND_OPCODE_WAIT                                0x07
#define   AQ_COMMAND_END_COMMAND_OPCODE_LINK                                0x08
#define   AQ_COMMAND_END_COMMAND_OPCODE_STALL                               0x09
#define   AQ_COMMAND_END_COMMAND_OPCODE_CALL                                0x0A
#define   AQ_COMMAND_END_COMMAND_OPCODE_RETURN                              0x0B

/*******************************************************************************
**                            ~~~~~~~~~~~~~~~~~~~~                            **
**                            Command AQCommandNop                            **
**                            ~~~~~~~~~~~~~~~~~~~~                            **
*******************************************************************************/

#define AQCommandNopCmdAddrs                                              0x0F05
#define AQ_COMMAND_NOP_Address                                           0x03C14
#define AQ_COMMAND_NOP_Count                                                   1

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define AQ_COMMAND_NOP_COMMAND_Index                                           0
#define AQ_COMMAND_NOP_COMMAND_CmdAddrs                                   0x0F05

#define AQ_COMMAND_NOP_COMMAND_OPCODE                                    31 : 27
#define AQ_COMMAND_NOP_COMMAND_OPCODE_End                                     31
#define AQ_COMMAND_NOP_COMMAND_OPCODE_Start                                   27
#define AQ_COMMAND_NOP_COMMAND_OPCODE_Type                                   U05
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_LOAD_STATE                          0x01
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_END                                 0x02
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_NOP                                 0x03
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_START_DE                            0x04
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_WAIT                                0x07
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_LINK                                0x08
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_STALL                               0x09
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_CALL                                0x0A
#define   AQ_COMMAND_NOP_COMMAND_OPCODE_RETURN                              0x0B

/*******************************************************************************
**                          ~~~~~~~~~~~~~~~~~~~~~~~~                          **
**                          Command AQCommandStartDE                          **
**                          ~~~~~~~~~~~~~~~~~~~~~~~~                          **
*******************************************************************************/

#define AQCommandStartDECmdAddrs                                          0x0F06
#define AQ_COMMAND_START_DE_Address                                      0x03C18
#define AQ_COMMAND_START_DE_Count                                              1

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define AQ_COMMAND_START_DE_COMMAND_Index                                      0
#define AQ_COMMAND_START_DE_COMMAND_CmdAddrs                              0x0F06

/* Number of 32-bit data words to send.  The data follows the rectangles,     **
** aligned at 64-bit.                                                         */
#define AQ_COMMAND_START_DE_COMMAND_DATA_COUNT                           26 : 16
#define AQ_COMMAND_START_DE_COMMAND_DATA_COUNT_End                            26
#define AQ_COMMAND_START_DE_COMMAND_DATA_COUNT_Start                          16
#define AQ_COMMAND_START_DE_COMMAND_DATA_COUNT_Type                          U11

/* Number of rectangles to send.  The rectangles follow the command, aligned  **
** at 64-bit.                                                                 */
#define AQ_COMMAND_START_DE_COMMAND_COUNT                                 15 : 8
#define AQ_COMMAND_START_DE_COMMAND_COUNT_End                                 15
#define AQ_COMMAND_START_DE_COMMAND_COUNT_Start                                8
#define AQ_COMMAND_START_DE_COMMAND_COUNT_Type                               U08

#define AQ_COMMAND_START_DE_COMMAND_OPCODE                               31 : 27
#define AQ_COMMAND_START_DE_COMMAND_OPCODE_End                                31
#define AQ_COMMAND_START_DE_COMMAND_OPCODE_Start                              27
#define AQ_COMMAND_START_DE_COMMAND_OPCODE_Type                              U05
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_LOAD_STATE                     0x01
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_END                            0x02
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_NOP                            0x03
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_START_DE                       0x04
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_WAIT                           0x07
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_LINK                           0x08
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_STALL                          0x09
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_CALL                           0x0A
#define   AQ_COMMAND_START_DE_COMMAND_OPCODE_RETURN                         0x0B

/*******************************************************************************
**                            ~~~~~~~~~~~~~~~~~~~~~                           **
**                            Command AQCommandWait                           **
**                            ~~~~~~~~~~~~~~~~~~~~~                           **
*******************************************************************************/

#define AQCommandWaitCmdAddrs                                             0x0F07
#define AQ_COMMAND_WAIT_Address                                          0x03C1C
#define AQ_COMMAND_WAIT_Count                                                  1

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define AQ_COMMAND_WAIT_COMMAND_Index                                          0
#define AQ_COMMAND_WAIT_COMMAND_CmdAddrs                                  0x0F07

/* Number of cycles to wait until the next command gets fetched. */
#define AQ_COMMAND_WAIT_COMMAND_DELAY                                     15 : 0
#define AQ_COMMAND_WAIT_COMMAND_DELAY_End                                     15
#define AQ_COMMAND_WAIT_COMMAND_DELAY_Start                                    0
#define AQ_COMMAND_WAIT_COMMAND_DELAY_Type                                   U16

#define AQ_COMMAND_WAIT_COMMAND_OPCODE                                   31 : 27
#define AQ_COMMAND_WAIT_COMMAND_OPCODE_End                                    31
#define AQ_COMMAND_WAIT_COMMAND_OPCODE_Start                                  27
#define AQ_COMMAND_WAIT_COMMAND_OPCODE_Type                                  U05
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_LOAD_STATE                         0x01
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_END                                0x02
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_NOP                                0x03
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_START_DE                           0x04
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_WAIT                               0x07
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_LINK                               0x08
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_STALL                              0x09
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_CALL                               0x0A
#define   AQ_COMMAND_WAIT_COMMAND_OPCODE_RETURN                             0x0B

/*******************************************************************************
**                            ~~~~~~~~~~~~~~~~~~~~~                           **
**                            Command AQCommandLink                           **
**                            ~~~~~~~~~~~~~~~~~~~~~                           **
*******************************************************************************/

#define AQCommandLinkCmdAddrs                                             0x0F0C
#define AQ_COMMAND_LINK_Address                                          0x03C30
#define AQ_COMMAND_LINK_Count                                                  2

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define AQ_COMMAND_LINK_COMMAND_Index                                          0
#define AQ_COMMAND_LINK_COMMAND_CmdAddrs                                  0x0F0C

/* Number of 64-bit words to fetch.  Make sure this number is not too low,    **
** nothing else will be fetched.  So, make sure that the last command in the  **
** new command buffer is either an END, a LINK, a CALL, or a RETURN.          */
#define AQ_COMMAND_LINK_COMMAND_PREFETCH                                  15 : 0
#define AQ_COMMAND_LINK_COMMAND_PREFETCH_End                                  15
#define AQ_COMMAND_LINK_COMMAND_PREFETCH_Start                                 0
#define AQ_COMMAND_LINK_COMMAND_PREFETCH_Type                                U16

#define AQ_COMMAND_LINK_COMMAND_OPCODE                                   31 : 27
#define AQ_COMMAND_LINK_COMMAND_OPCODE_End                                    31
#define AQ_COMMAND_LINK_COMMAND_OPCODE_Start                                  27
#define AQ_COMMAND_LINK_COMMAND_OPCODE_Type                                  U05
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_LOAD_STATE                         0x01
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_END                                0x02
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_NOP                                0x03
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_START_DE                           0x04
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_WAIT                               0x07
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_LINK                               0x08
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_STALL                              0x09
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_CALL                               0x0A
#define   AQ_COMMAND_LINK_COMMAND_OPCODE_RETURN                             0x0B

/* Offset Address
** ~~~~~~~~~~~~~~ */
#define AQ_COMMAND_LINK_ADDRESS_Index                                          1
#define AQ_COMMAND_LINK_ADDRESS_CmdAddrs                                  0x0F0D

#define AQ_COMMAND_LINK_ADDRESS_TYPE                                     31 : 31
#define AQ_COMMAND_LINK_ADDRESS_TYPE_End                                      31
#define AQ_COMMAND_LINK_ADDRESS_TYPE_Start                                    31
#define AQ_COMMAND_LINK_ADDRESS_TYPE_Type                                    U01
#define   AQ_COMMAND_LINK_ADDRESS_TYPE_SYSTEM                                0x0
#define   AQ_COMMAND_LINK_ADDRESS_TYPE_VIRTUAL_SYSTEM                        0x1

#define AQ_COMMAND_LINK_ADDRESS_ADDRESS                                   30 : 0
#define AQ_COMMAND_LINK_ADDRESS_ADDRESS_End                                   30
#define AQ_COMMAND_LINK_ADDRESS_ADDRESS_Start                                  0
#define AQ_COMMAND_LINK_ADDRESS_ADDRESS_Type                                 U31

/*******************************************************************************
**                              ~~~~~~~~~~~~~~~~~                             **
**                              Command gccmdCall                             **
**                              ~~~~~~~~~~~~~~~~~                             **
*******************************************************************************/

#define gccmdCallCmdAddrs                                                 0x0F18
#define GCCMD_CALL_Address                                               0x03C60
#define GCCMD_CALL_Count                                                       4

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define GCCMD_CALL_COMMAND_Index                                               0
#define GCCMD_CALL_COMMAND_CmdAddrs                                       0x0F18

/* Number of 64-bit words to fetch.  Make sure this number is not too low,    **
** nothing else will be fetched.  So, make sure that the last command in the  **
** new command buffer is either an END, a LINK, a CALL, or a RETURN.          */
#define GCCMD_CALL_COMMAND_PREFETCH                                       15 : 0
#define GCCMD_CALL_COMMAND_PREFETCH_End                                       15
#define GCCMD_CALL_COMMAND_PREFETCH_Start                                      0
#define GCCMD_CALL_COMMAND_PREFETCH_Type                                     U16

#define GCCMD_CALL_COMMAND_OPCODE                                        31 : 27
#define GCCMD_CALL_COMMAND_OPCODE_End                                         31
#define GCCMD_CALL_COMMAND_OPCODE_Start                                       27
#define GCCMD_CALL_COMMAND_OPCODE_Type                                       U05
#define   GCCMD_CALL_COMMAND_OPCODE_LOAD_STATE                              0x01
#define   GCCMD_CALL_COMMAND_OPCODE_END                                     0x02
#define   GCCMD_CALL_COMMAND_OPCODE_NOP                                     0x03
#define   GCCMD_CALL_COMMAND_OPCODE_START_DE                                0x04
#define   GCCMD_CALL_COMMAND_OPCODE_WAIT                                    0x07
#define   GCCMD_CALL_COMMAND_OPCODE_LINK                                    0x08
#define   GCCMD_CALL_COMMAND_OPCODE_STALL                                   0x09
#define   GCCMD_CALL_COMMAND_OPCODE_CALL                                    0x0A
#define   GCCMD_CALL_COMMAND_OPCODE_RETURN                                  0x0B

/* Offset Address
** ~~~~~~~~~~~~~~ */
#define GCCMD_CALL_ADDRESS_Index                                               1
#define GCCMD_CALL_ADDRESS_CmdAddrs                                       0x0F19

#define GCCMD_CALL_ADDRESS_TYPE                                          31 : 31
#define GCCMD_CALL_ADDRESS_TYPE_End                                           31
#define GCCMD_CALL_ADDRESS_TYPE_Start                                         31
#define GCCMD_CALL_ADDRESS_TYPE_Type                                         U01
#define   GCCMD_CALL_ADDRESS_TYPE_SYSTEM                                     0x0
#define   GCCMD_CALL_ADDRESS_TYPE_VIRTUAL_SYSTEM                             0x1

#define GCCMD_CALL_ADDRESS_ADDRESS                                        30 : 0
#define GCCMD_CALL_ADDRESS_ADDRESS_End                                        30
#define GCCMD_CALL_ADDRESS_ADDRESS_Start                                       0
#define GCCMD_CALL_ADDRESS_ADDRESS_Type                                      U31

/* Offset ReturnPrefetch
** ~~~~~~~~~~~~~~~~~~~~~ */
#define GCCMD_CALL_RETURN_PREFETCH_Index                                       2
#define GCCMD_CALL_RETURN_PREFETCH_CmdAddrs                               0x0F1A

/* Number of 64-bit words to fetch after a Return has been issued.  Make sure **
** this number if not too low nothing else will be fetched.  So, make sure    **
** the last command in this prefetch block is either an END, a LINK, a CALL,  **
** or a RETURN.                                                               */
#define GCCMD_CALL_RETURN_PREFETCH_PREFETCH                               15 : 0
#define GCCMD_CALL_RETURN_PREFETCH_PREFETCH_End                               15
#define GCCMD_CALL_RETURN_PREFETCH_PREFETCH_Start                              0
#define GCCMD_CALL_RETURN_PREFETCH_PREFETCH_Type                             U16

/* Offset ReturnAddress
** ~~~~~~~~~~~~~~~~~~~~ */
#define GCCMD_CALL_RETURN_ADDRESS_Index                                        3
#define GCCMD_CALL_RETURN_ADDRESS_CmdAddrs                                0x0F1B

#define GCCMD_CALL_RETURN_ADDRESS_TYPE                                   31 : 31
#define GCCMD_CALL_RETURN_ADDRESS_TYPE_End                                    31
#define GCCMD_CALL_RETURN_ADDRESS_TYPE_Start                                  31
#define GCCMD_CALL_RETURN_ADDRESS_TYPE_Type                                  U01
#define   GCCMD_CALL_RETURN_ADDRESS_TYPE_SYSTEM                              0x0
#define   GCCMD_CALL_RETURN_ADDRESS_TYPE_VIRTUAL_SYSTEM                      0x1

#define GCCMD_CALL_RETURN_ADDRESS_ADDRESS                                 30 : 0
#define GCCMD_CALL_RETURN_ADDRESS_ADDRESS_End                                 30
#define GCCMD_CALL_RETURN_ADDRESS_ADDRESS_Start                                0
#define GCCMD_CALL_RETURN_ADDRESS_ADDRESS_Type                               U31

/*******************************************************************************
**                             ~~~~~~~~~~~~~~~~~~~                            **
**                             Command gccmdReturn                            **
**                             ~~~~~~~~~~~~~~~~~~~                            **
*******************************************************************************/

#define gccmdReturnCmdAddrs                                               0x0F0E
#define GCCMD_RETURN_Address                                             0x03C38
#define GCCMD_RETURN_Count                                                     1

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define GCCMD_RETURN_COMMAND_Index                                             0
#define GCCMD_RETURN_COMMAND_CmdAddrs                                     0x0F0E

#define GCCMD_RETURN_COMMAND_OPCODE                                      31 : 27
#define GCCMD_RETURN_COMMAND_OPCODE_End                                       31
#define GCCMD_RETURN_COMMAND_OPCODE_Start                                     27
#define GCCMD_RETURN_COMMAND_OPCODE_Type                                     U05
#define   GCCMD_RETURN_COMMAND_OPCODE_LOAD_STATE                            0x01
#define   GCCMD_RETURN_COMMAND_OPCODE_END                                   0x02
#define   GCCMD_RETURN_COMMAND_OPCODE_NOP                                   0x03
#define   GCCMD_RETURN_COMMAND_OPCODE_START_DE                              0x04
#define   GCCMD_RETURN_COMMAND_OPCODE_WAIT                                  0x07
#define   GCCMD_RETURN_COMMAND_OPCODE_LINK                                  0x08
#define   GCCMD_RETURN_COMMAND_OPCODE_STALL                                 0x09
#define   GCCMD_RETURN_COMMAND_OPCODE_CALL                                  0x0A
#define   GCCMD_RETURN_COMMAND_OPCODE_RETURN                                0x0B

/*******************************************************************************
**                              ~~~~~~~~~~~~~~~~~                             **
**                              Command AQCommand                             **
**                              ~~~~~~~~~~~~~~~~~                             **
*******************************************************************************/

/* Offset TopLeft
** ~~~~~~~~~~~~~~ */

#define AQ_COMMAND_TOP_LEFT_Y                                            31 : 16
#define AQ_COMMAND_TOP_LEFT_Y_End                                             31
#define AQ_COMMAND_TOP_LEFT_Y_Start                                           16
#define AQ_COMMAND_TOP_LEFT_Y_Type                                           U16

#define AQ_COMMAND_TOP_LEFT_X                                             15 : 0
#define AQ_COMMAND_TOP_LEFT_X_End                                             15
#define AQ_COMMAND_TOP_LEFT_X_Start                                            0
#define AQ_COMMAND_TOP_LEFT_X_Type                                           U16

/* Offset BottomRight
** ~~~~~~~~~~~~~~~~~~ */

#define AQ_COMMAND_BOTTOM_RIGHT_Y                                        31 : 16
#define AQ_COMMAND_BOTTOM_RIGHT_Y_End                                         31
#define AQ_COMMAND_BOTTOM_RIGHT_Y_Start                                       16
#define AQ_COMMAND_BOTTOM_RIGHT_Y_Type                                       U16

#define AQ_COMMAND_BOTTOM_RIGHT_X                                         15 : 0
#define AQ_COMMAND_BOTTOM_RIGHT_X_End                                         15
#define AQ_COMMAND_BOTTOM_RIGHT_X_Start                                        0
#define AQ_COMMAND_BOTTOM_RIGHT_X_Type                                       U16

/*******************************************************************************
**                                ~~~~~~~~~~~~~                               **
**                                Command Stall                               **
**                                ~~~~~~~~~~~~~                               **
*******************************************************************************/

#define StallCmdAddrs                                                     0x0F16
#define STALL_Address                                                    0x03C58
#define STALL_Count                                                            2

/* Offset Command
** ~~~~~~~~~~~~~~ */
#define STALL_COMMAND_Index                                                    0
#define STALL_COMMAND_CmdAddrs                                            0x0F16

#define STALL_COMMAND_OPCODE                                             31 : 27
#define STALL_COMMAND_OPCODE_End                                              31
#define STALL_COMMAND_OPCODE_Start                                            27
#define STALL_COMMAND_OPCODE_Type                                            U05
#define   STALL_COMMAND_OPCODE_LOAD_STATE                                   0x01
#define   STALL_COMMAND_OPCODE_END                                          0x02
#define   STALL_COMMAND_OPCODE_NOP                                          0x03
#define   STALL_COMMAND_OPCODE_START_DE                                     0x04
#define   STALL_COMMAND_OPCODE_WAIT                                         0x07
#define   STALL_COMMAND_OPCODE_LINK                                         0x08
#define   STALL_COMMAND_OPCODE_STALL                                        0x09
#define   STALL_COMMAND_OPCODE_CALL                                         0x0A
#define   STALL_COMMAND_OPCODE_RETURN                                       0x0B

/* Offset Stall
** ~~~~~~~~~~~~ */
#define STALL_STALL_Index                                                      1
#define STALL_STALL_CmdAddrs                                              0x0F17

#define STALL_STALL_SOURCE                                                 4 : 0
#define STALL_STALL_SOURCE_End                                                 4
#define STALL_STALL_SOURCE_Start                                               0
#define STALL_STALL_SOURCE_Type                                              U05
#define   STALL_STALL_SOURCE_FRONT_END                                      0x01
#define   STALL_STALL_SOURCE_PIXEL_ENGINE                                   0x07
#define   STALL_STALL_SOURCE_DRAWING_ENGINE                                 0x0B

#define STALL_STALL_DESTINATION                                           12 : 8
#define STALL_STALL_DESTINATION_End                                           12
#define STALL_STALL_DESTINATION_Start                                          8
#define STALL_STALL_DESTINATION_Type                                         U05
#define   STALL_STALL_DESTINATION_FRONT_END                                 0x01
#define   STALL_STALL_DESTINATION_PIXEL_ENGINE                              0x07
#define   STALL_STALL_DESTINATION_DRAWING_ENGINE                            0x0B

