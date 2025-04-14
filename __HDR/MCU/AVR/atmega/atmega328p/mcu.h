/*Описание кристала atmega328p*/
#ifndef __MCU_AM328P__
#define __MCU_AM328P__

#include <avr/io.h>

#define GPIO_PORTB  PORTB
#define GPIO_B_0    PORTB0
#define GPIO_B_1    PORTB1
#define GPIO_B_2    PORTB2
#define GPIO_B_3    PORTB3
#define GPIO_B_4    PORTB4
#define GPIO_B_5    PORTB5
#define GPIO_B_6    PORTB6
#define GPIO_B_7    PORTB7

#define GPIO_PORTC  PORTC
#define GPIO_C_0    PORTC0
#define GPIO_C_1    PORTC1
#define GPIO_C_2    PORTC2
#define GPIO_C_3    PORTC3
#define GPIO_C_4    PORTC4
#define GPIO_C_5    PORTC5
#define GPIO_C_6    PORTC6

#define GPIO_PORTD  PORTD
#define GPIO_D_0    PORTD0
#define GPIO_D_1    PORTD1
#define GPIO_D_2    PORTD2
#define GPIO_D_3    PORTD3
#define GPIO_D_4    PORTD4
#define GPIO_D_5    PORTD5
#define GPIO_D_6    PORTD6
#define GPIO_D_7    PORTD7

#define HW_UART0 0

#define HW_SPI 1

#define HW_I2C 1

#define PIN_INT0 INT0   
#define PIN_INT1 INT1

#define TWI_NUMBER      1
#define TIMER_NUMBER    3
#define SPI_NUMBER      1
#define UART_NUMBER     1

#endif /* __MCU_AM328P__ */