/*
 * aqmem.h
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
**                           ~~~~~~~~~~~~~~~~~~~~~~~                          **
**                           Module MemoryController                          **
**                           ~~~~~~~~~~~~~~~~~~~~~~~                          **
*******************************************************************************/

/* Register AQMemoryFePageTable **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQMemoryFePageTableRegAddrs                                       0x0100
#define AQ_MEMORY_FE_PAGE_TABLE_Address                                  0x00400
#define AQ_MEMORY_FE_PAGE_TABLE_MSB                                           15
#define AQ_MEMORY_FE_PAGE_TABLE_LSB                                            0
#define AQ_MEMORY_FE_PAGE_TABLE_BLK                                            0
#define AQ_MEMORY_FE_PAGE_TABLE_Count                                          1
#define AQ_MEMORY_FE_PAGE_TABLE_FieldMask                             0xFFFFF000
#define AQ_MEMORY_FE_PAGE_TABLE_ReadMask                              0xFFFFF000
#define AQ_MEMORY_FE_PAGE_TABLE_WriteMask                             0xFFFFF000
#define AQ_MEMORY_FE_PAGE_TABLE_ResetValue                            0x00000000

/* Base address for FE virtual address lookup table. */
#define AQ_MEMORY_FE_PAGE_TABLE_BASE_ADDRESS                             31 : 12
#define AQ_MEMORY_FE_PAGE_TABLE_BASE_ADDRESS_End                              31
#define AQ_MEMORY_FE_PAGE_TABLE_BASE_ADDRESS_Start                            12
#define AQ_MEMORY_FE_PAGE_TABLE_BASE_ADDRESS_Type                            U20


/* Register AQMemoryPePageTable **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQMemoryPePageTableRegAddrs                                       0x0102
#define AQ_MEMORY_PE_PAGE_TABLE_Address                                  0x00408
#define AQ_MEMORY_PE_PAGE_TABLE_MSB                                           15
#define AQ_MEMORY_PE_PAGE_TABLE_LSB                                            0
#define AQ_MEMORY_PE_PAGE_TABLE_BLK                                            0
#define AQ_MEMORY_PE_PAGE_TABLE_Count                                          1
#define AQ_MEMORY_PE_PAGE_TABLE_FieldMask                             0xFFFFF000
#define AQ_MEMORY_PE_PAGE_TABLE_ReadMask                              0xFFFFF000
#define AQ_MEMORY_PE_PAGE_TABLE_WriteMask                             0xFFFFF000
#define AQ_MEMORY_PE_PAGE_TABLE_ResetValue                            0x00000000

/* Base address for color buffer virtual address lookup table. */
#define AQ_MEMORY_PE_PAGE_TABLE_BASE_ADDRESS                             31 : 12
#define AQ_MEMORY_PE_PAGE_TABLE_BASE_ADDRESS_End                              31
#define AQ_MEMORY_PE_PAGE_TABLE_BASE_ADDRESS_Start                            12
#define AQ_MEMORY_PE_PAGE_TABLE_BASE_ADDRESS_Type                            U20


/* Register AQMemoryRaPageTable **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define AQMemoryRaPageTableRegAddrs                                       0x0104
#define AQ_MEMORY_RA_PAGE_TABLE_Address                                  0x00410
#define AQ_MEMORY_RA_PAGE_TABLE_MSB                                           15
#define AQ_MEMORY_RA_PAGE_TABLE_LSB                                            0
#define AQ_MEMORY_RA_PAGE_TABLE_BLK                                            0
#define AQ_MEMORY_RA_PAGE_TABLE_Count                                          1
#define AQ_MEMORY_RA_PAGE_TABLE_FieldMask                             0xFFFFF000
#define AQ_MEMORY_RA_PAGE_TABLE_ReadMask                              0xFFFFF000
#define AQ_MEMORY_RA_PAGE_TABLE_WriteMask                             0xFFFFF000
#define AQ_MEMORY_RA_PAGE_TABLE_ResetValue                            0x00000000

/* Base address for early-z virtual address lookup table. */
#define AQ_MEMORY_RA_PAGE_TABLE_BASE_ADDRESS                             31 : 12
#define AQ_MEMORY_RA_PAGE_TABLE_BASE_ADDRESS_End                              31
#define AQ_MEMORY_RA_PAGE_TABLE_BASE_ADDRESS_Start                            12
#define AQ_MEMORY_RA_PAGE_TABLE_BASE_ADDRESS_Type                            U20

