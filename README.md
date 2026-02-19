# 🚀 My C Programming Journey

Welcome! I am a Freshman Software Engineering student at Ankara University.
This repository documents my progress in learning the C programming language. My goal is to combine my passion for **Formula 1** with software engineering to become a Motorsport Engineer. 🏎️

## 📂 Project Highlights

### 1. 🏎️ F1 Launch Control System (`f1LaunchControl.c`)
A simulation of the Red Bull RB21 launch sequence (Start Procedure).
- **Features:** Engine temperature monitoring, **Anti-Stall System** logic, and RPM-based launch feedback.
- **Concepts:** `If-Else` ladders, `Functions`, `Input Validation`, and state management.

### 2. 🔋 Battery Management System (`BatteryManagementSystem.c`)
A telemetry simulation for an F1 ERS (Energy Recovery System) battery unit. It monitors charge levels and health status.

### 3. ⏱️ Lap Time Calculator (`lapTimeCalculatorV1.0.c`)
An algorithm to calculate and analyze sector times and total lap durations.

### 4. 🛠️ Pit Stop Strategy (`pitStopStrategy.c`)
Basic logic for race strategy calculations and decision making processes.

### 5. 📡 Telemetry Converter (`telemetryConverter.c`)
A utility tool designed to convert race data units (e.g., MPH to KPH, Fahrenheit to Celsius) for data analysis.

### 6. 🧮 Calculator (`calculator.c`)
My first project to understand arithmetic operations and user input in C.

### 7. 🕹️🏎️🔴🔵 Steering Wheel (`f1SteeringWheel.c`)
A console-based simulation of a 2026-spec F1 steering wheel interface.
- **Features:** Implementation of **2026 Regulations** (MOM - Manual Override Mode, Active Aero), Pit Limiter logic with return values, Gearbox memory system, and Battery (ERS) management.
- **Concepts:** `Switch-Case` State Machine, `Infinite Loops` (Real-time polling), Global Variables, and Modular Function Design.
---

### 8. 🏁🏎 Race Control Panel (`raceControlPanel.c`) 
Description: A modular C simulation mimicking an F1 Race Engineer's control panel. Features real-time telemetry generation (Engine/Tyres), physics-based calculations (Fuel/Downforce), and interactive system monitoring via a CLI loop.

Tech Stack: C, Modular Functions, Physics Logic (math.h), Stochastic Simulation (rand).

### 9. 💻 Telemetry Analysis Program (`lapTimeCalculatorV1.1.c`)
Description: A telemetry analysis program was developed using arrays in the C language (lap time and average speed calculation).

### 10. 💻🧮 F1 Tyre Life and Strategy Simulator V1.0 (`f1TyreLifeCalculateV1.0.c`)
Description: F1 Tire Life and Strategy Simulator V1.0 calculates tire life based on the track and determine the optimal strategy. The tire life calculation section is implemented in version V1.0, and the strategy determination section will be added in version V1.1.

### 11. 🏎️ 🗂️F1 Telemetry System Using Struct (`f1TelemetrySystemStructs.c`)
Description: A structured data management system designed to handle driver telemetry, tyre compounds, and sector times using C Structures (structs) and Arrays.

### 12. 💻🧮 F1 Tyre Life and Strategy Simulator V1.1 (`f1TyreLifeCalculateV1.1.c`)

**Description:**
This update transforms the V1.0 base model into a more realistic simulation. V1.1 introduces a new physics calculation for fuel load and significantly improves the user interface.

**New Features & Improvements (V1.1):**
* **Physics Engine Upgrade (Fuel & Weight):** Implemented "Dynamic Fuel Load" logic. The simulation now accounts for the car getting lighter lap-by-lap due to fuel burn, providing a much more accurate tire life estimation compared to the static model in V1.0.
* **UI & Usability:** Redesigned the menu structure for a smoother experience. Added a "Small Menu" loop to keep the screen clean during multiple calculations.
* **Polishing:** Corrected spelling errors (Typos) in track data and updated prompts to use professional F1 terminology (e.g., changed "Tyre Type" to "Tyre Compound").

### 13. 💻🧮 F1 Tyre Life and Strategy Simulator V1.2 (`f1TyreLifeCalculateV1.2.c`)
Description: This major update transforms the project from a basic tyre life calculator into a complete Race Strategy Simulator.
What's New in v1.2:
* Strategy Optimization Logic: Implemented calculateBestStrategy() function to determine the fastest race plan.
* Scenario Comparison: The algorithm now simulates and compares 22 different pit-stop strategies (including 1-stop and 2-stop variations like S-M, S-H, S-S-M, M-H-S).
* Total Race Time Calculation: Added physics-based calculations for total race duration, accounting for pit-stop loss (pitWay), tyre degradation, and fuel load.
* Stint Analysis: Introduced helper functions (calculate_1Stop, calculate_2Stop) to simulate specific tyre stints accurately.

### 14. 💻 Telemetry Data Filter (`telemetryDataFilter.c`)
A C-based Linked List filtering system designed to process F1 sector times.

### 15. 💻🧮 F1 Tyre Life and Strategy Simulator V1.3 (`f1TyreLifeCalculateV1.3.c`)
📌 Version 1.3 - Key Improvements and RefactoringFollowing the initial release (v1.2), I have implemented several architectural and logic-based updates to increase both the accuracy of the simulation and the quality of the code.
* 1. Data Structure RefactoringOld (v1.2): Used a complex switch-case block within a function to fetch track data. This was inefficient for large-scale calculations.New (v1.3): Implemented a Global Struct Array (Track allTracks[24]). This allows for $O(1)$ time complexity when accessing track data, leading to a cleaner and more scalable codebase.
* 2. Standardization of ConstantsInstead of using "Magic Numbers" (hardcoded values) inside functions, I have moved all physical coefficients to #define macros.This improvement allows for easy calibration of the entire simulation (e.g., tire wear rates, fuel effects) from a single location at the top of the file, adhering to Clean Code principles.
* 3. Strategy Logic & The "5 km Rule"Problem: In v1.2, Soft compounds were performing unrealistically well on long circuits.Solution: Introduced a conditional logic known as the "5 km Rule". If a track's length exceeds $5\text{ km}$ (e.g., Spa-Francorchamps, Jeddah), a 25% life penalty is applied to Soft compounds. This accurately reflects real-world thermal degradation and forces the simulator to consider more realistic Medium/Hard strategies for longer races.
* 4. Physics and Accuracy CalibrationIdeal Mileage: Adjusted the base idealKm from 190 km to 250 km to better match official Pirelli tire data.Environmental Factors: Refined the WEIGHT_PENALTY and TEMPERATURE_EFFECT coefficients to ensure that heavy fuel loads and high track temperatures influence tire life realistically without causing mathematical instability.Global Variable Bug Fix: Resolved a critical issue where global tire coefficients were being modified during iterations, ensuring every strategy calculation starts with fresh, consistent data.

📈 Accuracy and ResultsBased on comparisons with 2024/2025 race data, version 1.3 achieves an estimated 88-92% accuracy in predicting the winning strategy and total race time for most dry-weather scenarios.


## 👨‍💻 About Me
I am an aspiring software engineer focusing on **Clean Code** and algorithmic logic. I enjoy solving problems related to physics and racing strategies.

---
*Work in progress. Updates are coming!*
