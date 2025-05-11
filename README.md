# Arduino Nano Based Timer

This is a simple countdown timer project built using an Arduino Nano, I²C 16x2 LCD, push buttons, and an active buzzer.

## 🛠 Components Used
- Arduino Nano  
- I²C 16x2 LCD display  
- 3 Push buttons (Minutes, Seconds, Start/Stop)  
- Active Piezo Buzzer  
- Jumper wires and breadboard  

## ⚙️ Features
- Set minutes and seconds using push buttons  
- Start/Stop the countdown with a dedicated button  
- Long press (≥ 3s) on Start/Stop resets the timer  
- Active buzzer beeps when timer ends  
- LCD shows countdown in real time  

## 🔌 Pin Connections

| Component        | Arduino Nano Pin |
|------------------|------------------|
| LCD SDA          | A4               |
| LCD SCL          | A5               |
| LCD VCC/GND      | 5V / GND         |
| Minute Button    | D2               |
| Second Button    | D3               |
| Start/Stop Button| D5               |
| Buzzer (+)       | D4               |
| Buzzer (–)       | GND              |

Buttons are connected to ground, and their pins are configured with internal pull-up resistors in code.

## 🧪 How to Use
1. Upload the code to the Arduino Nano.
2. Use the Minute and Second buttons to set the timer.
3. Press Start/Stop to begin countdown.
4. Hold Start/Stop for 3 seconds to reset timer at any point.

## Note
In the reference picture, an Arduino Uno has been used instead of an Arduino Nano. The connections remain the same.
