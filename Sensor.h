#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  protected:
    unsigned short sensorPin;
  public:
    virtual void begin() = 0;
};

#endif