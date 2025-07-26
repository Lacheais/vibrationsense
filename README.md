# vibrationsense
# Simple Vibration/Earthquake Sensor using Accelerometers with IoT Integration through Thingspeak

This repository contains the code and architecture of a project to detect vibrations for possible earthquake response. The system utilizes the ESP32 microcontroller, using
its WiFi module to connect to Thingspeak, an IoT platform that allows realtime display of sensor readings and advanced analysis and visualization of collected data.

# Overview
- **Author:** Lacheais
- **Year:** 2025

This work is a simple project for software/hardware integration using IoT.

# Features

- ESP32 with ADXL345 accelerometers for vibration sensing 
- Integrated LED and Buzzer warning signals in case of strong vibrations
- Hardware connected to Thingspeak IoT via WiFi to enable real-time remote monitoring of different sensor units
- Data visualization and analysis using MATLAB Analysis and display through Thingspeak channel
- Warning messages through Outlook in case strong vibration readings are received in a corresponding unit

# Hardware Components
- ESP32
- 5V Buzzer
- 5V LED lights (Green and Red)
- ADXL345 Accelerometer
- PCB Board


#  Project Structure

vibrationsense/
├── Photos/ # Document photos of the project
├── 1stlocation_warn.txt/ # MATLAB code for IoT email warnings 1
├── 2ndlocation_warn.txt/ # MATLAB code for IoT email warnings 2
├── Esp32_code_vibsense.ino/ # Arduino/ESP32 Code (C/C++) to be run in Arduino IDE
├── README.md # Project description
*code contains variables such as channel IDs and API keys which are different for each project, please check your own copies 
