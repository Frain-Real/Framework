/* Аппаратно-зависимый модуль работы с АЦП */
#pragma once
#include "standard.h"
template <typename _PLATFORM>
class Hw_ADC {
private:
public:
    u16 _PLATFORM::readADC(u8 channel);
};