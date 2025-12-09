#include "SensorModuleLCDScreen.h"
#include "PhSensor.h"
#include "TurbiditySensor.h"
#include "TDSSensor.h"
#include "TemperatureSensor.h"

//Analog Pins
#define PH_PIN A0
#define TDS_PIN A1
#define TURBIDITY_PIN A2
#define TEMP_PIN 3

//Digital Pins
#define LCD_CS 10
#define LCD_RST 8
#define LCD_RS 9
#define SDI 11
#define SCK 13
#define LED 5
#define SDO 12
#define CTP_RST 6
#define CTP_INT 7
#define SD_CS 4

const int INPUT_COUNT = 4; 

// LCD screen
SensorModuleLCDScreen lcd(LCD_CS, LCD_RS, SDO, SDI, LCD_RST, SCK, LED, INPUT_COUNT);

// Temperature Sensor
TemperatureSensor temperatureSensor(TEMP_PIN);
// PH Sensor
PhSensor phSensor(PH_PIN);
// Turbidity Sensor
TurbiditySensor turbiditySensor(TURBIDITY_PIN);
// TDS Sensor
TDSSensor tdsSensor(TDS_PIN);

void setup() {
  lcd.begin();
  temperatureSensor.begin();
  phSensor.begin();
  tdsSensor.begin();
}

void loop() {
  lcd.clearScreen();
  
  // Temp sensor interactions
  temperatureSensor.readTemp();
  float tempValueC = temperatureSensor.getTempC();

  // TDS sensor interactions
  tdsSensor.getTdsSamples();
  tdsSensor.readTdsValue(tempValueC);
  float tdsValue = tdsSensor.getTds();

  // Turbidity sensor interactions
  turbiditySensor.readTurbidity();;
  turbiditySensor.getClarityPercentage();
  float turbidityValue = turbiditySensor.getClarity();

  // PH sensor interactions
  phSensor.getPhVoltage();
  phSensor.readPh(tempValueC);
  float phValue = phSensor.getPh();

  float data[INPUT_COUNT] = {tempValueC, tdsValue, turbidityValue, phValue};

  lcd.displayData(data);

  delay(1000);
}