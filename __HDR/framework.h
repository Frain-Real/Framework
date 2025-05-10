#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__
#include "target.h"

#ifndef UART
    #error "UART not defined in target"
#elif UART == true
    #include "uart.h"
#endif
#ifndef SW_TIMER 
    #error "SW_TIMER  not defined in target"
#elif SW_TIMER == true
    #include "sw_timer.h"
#endif
#ifndef ANAL_DIG_CON
    #error "ANAL_DIG_CON not defined in target"
#elif ANAL_DIG_CON == true
    #include "adc.h"
#endif
#ifndef SUPERVISOR
    #error "SUPERVISOR not defined in target"
#elif SUPERVISOR == true
    #include "supervisor.h"
#endif
#ifndef EEPROM
    #error "EEPROM not defined in target"
#elif EEPROM == true
    #include "eeprom.h"
#endif
#ifndef VUSB
    #error "VUSB not defined in target"
#elif VUSB == true
    #include "vusb.h"
#endif
#ifndef GPIO
    #error "GPIO not defined in target"
#elif GPIO == true
    #include "gpio.h"
#endif
#ifndef RTC
    #error "RTC not defined in target"
#elif RTC == true
    #include "rtc.h"
#endif
#ifndef PWM
    #error "PWM not defined in target"
#elif PWM == true
    #include "pwm.h"
#endif
#ifndef I2C
    #error "I2C not defined in target"
#elif I2C == true
    #include "i2c.h"
#endif
#ifndef SPI
    #error "SPI not defined in target"
#elif SPI == true
    #include "spi.h"
#endif

class Framework {
    public:
    Framework();
    Framework(Framework &other) = delete;
    void operator=(const Framework &) = delete;

#if UART == true
    #ifndef UART_USE_NUMBER
        #error "Определите в target.h UART_USE_NUMBER"
    #elif UART_USE_NUMBER > UART_NUMBER
        #error "На устройстве меньше UART интерфейсов, чем использует программа"
    #elif UART_USE_NUMBER >= 1
        #if !defined(UART0) && !defined (UART1)
            #error "Определите в target.h UART0 или UART1"
        #elif defined UART0
            Uart uart0;
        #elif defined UART1
            Uart uart1;
        #endif
    #elif UART_USE_NUMBER == 2
        #if !defined(UART0) || !defined (UART1)
            #error "Определите в target.h UART0 и UART1"
        #else
            Uart uart0;
            Uart uart1;
        #endif
    #endif
#endif

#if I2C == true
    #ifndef I2C_USE_NUMBER
        #error "Определите в target.h I2C_USE_NUMBER"
    #elif I2C_USE_NUMBER > TWI_NUMBER
        #error "На устройстве меньше I2C интерфейсов, чем использует программа"
    #elif I2C_USE_NUMBER >= 1
        #ifndef I2C0 || I2C1
            #error "Определите в target.h I2C0 или I2C1"
        #elif defined I2C0
            I2c i2c0;
        #elif defined I2C1
            I2c i2c1;
        #endif
    #elif I2C_USE_NUMBER == 2
        #if !defined (I2C0) || !defined (I2C1)
            #error "Определите в target.h I2C0 и I2C1"
        #else
            I2c i2c0;
            I2c i2c1;
        #endif
    #endif
#endif

#if SPI == true
    #ifndef SPI_USE_NUMBER
        #error "Определите в target.h SPI_USE_NUMBER"
    #elif SPI_USE_NUMBER > SPI_NUMBER
        #error "На устройстве меньше SPI интерфейсов, чем использует программа"
    #elif SPI_USE_NUMBER >= 1
        #if !defined (SPI0) && !defined (SPI1)
            #error "Определите в target.h SPI0 или SPI1"
        #elif defined SPI0
            Spi spi0;
        #elif defined SPI1
            Spi spi1
        #endif
    #elif SPI_USE_NUMBER == 2
        #if !defined (SPI0) || !defined (SPI1)
            #error "Определите в target.h SPI0 и SPI1"
        #else
            Spi spi0;
            Spi spi1;
        #endif
    #endif
#endif


    static Framework *getInstance();

}; 
#endif /* __FRAMEWORK_H__ */