/*! ----------------------------------------------------------------------------
 * @file    sleep.h
 * @brief   platform dependent sleep implementation
 *
 * @attention
 *
 * Copyright 2015 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author Decawave
 */

#ifndef _SLEEP_H_
#define _SLEEP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: deca_sleep()
 *
 * Wait for a given amount of time.
 * /!\ This implementation is designed for a single threaded application and is blocking.
 *
 * param  milliseconds  time to wait in milliseconds
 */
void deca_sleep(unsigned int milliseconds);

#ifdef __cplusplus
}
#endif

#endif /* _SLEEP_H_ */
