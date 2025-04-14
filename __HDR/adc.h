/* Аппаратно-независимый модуль работы с АЦП */
#ifndef __SW_ADC__
#define __SW_ADC__

#include "standard.h"
#include "hw_adc.h"


/* Верхнеуровневая абстракция для работы АЦП на микроконтроллере */
/* Адаптер для работы АЦП на микроконтроллере */
class ADC {
public:
    virtual u16 readADC(u8 channel) = 0;
    virtual ~ADC() = default;
};


/* Адаптер для работы АЦП на микроконтроллере */
template <typename _PLATFORM>
class ADCAdapter : protected ADC {
private:

    _PLATFORM::Hw_ADC* hard_adc;
public:
    ADCAdapter(Hw_ADC* harware) : hard_adc(harware){}

    u16 readADC(u8 channel) override {
        
        return hard_adc->readADC(channel);
    }
};

#endif /* __SW_ADC__ */
