/**************************************************************************//**
 * @file     hal_timer.h
 * @brief    The HAL API implementation for the G-Timer device.
 * @version  V1.00
 * @date     2020-11-12
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_
#include "cmsis.h"
#include "hal_timer_nsc.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_timer TIMER
 * @ingroup 8195bh_hal
 * @{
 * @brief The TIMER HAL module of the HS platform.
 */

/**
  * @brief The stubs functions table to exports TIMER HAL functions in ROM.
  */

extern const hal_timer_func_stubs_t hal_gtimer_stubs;

#if !defined(CONFIG_BUILD_SECURE)
extern const hal_timer_func_stubs_t __rom_stubs_hal_timer_s;
#endif


/**
 *  @brief To read timer group interrupt status
 *
 *  @param[in] ptg_adp The timer group adapter.
 *
 *  @returns The interrupt pending status
 */
__STATIC_INLINE
uint8_t hal_timer_group_get_ists(hal_timer_group_adapter_t *ptg_adp)
{
	TG_TypeDef *TG_OBJ = (TG_TypeDef *)(ptg_adp->tg_ba);
	return TG_OBJ->TG_ISTS;
}

/**
 *  @brief To read timer group interrupt raw status (without mask)
 *
 *  @param[in] ptg_adp The timer group adapter.
 *
 *  @returns The interrupt pending status
 */
__STATIC_INLINE
uint8_t hal_timer_group_get_rists(hal_timer_group_adapter_t *ptg_adp)
{
	TG_TypeDef *TG_OBJ = (TG_TypeDef *)(ptg_adp->tg_ba);
	return TG_OBJ->TG_RAW_ISTS;
}

/**
 *  @brief To get the interrupt pending status (with mask).
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The interrupt pending status
 */
__STATIC_INLINE
uint8_t hal_timer_get_int_pending(phal_timer_adapter_t ptimer_adp)
{
	TG_TypeDef *TG_OBJ = (TG_TypeDef *)(ptimer_adp->tg_ba);
	return TG_OBJ->TG_ISTS & (1 << ptimer_adp->tid);
}

/**
 *  @brief To get the interrupt pending status (without mask).
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The interrupt pending status
 */
__STATIC_INLINE
uint8_t hal_timer_get_rint_pending(phal_timer_adapter_t ptimer_adp)
{
	TG_TypeDef *TG_OBJ = (TG_TypeDef *)(ptimer_adp->tg_ba);
	return TG_OBJ->TG_RAW_ISTS & (1 << ptimer_adp->tid);
}

/**
 *  @brief To set the reload value for timer operation mode.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] reload The relaod counter value for timer mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_reload(phal_timer_adapter_t ptimer_adp, uint32_t reload)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	TM_OBJ->TM_LC = reload;
}

/**
 *  @brief To read the timer counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The timer counter value
 */
__STATIC_INLINE
uint32_t hal_timer_read(phal_timer_adapter_t ptimer_adp)
{
	uint32_t cnt;

	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);

	do {
		cnt = TM_OBJ->TM_TC;
	} while (cnt != TM_OBJ->TM_TC);

	return cnt;
}

/**
 *  @brief To set the timer counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] tc The timer counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_write(phal_timer_adapter_t ptimer_adp, uint32_t tc)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	TM_OBJ->TM_TC = tc;
}

/**
 *  @brief To write the timer pre-scale counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] psc The pre-scale counter value
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_write_prescal_cnt(phal_timer_adapter_t ptimer_adp, uint16_t psc)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	TM_OBJ->TM_PC = psc;
}

/**
 *  @brief To read the timer pre-scale counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The pre-scaler current counter value
 */
__STATIC_INLINE
uint16_t hal_timer_read_prescal_cnt(phal_timer_adapter_t ptimer_adp)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	return TM_OBJ->TM_PC;
}

