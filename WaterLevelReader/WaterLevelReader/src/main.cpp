#include <Arduino.h>

const int NUM_SENSORS = 4;
const int SENSOR_PINS[NUM_SENSORS] = {A0, A1, A2, A3};
const int LED_PIN = LED_BUILTIN;
const int THRESHOLD = 1000;

const int WINDOW_SIZE = 10;
const int DRYING_RATE = 50;

bool waterDetected[NUM_SENSORS];
bool drying[NUM_SENSORS];
int history[NUM_SENSORS][WINDOW_SIZE];
int historyIndex[NUM_SENSORS];
bool historyFilled[NUM_SENSORS];
bool prevWaterDetected[NUM_SENSORS];
bool prevDrying[NUM_SENSORS];

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);

  for (int s = 0; s < NUM_SENSORS; s++) {
    pinMode(SENSOR_PINS[s], INPUT);
    waterDetected[s] = false;
    drying[s] = false;
    prevWaterDetected[s] = false;
    prevDrying[s] = false;
    historyIndex[s] = 0;
    historyFilled[s] = false;
    for (int i = 0; i < WINDOW_SIZE; i++) history[s][i] = 0;
  }

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  for (int s = 0; s < NUM_SENSORS; s++) {
    int raw = analogRead(SENSOR_PINS[s]);

    // Store in circular buffer
    history[s][historyIndex[s]] = raw;
    historyIndex[s] = (historyIndex[s] + 1) % WINDOW_SIZE;
    if (historyIndex[s] == 0) historyFilled[s] = true;

    // Calculate drop over the window: oldest reading minus current
    int oldestIndex = historyFilled[s] ? historyIndex[s] : 0;
    int dropOverWindow = history[s][oldestIndex] - raw;

    if (drying[s]) {
      if (raw <= THRESHOLD) {
        drying[s] = false;
      } else if (historyFilled[s] && raw > 500 && dropOverWindow <= 0) {
        drying[s] = false;
        waterDetected[s] = true;
        if (s == 0) digitalWrite(LED_PIN, HIGH);
      }
    } else if (!waterDetected[s] && raw > THRESHOLD) {
      waterDetected[s] = true;
      if (s == 0) digitalWrite(LED_PIN, HIGH);
    } else if (waterDetected[s] && historyFilled[s]) {
      if (dropOverWindow > DRYING_RATE) {
        waterDetected[s] = false;
        drying[s] = true;
        if (s == 0) digitalWrite(LED_PIN, LOW);
      }
    }

    // Serial output per sensor
    Serial.print("S");
    Serial.print(s);
    Serial.print(": ");
    Serial.print(raw);
    Serial.print(" ");
    Serial.print(waterDetected[s] ? "WATER" : (drying[s] ? "DRYING" : "DRY"));
    if (s < NUM_SENSORS - 1) Serial.print(" | ");
  }
  Serial.println();

  delay(500);
}
