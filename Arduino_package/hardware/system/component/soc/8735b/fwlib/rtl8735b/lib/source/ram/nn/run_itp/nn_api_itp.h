/**************************************************************************//**
 * @file     nn_api.h
 * @brief    nn_api header
 * @version  V1.00
 * @date     2016-06-08
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
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

#ifndef _HAL_NNAPIITP_H_
#define _HAL_NNAPIITP_H_

//API used in nn_detect
void nn_config_roi(struct MODEL_INFO_S *model_info,
				   struct cvRect_S     *ROIRect);
void nn_config_rgb(struct MODEL_INFO_S *model_info,
				   unsigned char       *frame_in);

#endif  // end of "#define _HAL_NNAPIITP_H_"
