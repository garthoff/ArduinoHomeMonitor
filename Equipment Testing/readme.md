# Arduino Home Monitorsadfasdf
# By: Sergio Escuderasdfsadfdsa

## Background information
This is my first mayor project in Arduino and I will use this repository to create a full code documentation of everything needed for other Arduino enthusiasts to replicate, learn and make use of all the information gathered here.
I must first of all thank Trystan Lee and all the members of openenergymonitor.org for creating such an amazing website full of very usefull information and providing help to anyone who needs it. I will sure try to remark this gratitude in all my code that has some work from openenergymonitor.org 


## Libraries Needed
Here is a list of all the libraries used along the project. All this libraries have been found on the internet, none of them are created by me so hopefully the creators have left some information in their files stating this. All I want to do is help by providing a simple list of libraries which have been tested in Arduino 1.0.1 and are fully working as well as adding some interesting examples.
* LCD bv4618_I: https://github.com/ArduinoHomeMonitor/Libraries/bv4618_I
* LCD LiquidCrystal_I2C: https://github.com/ArduinoHomeMonitor/Libraries/LiquidCrystal_I2C
* Temperature & Humidity Sensor DHT11: https://github.com/ArduinoHomeMonitor/Libraries/DHT11
	* Temperature control library: http://download.milesburton.com/Arduino/MaximTemperature/ (version 372 works with Arduino 1.0) and OneWire library: http://www.pjrc.com/teensy/td_libs_OneWire.html
* MemoryFree: https://github.com/ArduinoHomeMonitor/Libraries/MemoryFree
* OneWire: https://github.com/ArduinoHomeMonitor/Libraries/OneWire
* RTClib: https://github.com/ArduinoHomeMonitor/Libraries/RTClib
	* https://github.com/jcw/rtclib
* Ultrasonic: https://github.com/ArduinoHomeMonitor/Libraries/Ultrasonic
* RF: VirtualWire: https://github.com/ArduinoHomeMonitor/Libraries/VirtualWire
	* RFM12: http://github.com/jcw/jeelib
* Mains Voltage and current: https://github.com/openenergymonitor/EmonLib


## ArduinoHomeMonitor Modules Examples
The EmonTx code guide goes through main components required to put a full emontx firmware together. It's recommended that you work through these examples first so that you have a good understanding of how the full firmware's work.
The order in which this modules appear listed here has been stablished in order to allow a profitable step by step learning curve. This means learning things like LCDs on the first step allows to be able to integrate LCD screen in the learning curve whenever neccesary.
* [LCD] (https://github.com/ArduinoHomeMonitor/Equipment Testing/a_LCD/Testing/Testing.ino)
* [LCD] (https://github.com/ArduinoHomeMonitor/Equipment Testing/a_LCD)
* [Temperature Sensors DS1820] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
* [Temperature & Humidity sensor DHT11] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
	* [04 - Temperature](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/d_Temperature/d_Temperature.ino)
* [Status_Led] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
* [RTC1307] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
* [RTC Internet] ()
https://github.com/openenergymonitor/EmonGLCD/blob/master/HomeEnergyMonitor/HomeEnergyMonitor.ino


* [Ethernet] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
* [Ultrasonic] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
* [EnergyMeter] (https://github.com/ArduinoHomeMonitor/Equipment Testing/h_EnergyMeter)
	* [01 - Single CT](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/a_SingleCT/a_SingleCT.ino)
	* [02 - Second CT](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/b_SecondCT/b_SecondCT.ino)
	* [03 - AC Voltage](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/c_ACVoltage/c_ACVoltage.ino)
* [Watchdog] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
	* [08 - Watchdog](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/h_watchdog/h_watchdog.ino)
* [Speaker] (https://github.com/ArduinoHomeMonitor/Equipment Testing/)
* [Pulse counting] ()
	* [05 - Pulse Counting](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/e_PulseCounting/e_PulseCounting.ino)
* [RF] ()
	* [07 - Transmitting Data](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/g_TransmittingData/g_TransmittingData.ino)
* [Others]
	* [06 - Elster Meter](https://github.com/openenergymonitor/emonTxFirmware/blob/master/Guide/f_ElsterMeter/f_ElsterMeter.ino)

## Full ArduinoHomeMonitor Firmware's
Here is a list of the different firmware builds, each of them tries to fullfil the multiple environments or requirements the project demands

* Master Unit - 
	* **emonTx_CT123** - Apparent Power Example - Use this example if only using CT sensors. Monitors AC current using one CT sensor and transmit data via wireless using RFM12B to emonBase. 
	* **emonTx_CT123_Voltage** - Real Power - Use this example if using an AC-AC adapter with as well as CT sensors. AC-AC plug-in adapter to monitors AC RMS voltage and give real power and current direction readings. 
	* **emonTx_Pulse** - Use for counting pulses from pulse output utility meter (flashing LED). Optical sensor can be used to detect pulses. 
	* **emonTx_Temperature** - For using multiple DS18B20 temperature sensors on a one-wire bus with emonTx. Uses direct addressing method, run the 'temperature search' sketch to find the addresses of the DS18B20 sensors and insert into main example. http://openenergymonitor.org/emon/buildingblocks/DS18B20-temperature-sensing
	* **Note:** CT must be clipped round either the Live or Neutral wire, not both! 
* Diesel monitor
* Watchdog module
* Data visualizer

When the example has been successfully uploaded the green LED should blink quickly once very 10's


## Sensors
* 100A max clip-on current sensor CT
* AC-AC Adapter - AC voltage sensor (Euro plug)
* DS18B20 temperature sensing kit
* TSL257 optical pulse sensing kit
* TSL261R IR Sensor Kit
* Waterproof DS18B20 temperature sensing kit
* Ultrasonic sensor
* PIR sensor
* LDR sensor light

## Hardware required
* Full list of parts, price, where to buy
* ArduinoHomeMonitor Master
** Arduino MEGA
** LCD display
** LED
* ArduinoHomeMonitor Diesel Monitor
* ArduinoHomeMonitor Watchdog module
* ArduinoHomeMonitor Data visualizer
** Arduino Nano
** LCD display
