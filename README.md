# Heater Control System

## Overview

This project implements a basic heater control system using an Arduino UNO and a DHT22 temperature sensor. The system monitors ambient temperature and switches a heater (simulated by an LED) on or off based on predefined thresholds.

## Features

* Real-time temperature monitoring with DHT22
* Heater control via GPIO with state transitions
* Buzzer warning in Overheat state
* Serial logging of system state and temperature
* LED to simulate heater activity

## System Components

* **Microcontroller:** Arduino UNO
* **Sensors:** DHT22 temperature sensor
* **Actuators:** LED (simulated heater), Buzzer
* **Interface:** USB Serial Monitor

## Connections

| Component    | Pin       |
| ------------ | --------- |
| DHT22        | Digital 2 |
| Heater (LED) | Digital 3 |
| Buzzer       | Digital 4 |

## State Logic

* **IDLE**: Temp > Target + Tolerance → Heater OFF
* **HEATING**: Temp < Target → Heater ON
* **STABILIZING**: Temp around Target → Toggle Heater
* **TARGET REACHED**: Temp == Target → Heater OFF
* **OVERHEAT**: Temp >= Overheat Threshold → Heater OFF + Buzzer ON

## Serial Output Example

```
Heater Control System Initialized.
Temperature: 43.30 °C
State: HEATING. Heater ON
Temperature: 74.50 °C
State: IDLE. Heater OFF
```

## How to Run (on Wokwi)

1. Open the simulation link: [Wokwi Simulation](https://wokwi.com/projects/437798686122748929)
2. Click the **Play** button to start the simulation
3. Observe temperature and state logs in the Serial Monitor

## Future Enhancements

* BLE broadcasting via ESP32
* FreeRTOS for task scheduling
* OLED UI and selectable heating profiles
* Cloud logging and mobile app integration

---


