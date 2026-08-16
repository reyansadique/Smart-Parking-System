# Smart Parking System using Ultrasonic Sensors

## Overview

The **Smart Parking System using Ultrasonic Sensors** is an embedded-systems project designed to automatically detect parking-slot occupancy and provide real-time information about available parking spaces.

The system uses an ESP32 microcontroller and four HC-SR04 ultrasonic sensors to monitor four parking slots. Each slot is classified as either **FREE** or **OCCUPIED** based on measured distance.

The system provides visual and audible feedback through red/green LEDs, an SSD1306 OLED display, and a buzzer.

## Problem Statement

Traditional parking facilities often require drivers to manually search for available spaces. This can increase parking search time, traffic congestion, and inefficient utilization of parking spaces.

This project demonstrates a low-cost embedded solution for automated parking-slot monitoring.

## Objectives

- Detect parking-slot occupancy automatically.
- Measure distance using ultrasonic sensors.
- Process multiple sensor inputs using an ESP32.
- Calculate the number of available parking slots.
- Display slot status using an OLED.
- Provide red/green LED indications.
- Generate a parking-full buzzer alert.
- Demonstrate embedded GPIO, timing, sensor interfacing, state tracking, and I2C communication.
- Validate the system through virtual simulation.

## Industry Relevance

The same basic concept can be extended to parking systems used in:

- Shopping malls
- Airports
- Hospitals
- Universities
- Offices
- Railway stations
- Residential societies
- Smart-city infrastructure
- Commercial parking facilities

Potential business benefits include reduced parking search time, improved space utilization, automated monitoring, and better customer experience.

## Features

- Four independent parking slots
- Four HC-SR04 ultrasonic sensors
- Real-time FREE/OCCUPIED detection
- Available-slot counting
- Occupied-slot counting
- Green LED for available slot
- Red LED for occupied slot
- SSD1306 OLED display
- Parking-full buzzer
- Serial Monitor diagnostics
- Invalid ultrasonic reading handling
- Adjustable occupancy threshold
- Wokwi virtual simulation
- Modular embedded firmware

## Components Used

| Component | Quantity |
|---|---:|
| ESP32 DevKit | 1 |
| HC-SR04 Ultrasonic Sensor | 4 |
| Green LED | 4 |
| Red LED | 4 |
| 220 Ω Resistor | 8 |
| SSD1306 OLED | 1 |
| Buzzer | 1 |
| Breadboard | 1 |
| Jumper Wires | As required |
| Power Supply | 1 |

## Embedded Systems Concepts

This project demonstrates:

- GPIO configuration
- Digital input/output
- Ultrasonic sensor interfacing
- Trigger and echo timing
- Distance calculation
- Threshold-based classification
- State tracking
- Sensor polling
- I2C communication
- OLED interfacing
- LED control
- Buzzer control
- Serial debugging
- Modular firmware design

## System Architecture

```text
HC-SR04 Sensors
       |
       v
     ESP32
       |
       +----> Slot Detection
       |
       +----> Available Slot Counter
       |
       +----> Red/Green LEDs
       |
       +----> SSD1306 OLED
       |
       +----> Buzzer
```

## Pin Configuration

| Component | GPIO |
|---|---:|
| OLED SDA | 21 |
| OLED SCL | 22 |
| Sensor 1 TRIG | 5 |
| Sensor 1 ECHO | 17 |
| Sensor 2 TRIG | 16 |
| Sensor 2 ECHO | 4 |
| Sensor 3 TRIG | 27 |
| Sensor 3 ECHO | 26 |
| Sensor 4 TRIG | 25 |
| Sensor 4 ECHO | 33 |
| Green LED 1 | 12 |
| Green LED 2 | 14 |
| Green LED 3 | 32 |
| Green LED 4 | 15 |
| Red LED 1 | 2 |
| Red LED 2 | 13 |
| Red LED 3 | 23 |
| Red LED 4 | 18 |
| Buzzer | 19 |

## Distance Calculation

The HC-SR04 measures the round-trip travel time of an ultrasonic pulse.

```text
Distance = (Echo Time × Speed of Sound) / 2
```

For implementation:

```text
distance_cm = echo_time × 0.0343 / 2
```

The division by two is required because the measured time represents the signal traveling from the sensor to the object and back.

## Parking Slot Logic

The project uses a configurable threshold.

Example:

```text
Threshold = 15 cm
```

Logic:

