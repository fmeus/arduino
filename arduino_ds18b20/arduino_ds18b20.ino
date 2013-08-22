#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress devices[4];

int numDevices;
float tempMax, tempMin;

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  numDevices = sensors.getDeviceCount();

  Serial.print("Number of sensors found = ");
  Serial.print( numDevices );
  Serial.print("\n\r");

  for(int i=0; i < numDevices ; i++)
  {
    sensors.getAddress(devices[i], i);
    sensors.setResolution(devices[i], 10);
  }
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print(tempC);
    Serial.print("C");
  }
  if ( tempC < tempMin || tempMin == NULL ) { tempMin = tempC; }
  if ( tempC > tempMax || tempMax == NULL ) { tempMax = tempC; }
}

void loop(void)
{ 
  delay(2000);  
  Serial.print("Getting temperatures...\n\r");
  sensors.requestTemperatures();

  for(int i=0; i < numDevices ; i++)
  {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    printTemperature(devices[i]);
    Serial.print("\n\r");    
  }

  // Min/Max
  Serial.print( "   Min = " );
  Serial.print( tempMin );
  Serial.print( "C, Max = " );
  Serial.print( tempMax );  
  Serial.print( "C" );  
  Serial.print("\n\r");    
}

