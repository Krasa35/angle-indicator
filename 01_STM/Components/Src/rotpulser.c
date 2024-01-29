/**
 * @file rotpulser.c
 * @brief Rotary pulser implementation
 * @date Jan 14, 2024
 * @author Krasa
 */

#include "rotpulser.h"

/**
 * @brief Default rotary pulser handle initialization
 */
_PULSER_handle hpsr = {
    .set_angle = 0.0,
    .angle_overflow = 0.0,
    .button = GPIO_PIN_RESET
};
