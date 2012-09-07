//#include <OneWire.h>

/* DS18S20 Temperature chip i/o */
/*
OneWire  ds(2);  // on pin 10


#define DS18S20_ID 0x10
#define DS18B20_ID 0x28

float temp1;
float temp2;
float temp3;

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  if ( !ds.search(addr)) {
    Serial.print("No more addresses.\n");
    ds.reset_search();
    delay(250);
    return;
  }
  
  Serial.print("R=");
  for( i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!\n");
      return;
  }
  
  if ( addr[0] != DS18B20_ID) {
      Serial.print("Device is not a DS18S20 family device.\n");
      return;
  }

  // The DallasTemperature library can do all this work for you!

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end
  
  delay(2000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  Serial.print("P=");
  Serial.print(present,HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print( OneWire::crc8( data, 8), HEX);
  Serial.println();
 
  //temp = ( (data[1] << 8) + data[0] )*0.0625;
  //Serial.println(temp);
  Serial.print("Address: ");         Serial.print(addr[1], HEX);
  Serial.print("\t Temperature: ");  Serial.print(  ( (data[1] << 8) + data[0] )*0.0625  );
  Serial.println();
  
 if (addr[1] == 0x1D) { temp1 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0x1B) { temp2 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0x4F) { temp3 = ( (data[1] << 8) + data[0] )*0.0625; }
 
  Serial.print(temp1);Serial.print("\t");
  Serial.print(temp2);Serial.print("\t");
  Serial.println(temp3);

}

*/
