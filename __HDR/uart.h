#ifndef __UART_H__
#define __UART_H__
#include "standard.h"
#include "target.h"

class Uart
{
private:
    /* data */
public:
    Uart(int number);
    ~Uart();
    void cout();
};

#endif /*  __UART_H__ */

