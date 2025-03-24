/*! ----------------------------------------------------------------------------
 * @file    port.c
 * @brief   HW specific definitions and functions for portability
 *
 * @attention
 *
 * Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author Decawave
 */

#include "port.h"
#include "brdcfg.h"
#include "deca_device_api.h"
#include "main.h"
// #include "stm32f4xx_hal_conf.h"

// static volatile uint32_t signalResetDone;

/* @fn    portGetTickCnt
 * @brief wrapper for to read a SysTickTimer, which is incremented with
 *        CLOCKS_PER_SEC frequency.
 *        The resolution of time32_incr is usually 1/1000 sec.
 * */
// __INLINE uint32_t portGetTickCnt(void)
// {
//     return HAL_GetTick();
// }

void usleep(uint32_t microseconds)
{
    TIMER_USEC_TIMX->CNT = 0x00U;
    while (TIMER_USEC_TIMX->CNT < microseconds)
    {
    }
}

/* @fn    Sleep
 * @brief Sleep delay in ms using SysTick timer
 * */
inline void Sleep(uint32_t milliseconds)
{
    LL_mDelay(milliseconds);
}

/**
 * @brief  Checks whether the specified EXTI line is enabled or not.
 * @param  EXTI_Line: specifies the EXTI line to check.
 *   This parameter can be:
 *     @arg EXTI_Linex: External interrupt line x where x(0..19)
 * @retval The "enable" state of EXTI_Line (SET or RESET).
 */
// ITStatus EXTI_GetITEnStatus(uint32_t x)
// {
//     return ((NVIC->ISER[(((uint32_t)x) >> 5UL)] & (uint32_t)(1UL << (((uint32_t)x) & 0x1FUL))) == (uint32_t)RESET) ? (RESET) : (SET);
// }

/* @fn      reset_DW1000
 * @brief   DW_RESET pin on DW1000 has 2 functions
 *          In general it is output, but it also can be used to reset the digital
 *          part of DW1000 by driving this pin low.
 *          Note, the DW_RESET pin should not be driven high externally.
 * */
void reset_DW1000(void)
{
    // GPIO_InitTypeDef GPIO_InitStruct;
    // Enable GPIO used for DW1000 reset as open collector output
    // GPIO_InitStruct.Pin = DW_RESET_Pin;
    // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // HAL_GPIO_Init(DW_RESET_GPIO_Port, &GPIO_InitStruct);
    // drive the RSTn pin low
    // HAL_GPIO_WritePin(DW_RESET_GPIO_Port, DW_RESET_Pin, GPIO_PIN_RESET);

#if defined(STM32F103C8TX_UWBX1PRO) || defined(STM32F105RCTX_EVB1000) || defined(STM32F429ZITX_NUCLEO) || defined(STM32H723ZGTX_NUCLEO) || defined(STM32H745ZITX_CM7_NUCLEO) || defined(STM32H753ZITX_NUCLEO) || defined(STM32L432KCUX_NUCLEO)
    LL_GPIO_ResetOutputPin(DW1K_XCVR_ALPHA_GPIO_RST_PRT, DW1K_XCVR_ALPHA_GPIO_RST_PIN);
#endif

    usleep(1);

#if defined(STM32F103C8TX_UWBX1PRO) || defined(STM32F105RCTX_EVB1000) || defined(STM32F429ZITX_NUCLEO) || defined(STM32H723ZGTX_NUCLEO) || defined(STM32H745ZITX_CM7_NUCLEO) || defined(STM32H753ZITX_NUCLEO) || defined(STM32L432KCUX_NUCLEO)
    LL_GPIO_SetOutputPin(DW1K_XCVR_ALPHA_GPIO_RST_PRT, DW1K_XCVR_ALPHA_GPIO_RST_PIN);
#endif

    // put the pin back to output open-drain (not active)
    // setup_DW1000RSTnIRQ(0);

    Sleep(2);
}

/* @fn      setup_DW1000RSTnIRQ
 * @brief   setup the DW_RESET pin mode
 *          0 - output Open collector mode
 *          !0 - input mode with connected EXTI0 IRQ
 * */
// void setup_DW1000RSTnIRQ(int enable)
// {
//     GPIO_InitTypeDef GPIO_InitStruct;

//     if (enable)
//     {
//         // Enable GPIO used as DECA RESET for interrupt
//         GPIO_InitStruct.Pin = DW_RESET_Pin;
//         GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
//         GPIO_InitStruct.Pull = GPIO_NOPULL;
//         HAL_GPIO_Init(DW_RESET_GPIO_Port, &GPIO_InitStruct);

