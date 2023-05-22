/*
 * Copyright (c) 2022 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_BASE_RPC_SRC_RPC_COMMON_H
#define AMEBA_BASE_RPC_SRC_RPC_COMMON_H

#include "rpc/rpc_struct.h"
#include "hardware/rpc/rpc_hw_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

bool_t xdr_RPC_STRUCT(XDR *xdrs, RPC_STRUCT *objp);
RPCHwManager *GetRPCManager(void);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_RPC_SRC_RPC_COMMON_H