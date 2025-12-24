#include <AccelStepper.h>

#define DIR 16
#define PUL 17

#define TRIG_PIN 33  // 🔼 Trigger pin
#define ECHO_PIN 32  // 🔽 Echo pin

AccelStepper stepper(AccelStepper::DRIVER, PUL, DIR);

long targetPosition = 0;
unsigned long lastSensorRead = 0;
const unsigned long sensorInterval = 100; // ms

String inputString = "";  // incoming serial buffer

// 📊 Noise filter: simple moving average
const int numSamples = 5;
float readings[numSamples];
int readIndex = 0;
float total = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(10000); // realistic acceleration

  // Initialize readings to zero
  for (int i = 0; i < numSamples; i++) {
    readings[i] = 0;
  }
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout at 30ms
  if (duration > 0) {
    return duration * 0.034 / 2;  // Convert to cm
  }
  return -1;  // Invalid reading
}

float getFilteredDistance() {
  float distance = getDistance();
  if (distance > 0) {
    // Remove the oldest reading
    total -= readings[readIndex];
    // Add the new one
    readings[readIndex] = distance;
    total += distance;
    // Move to next index
    readIndex = (readIndex + 1) % numSamples;

    return total / numSamples;  // Return average
  }
  return -1;
}

void loop() {
  // 📡 Read and filter ultrasonic sensor every 100 ms
  if (millis() - lastSensorRead >= sensorInterval) {
    lastSensorRead = millis();
    float filteredDistance = getFilteredDistance();
    if (filteredDistance > 0) {
      Serial.println(filteredDistance, 2);  // Print cleaned distance
    }
  }

  // 📥 Read serial for motor commands
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      targetPosition = inputString.toInt();
      stepper.moveTo(targetPosition);
      inputString = "";
    } else {
      inputString += inChar;
    }
  }

  // 🚀 Run the stepper
  stepper.run();
}