```text
Distance < 15 cm  → OCCUPIED
Distance >= 15 cm → FREE
```

Example:

```text
S1 = 10 cm → OCCUPIED
S2 = 30 cm → FREE
S3 = 12 cm → OCCUPIED
S4 = 35 cm → FREE
```

Result:

```text
Occupied = 2
Available = 2
```

## Folder Structure

```text
Smart-Parking-Ultrasonic-Embedded-System/
│
├── src/
├── arduino_code/
├── simulation/
├── circuit_diagram/
├── data/
├── test_cases/
├── outputs/
├── screenshots/
├── reports/
├── docs/
├── README.md
└── .gitignore
```

## Installation

1. Install Arduino IDE.
2. Install ESP32 board support.
3. Select ESP32 Dev Module.
4. Install Adafruit GFX Library.
5. Install Adafruit SSD1306 Library.
6. Connect the hardware.
7. Verify the pin mapping.
8. Upload the firmware.

## How to Run

1. Power the ESP32.
2. Open Serial Monitor at 115200 baud.
3. Observe ultrasonic distance readings.
4. Place an object in front of a parking sensor.
5. Observe the corresponding slot changing to OCCUPIED.
6. Remove the object.
7. Observe the slot returning to FREE.
8. Occupy all four slots.
9. Verify the parking-full alert.

## Virtual Simulation

The project can be simulated using Wokwi.

Simulation sequence:

```text
All sensors > threshold
        ↓
All slots FREE

Reduce Sensor 1 distance
        ↓
Slot 1 OCCUPIED

Reduce Sensors 2 and 3
        ↓
Available slots decrease

Reduce all sensor distances
        ↓
PARKING FULL
Buzzer ON
```

## Test Cases

| Test | Expected Result |
|---|---|
| All slots free | Available = 4 |
| One occupied | Available = 3 |
| Two occupied | Available = 2 |
| Three occupied | Available = 1 |
| All occupied | Available = 0 |
| Vehicle leaves | Available count increases |
| Invalid echo | Invalid reading handled |
| OLED update | Current state displayed |
| LED update | Correct LED activated |
| Full parking | Buzzer activated |

## Sample Output

```text
Slot 1: Distance = 10.24 cm | State = OCCUPIED
Slot 2: Distance = 31.16 cm | State = FREE
Slot 3: Distance = 12.05 cm | State = OCCUPIED
Slot 4: Distance = 34.20 cm | State = FREE

Occupied Slots: 2
Available Slots: 2
STATUS: SPACE AVAILABLE
```

## Screenshots

Recommended evidence:

- Circuit diagram
- Complete simulation
- All slots free
- Slot 1 occupied
- Multiple occupied slots
- Parking-full condition
- OLED display
- LED indications
- Buzzer
- Serial Monitor
- Source code
- Test results
- GitHub repository
- README

## Results

The system successfully demonstrates real-time monitoring of four parking slots using ultrasonic distance measurement.

The ESP32 processes sensor data, classifies each slot, calculates available parking capacity, updates the OLED display, controls slot LEDs, and activates a buzzer when all slots are occupied.

## Limitations

- HC-SR04 readings can be affected by object angle and environmental conditions.
- Ultrasonic sensors can experience cross-talk when multiple sensors operate simultaneously.
- The occupancy threshold requires calibration.
- This prototype does not include cloud connectivity.
- The prototype does not provide vehicle identification.
- The basic system does not include payment or reservation functionality.

## Future Improvements

Possible extensions include:

- ESP32 Wi-Fi connectivity
- MQTT integration
- Cloud dashboard
- Mobile application
- Automatic barrier gate
- RFID-based vehicle identification
- License plate recognition
- Parking reservation
- Historical occupancy analytics
- Database integration
- Multiple parking-zone monitoring
- Real-time web dashboard
- Sensor fault detection
- OTA firmware updates

## Learning Outcomes

This project provides practical experience with:

- ESP32 programming
- Embedded C/C++
- GPIO
- ultrasonic sensors
- timing measurement
- sensor interfacing
- threshold logic
- state machines
- I2C
- OLED displays
- actuator control
- debugging
- simulation
- Git
- GitHub
- embedded-system documentation

## Author

**Sadique Reyan**

B.Tech Mechanical Engineering Student

Project Area: Embedded Systems / Microcontroller Programming / Sensor Integration

## License

This project is intended for educational and portfolio purposes.
