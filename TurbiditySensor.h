#ifndef TURBIDITYSENSOR_H
#define TURBIDITYSENSOR_H

class TurbiditySensor {
  private:
    const float MAX_CLARITY = 100.0f;
    const float VREF = 5.0f;
    const float CLEAN_WATER_VOLTAGE = 4.21f;
    float turbidity, clarity, voltage;
    unsigned short sensorPin;
  public:
    TurbiditySensor(unsigned int);

    float turbidityToVoltage();
    void readTurbidity();
    void getClarityPercentage();
    float getClarity();
};

#endif