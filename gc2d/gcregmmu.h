/*
 * gcregmmu.h
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
**                                 ~~~~~~~~~~                                 **
**                                 Module MMU                                 **
**                                 ~~~~~~~~~~                                 **
*******************************************************************************/

/* Register gcregMMUSafeAddress **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* A 64-byte address that will acts as a 'safe' zone.  Any address that would **
** cause an exception is routed to this safe zone.  Reads will happend and    **
** writes will go to this address, but with a write-enable of 0. This         **
** register can only be programmed once after a reset - any attempt to write  **
** to this register after the initial write-after-reset will be ignored.      */

#define gcregMMUSafeAddressRegAddrs                                       0x0060
#define GCREG_MMU_SAFE_ADDRESS_Address                                   0x00180
#define GCREG_MMU_SAFE_ADDRESS_MSB                                            15
#define GCREG_MMU_SAFE_ADDRESS_LSB                                             0
#define GCREG_MMU_SAFE_ADDRESS_BLK                                             0
#define GCREG_MMU_SAFE_ADDRESS_Count                                           1
#define GCREG_MMU_SAFE_ADDRESS_FieldMask                              0xFFFFFFFF
#define GCREG_MMU_SAFE_ADDRESS_ReadMask                               0xFFFFFFC0
#define GCREG_MMU_SAFE_ADDRESS_WriteMask                              0xFFFFFFC0
#define GCREG_MMU_SAFE_ADDRESS_ResetValue                             0x00000000

#define GCREG_MMU_SAFE_ADDRESS_ADDRESS                                    31 : 0
#define GCREG_MMU_SAFE_ADDRESS_ADDRESS_End                                    31
#define GCREG_MMU_SAFE_ADDRESS_ADDRESS_Start                                   0
#define GCREG_MMU_SAFE_ADDRESS_ADDRESS_Type                                  U32

/* Register gcregMMUException (4 in total) **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Up to 4 registers that will hold the original address that generated an    **
** execption.                                                                 */

#define gcregMMUExceptionRegAddrs                                         0x0064
#define GCREG_MMU_EXCEPTION_Address                                      0x00190
#define GCREG_MMU_EXCEPTION_MSB                                               15
#define GCREG_MMU_EXCEPTION_LSB                                                2
#define GCREG_MMU_EXCEPTION_BLK                                                2
#define GCREG_MMU_EXCEPTION_Count                                              4
#define GCREG_MMU_EXCEPTION_FieldMask                                 0xFFFFFFFF
#define GCREG_MMU_EXCEPTION_ReadMask                                  0xFFFFFFFF
#define GCREG_MMU_EXCEPTION_WriteMask                                 0xFFFFFFFF
#define GCREG_MMU_EXCEPTION_ResetValue                                0x00000000

#define GCREG_MMU_EXCEPTION_ADDRESS                                       31 : 0
#define GCREG_MMU_EXCEPTION_ADDRESS_End                                       31
#define GCREG_MMU_EXCEPTION_ADDRESS_Start                                      0
#define GCREG_MMU_EXCEPTION_ADDRESS_Type                                     U32

/* Register gcregMMUConfiguration **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* This register controls the master TLB of the MMU. */

#define gcregMMUConfigurationRegAddrs                                     0x0061
#define GCREG_MMU_CONFIGURATION_Address                                  0x00184
#define GCREG_MMU_CONFIGURATION_MSB                                           15
#define GCREG_MMU_CONFIGURATION_LSB                                            0
#define GCREG_MMU_CONFIGURATION_BLK                                            0
#define GCREG_MMU_CONFIGURATION_Count                                          1
#define GCREG_MMU_CONFIGURATION_FieldMask                             0xFFFFFD99
#define GCREG_MMU_CONFIGURATION_ReadMask                              0xFFFFFD99
#define GCREG_MMU_CONFIGURATION_WriteMask                             0xFFFFFD99
#define GCREG_MMU_CONFIGURATION_ResetValue                            0x00000000

/* Upper bits of the page aligned (depending on the mode) master TLB. */
#define GCREG_MMU_CONFIGURATION_ADDRESS                                  31 : 10
#define GCREG_MMU_CONFIGURATION_ADDRESS_End                                   31
#define GCREG_MMU_CONFIGURATION_ADDRESS_Start                                 10
#define GCREG_MMU_CONFIGURATION_ADDRESS_Type                                 U22