/* Register AQMemoryDebug **
** ~~~~~~~~~~~~~~~~~~~~~~ */
#define AQMemoryDebugRegAddrs                                             0x0105
#define AQ_MEMORY_DEBUG_Address                                          0x00414
#define AQ_MEMORY_DEBUG_MSB                                                   15
#define AQ_MEMORY_DEBUG_LSB                                                    0
#define AQ_MEMORY_DEBUG_BLK                                                    0
#define AQ_MEMORY_DEBUG_Count                                                  1
#define AQ_MEMORY_DEBUG_FieldMask                                     0x000840FF
#define AQ_MEMORY_DEBUG_ReadMask                                      0x000840FF
#define AQ_MEMORY_DEBUG_WriteMask                                     0x000840FF
#define AQ_MEMORY_DEBUG_ResetValue                                    0x00000000

/* Limits the total number of outstanding read requests. */
#define AQ_MEMORY_DEBUG_MAX_OUTSTANDING_READS                              7 : 0
#define AQ_MEMORY_DEBUG_MAX_OUTSTANDING_READS_End                              7
#define AQ_MEMORY_DEBUG_MAX_OUTSTANDING_READS_Start                            0
#define AQ_MEMORY_DEBUG_MAX_OUTSTANDING_READS_Type                           U08

#define AQ_MEMORY_DEBUG_DISABLE_MINI_MMU_CACHE                           14 : 14
#define AQ_MEMORY_DEBUG_DISABLE_MINI_MMU_CACHE_End                            14
#define AQ_MEMORY_DEBUG_DISABLE_MINI_MMU_CACHE_Start                          14
#define AQ_MEMORY_DEBUG_DISABLE_MINI_MMU_CACHE_Type                          U01

#define AQ_MEMORY_DEBUG_LIMIT_CONTROL                                    19 : 19
#define AQ_MEMORY_DEBUG_LIMIT_CONTROL_End                                     19
#define AQ_MEMORY_DEBUG_LIMIT_CONTROL_Start                                   19
#define AQ_MEMORY_DEBUG_LIMIT_CONTROL_Type                                   U01
#define   AQ_MEMORY_DEBUG_LIMIT_CONTROL_REQUESTS                             0x0
#define   AQ_MEMORY_DEBUG_LIMIT_CONTROL_DATA                                 0x1

/* Register AQMemoryRa **
** ~~~~~~~~~~~~~~~~~~~ */
#define AQMemoryRaRegAddrs                                                0x0106
#define AQ_MEMORY_RA_Address                                             0x00418
#define AQ_MEMORY_RA_MSB                                                      15
#define AQ_MEMORY_RA_LSB                                                       0
#define AQ_MEMORY_RA_BLK                                                       0
#define AQ_MEMORY_RA_Count                                                     1
#define AQ_MEMORY_RA_FieldMask                                        0xFFFFFFFF
#define AQ_MEMORY_RA_ReadMask                                         0xFFFFFFFF
#define AQ_MEMORY_RA_WriteMask                                        0xFFFFFFFF
#define AQ_MEMORY_RA_ResetValue                                       0x00000000

/* Base address for all RA memory requests (all addresses are added with this **
** before going out of the chip)                                              */
#define AQ_MEMORY_RA_BASE_ADDRESS                                         31 : 0
#define AQ_MEMORY_RA_BASE_ADDRESS_End                                         31
#define AQ_MEMORY_RA_BASE_ADDRESS_Start                                        0
#define AQ_MEMORY_RA_BASE_ADDRESS_Type                                       U32

/* Register AQMemoryFe **
** ~~~~~~~~~~~~~~~~~~~ */
#define AQMemoryFeRegAddrs                                                0x0107
#define AQ_MEMORY_FE_Address                                             0x0041C
#define AQ_MEMORY_FE_MSB                                                      15
#define AQ_MEMORY_FE_LSB                                                       0
#define AQ_MEMORY_FE_BLK                                                       0
#define AQ_MEMORY_FE_Count                                                     1
#define AQ_MEMORY_FE_FieldMask                                        0xFFFFFFFF
#define AQ_MEMORY_FE_ReadMask                                         0xFFFFFFFF
#define AQ_MEMORY_FE_WriteMask                                        0xFFFFFFFF
#define AQ_MEMORY_FE_ResetValue                                       0x00000000

