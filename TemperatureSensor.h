#include <DallasTemperature.h>

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"

class TemperatureSensor:protected Sensor {
    private:
        DallasTemperature sensor;
        float tempValueC, tempValueF;
    public:
        TemperatureSensor(unsigned int);

        void begin();
        void readTemp();
        float getTempC();
        float getTempF();
};

#endif