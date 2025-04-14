#include "gpio.h"
#include "target.h"

void HWGpioPin::init(u8 port, u8 pin, u8 diraction, u8 pulled) {
    if(port == GPIO_PORTB) {
        if (diraction == (u8)OUTPUT) {
            DDRB |= (1 << pin);  // Установка пина как выхода
        } else {
            DDRB &= ~(1 << pin); // Установка пина как входа
            PORTB &= ~(1 << pin); // Отключение подтяжки (по умолчанию)
        }
    }
    if(port == GPIO_PORTC) {
        if (diraction == (u8)OUTPUT) {
            DDRC |= (1 << pin);
        } else {
            DDRC &= ~(1 << pin);
            PORTC &= ~(1 << pin);
        }
    }
    if(port == GPIO_PORTD) {
        if (diraction == (u8)OUTPUT) {
            DDRD |= (1 << pin);
        } else {
            DDRD &= ~(1 << pin);
            PORTD &= ~(1 << pin);
        }
    }
}

bool HWGpioPin::get(u8 port, u8 pin) {
    if(port == GPIO_PORTB)
        return (PINB & (1 << pin)) ? 1 : 0;
    if(port == GPIO_PORTC)
        return (PINC & (1 << pin)) ? 1 : 0;
    if(port == GPIO_PORTD)
        return (PIND & (1 << pin)) ? 1 : 0;
    return 0;
}

void HWGpioPin::set(u8 port, u8 pin, bool value) {
    if(port == GPIO_PORTB)
        value ? (PORTB |= (1 << pin)) : (PORTB &= ~(1 << pin));
    if(port == GPIO_PORTC)
        value ? (PORTC |= (1 << pin)) : (PORTC &= ~(1 << pin));
    if(port == GPIO_PORTD)
        value ? (PORTD |= (1 << pin)) : (PORTD &= ~(1 << pin));
}

