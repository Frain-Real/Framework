#pragma once
#include "standard.h"
#include "target.h"

class I2c {
private:
    /* data */
public:
    I2c(int number);
    ~I2c();
    void Send(u8* buff, int len);
    void Get(u8* buff, int len);
};