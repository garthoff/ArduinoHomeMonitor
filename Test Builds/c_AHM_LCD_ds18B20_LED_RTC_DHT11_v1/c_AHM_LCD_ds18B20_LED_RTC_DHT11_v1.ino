// ------------------------------------------------------------------------------------
// ******************************** ARDUINO HOME MONITOR ********************************
// Version: 1.0
// Last revision: 31/8/2012
// Licence: GNU GPL
// By: Sergio Escuder Campos
// Based on the work of Trystan Lea & Glyn Hudson openenergymonitor.org (Mains AC Non Invasive 3)
// ------------------------------------------------------------------------------------

/*
Performance stadistics
Loop time: 116
FreeMem:   6931
*/


#define VERSION "1"


//----------------------------------------------------------------------------------------------------------------------------------
// Defines
//----------------------------------------------------------------------------------------------------------------------------------

//#define DEBUG
  #define LCD
  #define DS18B20
  #define FreeMem                // http://www.arduino.cc/playground/Code/AvailableMemory
  #define RTC_module
  #define DHT11_module




//----------------------------------------------------------------------------------------------------------------------------------
// Connections - Input / Output Pins Mode
//----------------------------------------------------------------------------------------------------------------------------------

  //------------------------------------------------------------
  // Temperature Connections
  //------------------------------------------------------------
  //Using DS18B20 one wire sensors. Parasite or normal power mode is supported. In parasite power multiple sensors can share same bus
  //4.7K resistor between signal bus and +5v VCC (pin 2) 
  // ground pin 1 and 3 of DS18B20
  int temperature_sensor_bus_1 = 23;
  int temperature_sensor_bus_2 = 24;

  //------------------------------------------------------------
  // Input/Output Connections 
  //------------------------------------------------------------  
  int Pin_over_temp = 25;
  
  
  
  

  
  
//----------------------------------------------------------------------------------------------------------------------------------
// Libraries 
//----------------------------------------------------------------------------------------------------------------------------------

// ************************** FreeMem *******************************
// This library is used to check that we dont overfill the Arduino Memory
  #ifdef FreeMem
      #include <MemoryFree.h>
  #endif
// ************************** FreeMem *******************************

// ************************** LCD *******************************
  #ifdef LCD
    #include <Wire.h> 
    #include <LiquidCrystal_I2C.h>        // DFRobot.com
      LiquidCrystal_I2C lcd(0x27,20,4);   // set the LCD address to 0x27 for a 16 chars and 2 line display
  #endif
// ************************** LCD *******************************



// ************************** TEMPERATURES DS18B20 *******************************
  #ifdef DS18B20
        #include <OneWire.h>
        /* DS18S20 Temperature chip i/o */
        OneWire  ds_sup(temperature_sensor_bus_1);       // Number of the digital Pin of Network 1 Temperature bus - CIRCUITO SECUNDARIO ONE WIRE PARA: PLANTA SUPERIOR
        OneWire  ds_inf(temperature_sensor_bus_2);    // Number of the digital Pin of Network 2 Temperature bus - CIRCUITO SECUNDARIO ONE WIRE PARA: PLANTA INFERIOR
        
        #define DS18S20_ID 0x10    // Defines the addresses of the temperature sensors
        #define DS18B20_ID 0x28    // Defines the addresses of the temperature sensors
  #endif
// *******************************************************************************


//******* RTC *****************
  #ifdef RTC_module
      #include <Wire.h>
      #include "RTClib.h"
          RTC_DS1307 RTC;
  #endif
//*****************************


//******* RTC *****************
  #ifdef DHT11_module
        #include <dht11.h>
            dht11 DHT11;
        
        #define DHT11PIN 31
  #endif
//*****************************










// *********************** DEFINE VARIABLES ******************************/
// TEMPERATURE
float temp1;      float temp2;
float temp3;      float temp4;
float temp_caja;  float temp_amb;



// TIMERS - Create a variable to store each time a module has been run
unsigned long previousmillis;
unsigned long previousmillis_RTC;
unsigned long previousmillis_FreeMem;
unsigned long previousmillis_DHT11;

//RTC
int hours;  int minutes; int seconds;
long years;  int months;  int days;
// *********************** DEFINE VARIABLES ******************************/







void setup(void) {
// ***************** Define pins Modes ***************** //
    pinMode(Pin_over_temp,OUTPUT);
// ***************************************************** //  
  
  Serial.begin(9600);
  

// ************************ LCD ************************ //
#ifdef LCD
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);  lcd.print("Arduino Home Monitor");
  lcd.setCursor(0, 1);  lcd.print("VERSION "); lcd.print(VERSION);
  lcd.setCursor(0, 3);  lcd.print("Loading...");
#endif
// ***************************************************** //  
  

// *********** Check Temperatures Initially ************* //
#ifdef DS18B20
    checktemps_1();
    checktemps_1();
#endif
// ***************************************************** //  



// ************************ LCD ************************ //
#ifdef LCD
  delay(2000);
  lcd.clear();
#endif
// ***************************************************** //    


// ************************ RTC ************************ //
    Wire.begin();
    RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
// ***************************************************** //   


// ************************ DHT11 ************************ //
  #ifdef DHT11_module
      Serial.println("DHT11 TEST PROGRAM ");
      Serial.print("LIBRARY VERSION: ");
      Serial.println(DHT11LIB_VERSION);
  #endif
// ***************************************************** //   
  
}





unsigned long previous;



void loop(void) {
  
  Serial.println(millis() - previous);
  previous = millis();
  
  checktemps();
  updateLCD();
  
  
  if (temp_amb > 27)
    digitalWrite(Pin_over_temp, HIGH);
  else
    digitalWrite(Pin_over_temp, LOW);
  
  checkRTC();
  
  checkFreeMem();
  
  checkDHT11();
}
