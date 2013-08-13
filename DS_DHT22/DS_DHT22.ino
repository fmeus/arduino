#include <DHT22.h>
#include <LiquidCrystal.h>
#define DHT22_PIN 2

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

DHT22 myDHT22(DHT22_PIN);

void setup(void)
{
  lcd.setCursor (0,0);
  lcd.print("Initialized");
  lcd.setCursor(0,0);
}

void loop(void)
{ 
  DHT22_ERROR_t errorCode;
  delay(2000);
  errorCode = myDHT22.readData();

  float h = myDHT22.getHumidity();
  float t = myDHT22.getTemperatureC();
   
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
    lcd.setCursor(0,0);
    lcd.print("Humi: ");
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");

      break;
    case DHT_ERROR_CHECKSUM:
      lcd.setCursor(0,0);
    lcd.print("ERROR");
      break;
  }
}
