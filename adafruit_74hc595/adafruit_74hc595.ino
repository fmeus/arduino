/*
Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
 */

// Set to 1 when using Digispark (uses different ports)
#define BOARD_DIGISPARK 0

#if BOARD_DIGISPARK == 0
// Digispark
int latchPin = 4;
int clockPin = 5;
int dataPin = 3;
#else
// Arduino/Freeduino
int latchPin = 9;
int clockPin = 10;
int dataPin = 8;
#endif

byte leds = 0;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  leds = 0;
  updateShiftRegister();
  delay(500);
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(100);
  }
}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

