#include <esp_now.h>
#include <WiFi.h>

//=========================================
#define LED_PIN 2
const unsigned long LED_DURATION = 100; // LED stays ON for 100ms
unsigned long ledOnTime = 0;
bool ledOn = false;
//=========================================

// Callback function to handle incoming ESP-NOW data
void OnDataRecv(const esp_now_recv_info* recv_info, const uint8_t *data, int data_len) {
  // Convert MAC address to string format
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           recv_info->src_addr[0], recv_info->src_addr[1], recv_info->src_addr[2], 
           recv_info->src_addr[3], recv_info->src_addr[4], recv_info->src_addr[5]);
  
  // Convert received data to a string
  String receivedData = "";
  for (int i = 0; i < data_len; i++) {
    receivedData += (char)data[i]; // Append each byte as a character
  }

  // Print received information
  Serial.print("From: ");
  Serial.print(macStr);
  Serial.print(" | Data: ");
  Serial.println(receivedData);

  // Blink LED when new data is received
  digitalWrite(LED_PIN, HIGH);
  ledOnTime = millis();
  ledOn = true;
}

void setup() {
  Serial.begin(115200);  // Start serial communication
  WiFi.mode(WIFI_STA);   // Set the ESP32 to station mode
  
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register the callback function to handle incoming data
  esp_now_register_recv_cb(OnDataRecv);
  
  // Setup LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("ESP-NOW Receiver Ready...");
}

void loop() {
  // Turn off LED after LED_DURATION
  if (ledOn && millis() - ledOnTime >= LED_DURATION) {
    digitalWrite(LED_PIN, LOW);
    ledOn = false;
  }
}
