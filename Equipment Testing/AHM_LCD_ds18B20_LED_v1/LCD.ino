void updateLCD(){


    	lcd.setCursor(0, 0);
	lcd.print(millis()/1000);
	lcd.setCursor(0, 1);
	lcd.print("temp_caja: ");lcd.print(temp1);lcd.print(" C");
	lcd.setCursor(0, 2);
	lcd.print("temp_amb.: ");lcd.print(temp2);lcd.print(" C");
        lcd.setCursor(0, 3);
	lcd.print(TimeToString(millis()/1000));
}
