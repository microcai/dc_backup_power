


#include "controller.hpp"


Controller::Controller()
    : m_ina_dc(0x41)
    , m_ina_bat(0x40)
{
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

}

void Controller::setPWM(float duty)
{
    ledcWrite(0, duty * (2<<pwm_resolution_bits - 1));
}