/**
 *  @brief To set the reload value of the timer pre-scaler
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] psrc The pre-scaler counter reload value
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_prescal(phal_timer_adapter_t ptimer_adp, uint16_t psrc)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	TM_OBJ->TM_PR = psrc;
}

/**
 *  @brief To enable/start the timer.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_enable(phal_timer_adapter_t ptimer_adp)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	TM_OBJ->TM_CTRL |= TM_BIT_EN;
}

/**
 *  @brief To disable the timer.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_disable(phal_timer_adapter_t ptimer_adp)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	TM_OBJ->TM_CTRL &= (~TM_BIT_EN);
	TM_OBJ->TM_ISR &= 0x1F;
}

/**
 *  @brief To set the interrupt mask.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] imr The interrupt mask setting (0/1).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_imr(phal_timer_adapter_t ptimer_adp, uint8_t imr)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	if ((imr == (u8)1)) {
		TM_OBJ->TM_CTRL = TM_OBJ->TM_CTRL | (1 << TM_SHIFT_IMR);
	} else {
		TM_OBJ->TM_CTRL = TM_OBJ->TM_CTRL & ~(1 << TM_SHIFT_IMR);
	}
}

/**
 *  @brief To set the timer operation mode: timer (reload) mode or counter (one shot) mode
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] op_mode The timer operation mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_opmode(phal_timer_adapter_t ptimer_adp, timer_op_mode_t op_mode)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	if ((op_mode == (u8)1)) {
		TM_OBJ->TM_CTRL = TM_OBJ->TM_CTRL | (1 << TM_SHIFT_MOD);
	} else {
		TM_OBJ->TM_CTRL = TM_OBJ->TM_CTRL & ~(1 << TM_SHIFT_MOD);
	}
}

/**
 *  @brief To set the timer countting mode. (up counter/ down counter)
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] cnt_mode The countting mode. 0: up countting, 1: down countting
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_cntmode(phal_timer_adapter_t ptimer_adp, timer_cnt_mode_t cnt_mode)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	if ((cnt_mode == (u8)1)) {
		TM_OBJ->TM_CTRL = TM_OBJ->TM_CTRL | (1 << TM_SHIFT_CNT_MOD);
	} else {
		TM_OBJ->TM_CTRL = TM_OBJ->TM_CTRL & ~(1 << TM_SHIFT_CNT_MOD);
	}

}

/**
 *  @brief To read the interrupt status.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The interrupt status
 */
__STATIC_INLINE
uint32_t hal_timer_read_isr(phal_timer_adapter_t ptimer_adp)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	return TM_OBJ->TM_ISR;
}

/**
 *  @brief To clear the interrupt pending status.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] int_ev The pending interrupt to be cleared
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_clear_isr(phal_timer_adapter_t ptimer_adp, uint32_t int_ev)
{
	TM_TypeDef *TM_OBJ = (TM_TypeDef *)(ptimer_adp->tmr_ba);
	TM_OBJ->TM_ISR = int_ev;
}

/**
 *  @brief To convert a tick count to the time period in us
 *
 *  @param[in] ticks The number of ticks.
 *  @param[in] sclk_idx The timer SCLK selection.
 *
 *  @returns The converted time period in us.
 */
__STATIC_INLINE
uint32_t hal_timer_convert_ticks_to_us(uint32_t ticks, uint8_t sclk_idx)
{
	return hal_gtimer_stubs.hal_timer_convert_ticks_to_us(ticks, sclk_idx);
}

/**
 *  @brief To convert a time period in us to number of 32K ticks
 *
 *  @param[in] time_us The timer period in us.
 *  @param[in] sclk_idx The timer SCLK selection.
 *
 *  @returns The converted 32K ticks.
 */
__STATIC_INLINE
uint32_t hal_timer_convert_us_to_ticks(uint32_t time_us, uint8_t sclk_idx)
{
	return hal_gtimer_stubs.hal_timer_convert_us_to_ticks(time_us, sclk_idx);
}

/**
 *  @brief To convert a tick count to the time period in us
 *
 *  @param[in] ticks The number of ticks.
 *  @param[in] sclk_idx The timer SCLK selection.
 *
 *  @returns The converted time period in us.
 */
__STATIC_INLINE
uint64_t hal_timer_convert_ticks_to_us64(uint64_t ticks, uint8_t sclk_idx)
{
	return hal_gtimer_stubs.hal_timer_convert_ticks_to_us64(ticks, sclk_idx);
}

/**
 *  @brief To convert a time period in us to number of 32K ticks
 *
 *  @param[in] time_us The timer period in us.
 *  @param[in] sclk_idx The timer SCLK selection.
 *
 *  @returns The converted 32K ticks.
 */
__STATIC_INLINE
uint64_t hal_timer_convert_us_to_ticks64(uint64_t time_us, uint8_t sclk_idx)
{
	return hal_gtimer_stubs.hal_timer_convert_us_to_ticks64(time_us, sclk_idx);
}

