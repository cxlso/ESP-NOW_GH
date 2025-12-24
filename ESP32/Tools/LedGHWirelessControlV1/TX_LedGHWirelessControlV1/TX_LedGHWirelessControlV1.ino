#include <esp_now.h>
#include <WiFi.h>

// Slave ESP32 MAC Address
uint8_t slaveMAC[] = { 0x5C, 0x01, 0x3B, 0x74, 0x56, 0x68 };

// ESP-NOW Peer Info
esp_now_peer_info_t peerInfo;

// Buffer for received serial data
String receivedData = "";
String lastSentData = "";

// Variable to store the last sent message for printing in callback
String lastTransmittedMessage = "";

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Sent: " + lastTransmittedMessage + " | Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Function to send data via ESP-NOW
void sendData(const String &data) {
  // Convert String to char array for ESP-NOW transmission
  uint8_t dataBuffer[250];  // Ensure buffer size is sufficient
  int len = data.length();
  len = len > 250 ? 250 : len;  // Prevent overflow
  memcpy(dataBuffer, data.c_str(), len);

  // Store last sent message for debugging
  lastTransmittedMessage = data;

  // Send data
  esp_err_t result = esp_now_send(slaveMAC, dataBuffer, len);
  if (result != ESP_OK) {
    Serial.println("Error sending data");
  }
}

void setup() {
  Serial.begin(115200);
  
  // Set ESP32 to station mode
  WiFi.mode(WIFI_STA);

  Serial.println("ESPNow Transmitter Initialized");

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback function for sending status
  esp_now_register_send_cb(OnDataSent);

  // Configure peer
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, slaveMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer to ESP-NOW
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  }
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    receivedData = Serial.readStringUntil('\n');  // Read incoming data

    if (receivedData != lastSentData) { // Only send if new data is received
      sendData(receivedData);
      lastSentData = receivedData; // Update last sent data
    }
  }
}