/* Base address for all FE memory requests (all addresses are added with this **
** before going out of the chip)                                              */
#define AQ_MEMORY_FE_BASE_ADDRESS                                         31 : 0
#define AQ_MEMORY_FE_BASE_ADDRESS_End                                         31
#define AQ_MEMORY_FE_BASE_ADDRESS_Start                                        0
#define AQ_MEMORY_FE_BASE_ADDRESS_Type                                       U32

/* Register AQMemoryPec **
** ~~~~~~~~~~~~~~~~~~~~ */
#define AQMemoryPecRegAddrs                                               0x010A
#define AQ_MEMORY_PEC_Address                                            0x00428
#define AQ_MEMORY_PEC_MSB                                                     15
#define AQ_MEMORY_PEC_LSB                                                      0
#define AQ_MEMORY_PEC_BLK                                                      0
#define AQ_MEMORY_PEC_Count                                                    1
#define AQ_MEMORY_PEC_FieldMask                                       0xFFFFFFFF
#define AQ_MEMORY_PEC_ReadMask                                        0xFFFFFFFF
#define AQ_MEMORY_PEC_WriteMask                                       0xFFFFFFFF
#define AQ_MEMORY_PEC_ResetValue                                      0x00000000

/* Base address for all PE-Color memory requests (all addresses are added     **
** with this before going out of the chip)                                    */
#define AQ_MEMORY_PEC_BASE_ADDRESS                                        31 : 0
#define AQ_MEMORY_PEC_BASE_ADDRESS_End                                        31
#define AQ_MEMORY_PEC_BASE_ADDRESS_Start                                       0
#define AQ_MEMORY_PEC_BASE_ADDRESS_Type                                      U32

/* Register gcDbgCycleCounter **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Increments every cycle. */

#define gcDbgCycleCounterRegAddrs                                         0x010E
#define GC_DBG_CYCLE_COUNTER_Address                                     0x00438
#define GC_DBG_CYCLE_COUNTER_MSB                                              15
#define GC_DBG_CYCLE_COUNTER_LSB                                               0
#define GC_DBG_CYCLE_COUNTER_BLK                                               0
#define GC_DBG_CYCLE_COUNTER_Count                                             1
#define GC_DBG_CYCLE_COUNTER_FieldMask                                0xFFFFFFFF
#define GC_DBG_CYCLE_COUNTER_ReadMask                                 0xFFFFFFFF
#define GC_DBG_CYCLE_COUNTER_WriteMask                                0xFFFFFFFF
#define GC_DBG_CYCLE_COUNTER_ResetValue                               0x00000000

#define GC_DBG_CYCLE_COUNTER_COUNT                                        31 : 0
#define GC_DBG_CYCLE_COUNTER_COUNT_End                                        31
#define GC_DBG_CYCLE_COUNTER_COUNT_Start                                       0
#define GC_DBG_CYCLE_COUNTER_COUNT_Type                                      U32

/* Register gcOutstandingReads0 **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Number of outstanding reads per client in multiples of 8B. */

#define gcOutstandingReads0RegAddrs                                       0x010F
#define GC_OUTSTANDING_READS0_Address                                    0x0043C
#define GC_OUTSTANDING_READS0_MSB                                             15
#define GC_OUTSTANDING_READS0_LSB                                              0
#define GC_OUTSTANDING_READS0_BLK                                              0
#define GC_OUTSTANDING_READS0_Count                                            1
#define GC_OUTSTANDING_READS0_FieldMask                               0xFFFFFFFF
#define GC_OUTSTANDING_READS0_ReadMask                                0xFFFFFFFF
#define GC_OUTSTANDING_READS0_WriteMask                               0x00000000
#define GC_OUTSTANDING_READS0_ResetValue                              0x00000000

#define GC_OUTSTANDING_READS0_PEC                                          7 : 0
#define GC_OUTSTANDING_READS0_PEC_End                                          7
#define GC_OUTSTANDING_READS0_PEC_Start                                        0
#define GC_OUTSTANDING_READS0_PEC_Type                                       U08

#define GC_OUTSTANDING_READS0_PEZ                                         15 : 8
#define GC_OUTSTANDING_READS0_PEZ_End                                         15
#define GC_OUTSTANDING_READS0_PEZ_Start                                        8
#define GC_OUTSTANDING_READS0_PEZ_Type                                       U08

