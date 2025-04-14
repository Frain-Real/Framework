#include "framework.h"

#ifndef UART
    #error "UART not defined in target"
#elif UART == true
    #include "uart.h"
    #ifndef UART_USE_NUMBER
        #error "Определите в target.h UART_USE_NUMBER"
    #elif UART_USE_NUMBER > UART_NUMBER
        #error "На устройстве меньше UART интерфейсов, чем использует программа"
    #elif UART_USE_NUMBER >= 1
        #if !defined(UART0) && !defined (UART1)
            #error "Определите в target.h UART0 или UART1"
        #elif defined UART0
            Uart uart0(0);
        #elif defined UART1
            Uart uart1(1);
        #endif
    #elif UART_USE_NUMBER == 2
        #ifndef UART0 && UART1
            #error "Определите в target.h UART0 и UART1"
        #else
            Uart uart0(0);
            Uart uart1(1);
        #endif
    #endif
#endif

#ifndef SW_TIMER 
    #error "SW_TIMER  not defined in target"
#endif
#if SW_TIMER == true
    #include "sw_timer.h"
#endif

#ifndef ANAL_DIG_CON
    #error "ANAL_DIG_CON not defined in target"
#endif
#if ANAL_DIG_CON == true
    #include "adc.h"
    //Adc adc;
#endif

#ifndef SUPERVISOR
    #error "SUPERVISOR not defined in target"
#endif
#if SUPERVISOR == true
    #include "supervisor.h"
    Supervisor supervisor;
#endif

#ifndef GPIO
    #error "GPIO not defined in target"
#endif
#if GPIO == true
    #include "gpio.h"
#endif

#ifndef RTC
    #error "RTC not defined in target"
#endif
#if RTC == true
    #include "rtc.h"
    Rtc rtc;
#endif

#ifndef PWM
    #error "PWM not defined in target"
#endif
#if PWM == true
    #include "pwm.h"
#endif

#ifndef I2C
    #error "I2C not defined in target"
#elif I2C == true
    #include "i2c.h"
    #ifndef I2C_USE_NUMBER
        #error "Определите в target.h I2C_USE_NUMBER"
    #elif I2C_USE_NUMBER > TWI_NUMBER
        #error "На устройстве меньше I2C интерфейсов, чем использует программа"
    #elif I2C_USE_NUMBER >= 1
        #ifndef I2C0 || I2C1
            #error "Определите в target.h I2C0 или I2C1"
        #elif defined I2C0
            I2c i2c0(0);
        #elif defined I2C1
            I2c i2c1(1);
        #endif
    #elif I2C_USE_NUMBER == 2
        #if !defined (I2C0) && !defined (I2C1)
            #error "Определите в target.h I2C0 и I2C1"
        #else
            I2c i2c0(0);
            I2c i2c1(1);
        #endif
    #endif
#endif


#ifndef VUSB
    #error "VUSB not defined in target"
#endif
#if VUSB == true
    #include "vusb.h"
    Vusb usb;
#endif

#ifndef SPI
    #error "SPI not defined in target"
#endif
#if SPI == true
    #include "spi.h"
    #ifdef SPI0
        Spi spi0(0);
    #endif
    #ifdef SPI1
        Spi spi1(1);
    #endif
#endif

#ifndef SPI
    #error "I2C not defined in target"
#elif SPI == true
    #include "i2c.h"
    #ifndef SPI_USE_NUMBER
        #error "Определите в target.h SPI_USE_NUMBER"
    #elif SPI_USE_NUMBER > SPI_NUMBER
        #error "На устройстве меньше SPI интерфейсов, чем использует программа"
    #elif SPI_USE_NUMBER >= 1
        #ifndef SPI0 || SPI1
            #error "Определите в target.h SPI0 или SPI1"
        #elif defined SPI0
            Spi spi0(0);
        #elif defined SPI1
            Spi spi1(1);
        #endif
    #elif SPI_USE_NUMBER == 2
        #ifndef SPI0 && SPI1
            #error "Определите в target.h SPI0 и SPI1"
        #else
            Spi spi0(0);
            Spi spi1(1);
        #endif
    #endif
#endif

#ifndef EEPROM
    #error "EEPROM not defined in target"
#endif
#if EEPROM == true
    #include "eeprom.h"
    Eeprom eeprom;
#endif


Framework::Framework() {

}

Framework::~Framework() {

}
void Framework::cout() {
#if UART == true
    #ifdef UART0
        uart0.cout();
    #endif
    #ifdef UART1
        uart1.cout();
    #endif
#endif

#if SW_TIMER == true
    sw_timer__cout();
#endif

#if ANAL_DIG_CON == true
    //adc.cout();
#endif

#if GPIO == true
    //gpio__cout();
#endif

#if RTC == true
    rtc.cout();
#endif

#if PWM == true
    //Pwm__cout();
#endif

#if I2C == true
    #ifdef I2C0
        i2c0.cout();
    #endif
    #ifdef I2C1
        i2c1.cout();
    #endif
#endif

#if VUSB == true
    usb.cout();
#endif

#if SPI == true
    #ifdef SPI0
        spi0.cout();
    #endif
    #ifdef SPI1
        spi1.cout();
    #endif
#endif
}