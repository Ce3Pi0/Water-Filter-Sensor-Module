#ifndef TDSSENSOR_H
#define TDSSENSOR_H

#include "Sensor.h"

class TDSSensor:protected Sensor {
    private:
        static const int SCOUNT = 30;
        const float VREF = 5.0f;

        int analogBuffer[SCOUNT];  // store the analog value in the array, read from ADC
        int analogBufferTemp[SCOUNT];
        int analogBufferIndex = 0, copyIndex = 0;
        float averageVoltage = 0.0f, tdsValue = 0.0f;
    public:
        TDSSensor(unsigned int);

        void begin();
        void getTdsSamples();
        float readTdsValue(float);
        int getMedianNum(int[], int);
        float getTds();
};

#endif