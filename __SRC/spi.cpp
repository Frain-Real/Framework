#include "spi.h"

Spi::Spi(u8 num, spi__speed_e speed, spi__mode_e mode, spi__handler_t handler, void *ext_data)
{
}

Spi::~Spi()
{
}

event__e Spi::Send(u16 *buff, int len, spi__cout_t cout, void *ext_data)
{
    return event__e();
}

event__e Spi::Get(u16 *buff, int len, spi__cout_t cout, void *ext_data)
{
    return event__e();
}
