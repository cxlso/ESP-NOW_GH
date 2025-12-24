#include <esp_now.h>
#include <WiFi.h>
#include <AccelStepper.h>

//=========================================
// LED Definitions
#define LED_PIN 8
const unsigned long LED_DURATION = 100; // LED stays ON for 100ms
unsigned long ledOnTime = 0;
bool ledOn = false;

// Stepper Motor Definitions
#define DIR 10  // Direction pin
#define PUL 9  // Pulse (Step) pin
#define ENA 2  // Enable pin

AccelStepper stepper(AccelStepper::DRIVER, PUL, DIR);
long targetPosition = 0; // Target position received via ESP-NOW
//=========================================

// Callback function to handle incoming ESP-NOW data
void OnDataRecv(const esp_now_recv_info* recv_info, const uint8_t *data, int data_len) {
    // Convert received data to a string
    String receivedData = "";
    for (int i = 0; i < data_len; i++) {
        receivedData += (char)data[i];
    }

    // Convert received string to integer position
    targetPosition = receivedData.toInt();
    Serial.print("Received Target Position: ");
    Serial.println(targetPosition);

    // Move stepper motor to target position
    stepper.moveTo(targetPosition);

    // Blink LED to indicate data reception
    digitalWrite(LED_PIN, HIGH);
    ledOnTime = millis();
    ledOn = true;
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);   // Set ESP32 to station mode
    WiFi.begin("", "", 1);  // force channel 1
    WiFi.disconnect();

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv); // Register callback

    // Setup LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Setup stepper motor
    pinMode(ENA, OUTPUT);
    digitalWrite(ENA, LOW); // Enable the driver (LOW = enabled for many drivers)
    stepper.setMaxSpeed(1000);    // Set max speed (steps/sec)
    stepper.setAcceleration(100000); // Set acceleration (steps/sec²)

    Serial.println("ESP-NOW Receiver Ready...");
}

void loop() {
    // Run stepper motor to the latest received position
    if (stepper.distanceToGo() != 0) {
        stepper.run();
    }

    // Turn off LED after LED_DURATION
    if (ledOn && millis() - ledOnTime >= LED_DURATION) {
        digitalWrite(LED_PIN, LOW);
        ledOn = false;
    }
}