#define GC_OUTSTANDING_READS0_FE                                         23 : 16
#define GC_OUTSTANDING_READS0_FE_End                                          23
#define GC_OUTSTANDING_READS0_FE_Start                                        16
#define GC_OUTSTANDING_READS0_FE_Type                                        U08

#define GC_OUTSTANDING_READS0_MMU                                        31 : 24
#define GC_OUTSTANDING_READS0_MMU_End                                         31
#define GC_OUTSTANDING_READS0_MMU_Start                                       24
#define GC_OUTSTANDING_READS0_MMU_Type                                       U08

/* Register gcOutstandingReads1 **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Number of outstanding reads per client in multiples of 8B. */

#define gcOutstandingReads1RegAddrs                                       0x0110
#define GC_OUTSTANDING_READS1_Address                                    0x00440
#define GC_OUTSTANDING_READS1_MSB                                             15
#define GC_OUTSTANDING_READS1_LSB                                              0
#define GC_OUTSTANDING_READS1_BLK                                              0
#define GC_OUTSTANDING_READS1_Count                                            1
#define GC_OUTSTANDING_READS1_FieldMask                               0xFFFFFFFF
#define GC_OUTSTANDING_READS1_ReadMask                                0xFFFFFFFF
#define GC_OUTSTANDING_READS1_WriteMask                               0x00000000
#define GC_OUTSTANDING_READS1_ResetValue                              0x00000000

#define GC_OUTSTANDING_READS1_RA                                           7 : 0
#define GC_OUTSTANDING_READS1_RA_End                                           7
#define GC_OUTSTANDING_READS1_RA_Start                                         0
#define GC_OUTSTANDING_READS1_RA_Type                                        U08

#define GC_OUTSTANDING_READS1_TX                                          15 : 8
#define GC_OUTSTANDING_READS1_TX_End                                          15
#define GC_OUTSTANDING_READS1_TX_Start                                         8
#define GC_OUTSTANDING_READS1_TX_Type                                        U08

#define GC_OUTSTANDING_READS1_FC                                         23 : 16
#define GC_OUTSTANDING_READS1_FC_End                                          23
#define GC_OUTSTANDING_READS1_FC_Start                                        16
#define GC_OUTSTANDING_READS1_FC_Type                                        U08

/* This field keeps the value of total read requests or total requested  data **
** (in 64bits) depending on the value of LimitControl field in  AQMemoryDebug **
** register.                                                                  */
#define GC_OUTSTANDING_READS1_TOTAL                                      31 : 24
#define GC_OUTSTANDING_READS1_TOTAL_End                                       31
#define GC_OUTSTANDING_READS1_TOTAL_Start                                     24
#define GC_OUTSTANDING_READS1_TOTAL_Type                                     U08

/* Register gcOutstandingWrites **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Number of outstanding writes per client. */

#define gcOutstandingWritesRegAddrs                                       0x0111
#define GC_OUTSTANDING_WRITES_Address                                    0x00444
#define GC_OUTSTANDING_WRITES_MSB                                             15
#define GC_OUTSTANDING_WRITES_LSB                                              0
#define GC_OUTSTANDING_WRITES_BLK                                              0
#define GC_OUTSTANDING_WRITES_Count                                            1
#define GC_OUTSTANDING_WRITES_FieldMask                               0xFFFFFFFF
#define GC_OUTSTANDING_WRITES_ReadMask                                0xFFFFFFFF
#define GC_OUTSTANDING_WRITES_WriteMask                               0x00000000
#define GC_OUTSTANDING_WRITES_ResetValue                              0x00000000

#define GC_OUTSTANDING_WRITES_PEC                                          7 : 0
#define GC_OUTSTANDING_WRITES_PEC_End                                          7
#define GC_OUTSTANDING_WRITES_PEC_Start                                        0
#define GC_OUTSTANDING_WRITES_PEC_Type                                       U08

#define GC_OUTSTANDING_WRITES_PEZ                                         15 : 8
#define GC_OUTSTANDING_WRITES_PEZ_End                                         15
#define GC_OUTSTANDING_WRITES_PEZ_Start                                        8
#define GC_OUTSTANDING_WRITES_PEZ_Type                                       U08

