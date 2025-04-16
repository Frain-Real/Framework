#ifndef __SPI_H__
#define __SPI_H__
#include "standard.h"
#include "target.h"
#include "event.h"

enum spi__speed_e {
    SPI__BAUD_RATE_9600 = 9600,
    SPI__BAUD_RATE_19200 = 19200,
    SPI__BAUD_RATE_57600 = 57600,
    SPI__BAUD_RATE_115200 = 115200,
    SPI__BAUD_RATE_230400 = 230400,
};
using spi__speed_e = spi__speed_e;

enum spi__mode_e{
    SPI__MODE_ASSYNC,
    SPI__MODE_SYNC,
    SPI__MODE_MULTIPROCCESING,
};
using spi__mode_e = spi__mode_e;

enum spi__state_e{
    SPI__STATE_OFF,
    SPI__STATE_IDLE,
    SPI__STATE_RX,
    SPI__STATE_TX,
    SPI__STATE_FINISH_RX,
    SPI__STATE_FINISH_TX,
};
using spi__state_e = spi__state_e;

class Spi; // объявление класса

/*********************************************************************************
 * @brief Прототип коллаута SPI интерфейса, объявляется пользователем и вызывается по завершению принятия/отправки пакета данных
 * @param rx_buff Буфер отправленного сообщения
 * @param tx_buff Буфер приянятого сообщения
 * @param len_rx Длина буфера отправленного сообщения
 * @param len_tx Длина буфера принятого сообщения
 * @param ev Событие с которым вызывается коллаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
using spi__cout_t = event__e (*)(u16* rx_buff, u16* tx_buff, int len_rx, int len_tx, event__e ev, void* ext_data);

/*********************************************************************************
 * @brief Прототип хендлера SPI интерфейса, объявляется пользователем и вызывается по завершению инициализации/деструкции пакета данных
 * @param uart Указатель на объект SPI
 * @param ev Событие с которым вызывается коллаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
using spi__handler_t = event__e (*)(Spi* spi, event__e ev, void* ext_data);

class Spi {
    protected:
        int num;                   // Номер
        spi__state_e state;        // Состояние интерфейса
        u16* rx_buff;              // Буфер отправляемого
        u16* tx_buff;              // Буфер принимаемого
        spi__speed_e baud;         // Скорость интерфейса
        spi__mode_e mode;          // Режим
        int len_rx;                // Длина отправляемого пакета
        int len_tx;                // Длина принимаемого пакета
        spi__cout_t cout;          // Указатель на колаут
        spi__handler_t handler;    // Указатель на хэндлер
        void* ext_data;            // Пользовательские данные

        int cur_rx_buff_bite;      // Текущий байт отправки
        int cur_tx_buff_bite;      // Текущий байт приёма
    public:
/*********************************************************************************
 * @brief Конструктор интерфейса
 * @param num Номер интерфейса
 * @param speed Скорость интерфейса
 * @param mode Режим интерфейса
 * @param word_len Длина слова
 * @param handler Указатель на хэндлер
 *********************************************************************************/
        Spi(u8 num, spi__speed_e speed, spi__mode_e mode, spi__handler_t handler, void* ext_data);
        
/*********************************************************************************
 * @brief Диструктор интерфейса
 *********************************************************************************/
        ~Spi();

/*********************************************************************************
 * @brief Функция отправки буфера
 * @param buff Буфер отправленного сообщения
 * @param len Длина буфера
 * @param cout Указатель на колаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
        event__e Send(u16* buff, int len, spi__cout_t cout, void* ext_data);

/*********************************************************************************
 * @brief Функция получения буфера
 * @param buff Буфер принятого сообщения
 * @param len Длина буфера
 * @param cout Указатель на колаут
 * @param ext_data Пользовательские данные
 *********************************************************************************/
        event__e Get(u16* buff, int len, spi__cout_t cout, void* ext_data);
};

#endif /*  __SPI_H__ */

