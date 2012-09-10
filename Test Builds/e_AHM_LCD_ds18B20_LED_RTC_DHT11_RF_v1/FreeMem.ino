void checkFreeMem(){

    if (millis() - previousmillis_FreeMem > 10000)
  {
      previousmillis_FreeMem = millis();
    #ifdef FreeMem 
        Serial.print("freeMemory()=");       Serial.println(freeMemory());
    #endif
  }
}
