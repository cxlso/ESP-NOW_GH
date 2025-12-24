#include <AccelStepper.h>

#define DIR 16
#define PUL 17

#define JOY_X 33
#define JOY_Y 32

AccelStepper stepper(AccelStepper::DRIVER, PUL, DIR);

long targetPosition = 0;
unsigned long lastJoystickRead = 0;
const unsigned long joystickInterval = 100; // ms

String inputString = "";  // incoming serial buffer

void setup() {
  Serial.begin(115200);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(10000); // more realistic acceleration
}

void loop() {
  // 🕹 Read joystick every 100 ms
  if (millis() - lastJoystickRead >= joystickInterval) {
    lastJoystickRead = millis();
    int rawX = analogRead(JOY_X);
    int rawY = analogRead(JOY_Y);

    Serial.print(rawX);
    Serial.print(",");
    Serial.println(rawY);
  }

  // 📥 Read serial without blocking
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      targetPosition = inputString.toInt(); // convert when newline is received
      stepper.moveTo(targetPosition);
      inputString = ""; // clear buffer
    } else {
      inputString += inChar; // accumulate chars
    }
  }

  // 🚀 Run motor smoothly
  stepper.run();
}
