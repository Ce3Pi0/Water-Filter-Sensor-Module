#include <OneWire.h>
#include <DallasTemperature.h>

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(unsigned int sensorPin){
    this->sensorPin = sensorPin;
}

void TemperatureSensor::begin(){
    // Setup a oneWire instance to communicate with any OneWire devices
    OneWire oneWire(this->sensorPin);
    // Pass our oneWire reference to Dallas Temperature sensor 
    DallasTemperature tempSensor(&oneWire);
    this->sensor = tempSensor;

    this->sensor.begin();
}

void TemperatureSensor::readTemp(){
  this->sensor.requestTemperatures();
  this->tempValueC = this->sensor.getTempCByIndex(0);
  this->tempValueF = this->sensor.getTempFByIndex(0);
}

float TemperatureSensor::getTempC(){
  return this->tempValueC;
}

float TemperatureSensor::getTempF(){
  return this->tempValueF;
}