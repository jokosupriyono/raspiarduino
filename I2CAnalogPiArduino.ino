#include <Wire.h>

#define SLAVE_ADD 0x08
#define NOTE_C5 523
#define NOTE_E5 659
#define NOTE_G5 784
#define BUTTON  2
#define BUZZER  8
#define POT_PIN A0

int pin;
int ledArrayHigh;
int ledArrayLow;
volatile int mode = 0;
int prevMode = 0;
boolean buttonPressed = false;
volatile int adc8 = 0;

void setup()
{
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  for (pin = 3; pin < 14; pin++) {
    pinMode(pin, OUTPUT);
  }

  Wire.begin(SLAVE_ADD);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop()
{
  int adc = analogRead(POT_PIN);
  adc8 = map(adc, 0, 1023, 0, 255);

  if (mode != prevMode) {
    prevMode = mode;
    pin = 0;
    if (mode == 1) {
      tone(BUZZER, NOTE_C5, 100);
      delay(100);
      tone(BUZZER, NOTE_G5, 100);
      delay(100);
      noTone(BUZZER);
    }
    else if (mode == 2) {
      tone(BUZZER, NOTE_G5, 100);
      delay(100);
      tone(BUZZER, NOTE_C5, 100);
      delay(100);
      noTone(BUZZER);
    }
  }

  for (pin = 0; pin < 5; pin++) {
    if (mode == 1) {
      ledArrayHigh = 13 - pin;
      ledArrayLow = 7 - pin;
    }
    else if (mode == 2) {
      ledArrayHigh = 9 + pin;
      ledArrayLow = 3 + pin;
    }
    else if (mode == 3) {
      digitalWrite(ledArrayHigh, LOW);
      digitalWrite(ledArrayLow, LOW);
      continue;
    }
    digitalWrite(ledArrayHigh, HIGH);
    digitalWrite(ledArrayLow, HIGH);
    delay(100);
    digitalWrite(ledArrayHigh, LOW);
    digitalWrite(ledArrayLow, LOW);
    if (pin == 4) delay(100);
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  int inData = Wire.read(); // receive byte as an integer
  Serial.println(inData); // print the integer
  mode = inData;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write(adc8);
}
