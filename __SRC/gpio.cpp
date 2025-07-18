#include "gpio.h"
#include "target.h"
#ifndef PLATFORM
    #error "Определите платформу в файле target.h"
#else
#if PLATFORM==AVR
GpioPin::GpioPin(u8 port, u8 pin, gpio__alter_func_e alt_func, gpio__diraction_e diraction, gpio_pulled_e pulled) {
    this->alt_func = alt_func;
    this->port = port;
    this->pin = pin;
    this->diraction = diraction;
    this->pulled = pulled;
    switch (port) {
        case GPIO_PORTB: {
            if (diraction == OUTPUT) {
                DDRB |= (1 << pin);  // Установка пина как выхода
            } 
            else {
                DDRB &= ~(1 << pin); // Установка пина как входа
                PORTB &= ~(1 << pin); // Отключение подтяжки (по умолчанию)
            }
        }
            break;
        case GPIO_PORTC: {
            if (diraction == OUTPUT) {
                DDRC |= (1 << pin);  // Установка пина как выхода
            } 
            else {
                DDRC &= ~(1 << pin); // Установка пина как входа
                PORTC &= ~(1 << pin); // Отключение подтяжки (по умолчанию)
            }
            break;
        }
        case GPIO_PORTD: {
            if (diraction == OUTPUT) {
                DDRD |= (1 << pin);  // Установка пина как выхода
            } 
            else {
                DDRD &= ~(1 << pin); // Установка пина как входа
                PORTD &= ~(1 << pin); // Отключение подтяжки (по умолчанию)
            }
            break;
        }
    }
    if(diraction == OUTPUT)
        this->set(port, pin, false);
}
GpioPin::~GpioPin(){

}
bool GpioPin::get() {
    if(this->port == GPIO_PORTB)
        return (PINB & (1 << this->pin)) ? 1 : 0;
    if(this->port == GPIO_PORTC)
        return (PINC & (1 << this->pin)) ? 1 : 0;
    if(this->port == GPIO_PORTD)
        return (PIND & (1 << this->pin)) ? 1 : 0;
    return 0;
}
void GpioPin::set(bool value) {
    if(this->port == GPIO_PORTB)
        value ? (PORTB |= (1 << this->pin)) : (PORTB &= ~(1 << this->pin));
    if(this->port == GPIO_PORTC)
        value ? (PORTC |= (1 << this->pin)) : (PORTC &= ~(1 << this->pin));
    if(this->port == GPIO_PORTD)
        value ? (PORTD |= (1 << this->pin)) : (PORTD &= ~(1 << this->pin));
}
void GpioPin::toggle() {
    this->set(this->port, this->pin, !(this->get(this->port, this->pin)));
}
#endif /* PLATFORM==AVR */

#endif /* PLATFORM */