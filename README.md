# 🚀 My C Programming & F1 Engineering Journey

Welcome! I am **Kerem Can KOÇ** (aka `NeweyJunior`), a Freshman Software Engineering student at **Ankara University**.

This repository documents my progress in learning the **C programming language**. My goal is to combine my passion for **Formula 1** with software engineering to become a **Motorsport Engineer** or **Embedded Systems Engineer**.

Here, I simulate real-world F1 systems, from telemetry processing to race strategy algorithms.

---

## 📂 Project Structure & Highlights

### 🔋 `telemetry_systems`
*Focus: Sensor data processing, error handling, and system monitoring.*

#### 1. 🔋 Battery Management System (`battery_management.c`)
A telemetry simulation for an F1 ERS (Energy Recovery System) battery unit.
* **Features:** Monitors charge levels and health status.
* **Goal:** Ensuring optimal energy deployment during a race lap.

#### 2. 🛠️ IoT Sensor Data Filter (`sensor_data_control.c`)
**Linked List Implementation.** A robust filtering algorithm designed for embedded systems.
* **Function:** Efficiently removes "noise" or invalid readings (e.g., temperature outliers outside the -100°C to +100°C range) from dynamic memory.
* **Usage:** Ideal for simulating data processing in telemetry systems, ECUs, or environmental monitoring stations.

#### 3. 🏎️ 🗂️ F1 Telemetry System Using Struct (`telemetry_structs.c`)
A structured data management system designed to handle driver telemetry.
* **Tech Stack:** Uses **C Structures (structs)** and **Arrays**.
* **Data:** Manages driver info, tyre compounds, and sector times in a modular way.

#### 4. 📡 Telemetry Converter (`telemetry_converter.c`)
A utility tool designed for data analysis.
* **Function:** Converts race data units (e.g., MPH to KPH, Fahrenheit to Celsius) to standard engineering units.

#### 5. 💻 Telemetry Data Filter (`telemetry_filter.c`)
A C-based Linked List filtering system designed to process and store F1 sector times efficiently.

---

### 🏎️ `vehicle_dynamics`
*Focus: Physics-based controls and driver inputs.*

#### 1. 🏎️ F1 Launch Control System (`launch_control.c`)
A simulation of the **Red Bull RB21** launch sequence (Start Procedure).
* **Features:** 🌡️ Engine temperature monitoring, **Anti-Stall System** logic, and RPM-based launch feedback.
* **Concepts:** `If-Else` ladders, Input Validation, and state management.

#### 2. 🕹️ Steering Wheel Simulation (`steering_wheel.c`)
A console-based simulation of a **2026-spec F1 steering wheel** interface.
* **Features:**
    * Implementation of **2026 Regulations** (MOM - Manual Override Mode, Active Aero).
    * Pit Limiter logic with return values.
    * Gearbox memory system and Battery (ERS) management.
* **Concepts:** Switch-Case **State Machine**, Infinite Loops (Real-time polling), Global Variables, and Modular Function Design.

---

### 📊 `race_strategy`
*Focus: Data analysis, strategic decision-making, and simulations.*

#### 1. 💻🧮 F1 Tyre Life and Strategy Simulator (`tyre_life_calc.c`)
*This is my flagship project, evolving from a simple calculator to a complex race strategy simulator.*

**📌 Version 1.3 - Key Improvements (Current)**
* **Data Structure Refactoring:** Implemented a **Global Struct Array** (`Track allTracks[24]`). This allows for **O(1) time complexity** when accessing track data.
* **Standardization:** Moved all physical coefficients to `#define` macros (Clean Code principles).
* **The "5km Rule":** Logic to penalize **Soft compounds** by 25% on tracks longer than 5km (e.g., Spa, Jeddah) to simulate realistic thermal degradation.
* **Accuracy:** Achieves an estimated **88-92% accuracy** in predicting winning strategies compared to 2024/2025 race data.

**📜 Version History:**
* **v1.2:** Implemented `calculateBestStrategy()` to compare **22 different pit-stop strategies** (including 1-stop and 2-stop variations like S-M, S-H, S-S-M). Added physics-based calculations for total race duration.
* **v1.1:** Introduced **"Dynamic Fuel Load"** logic. The car gets lighter lap-by-lap, providing accurate tyre life estimation.
* **v1.0:** Basic tire life calculation based on track data.

#### 2. 🏁 Race Control Panel (`race_control.c`)
A modular C simulation mimicking an F1 Race Engineer's control panel.
* **Features:** Real-time telemetry generation (Engine/Tyres), physics-based calculations (Fuel/Downforce), and interactive system monitoring via a CLI loop.
* **Tech Stack:** Modular Functions, Physics Logic (`math.h`), Stochastic Simulation (`rand`).

#### 3. 🛠️ Pit Stop Strategy (`pit_stop_strategy.c`)
Basic logic for race strategy calculations and decision-making processes regarding pit windows.

#### 4. ⏱️ Lap Time Calculator (`lap_time_calculator.c`)
An algorithm to calculate and analyze sector times and total lap durations (`v1.0` logic).

#### 5. 💻 Telemetry Analysis Program (`average_speed_calculator.c`)
Originally `v1.1`, this tool uses **arrays** to calculate average speeds based on lap time data.

---

### 💾 `algorithms_ds`
*Focus: Computer Science fundamentals and Data Structures.*

#### 1. 💻📅 F1 Race Results Tracker (`race_results_tracker.c`)
**Linked List Implementation.** A C-based project that simulates storing and filtering Formula 1 race results.
* **Scenario:** Tracks **Max Verstappen's** race finishes.
* **Tech:** Demonstrates **dynamic memory allocation** (`malloc`/`calloc`/`free`) and data structure manipulation.
* **Filter Logic:** Applies a filter to keep only the races where the driver scored points (Top 10 finishes), simulating a points-scoring system.

---

## 👨‍💻 About Me
I am an aspiring software engineer focusing on **Clean Code** and **algorithmic logic**. I enjoy solving problems related to physics and racing strategies.

> *"To finish first, first you must finish."*
