#include <esp_now.h>
#include <WiFi.h>

#define MAX_PEERS 10  // Upper limit for safety

// Struct for combining MAC and ID
struct Device {
  const char* id;
  uint8_t mac[6];
};

// List of devices (Add more here)
Device devices[] = {
  {"A", {0x3C, 0x8A, 0x1F, 0xA0, 0x54, 0x7C}},  // A 3c:8a:1f:a0:54:7c
  {"B", {0x5C, 0x01, 0x3B, 0x74, 0x56, 0x68}},  // B 5c:01:3b:74:56:68
  {"C", {0x5C, 0x01, 0x3B, 0x72, 0xDB, 0xF4}},  // C 5c:01:3b:72:db:f4
};
const int macCount = sizeof(devices) / sizeof(devices[0]);

// Peer info
esp_now_peer_info_t peerInfo;

// Last message tracking
struct LastMessage {
  String data;
};
LastMessage lastMessages[MAX_PEERS];

// Status tracking
struct MessageStatus {
  String data;
  String status;
  char macStr[18];
};
MessageStatus messageStatuses[MAX_PEERS];
int statusCount = 0;

String receivedData = "";

// Callback for send result
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  for (int i = 0; i < macCount; i++) {
    if (memcmp(mac_addr, devices[i].mac, 6) == 0) {
      snprintf(messageStatuses[i].macStr, sizeof(messageStatuses[i].macStr),
               "%02X:%02X:%02X:%02X:%02X:%02X",
               mac_addr[0], mac_addr[1], mac_addr[2],
               mac_addr[3], mac_addr[4], mac_addr[5]);
      messageStatuses[i].data = lastMessages[i].data;
      messageStatuses[i].status = status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail";
      break;
    }
  }

  statusCount++;
  if (statusCount == macCount) {
    // Print summary
    for (int i = 0; i < macCount; i++) {
      Serial.print("MAC ");
      Serial.print(devices[i].id);
      Serial.print(": ");
      Serial.print(messageStatuses[i].macStr);
      Serial.print(" | Data: ");
      Serial.print(messageStatuses[i].data);
      Serial.print(" | Status: ");
      Serial.print(messageStatuses[i].status);
      if (i < macCount - 1) Serial.print(" || ");
    }
    Serial.println();
    statusCount = 0;
  }
}

// Add peer if not already added
void addPeer(const uint8_t *macAddr) {
  memcpy(peerInfo.peer_addr, macAddr, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;
  if (!esp_now_is_peer_exist(macAddr)) {
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Failed to add peer");
    }
  }
}

// Send data to device by index
void sendData(int index, const String &data) {
  uint8_t dataBuffer[250];
  int len = data.length();
  len = len > 250 ? 250 : len;
  memcpy(dataBuffer, data.c_str(), len);

  esp_err_t result = esp_now_send(devices[index].mac, dataBuffer, len);
  lastMessages[index].data = data;

  if (result != ESP_OK) {
    Serial.println("Error sending to " + String(devices[index].id));
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  Serial.println("ESPNow Transmitter Initialized");

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  memset(&peerInfo, 0, sizeof(peerInfo));

  for (int i = 0; i < macCount; i++) {
    addPeer(devices[i].mac);
  }
}

void loop() {
  if (Serial.available() > 0) {
    receivedData = Serial.readStringUntil('\n');
    receivedData.trim();

    int start = 0;
    while (start < receivedData.length()) {
      int sep = receivedData.indexOf(';', start);
      String pair = (sep == -1) ? receivedData.substring(start) : receivedData.substring(start, sep);

      int comma = pair.indexOf(',');
      if (comma != -1) {
        String id = pair.substring(0, comma);
        String value = pair.substring(comma + 1);

        bool found = false;
        for (int i = 0; i < macCount; i++) {
          if (id == devices[i].id) {
            sendData(i, value);
            found = true;
            break;
          }
        }

        if (!found) {
          Serial.println("Unknown ID: " + id);
        }
      }

      if (sep == -1) break;
      start = sep + 1;
    }
  }
}
