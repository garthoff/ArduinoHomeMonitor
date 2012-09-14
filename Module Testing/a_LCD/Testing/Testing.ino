// ************************ LCD ************************ //
#include <Wire.h>                  // DFRobot.com
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// ***************************************************** //  



void setup()
{
// ************************ LCD ************************ //
  lcd.init();                            // initialize the lcd 
  lcd.backlight();                       // turn on backlight
  lcd.print("*ArduinoHomeMonitor*");      // Print a message to the LCD.
  
  delay(5000);
// ***************************************************** //  

}

void loop()
{
// ************************ LCD ************************ //
  lcd.setCursor(0, 0);
	lcd.print("*ArduinoHomeMonitor*");
  lcd.setCursor(0, 1);
	lcd.print("millis(): ");lcd.print(millis());
  lcd.setCursor(0, 2);
	lcd.print("-------------------");
  lcd.setCursor(0, 3);
	lcd.print(" By: Sergio Escuder");
// ***************************************************** //  
}
