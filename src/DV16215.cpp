/*
  DV16215.cpp - Library for wrapper functions in order to 
  control Phico Datavision LCD-display module 
  model no: DV-16215-1-S2RB.

  Credits for TisteAndii for showing me (and others) an example of how to use ss-class inside a customized class:
  http://arduino.stackexchange.com/questions/22211/how-to-define-a-softwareserial-object-inside-a-class

  GitHub: http://github.com/CsCrazy85/Arduino/tree/master/Datavision%20LCD

  Version 1.0

*/
#include "DV16215.h"

/* 
 *  Constructor which begins the communication with the display
  */
LCD_DV16215::LCD_DV16215(SoftwareSerial *ss)
{
  serial = ss;
  begin(9600);
}

/* 
 *  Initiate SoftwareSerial connection
 */
void LCD_DV16215::begin(uint32_t baud)
{
  serial -> begin(baud);
}

/*
 * Clears both displays in the module.
 */
void LCD_DV16215::clearAllDisplays()
{
  clearTopDisplay();
  clearBottomDisplay();
}

/*
 * Clears only the top display.
 */
void LCD_DV16215::clearTopDisplay()
{
  serial -> write(DISPLAY_TOP);
  delay(1);
  serial -> write(1);
  delay(1);
}

/*
 * Clears only the bottom display.
 */
void LCD_DV16215::clearBottomDisplay()
{
  serial -> write(DISPLAY_BOTTOM);
  delay(1);
  serial -> write(1);
  delay(1);
}

/*
 * Clears the current display which is being used.
 */
void LCD_DV16215::clearDisplay()
{
  serial -> write(currentDisplay);
  delay(1);
  serial -> write(1);
  delay(1);
}

/*
 * Set top display active and set cursor
 * 
 * cursorPosition:  0 = leftmost space, 15 = rightmost space. 
 * row:             upper row = 0 or 1
 *                  lower row = 2
 * 
 * Note! cursorPosition has no checks if you try to set the cursor outside of the screen.
 */
void LCD_DV16215::setDisplayTop(uint8_t cursorPosition, uint8_t row)
{
    // Top
    serial -> write(DISPLAY_TOP);
    delay(1);
    // Set row
    if((row == 0) ||(row == 1))
    {
      row = DISPLAY_UPPER_ROW; // DISPLAY_UPPER_ROW
    }
    else if (row == 2)
    {
      row = DISPLAY_LOWER_ROW; // DISPLAY_LOWER_ROW
    }
    else
    {
      row = DISPLAY_UPPER_ROW; // default
    }
    serial -> write(row + cursorPosition);
    delay(1);
    currentDisplay = DISPLAY_TOP;
}

/*
 * Set bottom display active and set cursor. 
 * 
 * cursorPosition:  0 = leftmost space, 15 = rightmost space. 
 * row:             upper row = 0 or 1
 *                  lower row = 2
 *                  
 * Note! cursorPosition has no checks if you try to set the cursor outside of the screen.
 */
void LCD_DV16215::setDisplayBottom(uint8_t cursorPosition, uint8_t row)
{
    // Bottom
    serial -> write(DISPLAY_BOTTOM);
    delay(1);
    // Set row
    if((row == 0) ||(row == 1))
    {
      row = DISPLAY_UPPER_ROW; // DISPLAY_UPPER_ROW
    }
    else if (row == 2)
    {
      row = DISPLAY_LOWER_ROW; // DISPLAY_LOWER_ROW
    }
    else
    {
      row = DISPLAY_UPPER_ROW; // default
    }
    serial -> write(row + cursorPosition);
    delay(1);
    currentDisplay = DISPLAY_BOTTOM;
}

/*
 * Write text to the selected display. Please select display before using this. 
 * If display is not selected, then write is done to that display which was previously used.
 */
void LCD_DV16215::write(char str[])
{
  int len = 0;
  int i = 0;
  switch(currentDisplay)
  {
    case DISPLAY_TOP:
        serial -> write(DISPLAY_CMD_WRITE_D1);
        delay(1);
    break;
    case DISPLAY_BOTTOM:
        serial -> write(DISPLAY_CMD_WRITE_D2);
        delay(1);
    break;
  }
  while(str[i] != 0)
  {
    i++;
    if(i > 15) // 16 char is max
    {
      break;
    }
  }
  len = i;
  i = 0;
  while(len--)
  {
    serial -> write(str[i++]);
    delay(1);
  }
}

