
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
    void charge_loop();

    void output_loop();

    void setPWM(float duty, bool enable_pwm = true);

private:

    enum
    {
        // 充电模式.
        CHARGE_MODE,
        // 输出模式.
        OUTPUT_MODE,

        // 电池保护模式.
        PROTECT_MODE,
    } mode = PROTECT_MODE;

    INA226 m_ina_dc;
    INA226 m_ina_bat;

public:
    float m_min_dc_voltage = 11;
    float m_min_bat_voltage = 3.3;

};
