# INDUCTION-MOTOR-PROTECTION-USING-ARDUINO

This project involves a control system for a motor, incorporating various sensors to monitor and control its operation based on temperature, current, and vibration levels. The system is designed using an Arduino microcontroller.

## Table of Contents

- [Pin Assignments](#pin-assignments)
- [Setup](#setup)
- [Loop](#loop)
- [Functions](#functions)
  - [checkTemperature](#checktemperature)
  - [checkCurrent](#checkcurrent)
  - [checkVibration](#checkvibration)
  - [calculateRPM](#calculaterpm)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Pin Assignments

- `ENA`: Pin 3 (Enable motor A)
- `IN1`: Pin 4 (Motor A input 1)
- `IN2`: Pin 5 (Motor A input 2)
- `voltageSensorPin`: Analog Pin A0 (Voltage sensor)
- `currentSensorPin`: Analog Pin A1 (Current sensor)
- `vibrationSensorPin`: Digital Pin 8 (Vibration sensor)
- `resetButtonPin`: Digital Pin 7 (Reset button)
- `temperatureSensorPin`: Analog Pin A2 (Temperature sensor)

## Setup

The `setup` function initializes the motor control pins as outputs and sets up the vibration sensor and reset button as inputs with pull-up resistors. Serial communication is also initialized for debugging purposes.

## Loop

The `loop` function continuously monitors the motor's operation and environmental conditions. It checks for vibration, temperature, and current levels to ensure safe operation. It adjusts motor speed and provides real-time data such as voltage, current, and RPM (Rotations Per Minute).

## Functions

### checkTemperature

Monitors the temperature using an LM35D temperature sensor connected to `temperatureSensorPin`. It stops the motor if the temperature exceeds a preset threshold and waits for the reset button to be pressed.

### checkCurrent

Monitors the current drawn by the motor using a current sensor connected to `currentSensorPin`. It stops the motor if the current exceeds a preset threshold and waits for the reset button to be pressed.

### checkVibration

Monitors the vibration using a vibration sensor connected to `vibrationSensorPin`. It stops the motor if vibration is detected and waits for the reset button to be pressed to resume operation.

### calculateRPM

Calculates the motor's RPM based on pulses received from an encoder. RPM calculation is performed every second and displayed over serial communication.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno)
- Motor driver (e.g., L298N)
- LM35D temperature sensor
- Current sensor (e.g., ACS712)
- Vibration sensor (e.g., SW-420)
- Push button
- Connecting wires

## Software Requirements

- Arduino IDE

## Installation

1. Connect the motor driver and sensors to the Arduino board as per the pin assignments.
2. Upload the code to the Arduino using the Arduino IDE.

## Usage

1. Power the Arduino and connected components.
2. Ensure all sensors are correctly calibrated and connected.
3. Press the reset button to initialize the system.
4. The system will monitor motor operation and environmental conditions continuously.
5. Monitor the serial monitor for real-time data such as temperature, current, and RPM.
6. Press the reset button to reset the system if any abnormal conditions are detected.

## License

This project is licensed under the MIT License.
