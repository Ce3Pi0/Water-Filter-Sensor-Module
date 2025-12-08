#include <DallasTemperature.h>

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

class TemperatureSensor {
    private:
        unsigned int sensorPin;

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