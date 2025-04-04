# IoT-Based Smart Water Conservation System 💧

I have designed and developed a **smart irrigation and water monitoring system** designed using Arduino and multiple sensors, aimed at promoting efficient water usage in agriculture or home gardening. The system monitors environmental conditions such as **soil moisture**, **temperature**, **light intensity**, and **water tank level**, and makes decisions to control water flow and alert users based on the readings.

##  Live Simulation

👉 [Try it on Tinkercad](https://www.tinkercad.com/things/kHJRgUCdXit-water-conservation-system-iot?sharecode=4FAo9Fm678nV1PMf2O9gxzScBN9UI_FH98z7mQTScNc)

---

## 📌 Key Features

- **Soil Moisture Monitoring** – Determines when to water the plants.
- **Temperature Sensor (TMP36)** – Adjusts motor (pump) speed based on ambient temperature.
- **Ultrasonic Sensor** – Detects water tank levels and prevents motor operation during low water.
- **Light Sensor (LDR)** – Adjusts motor behavior based on light intensity.
- **Automated Motor Control** – Varies motor output based on environmental inputs.
- **Visual and Audio Alerts** – Uses RGB LEDs and a buzzer to indicate system status and warnings.
- **LCD Display (I2C)** – Shows live data: moisture %, temperature, light %, and water level status.
- **Serial Monitor Output** – For real-time logs and debugging via Serial Monitor.
- **Safety Mechanism** – Prevents watering if water tank is empty or soil is already moist.

---

##  Tech Stack

- **Arduino UNO**
- **Soil Moisture Sensor**
- **TMP36 Temperature Sensor**
- **Ultrasonic Sensor (HC-SR04)**
- **LDR (Light Dependent Resistor)**
- **I2C LCD Display**
- **LEDs & Buzzer**
- **DC Motors (Pump simulation)**
- **Tinkercad (Simulation Platform)**

---

##  Purpose

Designed with sustainability in mind, this system is intended to:
- Reduce unnecessary water usage
- Automate basic irrigation control
- Alert users in real time when attention is needed
- Provide actionable environmental data to users

This project can serve as a foundation for larger smart agriculture systems or home automation setups.

---
