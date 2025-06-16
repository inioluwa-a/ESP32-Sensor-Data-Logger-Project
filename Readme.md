# ESP32 Sensor Data Logger Project – Full Setup & Methodology Guide

## 🔍 What This Is
This project uses an ESP32 microcontroller to read sensor data (temperature, humidity, air quality, etc.) and send it wirelessly to a computer. Data is displayed on the Serial Monitor and can optionally be logged into Microsoft Excel using the Data Streamer add-in.

## 🧰 Tools and Components
### ✅ Hardware
- ESP32 Dev Board (e.g., ESP32 WROOM-32)
- Sensors (any combination of):
  - DHT11/DHT22 → Temp + Humidity
  - MQ135 → Air Quality
  - BH1750 or LDR → Light
  - BMP280/BME280 → Pressure + Altitude
  - GUVA-S12SD → UV
  - Soil Moisture Sensor
- Optional: 16x2 or 20x4 I2C LCD
- USB Cable (data-capable)

### ✅ Software
- Arduino IDE
- ESP32 Board Package for Arduino
- CP210x USB Driver (for board communication)
- Microsoft Excel with Data Streamer Add-in (optional)

## 🛠️ Full Methodology & Setup Instructions

### 1. Install CP210x USB Driver
- Download from Silicon Labs
- Install for your OS (Windows/macOS)
- Plug in the ESP32 via USB
- Open Device Manager → Ports (COM & LPT)
- You should see “CP210x USB to UART Bridge (COMX)”

### 2. Install Arduino IDE
- Download from arduino.cc and install

### 3. Add ESP32 Support in Arduino
- Open Arduino → File → Preferences
- Paste this URL into “Additional Board Manager URLs”:
  - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
- Go to Tools → Board → Board Manager → Search “ESP32” → Click Install

### 4. Select the Right Board & Port
- Tools → Board → ESP32 Arduino → ESP32 Dev Module
- Tools → Port → Select the COM port (e.g., COM3) shown in Device Manager
- **Tip:** If no port shows up, recheck cable or driver. Some USB cables are power-only.

### 5. Prepare and Upload the Code
- Open your .ino sketch (e.g., ESP32_Slave_Sensors.ino)
- Click ✅ Verify to compile
- Click ⬆️ Upload

#### 🧲 IMPORTANT Upload Tip
Some ESP32 boards need manual intervention during upload:
- Hold down the BOOT button on the ESP32
- While holding BOOT, click Upload in Arduino
- Watch for “Connecting….._____” or “Waiting for upload…”
- Release BOOT
- Upload should proceed automatically
- If upload fails, try again and time your BOOT release carefully. You may need to press EN (reset) if it hangs.

### 6. Open Serial Monitor
- Tools → Serial Monitor
- Set Baud Rate to 9600
- You’ll see output like: `Data, 23,2348, 0.00, 60, 0.00 …..`

### 7. View Sensor Data in Excel (Optional)
- Open Excel → Insert → Get Add-ins → Search “Data Streamer”
- Install and go to Data Streamer tab
- Click Connect a Device, select the same COM port
- Click Start Data
- ESP32 sensor data will fill into live Excel rows!

## 🔁 Summary of Workflow
[Sensors] → [ESP32] → Bluetooth → [Serial Monitor or Excel]

## 🧠 Additional Tips & Troubleshooting
| Issue                        | Solution                                                      |
|------------------------------|---------------------------------------------------------------|
| ESP32 not showing in Ports   | Check CP210x driver; try another USB cable                    |
| Code not uploading           | Try holding BOOT during upload as explained above             |
| Serial Monitor shows junk    | Check correct baud rate (9600)                                |
| No data in Excel             | Close Serial Monitor first – only one app can use COM port     |
| No Bluetooth data received   | Make sure Master ESP32 or paired device is active             |
| LCD not showing data         | Run I2C address scanner sketch to verify connections          |

## 📎 Useful Resources
- [ESP32 Arduino Docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [CP210x Driver Download](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
- [ESP-NOW Many-to-One Guide (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp-now-many-to-one-esp32/)
- [Installing the ESP32 Board in Arduino IDE (Random Nerd Tutorials)](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
- [ESP32 SPI Communication (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-spi-communication-arduino/)



