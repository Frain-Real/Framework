#ifndef __UART_H__
#define __UART_H__
#include "standard.h"
#include "target.h"
#include "event.h"
#include "list.h"
enum uart__baud_rate_e {
    UART__BAUD_RATE_9600 = 9600,
    UART__BAUD_RATE_19200 = 19200,
    UART__BAUD_RATE_57600 = 57600,
    UART__BAUD_RATE_115200 = 115200,
    UART__BAUD_RATE_230400 = 230400,
};
using uart__baud_rate_e = uart__baud_rate_e;

enum uart__mode_e{
    UART__MODE_ASSYNC,
    UART__MODE_SYNC,
    UART__MODE_MULTIPROCCESING,
};
using uart__mode_e = uart__mode_e;

enum uart__word_len_e{
    UART__WORD_LEN_8,
    UART__WORD_LEN_9
};
using uart__word_len_e = uart__word_len_e;

enum uart__state_e{
    UART__STATE_OFF,
    UART__STATE_IDLE,
    UART__STATE_RX,
    UART__STATE_TX,
    UART__STATE_FINISH_RX,
    UART__STATE_FINISH_TX,
};
using uart__state_e = uart__state_e;

class Uart; // объявление класса

/*********************************************************************************
 * @brief Прототип коллаута UART интерфейса, объявляется пользователем и вызывается по завершению принятия/отправки пакета данных
 * @param rx_buff Буфер отправленного сообщения
 * @param tx_buff Буфер приянятого сообщения
 * @param len_rx Длина буфера отправленного сообщения
 * @param len_tx Длина буфера принятого сообщения
 * @param ev Событие с которым вызывается коллаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
using uart__cout_t = event__e (*)(u16* rx_buff, u16* tx_buff, int len_rx, int len_tx, event__e ev, void* ext_data);

/*********************************************************************************
 * @brief Прототип хендлера UART интерфейса, объявляется пользователем и вызывается по завершению инициализации/деструкции пакета данных
 * @param uart Указатель на объект UART
 * @param ev Событие с которым вызывается коллаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
using uart__handler_t = event__e (*)(Uart* uart, event__e ev, void* ext_data);

class Uart {
    protected:
        int num;                    // Номер
        uart__state_e state;        // Состояние интерфейса
        u16* rx_buff;               // Буфер отправляемого
        u16* tx_buff;               // Буфер принимаемого
        uart__baud_rate_e baud;     // Скорость интерфейса
        uart__mode_e mode;          // Режим
        uart__word_len_e word_len;  // Длина слова
        int len_rx;                 // Длина отправляемого пакета
        int len_tx;                 // Длина принимаемого пакета
        uart__cout_t cout;          // Указатель на колаут
        uart__handler_t handler;    // Указатель на хэндлер
        void* ext_data;             // Пользовательские данные

        int cur_rx_buff_bite;       // Текущий байт отправки
        int cur_tx_buff_bite;       // Текущий байт приёма
    public:
/*********************************************************************************
 * @brief Конструктор интерфейса
 * @param num Номер интерфейса
 * @param baud Скорость интерфейса
 * @param mode Режим интерфейса
 * @param word_len Длина слова
 * @param handler Указатель на хэндлер
 *********************************************************************************/
        Uart(u8 num, uart__baud_rate_e baud, uart__mode_e mode, uart__word_len_e word_len, uart__handler_t handler, void* ext_data);


/*********************************************************************************
 * @brief Диструктор интерфейса
 *********************************************************************************/
        ~Uart();

/*********************************************************************************
 * @brief Функция отправки буфера
 * @param buff Буфер отправленного сообщения
 * @param len Длина буфера
 * @param cout Указатель на колаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
        event__e Send(u16* buff, int len, uart__cout_t cout, void* ext_data);

    /*********************************************************************************
 * @brief Функция получения буфера
 * @param buff Буфер принятого сообщения
 * @param len Длина буфера
 * @param cout Указатель на колаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
        event__e Get(u16* buff, int len, uart__cout_t cout, void* ext_data);
        
        friend void uart__tx_handler(int id);
        
        friend void uart__rx_handler(int id);
};


#endif /*  __UART_H__ */

