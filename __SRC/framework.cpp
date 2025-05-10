#include "framework.h"

static Framework framework;

Framework::Framework() {
    #if UART == true
    #ifndef UART_USE_NUMBER
        #error "Определите в target.h UART_USE_NUMBER"
    #elif UART_USE_NUMBER > UART_NUMBER
        #error "На устройстве меньше UART интерфейсов, чем использует программа"
    #elif UART_USE_NUMBER >= 1
        #if !defined(UART0) && !defined (UART1)
            #error "Определите в target.h UART0 или UART1"
        #elif defined UART0
            uart0(UART0_SETTINGS);
        #elif defined UART1
            uart1(UART1_SETTINGS);
        #endif
    #elif UART_USE_NUMBER == 2
        #if !defined(UART0) || !defined (UART1)
            #error "Определите в target.h UART0 и UART1"
        #else
            uart0(UART0_SETTINGS);
            uart1(UART1_SETTINGS);
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
            i2c0(I2C0_SETTINGS);
        #elif defined I2C1
            i2c1(I2C1_SETTINGS);
        #endif
    #elif I2C_USE_NUMBER == 2
        #if !defined (I2C0) || !defined (I2C1)
            #error "Определите в target.h I2C0 и I2C1"
        #else
            i2c0(I2C0_SETTINGS);
            i2c1(I2C1_SETTINGS);
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
            spi0(SPI0_SETTINGS);
        #elif defined SPI1
            spi1(SPI1_SETTINGS)
        #endif
    #elif SPI_USE_NUMBER == 2
        #if !defined (SPI0) || !defined (SPI1)
            #error "Определите в target.h SPI0 и SPI1"
        #else
            spi0(SPI0_SETTINGS);
            spi1(SPI1_SETTINGS);
        #endif
    #endif
#endif

}

Framework *Framework::getInstance() {
    return &framework;
}