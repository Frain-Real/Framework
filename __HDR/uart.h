#ifndef __UART_H__
#define __UART_H__
#include "standard.h"
#include "target.h"
#include "event.h"

enum {
    UART__BAUD_RATE_9600,
    UART__BAUD_RATE_19200,
    UART__BAUD_RATE_57600,
    UART__BAUD_RATE_115200,
    UART__BAUD_RATE_230400,
} uart__baud_rate_e;
using uart__baud_rate_e = uart__baud_rate_e;

enum {
    UART__MODE_ASSYNC,
    UART__MODE_SYNC,
    UART__MODE_MULTIPROCCESING,
} uart__mode_e;
using uart__mode_e = uart__mode_e;

enum {
    UART__WORD_LEN_8,
    UART__WORD_LEN_9
} uart__word_len_e;
using uart__word_len_e = uart__word_len_e;

enum {
    UART__STATE_IDLE,
    UART__STATE_INIT,
    UART__STATE_RX,
    UART__STATE_TX,
    UART__STATE_FINISH_RX,
    UART__STATE_FINISH_TX,
} uart__state_e;
using uart__state_e = uart__state_e;

class Uart;

using uart__cout_t = event__e (*)(u8* rx_buff, u8* tx_buff, int len_rx, int len_tx, event__e ev, void* ext_data);

using uart__handler_t = event__e (*)(Uart* uart, event__e ev, void* ext_data);

class Uart {
private:
    uart__state_e state;
    u8* rx_buff;
    u8* tx_buff;
    uart__baud_rate_e baud;
    uart__mode_e mode;
    uart__word_len_e word_len;
    int len_rx;    // Длина отправляемого пакета
    int len_tx;    // Длина принимаемого пакета
    uart__cout_t cout;
    uart__handler_t handler;
public:
    Uart(u8 num, uart__baud_rate_e baud, uart__mode_e mode, uart__word_len_e word_len, uart__handler_t handler);
    ~Uart();
    void Send(u8* buff, int len, uart__cout_t cout);
    void Get(u8* buff, int len, uart__cout_t cout);
};

#endif /*  __UART_H__ */

