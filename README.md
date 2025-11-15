## 🌾🕷️ AI Spider-Cam: The Crop Doctor from the Sky!

Ever seen a spider-cam zoom across a football field? Now imagine that — but instead of chasing sweaty athletes, it's gliding over your crop field, hunting down plant infections like a botanical superhero. 🦸‍♂️🌱

* [Objective](#-mission-precision-pesticide-power)
* [Working](#%EF%B8%8F-how-it-works)
* [prerequisites](#prerequisites)
* [Components required](#-components-youll-need)
* [Why It Rocks:](#-why-it-rocks)

### 🎯 Mission: Precision Pesticide Power!
This low-cost AI-powered field scanning system is designed to:
- Detect plant diseases with machine vision 🧠📸
- Analyze infection type and severity 🤒🌿
- Sprinkle just the right amount of pesticide — no more, no less 💧🎯
- Monitor soil moisture like a thirsty camel 🐪💦
- Buzz like a bee when things get exciting 🐝🔊

### 🕸️ How It Works:
Inspired by the spider-cam from sports broadcasting, our setup uses:
- A suspended camera rig to scan the field from above (no drones, no drama!)
- An AI model trained to spot sick leaves, sad stems, and soggy soil
- ESP32 + Raspberry Pi combo for brains and brawn 🧠💪
- Stepper motors and drivers to move with style 🕺
- A buzzer for alerts, warnings, or just to say “hi” 😄

## Prerequisites
- [setup raspberry pi and have it in working condition.](https://www.youtube.com/watch?v=CQtliTJ41ZE)
- make sure to enable SSH during making bootable SD card for pi.
- Use stepper_calibration code to calibreate camera near motor 3 or in the middle. [code](https://github.com/la2y-Bot/AI-Based-Plant-Disease-Detection-Smart-Pesticide-Spraying-System/tree/main/arduinoIDE_codes/stepper_calibration)
- make sure to connect esp32 and raspberry pi to same newtork (same localhost).
- Put python scripts in pi 👇
1. Find Pi’s IP (`hostname -I` on Pi).  
2. Open **PowerShell** on Windows.  
3. Run:  
   ```powershell
   scp C:\path\file.txt pi@<Pi_IP>:/home/pi/
   ```  
4. Enter Pi’s password when asked.  
5. Verify on Pi with:  
   ```bash
   ls /home/pi/
   ```

### 🧪 Components You’ll Need:
- 4× [5V DC stepper motors (28BYJ-48) 🌀](https://robu.in/product/28byj-48-stepper-motor-dc-5v/) ---> [datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- 4× [ULN2003 motor drivers 🎛️](https://robu.in/product/uln2003-driver-module-stepper-motor-driver-board) ---> [datasheet](https://www.digikey.com/en/htmldatasheets/production/7731644/0/0/1/uln2003)
- 1× [L298N H-bridge module 🚗](https://robu.in/product/l298-based-motor-driver-module-2a/) ---> [datasheet](https://www.st.com/resource/en/datasheet/l298.pdf)
- [Rainbow wires for that unicorn vibe 🌈](https://robu.in/product/1-27mm-26awg-pure-copper-40pin-dupont-wire-flexible-rainbow-color-flat-ribbon-cable-1-meter/)
- 1× [ESP32 (the smart cookie 🍪)](https://robu.in/product/esp-wroom-32-wifi-bluetooth-networking-smart-component-development-board/) For nerdy bedtime reading, consult the ESP32 datasheet PDF 😁👍 [esp32 datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- 1× [Raspberry Pi 3 or higher (Recommanded raspberry pi 4 the boss 🧑‍💼)](https://robu.in/product/raspberry-pi-4-model-b-with-4-gb-ram/) --> [For professionals only 😎](https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-datasheet.pdf)
- 1× [Camera module (your AI’s eyes 👀)](https://robu.in/product/raspberry-pi-camera-module/)
- Power cables, data cables, and a sprinkle of DIY magic ✨

### 💡 Why It Rocks:
- Saves money 💸
- Reduces chemical waste ♻️
- Boosts crop health 🌾
- Makes farming feel like sci-fi 🚀
