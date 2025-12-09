#ifndef PHSENSOR_H
#define PHSENSOR_H

#include "Sensor.h"
#include "DFRobot_PH.h"


class PhSensor:protected Sensor {
  private:
    DFRobot_PH sensor;
    float phVoltage, phValue;

  public:
    PhSensor(unsigned int);

    void begin();
    void getPhVoltage();
    void readPh(float);
    float getPh();
};

#endif