/**
 *  @brief The Common IRQ handler of G-Timer group.
 *
 *  @param[in] hid.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_irq_handler(void *hid)
{
	hal_gtimer_stubs.hal_timer_irq_handler(hid);
}

/**
 *  @brief To enable/disbale the timer counter match event.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] match_ev The match event number(0 ~ 3).
 *  @param[in] enable Enable control. (1: enable, 0: disable)
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_me_ctrl(phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, uint8_t enable)
{
	hal_gtimer_stubs.hal_timer_me_ctrl(ptimer_adp, match_ev, enable);
}

/**
 *  @brief To set the counter number of a counter match event.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] match_ev The match event number(0 ~ 3).
 *  @param[in] counter The counter value for the timer match filer to match to.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_me_counter(phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, uint32_t counter)
{
	hal_gtimer_stubs.hal_timer_set_me_counter(ptimer_adp, match_ev, counter);
}

#if 1

/**
 *  @brief To enable or disable a timer group block.
 *
 *  @param[in] tgid The timer group ID(index).
 *  @param[in] en  Enable control: 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_group_en_ctrl(uint32_t tgid, BOOL en)
{
	//hal_gtimer_stubs.hal_timer_group_en_ctrl (tgid, en);
}

/**
 *  @brief To enable/disable the APB clock for timer group block.
 *
 *  @param[in] tgid The timer group ID(index).
 *  @param[in] en  Enable control: 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_group_pclk_ctrl(uint32_t tgid, BOOL en)
{
	//hal_gtimer_stubs.hal_timer_group_pclk_ctrl (tgid, en);
}

/**
 *  @brief To enable/disable the system clock for timer group block.
 *
 *  @param[in] tgid The timer group ID(index).
 *  @param[in] en  Enable control: 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_group_sclk_ctrl(uint32_t tgid, BOOL en)
{
	//hal_gtimer_stubs.hal_timer_group_sclk_ctrl (tgid, en);
}

/**
 *  @brief To select the clock source for timer group block interrupt.
 *         When in sleep mode, just can use the SCLK for the interrupr circute.
 *
 *  @param[in] tgid The timer group ID(index).
 *  @param[in] clk_sel  The clock source selection: 0: APB clock, 1: SCLK.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_group_intclk_sel(uint32_t tgid, timer_interrupt_clk_t clk_sel)
{
	//hal_gtimer_stubs.hal_timer_group_intclk_sel (tgid, clk_sel);
}

/**
 *  @brief To select the source clock of a timer group.
 *
 *  @param[in] ptg_adp The timer group adapter.
 *  @param[in] sclk The source clock freq.
 *
 *  @returns void
 */

#endif

//__STATIC_INLINE
//void hal_timer_group_sclk_sel (hal_timer_group_adapter_t *ptg_adp, uint32_t sclk_freq)
//{
//#if defined(CONFIG_BUILD_NONSECURE)
//    hal_timer_group_sclk_sel_nsc(ptg_adp, sclk_freq);
//#else
//    hal_gtimer_stubs.hal_timer_group_sclk_sel (ptg_adp, sclk_freq);
//#endif
//}

#if !defined(CONFIG_BUILD_NONSECURE)
__STATIC_INLINE
hal_status_t hal_timer_group_sclk_sel(hal_timer_group_adapter_t *ptg_adp, uint32_t sclk_freq)
{
	return hal_gtimer_stubs.hal_timer_group_sclk_sel(ptg_adp, sclk_freq);
}
#endif


/**
 *  @brief To initial a HW timer group adapter.
 *
 *  @param[in] ptg_adp The timer group adapter.
 *  @param[in] tgid The timer group ID(index).
 *
 *  @returns void
 */


//__STATIC_INLINE
//void hal_timer_clock_init (uint32_t tgid, int en)
//{
//#if defined(CONFIG_BUILD_NONSECURE)
//    hal_timer_clock_init_nsc(tgid, en);
//#else
//    hal_gtimer_stubs.hal_timer_clock_init (tgid, en);
//#endif
//}

#if !defined(CONFIG_BUILD_NONSECURE)
__STATIC_INLINE
void hal_timer_clock_init(uint32_t tgid, int en)
{
	hal_gtimer_stubs.hal_timer_clock_init(tgid, en);
}
#endif


/**
 *  @brief To initial a HW timer group adapter.
 *
 *  @param[in] ptg_adp The timer group adapter.
 *  @param[in] tgid The timer group ID(index).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_group_init(hal_timer_group_adapter_t *ptg_adp, uint32_t tgid)
{
	hal_gtimer_stubs.hal_timer_group_init(ptg_adp, tgid);
}


/**
 *  @brief To de-initial(disable) a HW timer group adapter.
 *
 *  @param[in] ptg_adp The timer group adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_group_deinit(hal_timer_group_adapter_t *ptg_adp)
{
	hal_gtimer_stubs.hal_timer_group_deinit(ptg_adp);
}

/**
 *  @brief To initial a HW timer adapter.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] tid The timer ID(index).
 *  @param[in] tg The timer group ID(index).
 *
 *  @returns     HAL_OK:  Setting succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 */
