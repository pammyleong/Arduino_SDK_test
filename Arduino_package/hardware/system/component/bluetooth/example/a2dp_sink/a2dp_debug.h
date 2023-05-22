/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
* @file     a2dp_debug.h
* @brief    Source file for a2dp debug.
* @details  User command interfaces.
* @author   sherman
* @date     2021-12-27
* @version  v1.0
* *************************************************************************************
*/
#ifndef _A2DP_DEBUG_H_
#define _A2DP_DEBUG_H_

//#define CONFIG_A2DP_DEBUG

#ifdef CONFIG_A2DP_DEBUG
#define _dbgdump	printf("\n\r"); printf
#define PREFIX	"[A2DP]: "
#if	defined (_dbgdump)
#undef DBG_A2DP
#define DBG_A2DP(...)     do {\
		_dbgdump(PREFIX __VA_ARGS__);\
	}while(0)
#endif
#else
#define DBG_A2DP(x, ...) do {} while(0)
#endif /* _A2DP_DEBUG_H_ */

#endif /* _A2DP_DEBUG_H_ */