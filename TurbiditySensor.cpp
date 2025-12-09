#include <Arduino.h>
#include "TurbiditySensor.h"

TurbiditySensor::TurbiditySensor(unsigned int sensorPin) {
    this->sensorPin = sensorPin;
}

void TurbiditySensor::begin(){
  pinMode(this->sensorPin, INPUT);
}

float TurbiditySensor::turbidityToVoltage()  { 
  return this->turbidity * (this->VREF / 1024.0); 
}

void TurbiditySensor::readTurbidity() {
    this->turbidity = analogRead(this->sensorPin);
}

void TurbiditySensor::getClarityPercentage() {
  this->voltage = this->turbidityToVoltage();
  this->clarity = this->voltage / this->CLEAN_WATER_VOLTAGE * 100.0f;
}

float TurbiditySensor::getClarity() {
  if (this->clarity > this->MAX_CLARITY) return -1.0f;
  return this->clarity;
}