#define GC_OUTSTANDING_WRITES_FC                                         23 : 16
#define GC_OUTSTANDING_WRITES_FC_End                                          23
#define GC_OUTSTANDING_WRITES_FC_Start                                        16
#define GC_OUTSTANDING_WRITES_FC_Type                                        U08

#define GC_OUTSTANDING_WRITES_TOTAL                                      31 : 24
#define GC_OUTSTANDING_WRITES_TOTAL_End                                       31
#define GC_OUTSTANDING_WRITES_TOTAL_Start                                     24
#define GC_OUTSTANDING_WRITES_TOTAL_Type                                     U08

/* Register gcDebugControl0 **
** ~~~~~~~~~~~~~~~~~~~~~~~~ */
#define gcDebugControl0RegAddrs                                           0x011C
#define GC_DEBUG_CONTROL0_Address                                        0x00470
#define GC_DEBUG_CONTROL0_MSB                                                 15
#define GC_DEBUG_CONTROL0_LSB                                                  0
#define GC_DEBUG_CONTROL0_BLK                                                  0
#define GC_DEBUG_CONTROL0_Count                                                1
#define GC_DEBUG_CONTROL0_FieldMask                                   0x0F0F0F0F
#define GC_DEBUG_CONTROL0_ReadMask                                    0x0F0F0F0F
#define GC_DEBUG_CONTROL0_WriteMask                                   0x0F0F0F0F
#define GC_DEBUG_CONTROL0_ResetValue                                  0x00000000

/* Selects which set of 32 bit data to get from Fe. Resets the counters if    **
** set to 0xf.                                                                */
#define GC_DEBUG_CONTROL0_FE                                               3 : 0
#define GC_DEBUG_CONTROL0_FE_End                                               3
#define GC_DEBUG_CONTROL0_FE_Start                                             0
#define GC_DEBUG_CONTROL0_FE_Type                                            U04

/* Selects which set of 32 bit data to get from De. Resets the counters if    **
** set to 0xf.                                                                */
#define GC_DEBUG_CONTROL0_DE                                              11 : 8
#define GC_DEBUG_CONTROL0_DE_End                                              11
#define GC_DEBUG_CONTROL0_DE_Start                                             8
#define GC_DEBUG_CONTROL0_DE_Type                                            U04

/* Selects which set of 32 bit data to get from Pe. Resets the counters if    **
** set to 0xf.                                                                */
#define GC_DEBUG_CONTROL0_PE                                             19 : 16
#define GC_DEBUG_CONTROL0_PE_End                                              19
#define GC_DEBUG_CONTROL0_PE_Start                                            16
#define GC_DEBUG_CONTROL0_PE_Type                                            U04

/* Selects which set of 32 bit data to get from Sh. Resets the counters if    **
** set to 0xf.                                                                */
#define GC_DEBUG_CONTROL0_SH                                             27 : 24
#define GC_DEBUG_CONTROL0_SH_End                                              27
#define GC_DEBUG_CONTROL0_SH_Start                                            24
#define GC_DEBUG_CONTROL0_SH_Type                                            U04

/* Register gcregControl0 **
** ~~~~~~~~~~~~~~~~~~~~~~ */

/* Various control registers  */

#define gcregControl0RegAddrs                                             0x0156
#define GCREG_CONTROL0_Address                                           0x00558
#define GCREG_CONTROL0_MSB                                                    15
#define GCREG_CONTROL0_LSB                                                     0
#define GCREG_CONTROL0_BLK                                                     0
#define GCREG_CONTROL0_Count                                                   1
#define GCREG_CONTROL0_FieldMask                                      0x03FF000F
#define GCREG_CONTROL0_ReadMask                                       0x03FF000F
#define GCREG_CONTROL0_WriteMask                                      0x03FF000F
#define GCREG_CONTROL0_ResetValue                                     0x00800005

#define GCREG_CONTROL0_ENABLE_READ_MERGE                                   0 : 0
#define GCREG_CONTROL0_ENABLE_READ_MERGE_End                                   0
#define GCREG_CONTROL0_ENABLE_READ_MERGE_Start                                 0
#define GCREG_CONTROL0_ENABLE_READ_MERGE_Type                                U01

#define GCREG_CONTROL0_ENABLE_UNALIGNED_MERGE                              1 : 1
#define GCREG_CONTROL0_ENABLE_UNALIGNED_MERGE_End                              1
#define GCREG_CONTROL0_ENABLE_UNALIGNED_MERGE_Start                            1
#define GCREG_CONTROL0_ENABLE_UNALIGNED_MERGE_Type                           U01

