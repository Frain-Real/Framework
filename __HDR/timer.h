/* Аппаратно зависимая часть таймеров Atmega328P */

#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__
#include "standard.h"
#include "list.h"

typedef enum {
    HW_RUN,
    HW_STOP,
} hw_timer__state_e; // состояния таймера
/**
 * @brief Функция обратного вызова для таймеров
 * @param prescaller Предделитель таймера
 */
typedef void (hw_timer__cb) (u8 prescaller);

class Hw_timer {
protected:
    u16 min_iter_time;          // время срабатывания прерывания в мс
    u8 prescaller;              // предделитель таймера
    hw_timer__state_e hw_state;  // состояние таймера
    hw_timer__cb* cb;            // функция обратного вызова
public:
    Hw_timer(u16 new_min_iter_time, u8 new_prescaller);
    ~Hw_timer();
    void start();
    void stop();
};

class Sw_timer; // опеределение класса для работы с таймером

typedef enum {
    SW_TIMER_READY,
    SW_TIMER_RUN,
    SW_TIMER_STOP,
    SW_TIMER_FINISH,
} sw_timer__state_e; // состояния таймера

/**
 * @brief Указатель на функцию коллбек таймера
 * @param timer указаталь на таймер
 * @result void 
*/
typedef void (sw_timer_callback)(Sw_timer *timer);

class Sw_timer {
private:
    Hw_timer* hw_timer;         // аппаратный таймер
    u32 period;                 // время срабатывания прерывания в мс
    u16 prescaller;             // предделитель таймера
    sw_timer__state_e state;    // состояние таймера
    void* ext_data;             // пользовательские данные
    sw_timer_callback* cb;      // функция обратного вызова
public:
    /**
     * @brief Конструктор таймера 
     * @param period период срабатывания прерывания в мс
     * @result void 
    */
    Sw_timer(u32 period);

    /**
     * @brief Деструктор таймера 
     * @result void 
    */
    ~Sw_timer();

    /**
     * @brief Запуск таймера 
     * @param cb указатель на функцию обратного вызова
     * @param ext_data указатель на стороннюю информацию
     * @result void 
    */
    void start(sw_timer_callback* cb, void* ext_data);
    
    /**
     * @brief Остановка таймера 
     * @result void 
    */
    void stop();
     
    /**
     * @brief Получение текущего преддеделителя таймера 
     * @result u32 предделитель таймера
    */
    u32 get_prescaller();

    /**
     * @brief Получение текущего периода таймера 
     * @result u32 период таймера
    */
    u16 get_period();

    /**
     * @brief Получение текущего состояния таймера 
     * @result sw_timer__state_e состояние таймера
    */
    sw_timer__state_e get_state();
    
    /**
     * @brief Получение сторонней информации 
     * @param ext_data указатель на стороннюю информацию
     * @result void 
    */
    void get_ext_data(void *ext_data);

    /**
     * @brief Установка сторонней информации 
     * @param new_ext_data указатель на стороннюю информацию
     * @result void 
    */
    void set_ext_data(void *new_ext_data);
    
    /**
     * @brief Установка сторонней функции обратного вызова 
     * @param new_cb указатель на стороннюю функцию обратного вызова
     * @result void 
    */
    void set_cb(sw_timer_callback *new_cb);

    /**
     * @brief Установка предделителя таймера 
     * @param new_prescaler новое значение предделителя таймера
     * @result void 
    */
    void set_prescaller(u16 new_prescaller);
    /**
     * @brief Установка периода таймера 
     * @param new_period новое значение периода таймера
     * @result void 
    */
    void set_period(u32 new_period);

    /**
     * @brief Обновление состояния таймера вызывается при срабатывании прерывания
     * @result void 
    */
    void update_state();
};

#endif /* _HW_TIMER_H__ */