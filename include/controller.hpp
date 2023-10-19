
#pragma once


#include <Arduino.h>

#include <Wire.h>
#include <INA226.h>


#define PWM_PIN 9
#define PWM_EN 8

#define pwm_resolution_bits 12


class Controller
{
public:
    Controller();

    void loop();

protected:
    void setPWM(float duty);

private:

    INA226 m_ina_dc;
    INA226 m_ina_bat;

};
