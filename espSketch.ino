#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 columns, 4 rows

// Struct matching 60 bytes from sender
#pragma pack(push, 1)
typedef struct struct_message {
  int temperature;           // 4 bytes TEMP 
  int rHumidity;               // 4 Relative Humidity
  float moisture;              // 4 bytes (was raw2) (Showing 0.0) not M Showing 0 on NOT AQ
  float airQuality;     // 4 bytes Light Intensity 
  float pressure;           // 4 bytes Pressure
  float altitude;           // 4 bytes Altitude
  float accelY;           // 4 bytes NOT AQ Showing 0.00
  float accelZ;           // 4 bytes NOT AQ Showing 0.00
  float  gyroX;            // 4 bytes 
  float gyroY;            // 4 bytes (Showing 0.0)
  float gyroZ;            // 4 bytes
  float unknown2;      // 4 bytes (Showing 0.0 on M) Showing 0 on AQ and INT OR FLOAT X NOT AQ
  float unknown1;         // 4 bytes (used instead of seaLevelPressure) (Showing 0.0) Showing 0 on UV and int X
  float unknown;         // 4 bytes (showing 0.0) showing zero on float and M
  float seaLevelPressure; // 4 bytes () showing zero on int and AQ NOT AQ
}
struct_message;
#pragma pack(pop)

struct_message incomingData;


//  Raw Data Dump
void dumpAsFloats(const uint8_t* data, int len) {
  Serial.println(">>> Interpreting as float[]:");
  for (int i = 0; i < len; i += 4) {
    if (i + 4 <= len) {
      float f;
      memcpy(&f, data + i, sizeof(float));
      Serial.printf("Bytes [%02d-%02d]: %.3f\n", i, i + 3, f);
    }
  }
}

void dumpAsInts(const uint8_t* data, int len) {
  Serial.println(">>> Interpreting as int[]:");
  for (int i = 0; i < len; i += 4) {
    if (i + 4 <= len) {
      int v;
      memcpy(&v, data + i, sizeof(int));
      Serial.printf("Bytes [%02d-%02d]: %d\n", i, i + 3, v);
    }
  }
}

// Display data on LCD
void displayOnLCD() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:" + String(incomingData.temperature) + "\xDF" "C"); // Done

  lcd.setCursor(11, 0);
  lcd.print("M:" + String(incomingData.moisture, 2));

  lcd.setCursor(0, 1);
  lcd.print("AQ:" + String(incomingData.airQuality, 0) + "ppm");

  lcd.setCursor(11, 1);
  lcd.print("RH:" + String(incomingData.rHumidity) + "%");

  lcd.setCursor(0, 2);
  lcd.print("UV:" + String(incomingData.unknown1) + "w/m2" );

  lcd.setCursor(11, 2);
  lcd.print("Li:" + String(incomingData.seaLevelPressure));

  lcd.setCursor(0, 3);
  lcd.print("P:" + String(incomingData.pressure, 0) + "hPa"); //Done
  lcd.setCursor(11, 3);
  lcd.print("At:" + String(incomingData.altitude, 1) + "m"); //Done
}


// Callback when data is received
// void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len) {
//   Serial.print("Received from MAC: ");
//   Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
//                 recv_info->src_addr[0], recv_info->src_addr[1], recv_info->src_addr[2],
//                 recv_info->src_addr[3], recv_info->src_addr[4], recv_info->src_addr[5]);

//   Serial.print("Data length: ");
//   Serial.println(len);

//   Serial.println("Raw data:");
//   for (int i = 0; i < len; i++) {
//     Serial.printf("%02X ", data[i]);
//   }
//   Serial.println();

  // // SEE DECODED VALUES:
  // dumpAsInts(data, len);
  // dumpAsFloats(data, len);

  if (len == sizeof(struct_message)) {
    memcpy(&incomingData, data, sizeof(struct_message));
    displayOnLCD();

     // ✅ Excel Streamer-compatible printout
    Serial.print("DATA,");
    Serial.print(incomingData.temperature); Serial.print(",");
    Serial.print(incomingData.rHumidity); Serial.print(",");
    Serial.print(incomingData.moisture, 2); Serial.print(",");
    Serial.print(incomingData.airQuality, 2); Serial.print(",");
    Serial.print(incomingData.pressure, 1); Serial.print(",");
    Serial.print(incomingData.altitude, 2); Serial.print(",");
    Serial.print(incomingData.accelY, 2); Serial.print(",");
    Serial.print(incomingData.accelZ, 2); Serial.print(",");
    Serial.print(incomingData.gyroX, 2); Serial.print(",");
    Serial.print(incomingData.gyroY, 2); Serial.print(",");
    Serial.print(incomingData.gyroZ, 2); Serial.print(",");
    Serial.print(incomingData.unknown2, 2); Serial.print(",");
    Serial.print(incomingData.unknown1, 2); Serial.print(",");
    Serial.print(incomingData.unknown, 2); Serial.print(",");
    Serial.print(incomingData.seaLevelPressure, 2);
    Serial.println();

  } else {
    Serial.println("Invalid data length!");
  }
}

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for data");

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    lcd.setCursor(0, 1);
    lcd.print("ESP-NOW Error");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing to do here – waiting for ESP-NOW data
}