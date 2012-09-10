// ------------------------------------------------------------------------------------
// ******************************** ARDUINO HOME MONITOR ********************************
// Version: 2.0
// Last revision: 4/9/2012
// Licence: GNU GPL
// By: Sergio Escuder Campos
// Based on the work of Trystan Lea & Glyn Hudson openenergymonitor.org (Mains AC Non Invasive 3)
// ------------------------------------------------------------------------------------

/*
Performance stadistics
Loop time: 121
FreeMem:   6700
*/


#define VERSION "1"


//----------------------------------------------------------------------------------------------------------------------------------
// Defines
//----------------------------------------------------------------------------------------------------------------------------------

//#define DEBUG
  #define LCD
  #define DS18B20
 //     #define DS18D20_debug
  #define FreeMem                // http://www.arduino.cc/playground/Code/AvailableMemory
  #define RTC_module
 //   #define RTC_module_debug
  #define DHT11_module
    #define DHT11_module_debug
  #define Serial_excel    // prints values to serial coma separated




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


//----------------------------------------------------------------------------
// Ethernet
//----------------------------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>

/*
void begin(uint8_t *mac_address, IPAddress local_ip);
void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server);
void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway);
void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);
*/

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
IPAddress server(188,121,46,128); // Goddady  //IPAddress server(173,194,34,215); // Google

// Initialize the Ethernet client library with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

  char str[250];
//----------------------------------------------------------------------------





  //------------------------------------------------------------
  // Define Variables 
  //------------------------------------------------------------  
// TEMPERATURE
float temp1;      float temp2;
float temp3;      float temp4;
float temp_caja;  float temp_amb;



// TIMERS - Create a variable to store each time a module has been run
unsigned long previous;    // Used to check Arduino loop performance
unsigned long previousmillis;
unsigned long previousmillis_RTC;
unsigned long previousmillis_FreeMem;
unsigned long previousmillis_DHT11;
unsigned long previousmillis_excel;
  unsigned long previousMillisMYSQL;
//RTC
int hours;  int minutes; int seconds;
long years;  int months;  int days;

//DHT
int weather_status;

// *********************** DEFINE VARIABLES ******************************/







void setup(void) {
// ***************** Define pins Modes ***************** //
    pinMode(Pin_over_temp,OUTPUT);
// ***************************************************** //  
  
  Serial.begin(9600);
  
  // ****************** Ethernet SETUP ******************* //
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  } else {Serial.println("Ethernet connection stablished.");}
  // give the Ethernet shield a second to initialize:
  
  delay(1000);
// ***************************************************** //  


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
/*
  if (! RTC.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  */
// ***************************************************** //   



// ************************ DHT11 ************************ //
  #ifdef DHT11_module
      Serial.print("DHT11 LIBRARY VERSION: ");
      Serial.println(DHT11LIB_VERSION);
  #endif
// ***************************************************** //   
  
  

// ************** Check DHT11 Initially **************** //
#ifdef DHT11_module
    readDHT11();
    weather();
#endif
// ***************************************************** //  

}









void loop(void) {
 
 // During the 2º minute, do a loop performance check
  if (  (millis() > 60000) &&  (millis()<70000)  )
 { 
  Serial.println(millis() - previous);
  previous = millis();
 }
 
  checktemps();
  updateLCD();
  
  if (temp_amb > 27)    digitalWrite(Pin_over_temp, HIGH);  else    digitalWrite(Pin_over_temp, LOW);
  
  checkRTC();
  
  checkFreeMem();
  
  checkDHT11();

  #ifdef Serial_excel
   if (millis() - previousmillis_excel > 1000)
  {
    previousmillis_excel = millis();
        Serial.print(millis());
        Serial.print(";");Serial.print(temp_caja);
        Serial.print(";");Serial.print(temp_amb);
        Serial.print(";");Serial.print(DHT11.humidity);
        Serial.print(";");Serial.print(DHT11.temperature);
        Serial.print(";");Serial.print(dewPoint(DHT11.temperature, DHT11.humidity));
        Serial.print(";");Serial.print(dewPointFast(DHT11.temperature, DHT11.humidity));
        Serial.print(";");Serial.print(weather_status);
        Serial.println();
  }
  #endif
  
    uploadtomysql();
}




//--------------------------------------------------------------------------------------
// Construct JSON string - 3a) Create a string to be sent to the server
//--------------------------------------------------------------------------------------
void createJSON()
{
    //strcpy(str,"/emoncms/post.php?json=");                //URL //If your using a shared server add in full URL here
    strcpy(str,"GET http://xxxxxxxxxxxxxxxxx.com/arduinohomemonitor/post.php?json=");                         //URL

    srtJSON(str);                                   //Start JSON
      addJSON(str,"temp_box",temp_caja);            //JSON line 1
      addJSON(str,"temp_amb",temp_amb);             //JSON line 1
      addJSON(str,"tempDHT",DHT11.temperature);     //JSON line 1
      addJSON(str,"humDHT",DHT11.humidity);         //JSON line 1
      addJSON(str,"weather_status",weather_status); //JSON line 1
   endJSON(str);                                 //End JSON string
  
   strcat(str," HTTP/1.0");                      //End JSON
    
    Serial.println();        Serial.println(str);        Serial.println();
}


//--------------------------------------------------------------------------------------
// Send the string to the server
//--------------------------------------------------------------------------------------
void uploadtomysql(){
  
    if (millis() - previousMillisMYSQL > 10000) {
        previousMillisMYSQL = millis();
        
      createJSON();
       
         Serial.println("Connecting...");
    
        // Make a HTTP request:
        if (client.connect(server, 80)) {
          Serial.println("connected");
                    client.println(str);
                    client.println();
                    client.println();
                    client.stop();
                        
       //   digitalWrite(outPinStatusLed, HIGH);    // set the LED on
          }
          else {
       //   digitalWrite(outPinStatusLed, LOW);    // set the LED off
          }
      //-------------------------------- end of send data ---------------------------------------
    
    }
}
