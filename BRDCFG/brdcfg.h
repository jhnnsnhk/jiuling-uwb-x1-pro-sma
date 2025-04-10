#ifndef BRDCFG_H /*!< include guard. */
#define BRDCFG_H /*!< include guard. */

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_utils.h"
#include "usbd_cdc_if.h"

#define MCU_SPI_BUS_FLAG_IS_BUSY(spi_bus)             LL_SPI_IsActiveFlag_BSY(spi_bus)
#define MCU_SPI_BUS_FLAG_NOT_BUSY(spi_bus)            !LL_SPI_IsActiveFlag_BSY(spi_bus)
#define MCU_SPI_BUS_FLAG_RX_BUFFER_IS_EMPTY(spi_bus)  !LL_SPI_IsActiveFlag_RXNE(spi_bus)
#define MCU_SPI_BUS_FLAG_RX_BUFFER_NOT_EMPTY(spi_bus) LL_SPI_IsActiveFlag_RXNE(spi_bus)
#define MCU_SPI_BUS_FLAG_TX_BUFFER_IS_EMPTY(spi_bus)  LL_SPI_IsActiveFlag_TXE(spi_bus)
#define MCU_SPI_BUS_FLAG_TX_BUFFER_NOT_EMPTY(spi_bus) !LL_SPI_IsActiveFlag_TXE(spi_bus)

#define DW1000_GPIO_NSS_PIN            LL_GPIO_PIN_4
#define DW1000_GPIO_NSS_PRT            GPIOA
#define DW1000_GPIO_RST_PIN            LL_GPIO_PIN_0
#define DW1000_GPIO_RST_PRT            GPIOA
#define DW1000_GPIO_WKP_PIN            LL_GPIO_PIN_0
#define DW1000_GPIO_WKP_PRT            GPIOB
#define DW1000_SPI_BUS                 SPI1
#define DW1000_SPI_PRESCALER_MAX_SPEED LL_SPI_BAUDRATEPRESCALER_DIV4
#define DW1000_SPI_PRESCALER_MIN_SPEED LL_SPI_BAUDRATEPRESCALER_DIV32

#define TIMER_USEC_TIMX TIM1

#ifdef __cplusplus
}
#endif

#endif /*!< include guard. */