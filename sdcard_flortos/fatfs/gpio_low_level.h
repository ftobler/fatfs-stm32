/*
 * gpio_low_level.h
 *
 *  Created on: Feb 25, 2022
 *      Author: cchtofl01
 */
#ifndef GPIO_LOW_LEVEL_H_
#define GPIO_LOW_LEVEL_H_
#include "stdint.h"
#include "stm32f0xx_hal.h"
/**
 * low level macro to set gpio pin
 *
 * Sets the SRBB (Bit Set Reset Register) of the given pin. Only used for setting.
 * Resetting pins would require to shift left 16bits.
 */
#define gpio_ll_set(port, pin)        ((port)->BSRR = (uint32_t)(pin))
/**
 * low level macro to reset gpio pin
 *
 * Sets the RBB (Bit Reset Register) of the given pin
 * Setting pins would require to shift left 16bits
 */
#define gpio_ll_reset(port, pin)      ((port)->BRR = (uint32_t)(pin))
/**
 * low level macro to write gpio pin.
 * state: 0 -> reset pin, otherwise set pin
 */
#define gpio_ll_write(port, pin, state)    ({\
        if (state) {\
                gpio_ll_set((port), (pin));\
        } else {\
                gpio_ll_reset((port), (pin));\
        }\
})
/**
 * low level macro to read gpio pin
 * return 0 -> pin reset, otherwise pin set
 *
 * Reads the IDR (Input Data Register) of the given pin. Macro does not bother shifting.
 */
#define gpio_ll_read(port, pin)       ((port)->IDR & (uint16_t)(pin))
#endif /* GPIO_LOW_LEVEL_H_ */
