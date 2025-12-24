#include <AccelStepper.h>

#define DIR 16
#define PUL 17
#define LDR_PIN 33  // LDR analog input pin

AccelStepper stepper(AccelStepper::DRIVER, PUL, DIR);

long targetPosition = 0;
String inputString = "";  // Serial input buffer

// 📉 Smoothing filter for LDR
float alpha = 0.2;           // Smoothing factor
float smoothedValue = 0;

unsigned long lastLdrRead = 0;
const unsigned long ldrInterval = 50; // ms

void setup() {
  Serial.begin(115200);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(10000);

  smoothedValue = analogRead(LDR_PIN); // Initialize filter
}

void loop() {
  // 🌡 Read and smooth LDR every 50ms
  if (millis() - lastLdrRead >= ldrInterval) {
    lastLdrRead = millis();

    int rawValue = analogRead(LDR_PIN);
    smoothedValue = alpha * rawValue + (1 - alpha) * smoothedValue;

    Serial.println((int)smoothedValue);  // Print smoothed LDR value
  }

  // 📥 Handle incoming serial target position commands
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

  // ⚙️ Stepper run
  stepper.run();
}


/*
const int ldrPin = 33;
float alpha = 0.2;     // Smoothing factor (0 = very smooth, 1 = no smoothing)
float smoothedValue = 0;

void setup() {
  Serial.begin(115200);
  smoothedValue = analogRead(ldrPin);  // Initialize with first reading
}

void loop() {
  int rawValue = analogRead(ldrPin);
  smoothedValue = alpha * rawValue + (1 - alpha) * smoothedValue;

  Serial.println((int)smoothedValue);
  delay(50);
}
*/