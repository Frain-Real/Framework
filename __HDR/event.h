#ifndef __EVENT_H__
#define __EVENT_H__

enum event__e {
    EVENT__OK,
    EVENT__ERROR,
    EVENT__NO_DATA,
    EVENT__STOP,
    EVENT__INIT,
    EVENT__START_RX,
    EVENT__START_TX,
};

using event__e = event__e;
#endif /* __EVENT_H__ */

