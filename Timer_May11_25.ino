#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
const int buttonMinPin = 2;    // Minute button
const int buttonSecPin = 3;    // Second button
const int startStopPin = 5;    // Start/Stop button
const int buzzerPin = 4;       // Active buzzer

// Timer variables
int minutes = 0;
int seconds = 0;
bool countdownStarted = false;
unsigned long lastUpdate = 0;
unsigned long buttonPressTime = 0;
bool buttonHeld = false;

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27 for 16x2 LCD

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(buttonMinPin, INPUT_PULLUP);
  pinMode(buttonSecPin, INPUT_PULLUP);
  pinMode(startStopPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Set Time:");
  updateDisplay();
}

void loop() {
  // Handle startStop button with long press detection
if (digitalRead(startStopPin) == LOW && !buttonHeld) {
  buttonPressTime = millis();
  buttonHeld = true;
}

if (digitalRead(startStopPin) == HIGH && buttonHeld) {
  unsigned long heldDuration = millis() - buttonPressTime;
  buttonHeld = false;

  if (heldDuration >= 2000) {
    // Long press → Reset timer
    minutes = 0;
    seconds = 0;
    countdownStarted = false;
    lcd.clear();
    lcd.print("Set Time:");
    delay(1000);
    updateDisplay();
  } else {
    // Short press → Toggle start/stop
    countdownStarted = !countdownStarted;
    if (!countdownStarted) {
      lcd.clear();
      lcd.print("Timer Stopped");
      delay(1000);
      updateDisplay();
    }
  }
}


  // If the countdown is not started, set the time
  if (!countdownStarted) {
    if (digitalRead(buttonMinPin) == LOW) {
      delay(200);  // debounce delay
      minutes = (minutes + 1) % 100;  // Limit minutes to 99
      updateDisplay();
    }

    if (digitalRead(buttonSecPin) == LOW) {
      delay(200);  // debounce delay
      seconds = (seconds + 1) % 60;  // Limit seconds to 59
      updateDisplay();
    }
  } 
  // Countdown logic
  else {
    if (millis() - lastUpdate >= 1000) {
      lastUpdate = millis();
      
      if (seconds == 0) {
        if (minutes == 0) {
          lcd.clear();
          lcd.print("Time's up!");
          buzzerBeep();
          countdownStarted = false;
          lcd.clear();
          lcd.print("Set Time:");
          updateDisplay();
          return;
        } else {
          minutes--;
          seconds = 59;
        }
      } else {
        seconds--;
      }
      updateDisplay();
    }
  }
}

// Function to update the LCD display
void updateDisplay() {
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if (minutes < 10) lcd.print('0');
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print('0');
  lcd.print(seconds);
}

void buzzerBeep() {
  bool startStopPinPressed = false;
  while (!startStopPinPressed) {
    if (digitalRead(startStopPin) == LOW) {
      startStopPinPressed = true;
    }
    digitalWrite(buzzerPin, HIGH);  // Activate buzzer
    delay(100); // Buzzer stays on for 1 second
    digitalWrite(buzzerPin, LOW);   // Deactivate buzzer
    delay(100);
  }
}