

void weather(){

  
  if (DHT11.humidity < 40)
  {
 //     Serial.println("Humedad Menor a 40 - DRY");
      weather_status = 1;
  }
  else if (DHT11.humidity > 70)
  {
   //     Serial.println("Humedad mayor a 70 - WET");
        weather_status = 2;
  }
  else if (  (DHT11.temperature > 20) && (DHT11.temperature <= 27)    )
  {
   //     Serial.println("COMFORT appears when indoor humidity is between 40%-70% and indoor temperature is between + 20°C  ~  + 27°C");
        weather_status = 3;
  }
  else
  {
    //    Serial.println("NO COMFORT");
        weather_status = 4;
  }
  
}


/*
1 Symol "DRY" appears when indoor humidity is below 40%
2 Symol "WET" appears when indoor humidity is over 70%
3 Symol "COMFORT" appears when indoor humidity is between 40%-70% and indoor temperature is between + 20°C  ~  + 25°C


*/
