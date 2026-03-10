# Goal Line Technology Prototype

## Overview

This project is a **goal-line technology prototype** that detects when a football crosses the goal line using **computer vision and embedded hardware**.

The system uses an **ESP32-CAM module** to capture images of the goal area. The video stream is transmitted to a laptop through a **WiFi connection**, where a **Python script running a YOLOv3-tiny model** performs ball detection.
When the system determines that the ball has crossed the goal line, a **goal event is triggered** and displayed on a **4-digit 7-segment display**, which shows the message **"GOAL"**.

The project demonstrates a **low-cost implementation of automated goal detection**, combining computer vision, embedded programming, and simple hardware output.

---

## System Architecture

The system is composed of three main components:

1. **Image acquisition**

   * An **ESP32-CAM** captures frames of the goal area.
   * The ESP32 hosts a **web server written in C** that allows the device to connect to WiFi and transmit image data.

2. **Computer vision processing**

   * A **Python script** running on a laptop receives the video stream.
   * The script uses a **YOLOv3-tiny object detection model** to detect the ball in each frame.
   * The algorithm checks whether the detected ball crosses the **goal line region**.

3. **Goal indication**

   * When the ball fully crosses the goal line, the system triggers a **goal event**.
   * The event activates a **4-digit 7-segment display** that shows **GOAL**.

---

## Detection Logic

The detection is based on monitoring the **goal line area** within the camera view.

A goal is registered when the system detects that the **entire ball crosses the goal line**, regardless of whether it passes:

* along the **ground**
* **above the ground**

Once this condition is satisfied, the detection system sends a signal that triggers the display.

---

## Hardware Components

The prototype uses the following hardware:

* **ESP32-CAM**

  * Captures images of the goal area
  * Runs a lightweight **web server written in C**
  * Connects to WiFi and transmits frames to the laptop

* **FTDI Adapter**

  * Used to connect the **ESP32-CAM to the laptop**
  * Provides power and serial communication for programming and operation

* **4-Digit 7-Segment Display**

  * Displays the message **GOAL** when a goal is detected
  * Powered by an **external 5V power supply**

* **Reset Button**

  * Allows the display to be **manually reset** after a goal has been detected

* **5V Power Supply**

  * Provides power to the **7-segment display**

---

## Software Components

The system uses multiple software components:

* **C (ESP32 firmware)**

  * Implements the **WiFi connection**
  * Runs the **web server**
  * Handles image transmission from the ESP32-CAM

* **Python**

  * Processes incoming frames
  * Runs the **object detection algorithm**

* **YOLOv3-tiny**

  * Lightweight neural network used for **real-time ball detection**

---

## Workflow

1. The ESP32-CAM captures images of the goal area.
2. The ESP32 web server streams data to a laptop through WiFi.
3. A Python script receives the frames and runs **YOLOv3-tiny** to detect the ball.
4. The system evaluates whether the ball crosses the **goal line**.
5. If a goal is detected:

   * the **7-segment display shows "GOAL"**
6. The display can be **reset manually using a push button**.

---

## Purpose

This project demonstrates a **low-cost experimental implementation of goal-line technology**, using embedded systems and computer vision to automatically detect goals in football.

The prototype highlights how accessible hardware such as the **ESP32-CAM** combined with **deep learning models** can be used to create practical sports analysis and automation systems.
