#ifndef __HW_SUPERVISOR__
#define __HW_SUPERVISOR__

#include "standard.h"
#include "target.h"

#ifndef TWI_NUMBER
    #error "Определите TWI_NUMBER в device.h"
#endif

#ifndef TIMER_NUMBER
    #error "Определите TIMER_NUMBER в device.h"
#endif

#ifndef SPI_NUMBER
    #error "Определите SPI_NUMBER в device.h"
#endif

#ifndef UART_NUMBER
    #error "Определите UART_NUMBER в device.h"
#endif

typedef enum {
    WORK = 0,
    IDLE = 1,
    ADC_NOISE_REDUCTION = 3,
    POWER_DOWN = 5,
    POWER_SAVE = 7,
    STANDBY = 13,
    EXTENDED_STANDBY = 15,
} supervisor__state_e; // режимы работы контроллера

typedef enum {
    WDOG_4S = 8,
    WDOG_2S = 7,
    WDOG_1S = 6,
} hw_supervisor__watchdog_time_e; //время сторожевого таймера

typedef enum {
    ADC_PER = 0,
    UART_PER,
    SPI_PER,
    TIM0_PER = 5,
    TIM1_PER = 3, 
    TIM2_PER = 6,
    TWI_PER,
} hw_supervisor__peripheral_e;

class Hw_Supervisor {
private:
    supervisor__state_e state;
    hw_supervisor__watchdog_time_e reset_time;
public:
    /**
    * @def Конструктор программного супервизора
    * @param state Состояние супервизора
    * @param reset_time время срабатывания сторожевого таймера
    * @result void 
    */
    Hw_Supervisor(supervisor__state_e state, hw_supervisor__watchdog_time_e reset_time);
    
    /**
    * @def Деструктор программного супервизора
    * @result void 
    */
    ~Hw_Supervisor(void);

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
    void change_watchdog_time(int new_reset_time);

    /**
    * @def Функция обновление состояния перифирии
    * @result void 
    */
    void update_periphiral(int part, bool state);

    /**
    * @def Функция возвращет состояние контроллера
    * @result supervisor_state_e одно из состояний очереди 
    */
    supervisor__state_e get_state(void);

    /**
    * @def Функция возвращет время срабатывания сторожевого таймера
    * @result watchdog_time_e одно из состояний очереди 
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


#endif /* __HW_SUPERVISOR__ */