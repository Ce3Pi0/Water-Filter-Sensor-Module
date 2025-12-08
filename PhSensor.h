#ifndef PHSENSOR_H
#define PHSENSOR_H

#include "DFRobot_PH.h"

class PhSensor {
  private:
    DFRobot_PH sensor;
    float phVoltage, phValue;
    unsigned short sensorPin;

  public:
    PhSensor(unsigned int sensorPin);

    void begin();
    void getPhVoltage();
    void readPh(float);
    float getPh();
};

#endif