/*
  DV16215.h - Library for wrapper functions in order to 
  control Phico Datavision LCD-display module 
  model no: DV-16215-1-S2RB.
*/
#ifndef DV16215_h
#define DV16215_h

#include "Arduino.h"
#include <SoftwareSerial.h>

// Some defines to clarify the commands used
#define DISPLAY_TOP 17
#define DISPLAY_BOTTOM 21
#define DISPLAY_UPPER_ROW 128
#define DISPLAY_LOWER_ROW 192
#define DISPLAY_CMD_WRITE_D1 18
#define DISPLAY_CMD_WRITE_D2 22

class LCD_DV16215
{
  
  public:
    LCD_DV16215(SoftwareSerial *ss);
    void clearDisplay();
    void clearAllDisplays();
    void clearTopDisplay();
    void clearBottomDisplay();
    void setDisplayTop(uint8_t cursorPosition, uint8_t row);
    void setDisplayBottom(uint8_t cursorPosition, uint8_t row);
    void write(char str[]);

  private:
    SoftwareSerial *serial;
    int currentDisplay = DISPLAY_TOP; // default
    void begin(uint32_t baud);

};

#endif
