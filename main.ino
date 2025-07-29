#include "DHT.h"

// Pin Definitions
#define DHT_PIN       2
#define DHT_TYPE      DHT22
#define HEATER_PIN    3
#define BUZZER_PIN    4

// Temperature thresholds (°C)
const float TARGET_TEMP       = 60.0;
const float TOLERANCE         = 2.0;
const float MIN_HEAT_TRIGGER  = 50.0;
const float OVERHEAT_TEMP     = 75.0;

// DHT Sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Define system states
enum class HeaterState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

HeaterState currentState = HeaterState::IDLE;
float temperature = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();
  Serial.println("Heater Control System Initialized.");
}

void loop() {
  temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Error reading temperature from DHT22 sensor.");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  updateState(temperature);
  controlOutputs(currentState);

  delay(2000); // Delay between readings
}

void updateState(float temp) {
  if (temp >= OVERHEAT_TEMP) {
    currentState = HeaterState::OVERHEAT;
  } else if (temp >= (TARGET_TEMP - TOLERANCE) && temp < TARGET_TEMP) {
    currentState = HeaterState::STABILIZING;
  } else if (temp >= TARGET_TEMP && temp <= (TARGET_TEMP + TOLERANCE)) {
    currentState = HeaterState::TARGET_REACHED;
  } else if (temp < MIN_HEAT_TRIGGER) {
    currentState = HeaterState::HEATING;
  } else {
    currentState = HeaterState::IDLE;
  }
}

void controlOutputs(HeaterState state) {
  switch (state) {
    case HeaterState::IDLE:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("State: IDLE. Heater OFF");
      break;

    case HeaterState::HEATING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("State: HEATING. Heater ON");
      break;

    case HeaterState::STABILIZING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("State: STABILIZING. Fine heating...");
      break;

    case HeaterState::TARGET_REACHED:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("State: TARGET REACHED. Heater OFF");
      break;

    case HeaterState::OVERHEAT:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("State: OVERHEAT! Heater OFF. Buzzer ON.");
      break;
  }
}
