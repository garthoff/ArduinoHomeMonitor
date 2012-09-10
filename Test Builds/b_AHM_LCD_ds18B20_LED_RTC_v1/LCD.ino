void updateLCD(){


    	lcd.setCursor(0, 0);
	lcd.print("     ");lcd.print(TimeToString(millis()/1000));
	lcd.setCursor(0, 1);
	lcd.print("temp_caja: ");lcd.print(temp1);lcd.print(" C");
	lcd.setCursor(0, 2);
	lcd.print("temp_amb.: ");lcd.print(temp2);lcd.print(" C");
        lcd.setCursor(0, 3);
        
          #ifdef RTC_module
                // if less than 10, add a leading zero
                if ( days < 10)    lcd.print("0");              lcd.print(days);    lcd.print("/");  
                if ( months < 10)  lcd.print("0");              lcd.print(months);  lcd.print("/");  
                if ( years < 10)   lcd.print("0");              lcd.print(years);
                lcd.print("  ");
                if ( hours < 10)   lcd.print("0");              lcd.print(hours);    lcd.print(":");  
                if ( minutes < 10) lcd.print("0");              lcd.print(minutes);  lcd.print(":");  
                if ( seconds < 10) lcd.print("0");              lcd.print(seconds);  
                
               /*
               DateTime now = RTC.now();    // Update time value from RTC clock
                lcd.print(now.day(), DEC);  lcd.print("/");  lcd.print(now.month(), DEC);  lcd.print("/");  lcd.print(now.year(), DEC);
                lcd.print(" ");
                lcd.print(now.hour(), DEC);  lcd.print(":");  lcd.print(now.minute(), DEC);  lcd.print(":");  lcd.print(now.second(), DEC); 
               */ 
          #endif

}
