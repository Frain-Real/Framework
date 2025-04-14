#include "standard.h"
#include "hw_supervisor.h"


Hw_Supervisor::Hw_Supervisor(supervisor__state_e state = WORK, hw_supervisor__watchdog_time_e reset_time = WDOG_1S) {
    this->reset_time = reset_time;
    this->state = state;
    SMCR = 0x00;
    PRR = 0xff;
}

Hw_Supervisor::~Hw_Supervisor(void) {
    // выключаем спящий режим
    PRR = 0xff;
    SMCR = 0x00;
    //отключаем сторожевой таймер
    asm("cli");
    asm("wdr");
    MCUSR &= ~(1<<WDRF);
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR = 0x00;
    asm("sei");
    asm("ret");
}

void Hw_Supervisor::change_state(supervisor__state_e new_state) {
    this->state = new_state;
    WRITE_REG(SMCR,new_state);
}

void Hw_Supervisor::change_watchdog_time(int new_reset_time) {
    this->reset_time = (hw_supervisor__watchdog_time_e)new_reset_time;
    asm("cli");
    asm("wdr");
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR &= ~0x17;
    if(new_reset_time > 7)
        WDTCSR |= 1<<5;
    new_reset_time = new_reset_time % 8;
    WDTCSR |= new_reset_time;
    asm("sei");
    asm("ret");
}

void Hw_Supervisor::update_periphiral(int part, bool state) {
    if(part > 3)
        part = part + 2;
    part = hw_supervisor__peripheral_e(part);
    if(!state)
        PRR &= ~(1<<part);
    else
        PRR |= 1<<part;
}

supervisor__state_e Hw_Supervisor::get_state(void) {
    return this->state;
}

hw_supervisor__watchdog_time_e Hw_Supervisor::get_watchdog_time(void) {
    return this->reset_time;
}

u32 Hw_Supervisor::get_cpu_freq(void) {
    return F_CPU;
}
 
void Hw_Supervisor::cout(void) {
    
}