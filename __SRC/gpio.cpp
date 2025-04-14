#include "gpio.h"

GpioPin::GpioPin(u8 port, u8 pin, gpio__alter_func_e alt_func, gpio__diraction_e diraction, gpio_pulled_e pulled) {
    this->alt_func = alt_func;
    this->port = port;
    this->pin = pin;
    this->diraction = diraction;
    this->pulled = pulled;
        hw_pin->init(this->port, this->pin, diraction, pulled);
    if(diraction == OUTPUT)
        hw_pin->set(this->port, this->pin, false);
}
GpioPin::~GpioPin(){

}

bool GpioPin::get() {
    return hw_pin->get(this->port, this->pin);
}
void GpioPin::set(bool value) {
    hw_pin->set(this->port, this->pin, value);
}
void GpioPin::toggle() {
    hw_pin->set(this->port, this->pin, !(hw_pin->get(this->port, this->pin)));
}