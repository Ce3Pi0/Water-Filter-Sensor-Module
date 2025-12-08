#include "DFRobot_PH.h"
#include "PhSensor.h"


PhSensor::PhSensor(unsigned int sensorPin) {
  this->sensorPin = sensorPin;
}

void PhSensor::begin() {
  this->sensor.begin();
}

void PhSensor::getPhVoltage() {
  if (this->sensorPin <= A0) this->phVoltage = analogRead(this->sensorPin) / 1024.0 * 5000;  // Read the phVoltage
}

void PhSensor::readPh(float temp) {
  if (temp >= 5 && temp <= 60) this->phValue = this->sensor.readPH(phVoltage, temp);  // Convert phVoltage to pH with temperature compensation
}

float PhSensor::getPh() {
  return this->phValue;
}