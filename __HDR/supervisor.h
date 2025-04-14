#ifndef __SUPERVISOR_H__
#define __SUPERVISOR_H__
#include "standard.h"
#include "target.h"
#include "hw_supervisor.h"
/*
Супервизор занимается:
- отслеживанием потребности периферии и её включением отключением
- отслеживанием нагрузки ядра(переключением тактирования)
- Преключением сна

Отслеживание потребности периферии происходит автоматически при конфигурировании устройства (определяется в файле конфигурации) и
потребности передачи данных или приёма, и определяется в блоке конфигурации Connection

Отслеживание нагрузки ядра заключается в передаче ядром нагруженности и требований к задаче, на основе этих данных
Супервизор применяет требуемые настройки конфигурации тактирования

Отслеживание сна происходит на основе требований связи(Connection) и работы ядра
Отдельно производится переключение режима сна для считывания АЦП
*/


typedef struct {
    bool twi_power[TWI_NUMBER];
    bool timer_power[TIMER_NUMBER];
    bool spi_power[SPI_NUMBER];
    bool uart_power[UART_NUMBER];
    bool can_power[CAN_NUMBER];
    bool adc_power;
    bool dac_power;
    bool usb_power;
} supervisor__power_peripheral_t;

class Supervisor : protected Hw_Supervisor {
private:
    state
public:

    supervisor__power_peripheral_t per; //таблица перифирии устройства

    /**
    * @def Конструктор программного супервизора
    * @param state Состояние супервизора
    * @param reset_time время срабатывания сторожевого таймера
    * @result void 
    */
    Supervisor(supervisor__state_e state = WORK, hw_supervisor__watchdog_time_e reset_time = WDOG_1S);
    
    /**
    * @def Деструктор программного супервизора
    * @result void 
    */
    ~Supervisor(void);

    /**
    * @def Функция изменения состояния супервизора
    * @param new_state Новое состояние супервизора
    * @result void 
    */
    void change_state(supervisor__state_e new_state);

    /**
    * @def Функция изменения времения срабатывания сторожевого таймера
    * @param new_reset_time новое время срабатывания сторожевого таймера
    * @result void 
    */
    void change_watchdog_time(hw_supervisor__watchdog_time_e new_reset_time);

    /**
    * @def Функция обновление состояния перифирии
    * @result void 
    */
    void update_periphiral(void);

    /**
    * @def Функция возвращет состояние контроллера
    * @result supervisor_state_e одно из состояний очереди 
    */
    supervisor__state_e get_state(void);

    /**
    * @def Функция возвращет время срабатывания сторожевого таймера
    * @result hw_supervisor__watchdog_time_e одно из состояний очереди 
    */
    hw_supervisor__watchdog_time_e get_watchdog_time(void);
    
    /**
    * @def Функция возвращает частоту работы ядра микроконтроллера
    * @result частота работы ядра с Гц
    */
    u32 get_cpu_freq(void);
    
    /**
    * @def Коллоут супервизора
    * @result void
    */
    void cout(void);
};

#endif /* __SUPERVISOR_H__ */