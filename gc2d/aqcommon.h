/*
 * aqcommon.h
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
**                              ~~~~~~~~~~~~~~~~~                             **
**                              Module CommonUnit                             **
**                              ~~~~~~~~~~~~~~~~~                             **
*******************************************************************************/

/* Register AQPipeSelect **
** ~~~~~~~~~~~~~~~~~~~~~ */

/* Select the current graphics pipe. */

#define AQPipeSelectRegAddrs                                              0x0E00
#define AQ_PIPE_SELECT_Address                                           0x03800
#define AQ_PIPE_SELECT_MSB                                                    15
#define AQ_PIPE_SELECT_LSB                                                     0
#define AQ_PIPE_SELECT_BLK                                                     0
#define AQ_PIPE_SELECT_Count                                                   1
#define AQ_PIPE_SELECT_FieldMask                                      0x00000001
#define AQ_PIPE_SELECT_ReadMask                                       0x00000001
#define AQ_PIPE_SELECT_WriteMask                                      0x00000001
#define AQ_PIPE_SELECT_ResetValue                                     0x00000000

/* Selects the pipe to send states and data to.  Make  sure the PE is idle    **
** before you switch pipes.                                                   */
#define AQ_PIPE_SELECT_PIPE                                                0 : 0
#define AQ_PIPE_SELECT_PIPE_End                                                0
#define AQ_PIPE_SELECT_PIPE_Start                                              0
#define AQ_PIPE_SELECT_PIPE_Type                                             U01
#define   AQ_PIPE_SELECT_PIPE_PIPE3D                                         0x0
#define   AQ_PIPE_SELECT_PIPE_PIPE2D                                         0x1

/* Register AQEvent **
** ~~~~~~~~~~~~~~~~ */

/* Send an event. */

#define AQEventRegAddrs                                                   0x0E01
#define AQ_EVENT_Address                                                 0x03804
#define AQ_EVENT_MSB                                                          15
#define AQ_EVENT_LSB                                                           0
#define AQ_EVENT_BLK                                                           0
#define AQ_EVENT_Count                                                         1
#define AQ_EVENT_FieldMask                                            0x0000007F
#define AQ_EVENT_ReadMask                                             0x0000007F
#define AQ_EVENT_WriteMask                                            0x0000007F
#define AQ_EVENT_ResetValue                                           0x00000000

/* 5-bit event ID to send. */
#define AQ_EVENT_EVENT_ID                                                  4 : 0
#define AQ_EVENT_EVENT_ID_End                                                  4
#define AQ_EVENT_EVENT_ID_Start                                                0
#define AQ_EVENT_EVENT_ID_Type                                               U05

/* The event is sent by the FE. */
#define AQ_EVENT_FE_SRC                                                    5 : 5
#define AQ_EVENT_FE_SRC_End                                                    5
#define AQ_EVENT_FE_SRC_Start                                                  5
#define AQ_EVENT_FE_SRC_Type                                                 U01
#define   AQ_EVENT_FE_SRC_DISABLE                                            0x0
#define   AQ_EVENT_FE_SRC_ENABLE                                             0x1

/* The event is sent by the PE. */
#define AQ_EVENT_PE_SRC                                                    6 : 6
#define AQ_EVENT_PE_SRC_End                                                    6
#define AQ_EVENT_PE_SRC_Start                                                  6
#define AQ_EVENT_PE_SRC_Type                                                 U01
#define   AQ_EVENT_PE_SRC_DISABLE                                            0x0
#define   AQ_EVENT_PE_SRC_ENABLE                                             0x1

/* Register AQSemaphore **
** ~~~~~~~~~~~~~~~~~~~~ */

/* A sempahore state arms the semaphore in the destination. */

#define AQSemaphoreRegAddrs                                               0x0E02
#define AQ_SEMAPHORE_Address                                             0x03808
#define AQ_SEMAPHORE_MSB                                                      15
#define AQ_SEMAPHORE_LSB                                                       0
#define AQ_SEMAPHORE_BLK                                                       0
#define AQ_SEMAPHORE_Count                                                     1
#define AQ_SEMAPHORE_FieldMask                                        0x00001F1F
#define AQ_SEMAPHORE_ReadMask                                         0x00001F1F
#define AQ_SEMAPHORE_WriteMask                                        0x00001F1F
#define AQ_SEMAPHORE_ResetValue                                       0x00000000

