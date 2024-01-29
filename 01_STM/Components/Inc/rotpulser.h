/*
 * rotpulser.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Krasa
 */

#ifndef INC_ROTPULSER_H_
#define INC_ROTPULSER_H_

#include "init.h"

/**
 * @file rotpulser.h
 * @brief Header file for the Rotational Pulser module.
 *
 * This file contains the declarations for the Rotational Pulser module,
 * including the data structure definition.
 */

/**
 * @brief Rotational Pulser handle structure.
 *
 * This structure holds information and settings for the Rotational Pulser module.
 */
typedef struct {
    float32_t set_angle;        /**< Target angle set for the Rotational Pulser. */
    float32_t angle_overflow;   /**< Overflow value for the angle, if needed. */
    GPIO_PinState button;       /**< State of the button associated with the Rotational Pulser. */
} _PULSER_handle;

#endif /* INC_ROTPULSER_H_ */
