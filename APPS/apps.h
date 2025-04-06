#ifndef APPS_H /*!< include guard. */
#define APPS_H /*!< include guard. */

#ifdef __cplusplus
extern "C" {
#endif

#define APP_POLL /*!< COMMENT OR UNCOMMENT */
// #define APP_RESP /*!< COMMENT OR UNCOMMENT */

#if defined(APP_POLL)
#include "app_poll.h"
#endif

#if defined(APP_RESP)
#include "app_resp.h"
#endif

static inline void apps_execution(void)
{

    LL_SPI_Enable(DW1000_SPI_BUS);

    LL_TIM_EnableCounter(TIMER_USEC_TIMX);

#if defined(APP_POLL)
    app_poll();
#endif

#if defined(APP_RESP)
    app_resp();
#endif
}

#ifdef __cplusplus
}
#endif

#endif /*!< include guard. */