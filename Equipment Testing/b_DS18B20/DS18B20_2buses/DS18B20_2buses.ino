#include <OneWire.h>

/* DS18S20 Temperature chip i/o */

OneWire  ds_bus1(23);  // on pin 23
OneWire  ds_bus2(22);  // on pin 23

//#define DEBUG
#define DEBUG2

#define DS18S20_ID 0x10
#define DS18B20_ID 0x28

float temp1;
float temp2;
float temp3;

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {

    read_bus1();
    read_bus2();
    
}

void read_bus1()
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  if ( !ds_bus1.search(addr)) {
    #ifdef DEBUG
      Serial.print("No more addresses.\n");
    #endif
    ds_bus1.reset_search();
    delay(250);
    return;
  }
  
  #ifdef DEBUG
  Serial.print("R=");
  for( i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }
  #endif

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      #ifdef DEBUG
        Serial.print("CRC is not valid!\n");
      #endif
      return;
  }
  
  if ( addr[0] != DS18B20_ID) {
      Serial.print("Device is not a DS18S20 family device.\n");
      return;
  }

  // The DallasTemperature library can do all this work for you!

  ds_bus1.reset();
  ds_bus1.select(addr);
  ds_bus1.write(0x44,1);         // start conversion, with parasite power on at the end
  
  delay(2000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds_bus1.reset();
  ds_bus1.select(addr);    
  ds_bus1.write(0xBE);         // Read Scratchpad
  
  #ifdef DEBUG
    Serial.print("P=");
    Serial.print(present,HEX);
    Serial.print(" ");
  #endif
  
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds_bus1.read();
    #ifdef DEBUG
      Serial.print(data[i], HEX);
      Serial.print(" ");
    #endif
  }
  #ifdef DEBUG
    Serial.print(" CRC=");
    Serial.print( OneWire::crc8( data, 8), HEX);
    Serial.println();
  #endif
 

  #ifdef DEBUG2
    Serial.print("Address: ");         Serial.print(addr[1], HEX);
    Serial.print("\t Temperature: ");  Serial.print(  ( (data[1] << 8) + data[0] )*0.0625  );
    Serial.println();
  #endif
  
  // Modify the following addresses according to the sensors addresses
 if (addr[1] == 0x1D) { temp1 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0x1B) { temp2 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0x4F) { temp3 = ( (data[1] << 8) + data[0] )*0.0625; }
 
  Serial.println(" --- Temperature Sensors. Bus 1 --- ");
  Serial.print(temp1);Serial.print("\t");
  Serial.print(temp2);Serial.print("\t");
  Serial.print(temp3);
  Serial.println();

}



void read_bus2()
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  if ( !ds_bus2.search(addr)) {
    #ifdef DEBUG
      Serial.print("No more addresses.\n");
    #endif
    ds_bus2.reset_search();
    delay(250);
    return;
  }
  
  #ifdef DEBUG
  Serial.print("R=");
  for( i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }
  #endif

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      #ifdef DEBUG
        Serial.print("CRC is not valid!\n");
      #endif
      return;
  }
  
  if ( addr[0] != DS18B20_ID) {
      Serial.print("Device is not a DS18S20 family device.\n");
      return;
  }

  // The DallasTemperature library can do all this work for you!

  ds_bus2.reset();
  ds_bus2.select(addr);
  ds_bus2.write(0x44,1);         // start conversion, with parasite power on at the end
  
  delay(2000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds_bus2.reset();
  ds_bus2.select(addr);    
  ds_bus2.write(0xBE);         // Read Scratchpad
  
  #ifdef DEBUG
    Serial.print("P=");
    Serial.print(present,HEX);
    Serial.print(" ");
  #endif
  
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds_bus2.read();
    #ifdef DEBUG
      Serial.print(data[i], HEX);
      Serial.print(" ");
    #endif
  }
  #ifdef DEBUG
    Serial.print(" CRC=");
    Serial.print( OneWire::crc8( data, 8), HEX);
    Serial.println();
  #endif
 

  #ifdef DEBUG2
    Serial.print("Address: ");         Serial.print(addr[1], HEX);
    Serial.print("\t Temperature: ");  Serial.print(  ( (data[1] << 8) + data[0] )*0.0625  );
    Serial.println();
  #endif
  
  // Modify the following addresses according to the sensors addresses
 if (addr[1] == 0x1D) { temp1 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0x1B) { temp2 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0x4F) { temp3 = ( (data[1] << 8) + data[0] )*0.0625; }

  Serial.println(" --- Temperature Sensors. Bus 2 --- "); 
  Serial.print(temp1);Serial.print("\t");
  Serial.print(temp2);Serial.print("\t");
  Serial.print(temp3);
  Serial.println();

}
