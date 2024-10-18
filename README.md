# Smart Military Shoes

## Overview

The **Smart Military Shoe System** is an innovative footwear designed for modern warfare to enhance soldiers' situational awareness and provide real-time feedback. It helps soldiers detect mines, track their location, monitor health vitals (heartbeat and SpO2), and maintain balance in challenging terrains. This smart system aims to improve safety and performance on the battlefield.

## Features

### 1. Mine Detection and Disabling

- Equipped with a metal detector sensor that identifies metal objects like mines.
- The system alerts the soldier via a buzzer when a mine is detected.

### 2. Location Tracking

- Includes a GPS module that periodically tracks the soldier’s location.
- Location data is sent to a specific phone number via SMS using the SIM800L 2G module.

### 3. Health Monitoring

- The shoe system is equipped with a MAX30100 sensor to measure the soldier’s heartbeat and SpO2 levels.
- Provides real-time monitoring of vital signs to assess health conditions.

### 4. Balancing Spikes

- Retractable spikes deployed from the sole help soldiers maintain balance in muddy or uneven terrains.
- Automatically adjusts based on the terrain conditions for better stability.

## Components

- **Arduino Uno**: Microcontroller used to control the sensors and components.
- **Ultrasonic Sensor Module**: Assists in proximity detection.
- **16x2 LCD**: Displays key information such as heartbeat, SpO2 levels, and location data.
- **GPS Module and GSM Module (SIM800L 2G)**: Used for tracking the soldier’s location and sending it via SMS.
- **MAX30100 Pulse Oximeter Sensor**: Monitors blood oxygen levels and heart rate.
- **Soil Moisture Sensor**: Measures water content in the soil to improve traction.
- **Load Cell**: Measures pressure applied to the shoe.
- **Servo Motors**: Used to control the retractable spikes for balance.

## System Flow

The system is designed to:

1. Detect mines and alert the soldier. Also it will disable the mine using plaster of paris
2. Track the soldier’s location and send updates via SMS.
3. Continuously monitor health vitals (heartbeat and SpO2).
4. Deploy balancing spikes when necessary based on the terrain.

---

This project provides a practical solution to the challenges soldiers face in the field by integrating advanced sensors and real-time monitoring in a wearable device.
