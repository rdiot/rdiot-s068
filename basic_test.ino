/* SI7021 Humidity Sensor (GY-21) [S068] : http://rdiot.tistory.com/58 [RDIoT Demo] */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SI7021.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // LCD2004
SI7021 sensor;

void setup()
{
  lcd.init();  // initialize the lcd 
  lcd.backlight();
  lcd.print("start LCD2004");

  sensor.begin();

  delay(1000);

  lcd.clear();
}

void loop()
{
 
  lcd.setCursor(0,0);
  lcd.print("S068:SI7021");

  // temperature is an integer in hundredths
  float temperature = sensor.getCelsiusHundredths();
  temperature = temperature / 100.0;
  
  lcd.setCursor(0,1);
  lcd.print("temperature:"+(String)temperature+"'C");

  int humidity = sensor.getHumidityPercent();
  lcd.setCursor(0,2);
  lcd.print("humidity:"+(String)humidity+"% ");

  // this driver should work for SI7020 and SI7021, this returns 20 or 21 
  //int deviceid = sensor.getDeviceId(); //=20
  //lcd.setCursor(0,3);
  //lcd.print("deviceid:"+(String)deviceid);

  sensor.setHeater(true);
  delay(10000);
  sensor.setHeater(false);

  //cool down
  delay(10000);

  // get humidity and temperature in one shot, saves power because sensor takes temperature when doing humidity anyway
  si7021_env data = sensor.getHumidityAndTemperature();
  int t = data.celsiusHundredths;
  int h = data.humidityBasisPoints;
  lcd.setCursor(0,3);
  lcd.print("t="+(String)t+" h="+(String)h);

 delay(5000);

}
