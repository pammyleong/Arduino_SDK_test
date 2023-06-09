/**************************************************************************//**
* @file        hal_eth_nsc.h
* @brief       The HAL Non-secure callable API implementation for Ethernet
*
* @version     V1.00
* @date        2022-11-15
*
* @note
*
******************************************************************************
*
* Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************/



#ifndef _HAL_ETH_NSC_H_
#define _HAL_ETH_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */
#include "hal_eth.h"
#ifdef  __cplusplus
extern "C"
{
#endif

/**
* @addtogroup hal_eth_nsc Ethernet NSC
* @{
*/
#if defined(CONFIG_BUILD_SECURE)
void NS_ENTRY hal_eth_sys_hw_ctrl_nsc(u8 hw_id, u8 en);

#endif

#if defined(CONFIG_BUILD_NONSECURE)
void hal_eth_sys_hw_ctrl_nsc(u8 hw_id, u8 en);

#if !defined(ENABLE_SECCALL_PATCH)
#define hal_eth_sys_hw_ctrl             hal_eth_sys_hw_ctrl_nsc

#endif

#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

/** @} */ /* End of group hal_eth_nsc */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_ETH_NSC_H_"
