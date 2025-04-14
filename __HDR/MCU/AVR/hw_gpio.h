#ifndef __HWGPIO_H__
#define __HWGPIO_H__
#include "target.h"
#include "standard.h"

class HWGpioPin {
public:
    void init(u8 port, u8 pin, u8 diraction, u8 pulled);
    bool get(u8 port, u8 pin);
    void set(u8 port, u8 pin, bool value);
};

#endif /* __HWGPIO_H__ */