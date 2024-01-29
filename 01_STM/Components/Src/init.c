/**
 * @file init.c
 * @brief Initialization file for the project
 * @date Jan 13, 2024
 * @author Krasa
 */
#include "init.h"

/**
 * @brief Global MenuHandle structure for managing system state and commands.
 */
MenuHandle hmen = {
    .state = _IDLE,
    .com = {
        ._DEBUG = "ERROR! UNDEFINED VALUE",
        ._REMOTE = "ERROR! UNDEFINED VALUE",
        ._MANUAL = "ERROR! UNDEFINED VALUE",
        ._IDLE = "ERROR! UNDEFINED VALUE",
    },
    .compStrings = {
        ._DEBUG = "DEBUG",
        ._REMOTE = "REMOTE",
        ._MANUAL = "MANUAL",
        ._IDLE = "IDLE",
    }
};
