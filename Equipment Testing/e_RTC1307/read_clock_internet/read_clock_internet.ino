/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress server(173,194,33,104); // Google
//IPAddress server(173,194,34,215); // Google
IPAddress server(188,121,46,128); // Goddady 

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;




  long year;
  
  
  
void setup() {
  // start the serial library:
  Serial.begin(9600);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
 
}

unsigned long previousmillis;

void loop()
{
  
  if (millis() - previousmillis > 10000)
  {
    previousmillis = millis();
    
     Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET http://www.sectorsocarrat.com/arduinohomemonitor/clock.php HTTP/1.0");
    client.println();
    analyze_response();
   // client.stop();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }


 
  if (year > 0) Serial.println("Time acquired");
  }
}

unsigned long recheckmillis;

void analyze_response()
{
    char c;
    recheckmillis = millis();
    while (      (client.available())   ||   (millis() - recheckmillis >1000)  )
    {
    Serial.println("Waiting for client available");
    c = client.read();Serial.println(c);
    if (client.available()) {Serial.println("clientavailable");}
    }
  /*
    Serial.println("Analyze Response...");
  int month;
  int day;
  float temp;

  */
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    Serial.println("clientavailable");
    c = client.read();Serial.println(c);
    while (c != '#') { 
      c = client.read();Serial.println(c);

      if (millis() - previousmillis > 3000) 
      break;
      }
      /*
    Serial.println("String started");
    temp = (client.read() - '0');
    year = temp * 1000;
    temp = (client.read() - '0');
    year = year + temp * 100;
    temp = (client.read() - '0');
    year = year + temp * 10;
    temp = (client.read() - '0');
    year = year + temp * 1;
    */
  }
    Serial.print(year);
  }

