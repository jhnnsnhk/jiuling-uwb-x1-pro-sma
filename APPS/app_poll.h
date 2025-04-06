#ifndef APP_POLL_H /*!< include guard. */
#define APP_POLL_H /*!< include guard. */

#ifdef __cplusplus
extern "C" {
#endif

#include "brdcfg.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "port.h"

static dwt_config_t config = {
    2,               /* Channel number. */
    DWT_PRF_64M,     /* Pulse repetition frequency. */
    DWT_PLEN_1024,   /* Preamble length. Used in TX only. */
    DWT_PAC32,       /* Preamble acquisition chunk size. Used in RX only. */
    9,               /* TX preamble code. Used in TX only. */
    9,               /* RX preamble code. Used in RX only. */
    1,               /* 0 to use standard SFD, 1 to use non-standard SFD. */
    DWT_BR_110K,     /* Data rate. */
    DWT_PHRMODE_STD, /* PHY header mode. */
    (1025 + 64 - 32) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};

static uint8_t tx_msg[] = {0xC5, 0, 'D', 'E', 'C', 'A', 'W', 'A', 'V', 'E', 0, 0};

static inline void app_poll(void)
{

    reset_DW1000();

    port_set_dw1000_slowrate();

    if (dwt_initialise(DWT_LOADNONE) == DWT_ERROR)
    {
        while (1)
        {
        };
    }

    port_set_dw1000_fastrate();

    dwt_configure(&config);

    while (1)
    {

        dwt_writetxdata(sizeof(tx_msg), tx_msg, 0);

        dwt_writetxfctrl(sizeof(tx_msg), 0, 0);

        dwt_starttx(DWT_START_TX_IMMEDIATE);

        while (!(dwt_read32bitreg(SYS_STATUS_ID) & SYS_STATUS_TXFRS))
        {
        };

        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS);

        Sleep(1000);

        tx_msg[1]++;
    }
}

#ifdef __cplusplus
}
#endif

#endif /*!< include guard. */