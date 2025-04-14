/* Аппаратно-независимый модуль работы с АЦП */
#ifndef __HW_ADC__
#define __HW_ADC__

#include "standard.h"
template <typename _PLATFORM>
class Hw_ADC{
    private:

    public:
        u16 _PLATFORM::readADC(u8 channel);
};

#endif /* __HW_ADC__ */