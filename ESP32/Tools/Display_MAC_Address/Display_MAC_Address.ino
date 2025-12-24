#include <WiFi.h>
#include <esp_wifi.h>

// Function to read and print the MAC address
void readMacAddress(){
  uint8_t baseMac[6]; // Array to store the MAC address
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac); // Get the MAC address of the Wi-Fi station interface
  
  if (ret == ESP_OK) { // Check if MAC retrieval was successful
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]); // Print MAC address in hexadecimal format
  } else {
    Serial.println("Failed to read MAC address"); // Print error message if retrieval fails
  }
}

void setup(){
  Serial.begin(115200); // Initialize serial communication at 115200 baud rate
  
  WiFi.mode(WIFI_STA); // Set Wi-Fi mode to Station (STA)
  WiFi.begin(); // Initialize Wi-Fi (not necessarily connecting to a network)

  Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
  readMacAddress(); // Call function to read and print MAC address
}
 
void loop(){
  // No operations in loop
}


//Press reset if it doesn't work