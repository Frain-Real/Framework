/* Реализация программно независимой части таймеров для Atmega328P */

#include "standard.h"
#include "device.h"
#include "timer.h"

extern Hw_timer hw_timer0(1000, 8);

Sw_timer::Sw_timer(u32 period) {
    this->period = period;
    this->state = SW_TIMER_READY;
    this->hw_timer = &hw_timer0;
    this->hw_timer->start();
}

Sw_timer::~Sw_timer() {
    this->cb = NULL;
    this->ext_data = NULL;
    this->state = SW_TIMER_FINISH;
    this->hw_timer = NULL;
    this->hw_timer->stop();
}

void Sw_timer::start(sw_timer_callback *cb, void *ext_data) {
    this->cb = cb;
    this->ext_data = ext_data;
    this->state = SW_TIMER_RUN;
}

void Sw_timer::stop() {
    this->state = SW_TIMER_STOP;
}

u32 Sw_timer::get_prescaller() {
    return this->period;
}

u16 Sw_timer::get_period() {
    return this->prescaller;
}

sw_timer__state_e Sw_timer::get_state() {
    return this->state;
}

void Sw_timer::get_ext_data(void *ext_data) {
    ext_data = this->ext_data;
}

void Sw_timer::set_ext_data(void *new_ext_data) {
    this->ext_data = new_ext_data;
}

void Sw_timer::set_cb(sw_timer_callback *new_cb) {
    this->cb = new_cb;
}

void Sw_timer::set_prescaller(u16 new_prescaller) {
    this->prescaller = new_prescaller;
}

void Sw_timer::set_period(u32 new_period) {
    this->period = new_period;
}

void Sw_timer::update_state() {
    
}
