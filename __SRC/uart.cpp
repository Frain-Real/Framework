#include "standard.h"
#include "uart.h"
#include "list.h"

List <Uart> uart__list;

Uart::Uart(u8 num, uart__baud_rate_e baud, uart__mode_e mode, uart__word_len_e word_len, uart__handler_t handler, void* ext_data) {
    this->baud = baud;
    this->mode = mode;
    this->word_len = word_len;
    this->handler = handler;
    this->state = UART__STATE_IDLE;
    this->num = num;
    /* Установка скорости */
    WRITE_REG(UBRR0H, ((F_CPU / 16 / baud - 1) >> 8) % 4);
    WRITE_REG(UBRR0L, (F_CPU / 16 / baud - 1) % 8);

    /* Включить RX и TX */
    SET_BIT(UCSR0B, RXEN0|TXEN0);

    /* Установить скорость данных, количество стоповых бит и режим передачи */
    SET_BIT(UCSR0C, UCSZ00|UCSZ01|USBS0);
    CLEAR_BIT(UCSR0C, UCSZ02);

    switch (mode) {
        case UART__MODE_ASSYNC: {
            CLEAR_BIT(UCSR0C, UMSEL00|UMSEL01);
            CLEAR_BIT(UCSR0C, UCPOL0);
            break;
        }
        case UART__MODE_SYNC: {
            SET_BIT(UCSR0C, UMSEL00);
            CLEAR_BIT(UCSR0C, UMSEL01);
            SET_BIT(UCSR0C, UCPOL0);
            break;
        }
        case UART__MODE_MULTIPROCCESING: {
            SET_BIT(UCSR0C, UMSEL00|UMSEL01);
            break;
        }
        default: {
            handler(this, EVENT__ERROR, ext_data);
            return;
        }
    }
    switch(word_len) {
        case UART__WORD_LEN_8: {
            CLEAR_BIT(UCSR0C, UCSZ02);
            break;
        }
        case UART__WORD_LEN_9: {
            SET_BIT(UCSR0C, UCSZ02);
            break;
        }
        default: {
            handler(this, EVENT__ERROR, ext_data);
            return;
        }
    }
    this->ext_data = ext_data;

    uart__list.insert(num + 1, *this);
    handler(this, EVENT__INIT, ext_data);
}

Uart::Uart() {
}

void Uart::operator()(u8 num, uart__baud_rate_e baud, uart__mode_e mode, uart__word_len_e word_len, uart__handler_t handler, void *ext_data) {
    this->baud = baud;
    this->mode = mode;
    this->word_len = word_len;
    this->handler = handler;
    this->state = UART__STATE_IDLE;
    this->num = num;
    /* Установка скорости */
    WRITE_REG(UBRR0H, ((F_CPU / 16 / baud - 1) >> 8) % 4);
    WRITE_REG(UBRR0L, (F_CPU / 16 / baud - 1) % 8);

    /* Включить RX и TX */
    SET_BIT(UCSR0B, RXEN0|TXEN0);

    /* Установить скорость данных, количество стоповых бит и режим передачи */
    SET_BIT(UCSR0C, UCSZ00|UCSZ01|USBS0);
    CLEAR_BIT(UCSR0C, UCSZ02);

    switch (mode) {
        case UART__MODE_ASSYNC: {
            CLEAR_BIT(UCSR0C, UMSEL00|UMSEL01);
            CLEAR_BIT(UCSR0C, UCPOL0);
            break;
        }
        case UART__MODE_SYNC: {
            SET_BIT(UCSR0C, UMSEL00);
            CLEAR_BIT(UCSR0C, UMSEL01);
            SET_BIT(UCSR0C, UCPOL0);
            break;
        }
        case UART__MODE_MULTIPROCCESING: {
            SET_BIT(UCSR0C, UMSEL00|UMSEL01);
            break;
        }
        default: {
            handler(this, EVENT__ERROR, ext_data);
            return;
        }
    }
    switch(word_len) {
        case UART__WORD_LEN_8: {
            CLEAR_BIT(UCSR0C, UCSZ02);
            break;
        }
        case UART__WORD_LEN_9: {
            SET_BIT(UCSR0C, UCSZ02);
            break;
        }
        default: {
            handler(this, EVENT__ERROR, ext_data);
            return;
        }
    }
    this->ext_data = ext_data;

    uart__list.insert(num + 1, *this);
    handler(this, EVENT__INIT, ext_data);
}

Uart::~Uart() {
    WRITE_REG(UDR0, 0);
    CLEAR_BIT(UCSR0B, RXEN0|TXEN0);
    this->handler(this, EVENT__STOP, this->ext_data);
    uart__list.remove(this->num + 1);
}

event__e Uart::Send(u16 *buff, int len, uart__cout_t cout, void* ext_data) {
    if(cout == nullptr || buff == nullptr || len <= 0)
        return EVENT__ERROR;
    this->len_rx = len;
    this->cout = cout;
    this->rx_buff = buff;
    this->ext_data = ext_data;
    this->state = UART__STATE_RX;
    SET_BIT(UCSR0B , RXCIE0);
    handler(this, EVENT__START_RX, ext_data);
    return EVENT__OK;
}

event__e Uart::Get(u16 *buff, int len, uart__cout_t cout, void* ext_data) {
    if(cout == nullptr || buff == nullptr || len <= 0)
        return EVENT__ERROR;
    this->len_tx = len;
    this->cout = cout;
    this->tx_buff = buff;
    this->ext_data = ext_data;
    this->state = UART__STATE_TX;
    SET_BIT(UCSR0B , TXCIE0);
    handler(this, EVENT__START_TX, ext_data);
    return EVENT__OK;
}

void uart__tx_handler(int id) {
    Uart* inter = &uart__list[id];
    if(inter->cur_tx_buff_bite == inter->len_tx) {
        inter->state = UART__STATE_FINISH_TX;
        inter->cout(inter->rx_buff,inter->tx_buff, inter->len_rx, inter->len_tx, EVENT__OK, inter->ext_data);
        inter->state = UART__STATE_IDLE;
        return;
    }
    if(inter->word_len == UART__WORD_LEN_9) {
        CLEAR_BIT(UCSR0B, TXB80);
        if (inter->tx_buff[inter->cur_tx_buff_bite] & 0x0100)
            SET_BIT(UCSR0B, TXB80);
    }
    UDR0 = inter->tx_buff[inter->cur_tx_buff_bite];
    inter->cur_tx_buff_bite++;
}

void uart__rx_handler(int id) {
    Uart* inter = &uart__list[id];
    if(inter->cur_rx_buff_bite == inter->len_rx) {
        inter->state = UART__STATE_FINISH_TX;
        inter->cout(inter->rx_buff,inter->tx_buff, inter->len_rx, inter->len_tx, EVENT__OK, inter->ext_data);
        inter->state = UART__STATE_IDLE;
        return;
    }
    u8 status, resh, resl;
    status = UCSR0A;
    if(inter->word_len == UART__WORD_LEN_9) {
        resh = UCSR0B;
        resh = (resh >> 1) & 0x01;
    }
    else {
        resh = 0;
    }
    resl = UDR0;
    if (status & ((1<<FE0)|(1<<DOR0)|(1<<UPE0)))
        inter->cout(inter->rx_buff, inter->tx_buff, inter->len_rx, inter->len_tx, EVENT__ERROR, inter->ext_data);
    inter->rx_buff[inter->cur_rx_buff_bite] = ((resh << 8) | resl);
    inter->cur_rx_buff_bite++;
}

