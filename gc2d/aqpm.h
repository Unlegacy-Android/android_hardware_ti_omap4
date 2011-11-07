/*
 * aqpowermgmtreg.h
 *
 * Copyright (C) 2010-2011 Texas Instruments, Inc.
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
**                      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                      **
**                      Module PowerManagementController                      **
**                      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                      **
*******************************************************************************/

/* Register gcModulePowerControls **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Control register for module level power controls. */

#define gcModulePowerControlsRegAddrs                                     0x0040
#define GC_MODULE_POWER_CONTROLS_Address                                 0x00100
#define GC_MODULE_POWER_CONTROLS_MSB                                          15
#define GC_MODULE_POWER_CONTROLS_LSB                                           0
#define GC_MODULE_POWER_CONTROLS_BLK                                           0
#define GC_MODULE_POWER_CONTROLS_Count                                         1
#define GC_MODULE_POWER_CONTROLS_FieldMask                            0xFFFF00F7
#define GC_MODULE_POWER_CONTROLS_ReadMask                             0xFFFF00F7
#define GC_MODULE_POWER_CONTROLS_WriteMask                            0xFFFF00F7
#define GC_MODULE_POWER_CONTROLS_ResetValue                           0x00140020

/* Enables module level clock gating. */
#define GC_MODULE_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING                0 : 0
#define GC_MODULE_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING_End                0
#define GC_MODULE_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING_Start              0
#define GC_MODULE_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING_Type             U01

/* Disables module level clock gating for stall condition. */
#define GC_MODULE_POWER_CONTROLS_DISABLE_STALL_MODULE_CLOCK_GATING         1 : 1
#define GC_MODULE_POWER_CONTROLS_DISABLE_STALL_MODULE_CLOCK_GATING_End         1
#define GC_MODULE_POWER_CONTROLS_DISABLE_STALL_MODULE_CLOCK_GATING_Start       1
#define GC_MODULE_POWER_CONTROLS_DISABLE_STALL_MODULE_CLOCK_GATING_Type      U01

/* Disables module level clock gating for starve/idle condition. */
#define GC_MODULE_POWER_CONTROLS_DISABLE_STARVE_MODULE_CLOCK_GATING        2 : 2
#define GC_MODULE_POWER_CONTROLS_DISABLE_STARVE_MODULE_CLOCK_GATING_End        2
#define GC_MODULE_POWER_CONTROLS_DISABLE_STARVE_MODULE_CLOCK_GATING_Start      2
#define GC_MODULE_POWER_CONTROLS_DISABLE_STARVE_MODULE_CLOCK_GATING_Type     U01

/* Number of clock cycles to wait after turning on the clock. */
#define GC_MODULE_POWER_CONTROLS_TURN_ON_COUNTER                           7 : 4
#define GC_MODULE_POWER_CONTROLS_TURN_ON_COUNTER_End                           7
#define GC_MODULE_POWER_CONTROLS_TURN_ON_COUNTER_Start                         4
#define GC_MODULE_POWER_CONTROLS_TURN_ON_COUNTER_Type                        U04

/* Counter value for clock gating the module if the module is idle for  this  **
** amount of clock cycles.                                                    */
#define GC_MODULE_POWER_CONTROLS_TURN_OFF_COUNTER                        31 : 16
#define GC_MODULE_POWER_CONTROLS_TURN_OFF_COUNTER_End                         31
#define GC_MODULE_POWER_CONTROLS_TURN_OFF_COUNTER_Start                       16
#define GC_MODULE_POWER_CONTROLS_TURN_OFF_COUNTER_Type                       U16

/* Register gcModulePowerModuleControl **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Module level control registers. */

#define gcModulePowerModuleControlRegAddrs                                0x0041
#define GC_MODULE_POWER_MODULE_CONTROL_Address                           0x00104
#define GC_MODULE_POWER_MODULE_CONTROL_MSB                                    15
#define GC_MODULE_POWER_MODULE_CONTROL_LSB                                     0
#define GC_MODULE_POWER_MODULE_CONTROL_BLK                                     0
#define GC_MODULE_POWER_MODULE_CONTROL_Count                                   1
#define GC_MODULE_POWER_MODULE_CONTROL_FieldMask                      0x00000007
#define GC_MODULE_POWER_MODULE_CONTROL_ReadMask                       0x00000007
#define GC_MODULE_POWER_MODULE_CONTROL_WriteMask                      0x00000007
#define GC_MODULE_POWER_MODULE_CONTROL_ResetValue                     0x00000000

/* Disables module level clock gating for FE. */
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_FE      0 : 0
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_FE_End      0
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_FE_Start    0
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_FE_Type   U01

/* Disables module level clock gating for DE. */
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_DE      1 : 1
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_DE_End      1
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_DE_Start    1
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_DE_Type   U01

/* Disables module level clock gating for PE. */
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_PE      2 : 2
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_PE_End      2
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_PE_Start    2
#define GC_MODULE_POWER_MODULE_CONTROL_DISABLE_MODULE_CLOCK_GATING_PE_Type   U01

/* Register gcModulePowerModuleStatus **
** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Module level control status. */

#define gcModulePowerModuleStatusRegAddrs                                 0x0042
#define GC_MODULE_POWER_MODULE_STATUS_Address                            0x00108
#define GC_MODULE_POWER_MODULE_STATUS_MSB                                     15
#define GC_MODULE_POWER_MODULE_STATUS_LSB                                      0
#define GC_MODULE_POWER_MODULE_STATUS_BLK                                      0
#define GC_MODULE_POWER_MODULE_STATUS_Count                                    1
#define GC_MODULE_POWER_MODULE_STATUS_FieldMask                       0x00000007
#define GC_MODULE_POWER_MODULE_STATUS_ReadMask                        0x00000007
#define GC_MODULE_POWER_MODULE_STATUS_WriteMask                       0x00000000
#define GC_MODULE_POWER_MODULE_STATUS_ResetValue                      0x00000000

/* Module level clock gating is ON for FE. */
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_FE                0 : 0
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_FE_End                0
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_FE_Start              0
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_FE_Type             U01

/* Module level clock gating is ON for DE. */
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_DE                1 : 1
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_DE_End                1
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_DE_Start              1
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_DE_Type             U01

/* Module level clock gating is ON for PE. */
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_PE                2 : 2
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_PE_End                2
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_PE_Start              2
#define GC_MODULE_POWER_MODULE_STATUS_MODULE_CLOCK_GATED_PE_Type             U01