#define GCREG_CONTROL0_ENABLE_WRITE_MERGE                                  2 : 2
#define GCREG_CONTROL0_ENABLE_WRITE_MERGE_End                                  2
#define GCREG_CONTROL0_ENABLE_WRITE_MERGE_Start                                2
#define GCREG_CONTROL0_ENABLE_WRITE_MERGE_Type                               U01

#define GCREG_CONTROL0_ENABLE_UNALIGNED_WRITE_MERGE                        3 : 3
#define GCREG_CONTROL0_ENABLE_UNALIGNED_WRITE_MERGE_End                        3
#define GCREG_CONTROL0_ENABLE_UNALIGNED_WRITE_MERGE_Start                      3
#define GCREG_CONTROL0_ENABLE_UNALIGNED_WRITE_MERGE_Type                     U01

#define GCREG_CONTROL0_OUTSTANDING_READS_PER_CHANNEL                     25 : 16
#define GCREG_CONTROL0_OUTSTANDING_READS_PER_CHANNEL_End                      25
#define GCREG_CONTROL0_OUTSTANDING_READS_PER_CHANNEL_Start                    16
#define GCREG_CONTROL0_OUTSTANDING_READS_PER_CHANNEL_Type                    U10

/*******************************************************************************
**                              ~~~~~~~~~~~~~~~~                              **
**                              Command AQMemory                              **
**                              ~~~~~~~~~~~~~~~~                              **
*******************************************************************************/

/* Offset Address
** ~~~~~~~~~~~~~~ */

#define AQ_MEMORY_ADDRESS_TYPE                                           31 : 31
#define AQ_MEMORY_ADDRESS_TYPE_End                                            31
#define AQ_MEMORY_ADDRESS_TYPE_Start                                          31
#define AQ_MEMORY_ADDRESS_TYPE_Type                                          U01
#define   AQ_MEMORY_ADDRESS_TYPE_SYSTEM                                      0x0
#define   AQ_MEMORY_ADDRESS_TYPE_VIRTUAL_SYSTEM                              0x1

#define AQ_MEMORY_ADDRESS_ADDRESS                                         30 : 0
#define AQ_MEMORY_ADDRESS_ADDRESS_End                                         30
#define AQ_MEMORY_ADDRESS_ADDRESS_Start                                        0
#define AQ_MEMORY_ADDRESS_ADDRESS_Type                                       U31

/* Offset PageTableEntry
** ~~~~~~~~~~~~~~~~~~~~~ */

#define AQ_MEMORY_PAGE_TABLE_ENTRY_ADDRESS                               31 : 10
#define AQ_MEMORY_PAGE_TABLE_ENTRY_ADDRESS_End                                31
#define AQ_MEMORY_PAGE_TABLE_ENTRY_ADDRESS_Start                              10
#define AQ_MEMORY_PAGE_TABLE_ENTRY_ADDRESS_Type                              U22

#define AQ_MEMORY_PAGE_TABLE_ENTRY_LINKED                                  8 : 8
#define AQ_MEMORY_PAGE_TABLE_ENTRY_LINKED_End                                  8
#define AQ_MEMORY_PAGE_TABLE_ENTRY_LINKED_Start                                8
#define AQ_MEMORY_PAGE_TABLE_ENTRY_LINKED_Type                               U01

#define AQ_MEMORY_PAGE_TABLE_ENTRY_REFERENCE_COUNT                         7 : 0
#define AQ_MEMORY_PAGE_TABLE_ENTRY_REFERENCE_COUNT_End                         7
#define AQ_MEMORY_PAGE_TABLE_ENTRY_REFERENCE_COUNT_Start                       0
#define AQ_MEMORY_PAGE_TABLE_ENTRY_REFERENCE_COUNT_Type                      U08

/* Define TileStatus
** ~~~~~~~~~~~~~~~~~ */
#define   AQ_MEMORY_TILE_STATUS_REQUEST64                                    0x0
#define   AQ_MEMORY_TILE_STATUS_FAST_CLEAR                                   0x1
#define   AQ_MEMORY_TILE_STATUS_REQUEST32                                    0x2
#define   AQ_MEMORY_TILE_STATUS_REQUEST16                                    0x3
#define   AQ_MEMORY_TILE_STATUS_REQUEST8                                     0x4

