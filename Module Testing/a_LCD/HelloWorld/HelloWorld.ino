// ************************** LCD *******************************
    #include <Wire.h> 
    #include <LiquidCrystal_I2C.h>        // DFRobot.com
      LiquidCrystal_I2C lcd(0x27,20,4);   // set the LCD address to 0x27 for a 16 chars and 2 line display
// ************************** LCD *******************************


void setup()
{
  
// ************************ LCD ************************ //
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Hello, world!");
// ***************************************************** //  
}

void loop()
{
}