//         HAL_NVIC_EnableIRQ(EXTI0_IRQn); // pin #0 -> EXTI #0
//         HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
//     }
//     else
//     {
//         HAL_NVIC_DisableIRQ(EXTI0_IRQn); // pin #0 -> EXTI #0

//         // put the pin back to tri-state ... as
//         // output open-drain (not active)
//         GPIO_InitStruct.Pin = DW_RESET_Pin;
//         GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//         GPIO_InitStruct.Pull = GPIO_NOPULL;
//         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//         HAL_GPIO_Init(DW_RESET_GPIO_Port, &GPIO_InitStruct);
//         HAL_GPIO_WritePin(DW_RESET_GPIO_Port, DW_RESET_Pin, GPIO_PIN_SET);
//     }
// }

/* @fn      port_wakeup_dw1000
 * @brief   "slow" waking up of DW1000 using DW_CS only
 * */
// void port_wakeup_dw1000(void)
// {
//     HAL_GPIO_WritePin(DW_NSS_GPIO_Port, DW_NSS_Pin, GPIO_PIN_RESET);
//     Sleep(1);
//     HAL_GPIO_WritePin(DW_NSS_GPIO_Port, DW_NSS_Pin, GPIO_PIN_SET);
//     Sleep(7); // wait 7ms for DW1000 XTAL to stabilise
// }

/* @fn      port_wakeup_dw1000_fast
 * @brief   waking up of DW1000 using DW_CS and DW_RESET pins.
 *          The DW_RESET signalling that the DW1000 is in the INIT state.
 *          the total fast wakeup takes ~2.2ms and depends on crystal startup time
 * */
// void port_wakeup_dw1000_fast(void)
// {
// #define WAKEUP_TMR_MS (10)

//     uint32_t x = 0;
//     uint32_t timestamp = HAL_GetTick(); // protection

//     // setup_DW1000RSTnIRQ(0);        // disable RSTn IRQ
//     signalResetDone = 0; // signalResetDone connected to RST_PIN_IRQ
//     // setup_DW1000RSTnIRQ(1);        // enable RSTn IRQ
//     port_SPIx_clear_chip_select(); // CS low

//     // need to poll to check when the DW1000 is in the IDLE, the CPLL interrupt is not reliable
//     // when RSTn goes high the DW1000 is in INIT, it will enter IDLE after PLL lock (in 5 us)
//     while ((signalResetDone == 0) && ((HAL_GetTick() - timestamp) < WAKEUP_TMR_MS))
//     {
//         x++; // when DW1000 will switch to an IDLE state RSTn pin will high
//     }
//     setup_DW1000RSTnIRQ(0);      // disable RSTn IRQ
//     port_SPIx_set_chip_select(); // CS high

//     // it takes ~35us in total for the DW1000 to lock the PLL, download AON and go to IDLE state
//     usleep(35);
// }

/* @fn      port_set_dw1000_slowrate
 * @brief   set 2.25MHz
 *          note: hspi1 is clocked from 72MHz
 * */
void port_set_dw1000_slowrate(void)
{
#if defined(STM32F103C8TX_UWBX1PRO) || defined(STM32F105RCTX_EVB1000) || defined(STM32F429ZITX_NUCLEO) || defined(STM32H723ZGTX_NUCLEO) || defined(STM32H745ZITX_CM7_NUCLEO) || defined(STM32H753ZITX_NUCLEO) || defined(STM32L432KCUX_NUCLEO)
    LL_SPI_Disable(DW1K_XCVR_ALPHA_SPI_BUS);
    LL_SPI_SetBaudRatePrescaler(DW1K_XCVR_ALPHA_SPI_BUS, DW1K_XCVR_ALPHA_SPI_PRESCALER_MIN_SPEED);
    LL_SPI_Enable(DW1K_XCVR_ALPHA_SPI_BUS);
#endif
#if defined(STM32H723ZGTX_NUCLEO) || defined(STM32H745ZITX_CM7_NUCLEO) || defined(STM32H753ZITX_NUCLEO)
    LL_SPI_StartMasterTransfer(DW1K_XCVR_ALPHA_SPI_BUS);
#endif
}

/* @fn      port_set_dw1000_fastrate
 * @brief   set 18MHz
 *          note: hspi1 is clocked from 72MHz
 * */
