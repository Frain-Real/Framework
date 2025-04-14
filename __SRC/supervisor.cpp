#include "__FRAMEWORK/standard.h"
#include "__FRAMEWORK/supervisor.h"

Supervisor::Supervisor(supervisor__state_e state, hw_supervisor__watchdog_time_e reset_time): Hw_Supervisor(state, reset_time) {
    int i;
    for(i = 0; i < TWI_NUMBER; i++)
        this->per.twi_power[i] = true;
    for(i = 0; i < TIMER_NUMBER; i++)
        this->per.timer_power[i] = true;
    for(i = 0; i < SPI_NUMBER; i++)
        this->per.spi_power[i] = true;
    for(i = 0; i < UART_NUMBER; i++)
        this->per.uart_power[i] = true;
    this->per.adc_power = true;
}

Supervisor::~Supervisor(void) {

}

void Supervisor::change_state(supervisor__state_e new_state) {
    Hw_Supervisor::change_state(new_state);
}

void Supervisor::change_watchdog_time(hw_supervisor__watchdog_time_e new_reset_time) {
    Hw_Supervisor::change_watchdog_time(new_reset_time);
}

void Supervisor::update_periphiral(void) {
    Hw_Supervisor::update_periphiral(ADC_PER, per.adc_power);
    for (int i = 0; i < SPI_NUMBER; i++)
        Hw_Supervisor::update_periphiral(SPI_PER + i, per.spi_power[i]);
    for (int i = 0; i < TWI_NUMBER; i++)
        Hw_Supervisor::update_periphiral(TWI_PER + i, per.twi_power[i]);
    for (int i = 0; i < UART_NUMBER; i++)
        Hw_Supervisor::update_periphiral(UART_PER + i, per.uart_power[i]);
    for (int i = 0; i < TIMER_NUMBER; i++)
        Hw_Supervisor::update_periphiral(ADC_PER, per.timer_power[i]);
}

supervisor__state_e Supervisor::get_state(void) {
    return Hw_Supervisor::get_state();
}

hw_supervisor__watchdog_time_e Supervisor::get_watchdog_time(void) {
    return Hw_Supervisor::get_watchdog_time();
}

u32 Supervisor::get_cpu_freq(void) {
    return F_CPU;
}
 
void Supervisor::cout(void) {
    
}