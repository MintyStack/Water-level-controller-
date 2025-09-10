// ---------------- Automatic Water Level Controller ----------------
// Components: Arduino Uno, Water Level Sensors, Relay Module, LCD, Buzzer
// Author: Nandhika Sri (GitHub Project)
// ------------------------------------------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
int lowSensor = 2;     // Low level sensor
int midSensor = 3;     // Mid level sensor
int highSensor = 4;    // High level sensor
int relayPin = 5;      // Relay to control pump
int buzzerPin = 6;     // Buzzer for low alert

void setup() {
  pinMode(lowSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(highSensor, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Water Controller");
  delay(2000);
  lcd.clear();
}

void loop() {
  int low = digitalRead(lowSensor);
  int mid = digitalRead(midSensor);
  int high = digitalRead(highSensor);

  lcd.setCursor(0,0);
  lcd.print("Water Level:    ");

  if (high == HIGH) {
    lcd.setCursor(0,1);
    lcd.print("Tank Full      ");
    digitalWrite(relayPin, LOW);  // Pump OFF
    digitalWrite(buzzerPin, LOW);
  }
  else if (mid == HIGH) {
    lcd.setCursor(0,1);
    lcd.print("Half Filled    ");
    digitalWrite(relayPin, HIGH); // Pump ON
    digitalWrite(buzzerPin, LOW);
  }
  else if (low == HIGH) {
    lcd.setCursor(0,1);
    lcd.print("Low! Filling   ");
    digitalWrite(relayPin, HIGH); // Pump ON
    digitalWrite(buzzerPin, HIGH); // Alert buzzer
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("Empty! Filling ");
    digitalWrite(relayPin, HIGH); // Pump ON
    digitalWrite(buzzerPin, HIGH);
  }

  delay(1000);
}