/* Mask for Address field. */
#define GCREG_MMU_CONFIGURATION_MASK_ADDRESS                               8 : 8
#define GCREG_MMU_CONFIGURATION_MASK_ADDRESS_End                               8
#define GCREG_MMU_CONFIGURATION_MASK_ADDRESS_Start                             8
#define GCREG_MMU_CONFIGURATION_MASK_ADDRESS_Type                            U01
#define   GCREG_MMU_CONFIGURATION_MASK_ADDRESS_ENABLED                       0x0
#define   GCREG_MMU_CONFIGURATION_MASK_ADDRESS_MASKED                        0x1

/* Mask Flush field. */
#define GCREG_MMU_CONFIGURATION_MASK_FLUSH                                 7 : 7
#define GCREG_MMU_CONFIGURATION_MASK_FLUSH_End                                 7
#define GCREG_MMU_CONFIGURATION_MASK_FLUSH_Start                               7
#define GCREG_MMU_CONFIGURATION_MASK_FLUSH_Type                              U01
#define   GCREG_MMU_CONFIGURATION_MASK_FLUSH_ENABLED                         0x0
#define   GCREG_MMU_CONFIGURATION_MASK_FLUSH_MASKED                          0x1

/* Flush the MMU caches. */
#define GCREG_MMU_CONFIGURATION_FLUSH                                      4 : 4
#define GCREG_MMU_CONFIGURATION_FLUSH_End                                      4
#define GCREG_MMU_CONFIGURATION_FLUSH_Start                                    4
#define GCREG_MMU_CONFIGURATION_FLUSH_Type                                   U01
#define   GCREG_MMU_CONFIGURATION_FLUSH_FLUSH                                0x1

/* Mask Mode field. */
#define GCREG_MMU_CONFIGURATION_MASK_MODE                                  3 : 3
#define GCREG_MMU_CONFIGURATION_MASK_MODE_End                                  3
#define GCREG_MMU_CONFIGURATION_MASK_MODE_Start                                3
#define GCREG_MMU_CONFIGURATION_MASK_MODE_Type                               U01
#define   GCREG_MMU_CONFIGURATION_MASK_MODE_ENABLED                          0x0
#define   GCREG_MMU_CONFIGURATION_MASK_MODE_MASKED                           0x1

/* Set the mode for the Master TLB. */
#define GCREG_MMU_CONFIGURATION_MODE                                       0 : 0
#define GCREG_MMU_CONFIGURATION_MODE_End                                       0
#define GCREG_MMU_CONFIGURATION_MODE_Start                                     0
#define GCREG_MMU_CONFIGURATION_MODE_Type                                    U01
/* The Master TLB is 4kB in size and contains 1024 entries. Each page can be  **
** 4kB or 64kB in size.                                                       */
#define   GCREG_MMU_CONFIGURATION_MODE_MODE4_K                               0x0
/* The Master TLB is 1kB in size and contains 256 entries. Each page can be   **
** 4kB, 64kB, 1MB or 16MB in size.                                            */
#define   GCREG_MMU_CONFIGURATION_MODE_MODE1_K                               0x1

/* Register gcregMMUStatus **
** ~~~~~~~~~~~~~~~~~~~~~~~ */

/* Status register that holds which MMU generated an exception. */

#define gcregMMUStatusRegAddrs                                            0x0062
#define GCREG_MMU_STATUS_Address                                         0x00188
#define GCREG_MMU_STATUS_MSB                                                  15
#define GCREG_MMU_STATUS_LSB                                                   0
#define GCREG_MMU_STATUS_BLK                                                   0
#define GCREG_MMU_STATUS_Count                                                 1
#define GCREG_MMU_STATUS_FieldMask                                    0x00003333
#define GCREG_MMU_STATUS_ReadMask                                     0x00003333
#define GCREG_MMU_STATUS_WriteMask                                    0x00000000
#define GCREG_MMU_STATUS_ResetValue                                   0x00000000

