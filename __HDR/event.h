#pragma once

enum event__e {
    EVENT__OK,
    EVENT__ERROR,
    EVENT__NO_DATA,
    EVENT__STOP,
    EVENT__SET,
    EVENT__GET,
    EVENT__INIT,
    EVENT__START_RX,
    EVENT__START_TX,
};

using event__e = event__e;