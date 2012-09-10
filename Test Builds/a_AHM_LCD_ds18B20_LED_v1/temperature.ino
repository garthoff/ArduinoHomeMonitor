void checktemps_1(){
#ifdef DS18B20
  
   byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  if ( !ds_sup.search(addr)) {
    #ifdef DEBUG
      Serial.print("No more addresses.\n");
    #endif
    ds_sup.reset_search();
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

  ds_sup.reset();
  ds_sup.select(addr);
  ds_sup.write(0x44,1);         // start conversion, with parasite power on at the end
  
  delay(2000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds_sup.reset();
  ds_sup.select(addr);    
  ds_sup.write(0xBE);         // Read Scratchpad
  
  #ifdef DEBUG
    Serial.print("P=");
    Serial.print(present,HEX);
    Serial.print(" ");
  #endif
  
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds_sup.read();
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
  
 if (addr[1] == 0xAA) { temp1 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0xF4) { temp2 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0xF4) { temp3 = ( (data[1] << 8) + data[0] )*0.0625; }
 if (addr[1] == 0xF4) { temp4 = ( (data[1] << 8) + data[0] )*0.0625; }
 
 float media = (  (temp1+temp2)/2.0  );
 
  Serial.print(temp1);Serial.print("\t");
  Serial.print(temp2);Serial.print("\t");
  Serial.print(temp3);Serial.print("\t");
  Serial.print(temp4);Serial.print("\t");
  Serial.print(" Media: ");Serial.println(media);
  
  temp_caja = temp1;
  temp_amb = temp2;
  
  #ifdef DEBUG_excel
    Serial.print(millis()/1000);
    Serial.print(";");Serial.print(temp_caja);
    Serial.print(";");Serial.println(temp_amb);
  #endif

#endif

}
