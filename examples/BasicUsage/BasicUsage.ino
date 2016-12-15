/* PhicoDisplayModule Library-example
 *  This library provides wrapper functions in order to control
 *  Phico Datavision LCD-display module model no: DV-16215-1-S2RB.
 *  
 *  Functions underneath the hood uses SoftwareSerial library 
 *  on given pins. Please note that!
 *  
 *  Arduino board used here was Arduino Uno R3. Although any board should work, 
 *  since activity is based on SoftwareSerial-library.
 *  
 *  You have to remove solderbridge S3 and add solderbridge S2 in order
 *  to get this display to work with 9600 baud and inverted logic.
 *  
 */

#include <DV16215.h>

// Create SoftwareSerial
SoftwareSerial connection(10, 11, true); // RX, TX, inverted logic

// Create myLCD with SoftwareSerial connection
LCD_DV16215 myLCD(&connection);

void setup() 
{
  Serial.begin(9600,SERIAL_8N1); // debugging if needed
  myLCD.clearAllDisplays();   // Clear everything just in case
}

void loop() 
{
  testDisp1();
  myLCD.clearDisplay();
  testDisp2();
  myLCD.clearDisplay();
  delay(2000);
  testDisp1();
  testDisp2();
  delay(2000);
  
}
void testDisp1()
{
  myLCD.setDisplayTop(0,1);
  myLCD.write("D1 first row");
  myLCD.setDisplayTop(0,2);
  myLCD.write("D1 second row");
  delay(2000);
}
void testDisp2()
{
  myLCD.setDisplayBottom(0,1);
  myLCD.write("D2 first row");
  myLCD.setDisplayBottom(0,2);
  myLCD.write("D2 second row");
  delay(2000);
}