#define AQ_SEMAPHORE_SOURCE                                                4 : 0
#define AQ_SEMAPHORE_SOURCE_End                                                4
#define AQ_SEMAPHORE_SOURCE_Start                                              0
#define AQ_SEMAPHORE_SOURCE_Type                                             U05
#define   AQ_SEMAPHORE_SOURCE_FRONT_END                                     0x01
#define   AQ_SEMAPHORE_SOURCE_PIXEL_ENGINE                                  0x07
#define   AQ_SEMAPHORE_SOURCE_DRAWING_ENGINE                                0x0B

#define AQ_SEMAPHORE_DESTINATION                                          12 : 8
#define AQ_SEMAPHORE_DESTINATION_End                                          12
#define AQ_SEMAPHORE_DESTINATION_Start                                         8
#define AQ_SEMAPHORE_DESTINATION_Type                                        U05
#define   AQ_SEMAPHORE_DESTINATION_FRONT_END                                0x01
#define   AQ_SEMAPHORE_DESTINATION_PIXEL_ENGINE                             0x07
#define   AQ_SEMAPHORE_DESTINATION_DRAWING_ENGINE                           0x0B

/* Register AQFlush **
** ~~~~~~~~~~~~~~~~ */

/* Flush the current pipe. */

#define AQFlushRegAddrs                                                   0x0E03
#define AQ_FLUSH_Address                                                 0x0380C
#define AQ_FLUSH_MSB                                                          15
#define AQ_FLUSH_LSB                                                           0
#define AQ_FLUSH_BLK                                                           0
#define AQ_FLUSH_Count                                                         1
#define AQ_FLUSH_FieldMask                                            0x00000008
#define AQ_FLUSH_ReadMask                                             0x00000008
#define AQ_FLUSH_WriteMask                                            0x00000008
#define AQ_FLUSH_ResetValue                                           0x00000000

/* Flush the 2D pixel cache. */
#define AQ_FLUSH_PE2D_CACHE                                                3 : 3
#define AQ_FLUSH_PE2D_CACHE_End                                                3
#define AQ_FLUSH_PE2D_CACHE_Start                                              3
#define AQ_FLUSH_PE2D_CACHE_Type                                             U01
#define   AQ_FLUSH_PE2D_CACHE_DISABLE                                        0x0
#define   AQ_FLUSH_PE2D_CACHE_ENABLE                                         0x1

/* Register AQMMUFlush **
** ~~~~~~~~~~~~~~~~~~~ */

/* Flush the virtual addrses lookup cache inside the MC. */

#define AQMMUFlushRegAddrs                                                0x0E04
#define AQMMU_FLUSH_Address                                              0x03810
#define AQMMU_FLUSH_MSB                                                       15
#define AQMMU_FLUSH_LSB                                                        0
#define AQMMU_FLUSH_BLK                                                        0
#define AQMMU_FLUSH_Count                                                      1
#define AQMMU_FLUSH_FieldMask                                         0x00000009
#define AQMMU_FLUSH_ReadMask                                          0x00000009
#define AQMMU_FLUSH_WriteMask                                         0x00000009
#define AQMMU_FLUSH_ResetValue                                        0x00000000

/* Flush the FE address translation caches. */
#define AQMMU_FLUSH_FEMMU                                                  0 : 0
#define AQMMU_FLUSH_FEMMU_End                                                  0
#define AQMMU_FLUSH_FEMMU_Start                                                0
#define AQMMU_FLUSH_FEMMU_Type                                               U01
#define   AQMMU_FLUSH_FEMMU_DISABLE                                          0x0
#define   AQMMU_FLUSH_FEMMU_ENABLE                                           0x1

/* Flush the PE render target address translation caches. */
#define AQMMU_FLUSH_PEMMU                                                  3 : 3
#define AQMMU_FLUSH_PEMMU_End                                                  3
#define AQMMU_FLUSH_PEMMU_Start                                                3
#define AQMMU_FLUSH_PEMMU_Type                                               U01
#define   AQMMU_FLUSH_PEMMU_DISABLE                                          0x0
#define   AQMMU_FLUSH_PEMMU_ENABLE                                           0x1

