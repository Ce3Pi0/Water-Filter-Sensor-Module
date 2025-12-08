#include <Arduino.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_SPI.h>

#include <lcd_spi_registers.h>
#include <mcu_spi_magic.h>

#include "SensorModuleLCDScreen.h"

SensorModuleLCDScreen::SensorModuleLCDScreen(unsigned int LCD_CS, unsigned int LCD_RS, unsigned int SDO, unsigned int SDI, unsigned int LCD_RST, unsigned int SCK, unsigned int LED, unsigned int inputCount){
    LCDWIKI_SPI* lcd = new LCDWIKI_SPI(LCD_MODEL, LCD_CS, LCD_RS, SDO, SDI, LCD_RST, SCK, LED);
    this->lcd = lcd;
    this->inputCount = inputCount;
}

void SensorModuleLCDScreen::begin(){
    this->lcd->Init_LCD();
    this->lcd->Set_Rotation(1); // Horizontal Display
    this->lcd->Set_Text_Mode(true);
    this->lcd->Set_Text_Size(this->FONT_SIZE);
    this->lcd->Fill_Screen(this->BLACK); // Background Color
}

void SensorModuleLCDScreen::clearScreen(){
    if (sizeof(data) / sizeof(float) < this->inputCount) return;

    this->lcd->Set_Text_colour(this->BLACK);

    this->clearTempC(data[0]);
    this->clearTds(data[1]);
    this->clearClarity(data[2]);
    this->clearpH(data[3]);   

    this->lcd->Set_Text_colour(this->TEXT_COLOR);
}

void SensorModuleLCDScreen::displayData(float data[]){
    if (sizeof(data) / sizeof(float) > this->inputCount) return;

    for (int i = 0; i < this->inputCount; i++)
        this->data[i] = data[i];
    
    this->displayTempC(data[0]);
    this->displayTds(data[1]);
    this->displayClarity(data[2]);
    this->displaypH(data[3]);
}

void SensorModuleLCDScreen::displayTempC(float tempValue){
    if (tempValue < this->MIN_TEMP_C || tempValue > this->MAX_TEMP_C){
        this->lcd->Print_String("ERROR", 0, SensorModuleLCDScreen::FIRST);
    } else {
        String output = "C: " + String(tempValue);
        this->lcd->Print_String(output, 0, SensorModuleLCDScreen::FIRST);
    }
}

void SensorModuleLCDScreen::displayTds(float tdsValue) {
    if (tdsValue < this->MIN_TDS_VALUE) {
        this->lcd->Print_String("ERROR", 0, SensorModuleLCDScreen::SECOND);
    } else {
        String output = "TDS: " + String(tdsValue) + "ppm\n";
        this->lcd->Print_String(output, 0, SensorModuleLCDScreen::SECOND);
    }
}

void SensorModuleLCDScreen::displayClarity(float clarity) {
    if (clarity < this->MIN_CLARITY || clarity > this->MAX_CLARITY) {
        this->lcd->Print_String("ERROR", 0, SensorModuleLCDScreen::THIRD);
    } else {
        String output = "Clarity: " + String(clarity) + '%';
        this->lcd->Print_String(output, 0, SensorModuleLCDScreen::THIRD);
    }
}

void SensorModuleLCDScreen::displaypH(float phValue) {
    if (phValue < this->MIN_PH_VALUE || phValue > this->MAX_PH_VALUE) {
        this->lcd->Print_String("ERROR", 0, SensorModuleLCDScreen::FOURTH);
    } else {
        String output = "pH: " + String(phValue);
        this->lcd->Print_String(output, 0, SensorModuleLCDScreen::FOURTH);
    }
}

void SensorModuleLCDScreen::clearTempC(float tempValue) {
    String tempOutput = "   " + String(tempValue);
    this->lcd->Print_String(tempOutput, 0, SensorModuleLCDScreen::FIRST);
}

void SensorModuleLCDScreen::clearTds(float tdsValue) {
    String tdsOutput = "     " + String(tdsValue) + "ppm\n";
    this->lcd->Print_String(tdsOutput, 0, SensorModuleLCDScreen::SECOND);
}

void SensorModuleLCDScreen::clearClarity(float clarity) {
    String clarityOutput = "         " + String(clarity) + '%';
    this->lcd->Print_String(clarityOutput, 0, SensorModuleLCDScreen::THIRD);
}

void SensorModuleLCDScreen::clearpH(float phValue) {
    String phOutput = "    " + String(phValue);
    this->lcd->Print_String(phOutput, 0, SensorModuleLCDScreen::FOURTH);
}