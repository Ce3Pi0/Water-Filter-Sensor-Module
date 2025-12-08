#include <Arduino.h>
#include "TDSSensor.h"

TDSSensor::TDSSensor(unsigned int sensorPin) {
    this->sensorPin = sensorPin;
}

void TDSSensor::begin(){
    pinMode(this->sensorPin, INPUT);
}

void TDSSensor::getTdsSamples() {
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U) {  //every 40 milliseconds,read the analog value from the ADC
    analogSampleTimepoint = millis();
    this->analogBuffer[this->analogBufferIndex] = analogRead(this->sensorPin);  //read the analog value and store into the buffer
    this->analogBufferIndex++;
    if (this->analogBufferIndex == this->SCOUNT)
      this->analogBufferIndex = 0;
  }
}

float TDSSensor::readTdsValue(float temperature) {
  for (this->copyIndex = 0; this->copyIndex < this->SCOUNT; this->copyIndex++)
    this->analogBufferTemp[this->copyIndex] = this->analogBuffer[this->copyIndex];

  this->averageVoltage = this->getMedianNum(this->analogBufferTemp, this->SCOUNT) * (float)this->VREF / 1024.0;                                                                                                   // read the analog value more stable by the median filtering algorithm, and convert to voltage value
  float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);                                                                                                                //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  float compensationVoltage = this->averageVoltage / compensationCoefficient;                                                                                                             //temperature compensation
  tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;  //convert voltage value to tds value
}

int TDSSensor::getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}

float TDSSensor::getTds() {
  if (this->tdsValue < 0.0f) {
    return -1.0f;
  }
  return this->tdsValue;
}