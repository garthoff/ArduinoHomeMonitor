


void checkRTC(){

    // In each loop update the RTC value
        DateTime now = RTC.now();
    // Save each data in variables to access from any part of the program
        hours = now.hour(), DEC;     minutes = now.minute(), DEC;    seconds = now.second(), DEC;
        years = now.year(), DEC;   months = now.month(), DEC;      days = now.day(), DEC;
    
    // Only print values to serial every x seconds
  if (millis() - previousmillis_RTC > 10000)
  {
      previousmillis_RTC = millis();
      
      #ifdef RTC_module_debug
          Serial.print(now.year(), DEC);
          Serial.print('/');
          Serial.print(now.month(), DEC);
          Serial.print('/');
          Serial.print(now.day(), DEC);
          Serial.print(' ');
          Serial.print(now.hour(), DEC);
          Serial.print(':');
          Serial.print(now.minute(), DEC);
          Serial.print(':');
          Serial.print(now.second(), DEC);
          Serial.println();
    #endif
  } 
}



/*
void checkRTCbig(){

  DateTime now = RTC.now();

  if (statusdebug == 1)     {    printall();    }
    
// Si la fecha corresponde al primer valor unixtime es que hay un error en el RTC
  if (    (now.unixtime() == 2313941504)     ||      (! RTC.isrunning())      )
    {
      Serial.println("Error en RCT");
      tone(outPinBuzzer, 323, 500);  delay(500);  noTone(outPinBuzzer);
      tone(outPinBuzzer, 323, 500);  delay(500);  noTone(outPinBuzzer);
    }
  else 
  {
     if  (  (  (int)now.hour() == 0) && ((int)now.minute() < 10) && ((long)ch1.wh > 1000) )  
        {
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table[9])));    Serial.println( buffer );  // Serial.println("***** NEW DAY STARTED, SAVING DATA TO EEPROM *****");
             
             upload_sumakw();
             
             #ifdef EPROM
                 EEPROM_newday();
             #endif
             
        }

  }

}

void printall(){
    DateTime now = RTC.now();

    Serial.print("Week day: ");Serial.print(now.dayOfWeek(), DEC);
    Serial.print(" -- ");
    // Date
    Serial.print(now.year(), DEC);    Serial.print('/');    Serial.print(now.month(), DEC);     Serial.print('/');    Serial.print(now.day(), DEC);
    Serial.print(' ');
    // Time
    Serial.print(now.hour(), DEC);    Serial.print(':');    Serial.print(now.minute(), DEC);    Serial.print(':');    Serial.print(now.second(), DEC);
    Serial.println();
}

*/
