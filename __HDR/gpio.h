#ifndef __GPIO_H__
#define __GPIO_H__
#include "target.h"
#include "standard.h"
#include "hw_gpio.h"
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


class GpioPin {
    u8 port;
    u8 pin;
    gpio__alter_func_e alt_func;
    gpio__diraction_e diraction;
    gpio_pulled_e pulled;
    HWGpioPin* hw_pin;
public:
    GpioPin(u8 port, u8 pin, gpio__alter_func_e alt_func, gpio__diraction_e diraction, gpio_pulled_e pulled);
    ~GpioPin();
    bool get();
    void set(bool value);
    void toggle();
};

#endif /* __GPIO_H__ */