__STATIC_INLINE
hal_status_t hal_timer_bare_init(phal_timer_adapter_t ptimer_adp, timer_id_t tid, u8 tg)
{
	return hal_gtimer_stubs.hal_timer_bare_init(ptimer_adp, tid, tg);
}

/**
 *  @brief To un-initial a HW timer adapter.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_deinit(phal_timer_adapter_t ptimer_adp)
{
	hal_gtimer_stubs.hal_timer_deinit(ptimer_adp);
}

/**
 *  @brief To register a IRQ handler for a timer group.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] irq_handler The call back function of the IRQ.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_group_reg_irq(hal_timer_group_adapter_t *ptg_adp, irq_handler_t irq_handler)
{
	hal_gtimer_stubs.hal_timer_group_reg_irq(ptg_adp, irq_handler);
}

/**
 *  @brief To register a timer timeout IRQ call back function
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] callback The call back function.
 *  @param[in] phid The argument for call back function calling.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_reg_toirq(phal_timer_adapter_t ptimer_adp, timer_callback_t callback, void *phid)
{
	hal_gtimer_stubs.hal_timer_reg_toirq(ptimer_adp, callback, phid);
}

/**
 *  @brief To un-register a timer timeout IRQ call back function
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_unreg_toirq(phal_timer_adapter_t ptimer_adp)
{
	hal_gtimer_stubs.hal_timer_unreg_toirq(ptimer_adp);
}

/**
 *  @brief To register a timer counter matched IRQ call back function
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] match_ev The timer counter match event number (0 ~ 3).
 *  @param[in] callback The call back function.
 *  @param[in] phid The argument for call back function calling.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_reg_meirq(phal_timer_adapter_t ptimer_adp, uint8_t match_ev, timer_callback_t callback, void *phid)
{
	hal_gtimer_stubs.hal_timer_reg_meirq(ptimer_adp, match_ev, callback, phid);
}

/**
 *  @brief To un-register a timer counter matched IRQ call back function
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] match_ev The timer counter match event number (0 ~ 3).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_unreg_meirq(phal_timer_adapter_t ptimer_adp, uint8_t match_ev)
{
	hal_gtimer_stubs.hal_timer_unreg_meirq(ptimer_adp, match_ev);
}

/**
 *  @brief To configure the tick period of a timer by set the pre-scaler value.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] tick_ns The period (in ns) of a tick
 *
 *  @returns The real tick time.
 */
__STATIC_INLINE
uint32_t hal_timer_set_tick_time(phal_timer_adapter_t ptimer_adp, uint32_t tick_ns)
{
	return hal_gtimer_stubs.hal_timer_set_tick_time(ptimer_adp, tick_ns);
}

/**
 *  @brief To initial a HW timer as a free run counter mode.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] tid The timer ID(index).
 *  @param[in] cnt_mode The count mode, up count or down count.
 *  @param[in] tick_us The period (in us) of a tick
 *
 *  @returns The result. HAL_ERR_PARA or HAL_OK.
 */
__STATIC_INLINE
void hal_timer_init_free_run(phal_timer_adapter_t ptimer_adp, timer_id_t tid,
							 timer_cnt_mode_t cnt_mode, uint32_t tick_us, u8 tg)
{
	hal_gtimer_stubs.hal_timer_init_free_run(ptimer_adp, tid, cnt_mode, tick_us, tg);
}

/**
 *  @brief To indirect read the timer counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The timer counter value
 */
__STATIC_INLINE
uint32_t hal_timer_indir_read(phal_timer_adapter_t ptimer_adp)
{
	return hal_gtimer_stubs.hal_timer_indir_read(ptimer_adp);
}

/**
 *  @brief To read the counter and convert it as us unit.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The counter value in us.
 */
__STATIC_INLINE
uint64_t hal_timer_read_us(phal_timer_adapter_t ptimer_adp)
{
	return hal_gtimer_stubs.hal_timer_read_us(ptimer_adp);
}

/**
 *  @brief To read the counter and convert it as us unit.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The counter value in us.
 */
__STATIC_INLINE
uint64_t hal_timer_read_us64(phal_timer_adapter_t ptimer_adp)
{
	return hal_gtimer_stubs.hal_timer_read_us64(ptimer_adp);
}

/**
 *  @brief To initial a HW timer as timer mode for application.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] tid The timer ID(index).
 *
 *  @returns     HAL_OK:  Setting succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 */
__STATIC_INLINE
hal_status_t hal_timer_init(phal_timer_adapter_t ptimer_adp, timer_id_t tid)
{
	return hal_gtimer_stubs.hal_timer_init(ptimer_adp, tid);
}

