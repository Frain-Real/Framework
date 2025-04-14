#ifndef __SPI_H__
#define __SPI_H__
#include "standard.h"
#include "target.h"

class Spi {
private:
    /* data */
public:
    Spi(int number);
    ~Spi();
    void Send(u8* buff, int len);
    void Get(u8* buff, int len);
};

#endif /*  __SPI_H__ */

