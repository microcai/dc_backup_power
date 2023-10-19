


#include "controller.hpp"
#include "ArduinoNvs.h"

Controller::Controller()
    : m_ina_dc(0x41)
    , m_ina_bat(0x40)
{
  NVS.begin();

  if (NVS.getInt("magic") == 7788)
  {
    NVS.getFloat("bat_protect_voltage");
    NVS.getFloat("bat_min_voltage");
    NVS.getFloat("bat_max_voltage");

    NVS.getFloat("dc_min_voltage");
  }
  else
  {

  }

  Wire.setPins(19,18);

  // 10mΩ shunt
  m_ina_dc.setMaxCurrentShunt(10, 0.01);
  m_ina_bat.setMaxCurrentShunt(10, 0.01);

  m_ina_dc.begin();
  m_ina_bat.begin();

  // 启动先关闭 PWM 输出。
  digitalWrite(PWM_EN, 0);

  // use 250khz pwm
  ledcAttachPin(PWM_PIN, 0);
  ledcSetup(0, 250000, pwm_resolution_bits);

  ledcWrite(0, 0);
}

void Controller::loop()
{
  switch (mode)
  {
    case CHARGE_MODE:
    {
      charge_loop();
      // detect work mode.
      if ( m_ina_dc.getBusVoltage() < m_min_dc_voltage)
      {
        mode = OUTPUT_MODE;
      }

    }
    break;
    case OUTPUT_MODE:
    {
      output_loop();

      if (m_ina_bat.getBusVoltage() < m_min_bat_voltage )
      {
        mode = PROTECT_MODE;
      }
    }break;
    case PROTECT_MODE:
    {
      // 等待 dc 电力恢复.
      if (m_ina_dc.getBusVoltage() > (m_ina_bat.getBusVoltage() + 0.1))
      {
        // 有电就充一会
        charge_loop();
      }
      else
      {
        // 关闭输出
        setPWM(0, false);
      }

      if (m_ina_bat.getBusVoltage() > m_min_bat_voltage)
      {
        mode = CHARGE_MODE;
      }
    }
  }
}

void Controller::setPWM(float duty, bool enable_pwm)
{
  ledcWrite(0, duty * (2<<pwm_resolution_bits - 1));
  if (enable_pwm)
    digitalWrite(PWM_EN, 1);
  else
    digitalWrite(PWM_EN, 0);
}

void Controller::charge_loop()
{
  // TODO
  // 使用 3p3z 算法确定 pwm 占空比。使得充电电流不超过设定值. 同时充电电压也不超过设定值.
}

void Controller::output_loop()
{
  // TODO
  // 使用 3p3z 算法确定 pwm 占空比，使得输出电压不超过设定值.
}
