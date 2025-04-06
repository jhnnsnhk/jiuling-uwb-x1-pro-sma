/*! ----------------------------------------------------------------------------
 * @file    deca_spi.c
 * @brief   SPI access functions
 *
 * @attention
 *
 * Copyright 2015 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author Decawave
 */

#include "brdcfg.h"
#include "deca_device_api.h"
#include "main.h"
#include "port.h"

int readfromspi(uint16_t head_octets_number, const uint8_t* head_octets_buffer, uint32_t body_octets_number, uint8_t* body_octets_buffer)
{

    LL_GPIO_ResetOutputPin(DW1000_GPIO_NSS_PRT, DW1000_GPIO_NSS_PIN);

    for (uint8_t index = 0x00U; index < head_octets_number; index++)
    {

        while (MCU_SPI_BUS_FLAG_TX_BUFFER_NOT_EMPTY(DW1000_SPI_BUS))
        {
        }

        LL_SPI_TransmitData8(DW1000_SPI_BUS, *(head_octets_buffer + index));

        while (MCU_SPI_BUS_FLAG_RX_BUFFER_IS_EMPTY(DW1000_SPI_BUS))
        {
        }

        LL_SPI_ReceiveData8(DW1000_SPI_BUS);
    }

    for (uint16_t index = 0x00U; index < body_octets_number; index++)
    {

        while (MCU_SPI_BUS_FLAG_TX_BUFFER_NOT_EMPTY(DW1000_SPI_BUS))
        {
        }

        LL_SPI_TransmitData8(DW1000_SPI_BUS, 0x00U);

        while (MCU_SPI_BUS_FLAG_RX_BUFFER_IS_EMPTY(DW1000_SPI_BUS))
        {
        }

        *(body_octets_buffer + index) = LL_SPI_ReceiveData8(DW1000_SPI_BUS);
    }

    while (MCU_SPI_BUS_FLAG_TX_BUFFER_NOT_EMPTY(DW1000_SPI_BUS))
    {
    }

    while (MCU_SPI_BUS_FLAG_IS_BUSY(DW1000_SPI_BUS))
    {
    }

    LL_GPIO_SetOutputPin(DW1000_GPIO_NSS_PRT, DW1000_GPIO_NSS_PIN);

    return 0x00U;
}

int writetospi(uint16_t head_octets_number, const uint8_t* head_octets_buffer, uint32_t body_octets_number, const uint8_t* body_octets_buffer)
{

    LL_GPIO_ResetOutputPin(DW1000_GPIO_NSS_PRT, DW1000_GPIO_NSS_PIN);

    for (uint8_t index = 0x00U; index < head_octets_number; index++)
    {

        while (MCU_SPI_BUS_FLAG_TX_BUFFER_NOT_EMPTY(DW1000_SPI_BUS))
        {
        }

        LL_SPI_TransmitData8(DW1000_SPI_BUS, *(head_octets_buffer + index));

        while (MCU_SPI_BUS_FLAG_RX_BUFFER_IS_EMPTY(DW1000_SPI_BUS))
        {
        }

        LL_SPI_ReceiveData8(DW1000_SPI_BUS);
    }

    for (uint16_t index = 0x00U; index < body_octets_number; index++)
    {

        while (MCU_SPI_BUS_FLAG_TX_BUFFER_NOT_EMPTY(DW1000_SPI_BUS))
        {
        }

        LL_SPI_TransmitData8(DW1000_SPI_BUS, *(body_octets_buffer + index));

        while (MCU_SPI_BUS_FLAG_RX_BUFFER_IS_EMPTY(DW1000_SPI_BUS))
        {
        }

        LL_SPI_ReceiveData8(DW1000_SPI_BUS);
    }

    while (MCU_SPI_BUS_FLAG_TX_BUFFER_NOT_EMPTY(DW1000_SPI_BUS))
    {
    }

    while (MCU_SPI_BUS_FLAG_IS_BUSY(DW1000_SPI_BUS))
    {
    }

    LL_GPIO_SetOutputPin(DW1000_GPIO_NSS_PRT, DW1000_GPIO_NSS_PIN);

    return 0x00U;
}