void port_set_dw1000_fastrate(void)
{
#if defined(STM32F103C8TX_UWBX1PRO) || defined(STM32F105RCTX_EVB1000) || defined(STM32F429ZITX_NUCLEO) || defined(STM32H723ZGTX_NUCLEO) || defined(STM32H745ZITX_CM7_NUCLEO) || defined(STM32H753ZITX_NUCLEO) || defined(STM32L432KCUX_NUCLEO)
    LL_SPI_Disable(DW1K_XCVR_ALPHA_SPI_BUS);
    LL_SPI_SetBaudRatePrescaler(DW1K_XCVR_ALPHA_SPI_BUS, DW1K_XCVR_ALPHA_SPI_PRESCALER_MAX_SPEED);
    LL_SPI_Enable(DW1K_XCVR_ALPHA_SPI_BUS);
#endif
#if defined(STM32H723ZGTX_NUCLEO) || defined(STM32H745ZITX_CM7_NUCLEO) || defined(STM32H753ZITX_NUCLEO)
    LL_SPI_StartMasterTransfer(DW1K_XCVR_ALPHA_SPI_BUS);
#endif
}

/* @fn      HAL_GPIO_EXTI_Callback
 * @brief   IRQ HAL call-back for all EXTI configured lines
 *          i.e. DW_RESET_Pin and DW_IRQn_Pin
 * */
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {
//     if (GPIO_Pin == DW_RESET_Pin)
//     {
//         signalResetDone = 1;
//     }
//     else if (GPIO_Pin == DW_IRQn_Pin)
//     {
//         process_deca_irq();
//     }
//     else
//     {
//     }
// }

/* @fn      process_deca_irq
 * @brief   main call-back for processing of DW1000 IRQ
 *          it re-enters the IRQ routing and processes all events.
 *          After processing of all events, DW1000 will clear the IRQ line.
 * */
// __INLINE void process_deca_irq(void)
// {
//     while (port_CheckEXT_IRQ() != 0)
//     {

//         port_deca_isr();

//     } // while DW1000 IRQ line active
// }

/* @fn      port_DisableEXT_IRQ
 * @brief   wrapper to disable DW_IRQ pin IRQ
 *          in current implementation it disables all IRQ from lines 5:9
 * */
// __INLINE void port_DisableEXT_IRQ(void)
// {
//     NVIC_DisableIRQ(DECAIRQ_EXTI_IRQn);
// }

/* @fn      port_EnableEXT_IRQ
 * @brief   wrapper to enable DW_IRQ pin IRQ
 *          in current implementation it enables all IRQ from lines 5:9
 * */
// __INLINE void port_EnableEXT_IRQ(void)
// {
//     NVIC_EnableIRQ(DECAIRQ_EXTI_IRQn);
// }

/* @fn      port_GetEXT_IRQStatus
 * @brief   wrapper to read a DW_IRQ pin IRQ status
 * */
// __INLINE uint32_t port_GetEXT_IRQStatus(void)
// {
//     return EXTI_GetITEnStatus(DECAIRQ_EXTI_IRQn);
// }

/* @fn      port_CheckEXT_IRQ
 * @brief   wrapper to read DW_IRQ input pin state
 * */
// __INLINE uint32_t port_CheckEXT_IRQ(void)
// {
//     return HAL_GPIO_ReadPin(DW_IRQn_GPIO_Port, DW_IRQn_Pin);
// }

/* DW1000 IRQ handler definition. */
// port_deca_isr_t port_deca_isr = NULL;

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn port_set_deca_isr()
 *
 * @brief This function is used to install the handling function for DW1000 IRQ.
 *
 * NOTE:
 *   - As EXTI9_5_IRQHandler does not check that port_deca_isr is not null, the user application must ensure that a
 *     proper handler is set by calling this function before any DW1000 IRQ occurs!
 *   - This function makes sure the DW1000 IRQ line is deactivated while the handler is installed.
 *
 * @param deca_isr function pointer to DW1000 interrupt handler to install
 *
 * @return none
 */
void port_set_deca_isr(port_deca_isr_t deca_isr)
{
    (void)deca_isr;
    while (UINT8_MAX)
    {
    }

    /* Check DW1000 IRQ activation status. */
    ITStatus en = port_GetEXT_IRQStatus();

    /* If needed, deactivate DW1000 IRQ during the installation of the new handler. */
    if (en)
    {
        port_DisableEXT_IRQ();
    }
    // port_deca_isr = deca_isr;
    if (en)
    {
        port_EnableEXT_IRQ();
    }
}