/**
 *  @brief To set the tick count of the timer as given timeout value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] time_us The time period of timeout.
 *  @param[in] res_us The resolution of a tick time, in us.
 *                Value of 0 means didn't assign the tick resolution.
 *
 *  @returns The actual timeout value (us).
 */
__STATIC_INLINE
uint32_t hal_timer_set_timeout(phal_timer_adapter_t ptimer_adp, uint32_t time_us, uint32_t res_us)
{
	return hal_gtimer_stubs.hal_timer_set_timeout(ptimer_adp, time_us, res_us);
}

/**
 *  @brief To start an initialed timer.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] reload_mode The timer counter reload mode, one shot or periodical.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_start(phal_timer_adapter_t ptimer_adp, timer_app_mode_t reload_mode)
{
	hal_gtimer_stubs.hal_timer_start(ptimer_adp, reload_mode);
}

/**
 *  @brief To enable and setup a counter match event for a running timer.
 *         The function hal_timer_set_timeout_rtl8195bhp() must be called
 *         befor calling of this function.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] match_ev The match event number(0 ~ 3).
 *  @param[in] time_us The time period for the timer match event. This time period will be
 *                 converted to a tick count to set to the match event counter.
 *
 *  @returns     HAL_OK:  Setting succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 *  @returns     HAL_NOT_READY:  Error with data not ready.
 */
__STATIC_INLINE
hal_status_t hal_timer_enable_match_event(phal_timer_adapter_t ptimer_adp,
		timer_match_event_t match_ev, uint32_t time_us)
{
	return hal_gtimer_stubs.hal_timer_enable_match_event(ptimer_adp, match_ev, time_us);
}

/**
 *  @brief To start an initialed timer with one shot mode.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] time_us The time period of timeout.
 *  @param[in] callback The call back function for timeout event.
 *  @param[in] phid The argument for call back function calling.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_start_one_shot(phal_timer_adapter_t ptimer_adp, uint32_t time_us,
							  timer_callback_t callback, void *phid)
{
	hal_gtimer_stubs.hal_timer_start_one_shot(ptimer_adp, time_us, callback, phid);
}

/**
 *  @brief To start an initialed timer with periodical mode.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] time_us The time period of timeout.
 *  @param[in] callback The call back function for timeout event.
 *  @param[in] phid The argument for call back function calling.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_start_periodical(phal_timer_adapter_t ptimer_adp, uint32_t time_us,
								timer_callback_t callback, void *phid)
{
	hal_gtimer_stubs.hal_timer_start_periodical(ptimer_adp, time_us, callback, phid);
}

/**
 *  @brief To allocate a free timer device.
 *
 *  @param[in] timer_list A list of timer ID, the caller limit the allocated timer
 *                    should be one of this list. The list should end with MaxGTimerNum.
 *                    If the list is NULL, then no limit to the timer allocation.
 *
 *  @returns The allocated timer ID.
 */
__STATIC_INLINE
timer_id_t hal_timer_allocate(uint8_t *timer_list)
{
	return hal_gtimer_stubs.hal_timer_allocate(timer_list);
}

/**
 *  @brief Reads the tick count of the system timer. It start the counting
 *         when the system timer is started.
 *
 *  @returns    Current tick count of system time. The uint in us(micro-second).
 */
__STATIC_INLINE
uint64_t hal_read_systime_us(void)
{
	return hal_gtimer_stubs.hal_read_systime();
}

/**
 *  @brief Configures a hardware G-Timer as the free run system timer.
 *         The system timer is utilised to implement the time delay function.
 *
 *  @param[in]  ptimer_adp  The G-Timer adapter.
 *  @param[in]  tmr_id  The index of the G-Timer. The valid range of this value is 0 ~ 7.
 *  @param[in]  cnt_md  Set the counting mode of the system timer, up counting or down counting.
 *                        \arg \c GTimerCountUp  Up counting.
 *                        \arg \c GTimerCountDown  Down counting.
 *  @param[in]  tick_us  The tick time resolution, in micro-second, of the system timer.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_start_systimer(phal_timer_adapter_t ptimer_adp, uint32_t tmr_id,
						timer_cnt_mode_t cnt_md, uint32_t tick_us, uint8_t tg)
{
	hal_gtimer_stubs.hal_start_systimer(ptimer_adp, tmr_id, cnt_md, tick_us, tg);
}

uint32_t hal_read_curtime_us(void);
void hal_delay_us(uint32_t time_us);
BOOLEAN hal_is_timeout(uint32_t start_us, uint32_t timeout_us);

/** @} */ /* End of group hs_hal_timer */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_TIMER_H_"


