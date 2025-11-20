// Transmitter (Tx) - ESP32
#include <esp_now.h>
#include <WiFi.h>

#define input_pin1 34
#define input_pin2 35
#define SAMPLE_RATE 500  // Hz
#define SEND_INTERVAL_US (1000000 / SAMPLE_RATE)

typedef struct struct_message {
  int sensor1;
  int sensor2;
} struct_message;

struct_message dataToSend;

// Ganti dengan MAC address ESP32 Receiver (Rx)
uint8_t receiverAddress[] = {0xE8, 0x6B, 0xEA, 0xD4, 0xD4, 0xF4}; // <- Sesuaikan

esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init gagal");
    return;
  }

  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Gagal menambahkan peer");
    return;
  }

  Serial.println("Transmitter ESP-NOW siap.");
}

void loop() {
  static unsigned long lastSendTime = 0;
  unsigned long now = micros();

  if (now - lastSendTime >= SEND_INTERVAL_US) {
    lastSendTime = now;

    dataToSend.sensor1 = analogRead(input_pin1) * 1000 / 4095;
    dataToSend.sensor2 = analogRead(input_pin2) * 1000 / 4095;

    esp_now_send(receiverAddress, (uint8_t *)&dataToSend, sizeof(dataToSend));
  }
}
