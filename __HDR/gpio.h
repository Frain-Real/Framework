#pragma once
#include "target.h"
#include "standard.h"
typedef enum {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
} gpio__diraction_e;

typedef enum {
    PULL_UP,
    PULL_DOWN,
    NOT_PULLED,
} gpio_pulled_e;

typedef enum {
    NONE,
    ANALOG,
    INTERFACE,
} gpio__alter_func_e;