# Goal Line Technology Prototype

## Overview

This project is a **prototype goal-line technology system** that detects when a ball crosses the goal line using **computer vision and a hardware module based on an ESP32-CAM**.

The system captures images with the ESP32-CAM, sends them to a connected computer where a **Python detection script** runs, and determines whether the ball has crossed the goal line. When a goal is detected, the system triggers a **4-digit 7-segment display** that shows **"GOAL"**.

## How It Works

1. The **ESP32-CAM** captures frames from the camera.
2. A **web server written in C** runs on the ESP32, enabling WiFi connectivity and streaming data to a laptop.
3. The laptop processes the video stream using a **Python script with YOLOv3-tiny** for ball detection.
4. The system checks whether the ball crosses the **goal line**.
5. If the ball fully passes the line (either on the ground or above it), a **goal event is triggered**.
6. The **7-segment display** updates and shows **GOAL**.

## Hardware Components

* **ESP32-CAM** – camera module used for capturing frames
* **4-digit 7-segment display** – used to display the message **GOAL**
* **FTDI adapter** – used to connect and program the ESP32-CAM from a laptop

## Software Components

* **C (ESP32)** – used to implement the WiFi connection and web server for data transmission
* **Python** – used for the computer vision pipeline and goal detection
* **YOLOv3-tiny** – lightweight object detection model used to detect the ball

## Detection Logic

The detection system focuses on the **goal line area**.
A goal is detected when the ball **fully crosses the goal line**, regardless of whether it passes along the ground or above it.

When this condition is satisfied, the system triggers the goal event and updates the display to show **GOAL**.

## Purpose

This project demonstrates a **low-cost prototype of goal-line technology**, combining embedded systems and computer vision to automatically detect goal events in football.
