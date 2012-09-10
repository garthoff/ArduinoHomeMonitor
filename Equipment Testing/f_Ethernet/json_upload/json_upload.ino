//----------------------------------------------------------------------------
// Ethernet
//----------------------------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(188,121,46,128); // Goddady  //IPAddress server(173,194,34,215); // Google

// Initialize the Ethernet client library with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

  char str[250];
//----------------------------------------------------------------------------


  //------------------------------------------------------------
  // Define Variables 
  //------------------------------------------------------------  
  unsigned long previousMillisMYSQL;
  
  //------------------------------------------------------------
  // Input/Output Connections 
  //------------------------------------------------------------  
  int outPinStatusLed = 25;



//----------------------------------------------------------------------------
// Setup
//----------------------------------------------------------------------------
void setup()
{ 
  
// ***************** Define pins Modes ***************** //
    pinMode(outPinStatusLed,OUTPUT);
// ***************************************************** //  

// ***************** Define pins Modes ***************** //
  Serial.begin(9600);     // start the serial library
    Serial.println("Inicio setup...");
// ***************************************************** //  


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


  Serial.println("Fin de setup");
}


void loop ()
{
  uploadtomysql();
}




//--------------------------------------------------------------------------------------
// Construct JSON string - 3a) Create a string to be sent to the server
//--------------------------------------------------------------------------------------
void createJSON()
{
    //strcpy(str,"/emoncms/post.php?json=");                //URL //If your using a shared server add in full URL here
    strcpy(str,"GET http://xxxxxxxxxxxxxxxx.com/powermonitor/post.php?json=");                         //URL

    srtJSON(str);                             //Start JSON
      addJSON(str,"segundos",millis()/2);     //JSON line 2
      addJSON(str,"millis",millis());         //JSON line 1
    endJSON(str);                             //End JSON string
   // strcat(str," HTTP/1.0");                //End JSON
    
    Serial.println();        Serial.println(str);        Serial.println();
}


//--------------------------------------------------------------------------------------
// Send the string to the server
//--------------------------------------------------------------------------------------
void uploadtomysql(){
  
    if (millis() - previousMillisMYSQL > 30000) {
        previousMillisMYSQL = millis();
        
      createJSON();
       
         Serial.println("Connecting...");
    
        // Make a HTTP request:
        if (client.connect(server, 80)) {
          Serial.println("connected");
                        client.println(str);
                        client.println();
                        client.stop();
                        
          digitalWrite(outPinStatusLed, HIGH);    // set the LED on
          }
          else {
          digitalWrite(outPinStatusLed, LOW);    // set the LED off
          }
      //-------------------------------- end of send data ---------------------------------------
    
    }
}
