#define TRIG_PIN 33
#define ECHO_PIN 32
#define NUM_READINGS 10

float lastValidDistance = -1;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float getDistance() {
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout
  if (duration == 0) return -1;  // No echo or out of range
  return duration * 0.034 / 2;
}

void loop() {
  float distances[NUM_READINGS];
  int validCount = 0;

  // Take multiple readings
  for (int i = 0; i < NUM_READINGS; i++) {
    // Trigger the sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    float dist = getDistance();
    if (dist > 0) {  // Only store valid readings
      distances[validCount++] = dist;
    }

    delay(40);  // Small delay between readings
  }

  if (validCount == 0) {
    // If no valid readings, print last valid distance
    if (lastValidDistance >= 0) {
      Serial.println(lastValidDistance, 2);
    }
    // If no last valid distance, print nothing
  } else {
    // Find min and max
    float minVal = distances[0], maxVal = distances[0];
    for (int i = 1; i < validCount; i++) {
      if (distances[i] < minVal) minVal = distances[i];
      if (distances[i] > maxVal) maxVal = distances[i];
    }

    // Calculate sum excluding min and max if enough data
    float sum = 0;
    int count = 0;
    for (int i = 0; i < validCount; i++) {
      if (validCount > 2 && (distances[i] == minVal || distances[i] == maxVal)) {
        continue;  // Skip outliers
      }
      sum += distances[i];
      count++;
    }

    float average = sum / count;
    lastValidDistance = average;

    // Print only the number, no text
    Serial.println(average, 2);  // 2 decimal places
  }

  // You can reduce or remove this delay if needed
  delay(10);
}
