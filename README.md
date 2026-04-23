
# ESP32 HC-SR501 PIR Motion Sensor Driver

An interrupt-driven HC-SR501 PIR motion sensor driver for the ESP32 written in C using the ESP-IDF framework and FreeRTOS. 

This project demonstrates how to safely handle hardware interrupts by deferring processing to a main task using FreeRTOS queues, preventing CPU blocking inside the ISR.

## 🛠 Features
* **Interrupt-Driven:** Uses `GPIO_INTR_ANYEDGE` to detect both motion starts and stops without polling.
* **RTOS Integration:** Safely passes hardware events from the ISR to the main application via `xQueueSendFromISR`.
* **Sensor Calibration:** Includes an automatic 30-second initialization delay to prevent false triggers during sensor warmup (typical for PIR sensors).

## 🧰 Hardware Requirements
* ESP32 Development Board
* HC-SR501 PIR Motion Sensor
* Jumper Wires

## 🔌 Wiring
| PIR Sensor Pin | ESP32 Pin |
| :--- | :--- |
| VCC | 5V / 3.3V |
| OUT (Data) | GPIO 13 |
| GND | GND |

## 🚀 How to Run
1. Ensure you have the [ESP-IDF framework](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) installed and configured
2. Clone this repository
3. Wire the sensor according to the table above
4. Build, flash, and monitor the project:
   ```bash
   idf.py build flash monitor
