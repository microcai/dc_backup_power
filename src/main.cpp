
#include "controller.hpp"

Controller * controller = nullptr;

void setup()
{
  controller = new Controller();
}

void loop()
{
  // put your main code here, to run repeatedly:
  controller->loop();
}