/* MMU 3 caused an exception and the fourth gcregMMUException register holds  **
** the offending address.                                                     */
#define GCREG_MMU_STATUS_EXCEPTION3                                      13 : 12
#define GCREG_MMU_STATUS_EXCEPTION3_End                                       13
#define GCREG_MMU_STATUS_EXCEPTION3_Start                                     12
#define GCREG_MMU_STATUS_EXCEPTION3_Type                                     U02
#define   GCREG_MMU_STATUS_EXCEPTION3_SLAVE_NOT_PRESENT                      0x1
#define   GCREG_MMU_STATUS_EXCEPTION3_PAGE_NOT_PRESENT                       0x2
#define   GCREG_MMU_STATUS_EXCEPTION3_WRITE_VIOLATION                        0x3

/* MMU 2 caused an exception and the third gcregMMUException register holds   **
** the offending address.                                                     */
#define GCREG_MMU_STATUS_EXCEPTION2                                        9 : 8
#define GCREG_MMU_STATUS_EXCEPTION2_End                                        9
#define GCREG_MMU_STATUS_EXCEPTION2_Start                                      8
#define GCREG_MMU_STATUS_EXCEPTION2_Type                                     U02
#define   GCREG_MMU_STATUS_EXCEPTION2_SLAVE_NOT_PRESENT                      0x1
#define   GCREG_MMU_STATUS_EXCEPTION2_PAGE_NOT_PRESENT                       0x2
#define   GCREG_MMU_STATUS_EXCEPTION2_WRITE_VIOLATION                        0x3

/* MMU 1 caused an exception and the second gcregMMUException register holds  **
** the offending address.                                                     */
#define GCREG_MMU_STATUS_EXCEPTION1                                        5 : 4
#define GCREG_MMU_STATUS_EXCEPTION1_End                                        5
#define GCREG_MMU_STATUS_EXCEPTION1_Start                                      4
#define GCREG_MMU_STATUS_EXCEPTION1_Type                                     U02
#define   GCREG_MMU_STATUS_EXCEPTION1_SLAVE_NOT_PRESENT                      0x1
#define   GCREG_MMU_STATUS_EXCEPTION1_PAGE_NOT_PRESENT                       0x2
#define   GCREG_MMU_STATUS_EXCEPTION1_WRITE_VIOLATION                        0x3

/* MMU 0 caused an exception and the first gcregMMUException register holds   **
** the offending address.                                                     */
#define GCREG_MMU_STATUS_EXCEPTION0                                        1 : 0
#define GCREG_MMU_STATUS_EXCEPTION0_End                                        1
#define GCREG_MMU_STATUS_EXCEPTION0_Start                                      0
#define GCREG_MMU_STATUS_EXCEPTION0_Type                                     U02
#define   GCREG_MMU_STATUS_EXCEPTION0_SLAVE_NOT_PRESENT                      0x1
#define   GCREG_MMU_STATUS_EXCEPTION0_PAGE_NOT_PRESENT                       0x2
#define   GCREG_MMU_STATUS_EXCEPTION0_WRITE_VIOLATION                        0x3

/* Register gcregMMUControl **
** ~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Control register that enables the MMU (only time shot). */

#define gcregMMUControlRegAddrs                                           0x0063
#define GCREG_MMU_CONTROL_Address                                        0x0018C
#define GCREG_MMU_CONTROL_MSB                                                 15
#define GCREG_MMU_CONTROL_LSB                                                  0
#define GCREG_MMU_CONTROL_BLK                                                  0
#define GCREG_MMU_CONTROL_Count                                                1
#define GCREG_MMU_CONTROL_FieldMask                                   0x00000001
#define GCREG_MMU_CONTROL_ReadMask                                    0x00000000
#define GCREG_MMU_CONTROL_WriteMask                                   0x00000001
#define GCREG_MMU_CONTROL_ResetValue                                  0x00000000

/* Enable the MMU. For security reasons, once the MMU is  enabled it cannot   **
** be disabled anymore.                                                       */
#define GCREG_MMU_CONTROL_ENABLE                                           0 : 0
#define GCREG_MMU_CONTROL_ENABLE_End                                           0
#define GCREG_MMU_CONTROL_ENABLE_Start                                         0
#define GCREG_MMU_CONTROL_ENABLE_Type                                        U01
#define   GCREG_MMU_CONTROL_ENABLE_ENABLE                                    0x1

