#include <LCDWIKI_SPI.h>

#ifndef SENSORMODULELCDSCREEN_H
#define SENSORMODULELCDSCREEN_H

#define LCD_MODEL ST7796S

class SensorModuleLCDScreen {
    private:
        const float MIN_TEMP_C = -55.0f, MAX_TEMP_C = 125.0f;
        const float MIN_TDS_VALUE = 0.0f;
        const float MIN_CLARITY = 0.0f, MAX_CLARITY = 100.0f;
        const float MIN_PH_VALUE = 0.0f, MAX_PH_VALUE = 14.0f;

        const unsigned int FONT_SIZE = 5;
        const unsigned int BLACK = 0;
        const unsigned int TEXT_COLOR = 1000;
        LCDWIKI_SPI* lcd;
        unsigned int inputCount;
        float data[4];

        void displayTempC(float);
        void displayTds(float);
        void displayClarity(float);
        void displaypH(float);

        void clearTempC(float);
        void clearTds(float);
        void clearClarity(float);
        void clearpH(float);

        enum ROWS{
            FIRST = 0,
            SECOND = 45,
            THIRD = 90,
            FOURTH = 135
        };
    public:
        SensorModuleLCDScreen(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
        void begin();
        void clearScreen();
        void displayData(float[]);
};

#endif