/*

 Udp NTP Client
 
 Get the time from a Network Time Protocol (NTP) time server
 Demonstrates use of UDP sendPacket and ReceivePacket 
 For more on NTP time servers and the messages needed to communicate with them, 
 see http://en.wikipedia.org/wiki/Network_Time_Protocol
 
 created 4 Sep 2010 
 by Michael Margolis
 modified 17 Sep 2010
 by Tom Igoe
 
 This code is in the public domain.

 */
 
 
 /*
 You can use this website to monitor the unixtime stamp realtime, to test your script.
 http://www.epochconverter.com/
 */
 
#define RTC_module

  
//----------------------------------------------------------------------------------------------------------------------------------
// Libraries 
//----------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Ethernet + NTP config server
//----------------------------------------------------------------------------
#include <SPI.h>         
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress timeServer(192, 43, 244, 18); // time.nist.gov NTP server



//----------------------------------------------------------------------------
// EthernetUDP
//----------------------------------------------------------------------------
#include <EthernetUdp.h>
EthernetUDP Udp;                // A UDP instance to let us send and receive packets over UDP

const int NTP_PACKET_SIZE= 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 
unsigned int localPort = 8888;      // local port to listen for UDP packets
//----------------------------------------------------------------------------

//******* RTC *****************
  #ifdef RTC_module
      #include <Wire.h>
      #include "RTClib.h"
          RTC_DS1307 RTC;
  #endif
//*****************************



//------------------------------------------------------------
// Define Variables 
//------------------------------------------------------------  
unsigned long unixtimestamp;
unsigned long unixtimestamp_local;

unsigned long previousmillisUNIX;
unsigned long previousmillisRTC;
// **************** DEFINE VARIABLES *************************/




void setup() 
{
  Serial.begin(9600);

// ****************** Ethernet Setup ******************* //
  // start Ethernet and UDP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
    } else {
  Serial.println("Ethernet connection stablished.");}
  Udp.begin(localPort);
// ***************************************************** //  


// ************************ RTC ************************ //
     #ifdef LCD
          lcd.setCursor(0, 3);  lcd.print("Initiating RTC...   "); delay(1000);
     #endif
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
}









void loop()
{
  
  retreiveUnixtimestampInternet();      // UDP
  
  adjustTimeZoneSetRTC();              // RTC
  
}


void adjustTimeZoneSetRTC()
{
  
if (millis() - previousmillisRTC > 5000)
  {
    previousmillisRTC = millis();
    
  Serial.println("Adjusting Time and Setting RTC...");
  
    //************** Adjust 40 year offset ******************
         unsigned long adjust30years;
         adjust30years = 0;//2304;//(30 * 365 * 24 * 60 * 60);    // adjust +30 year offset SERGIO
         
    Serial.print("Unix before:");Serial.print(unixtimestamp);Serial.print(" - adjust 30 years: ");Serial.println(adjust30years);
     unixtimestamp = unixtimestamp - adjust30years ;    
    Serial.print("Unixtimestamp after fix: ");Serial.println(unixtimestamp);
    //******************************************************
    
    //**************** Adjust Time Zone ********************
    unixtimestamp_local = unixtimestamp + 3 * 3600;
    Serial.print("LOCAL unixtimestamp: ");Serial.println(unixtimestamp_local);
    //******************************************************

    //********************* Adjust RTC *********************
          Serial.println("RTC adjusting!");
          // following line sets the RTC to the date & time this sketch was compiled
          RTC.adjust(DateTime(unixtimestamp_local));
    //******************************************************
    
    
    Serial.println(" ********************** Adjusting COMPLETED !! **********************");
    Serial.println();Serial.println();
    
      SerialPrintRTC();                    // RTC print
  }
}
