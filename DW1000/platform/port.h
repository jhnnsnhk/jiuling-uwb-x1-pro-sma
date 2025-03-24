/*! ----------------------------------------------------------------------------
 * @file    port.h
 * @brief   HW specific definitions and functions for portability
 *
 * @attention
 *
 * Copyright 2015 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author Decawave
 */

#ifndef PORT_H_
#define PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

// #include "compiler.h"
#include <stdint.h>
#include <string.h>

// #include "stm32f4xx.h"
// #include "stm32f4xx_hal.h"

/* DW1000 IRQ (EXTI9_5_IRQ) handler type. */
typedef void (*port_deca_isr_t)(void);

/* DW1000 IRQ handler declaration. */
// port_deca_isr_t port_deca_isr;

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
void port_set_deca_isr(port_deca_isr_t deca_isr);

// #define BUFFLEN (64) //(4096+128)

// #define BUF_SIZE (64)

// #define USB_SUPPORT

// typedef struct
// {
//     uint16_t usblen;              /**< for RX from USB */
//     uint8_t usbbuf[BUF_SIZE * 3]; /**< for RX from USB */
// } __packed app_t;

// extern app_t app;

// typedef uint64_t uint64;

// typedef int64_t int64;

// #ifndef FALSE
// #define FALSE 0
// #endif

// #ifndef TRUE
// #define TRUE 1
// #endif

// typedef enum
// {
//     LED_PC6, // LED5
//     LED_PC7, // LED6
//     LED_PC8, // LED7
//     LED_PC9, // LED8
//     LED_ALL,
//     LEDn
// } led_t;

// #if !(EXTI9_5_IRQn)
// #define DECAIRQ_EXTI_IRQn (23)
// #else
// #define DECAIRQ_EXTI_IRQn (EXTI9_5_IRQn)
// #endif

// #if !(EXTI0_IRQn)
// #define EXTI0_IRQn (6)
// #endif

// #define DW1000_RST_PIN DW_RESET_Pin
// #define DW1000_RST_PRT DW_RESET_GPIO_Port

// #define DECAIRQ      DW_IRQn_Pin
// #define DECAIRQ_GPIO DW_IRQn_GPIO_Port

/* NSS pin is SW controllable */
// #define port_SPIx_set_chip_select()   HAL_GPIO_WritePin(DW_NSS_GPIO_Port, DW_NSS_Pin, GPIO_PIN_SET)
// #define port_SPIx_clear_chip_select() HAL_GPIO_WritePin(DW_NSS_GPIO_Port, DW_NSS_Pin, GPIO_PIN_RESET)

void Sleep(uint32_t milliseconds);

// unsigned long portGetTickCnt(void);

// void port_wakeup_dw1000(void);
// void port_wakeup_dw1000_fast(void);

void port_set_dw1000_slowrate(void);
void port_set_dw1000_fastrate(void);

void process_dwRSTn_irq(void);
// void process_deca_irq(void);

// void setup_DW1000RSTnIRQ(int enable);

void reset_DW1000(void);

// ITStatus EXTI_GetITEnStatus(uint32_t x);

uint32_t port_GetEXT_IRQStatus(void);
uint32_t port_CheckEXT_IRQ(void);
void port_DisableEXT_IRQ(void);
void port_EnableEXT_IRQ(void);
// extern uint32_t HAL_GetTick(void);
// HAL_StatusTypeDef flush_report_buff(void);

static inline void dw1k_qorvo_isr(void)
{
}

#ifdef __cplusplus
}
#endif

#endif /* PORT_H_ */
