void checkFreeMem(){
    #ifdef FreeMem 
    if (millis() - previousmillis_FreeMem > 60000)
  {
      previousmillis_FreeMem = millis();

        Serial.print("freeMemory()=");       Serial.println(freeMemory());

  }
    #endif
}
