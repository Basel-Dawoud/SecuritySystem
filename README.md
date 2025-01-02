# Door Locker Security System

This project implements a secure, microcontroller-based **Door Locker Security System** using two main components: a **Human Machine Interface (HMI)** module and a **Control Electronic Control Unit (ECU)** module. The system allows users to set and verify passwords for accessing a secure area, with feedback mechanisms for incorrect attempts and additional security measures.

---

## Features

- **Password Management**:
  - Set a new password.
  - Re-enter the password for confirmation.
  - Change an existing password.
- **Door Control**:
  - Unlock, lock, and stabilize the door based on user input.
- **Security Measures**:
  - Buzzer activation after 3 consecutive incorrect password attempts.
  - Secure password storage using an external EEPROM.
- **User Interface**:
  - LCD display for user prompts and status updates.
  - Keypad input for password entry and system interaction.
- **Modular Design**:
  - Separate HMI and Control ECU modules for clear functionality.

---

## System Overview

### HMI Module
The HMI module serves as the interface between the user and the system. It provides options to enter passwords and interact with the door lock system.

#### Key Components:
- **LCD Display**: Displays messages and prompts.
- **Keypad**: Takes user input.
- **UART Communication**: Facilitates communication with the Control ECU.

---

### Control ECU Module
The Control ECU module handles security logic, motor control, and password storage. It communicates with the HMI module and operates hardware components like the motor and buzzer.

#### Key Components:
- **EEPROM**: Stores passwords securely.
- **DC Motor**: Controls door locking and unlocking.
- **Buzzer**: Alerts after multiple incorrect password attempts.
- **UART Communication**: Receives commands from the HMI module.
- **TWI/I2C**: Handles EEPROM communication.

---

## Files Overview

### HMI Module
- `HMI_ECU_AppFile.c`: Main application file for the HMI.
- `keypad.c/h`: Keypad driver.
- `lcd.c/h`: LCD driver.
- `uart.c/h`: UART driver for communication.
- `timer1.c/h`: Timer driver for delays.
- `PasswordEntry.c/h`: Handles password-related operations.
- `common_macros.h`, `std_types.h`: Standard utilities.

### Control ECU Module
- `CONTROL_ECU_AppFile.c`: Main application file for the Control ECU.
- `DCMotor.c/h`: DC Motor driver for door control.
- `bzzer.c/h`: Buzzer driver.
- `external_eeprom.c/h`: EEPROM driver for secure storage.
- `adc.c/h`: ADC driver for potential sensor integration.
- `PWM.c/h`: PWM driver (optional for advanced motor control).
- `uart.c/h`: UART driver for communication.
- `twi.c/h`: TWI/I2C driver.
- `security_functions.c/h`: Contains security-related functionality.
- `common_macros.h`, `std_types.h`: Standard utilities.

---

## How It Works

1. **System Initialization**:
   - The HMI module initializes the LCD, UART, and Keypad.
   - The Control ECU initializes UART, EEPROM, and motor drivers.

2. **Password Setup**:
   - User sets a password via the HMI.
   - Password is confirmed and sent to the Control ECU for storage in EEPROM.

3. **Door Control**:
   - User chooses to unlock the door or change the password.
   - HMI sends commands to the Control ECU.
   - The Control ECU controls the motor to unlock or lock the door.

4. **Security Alerts**:
   - After 3 incorrect password attempts, the buzzer is activated for a security alert.

---

## Hardware Requirements

- Microcontrollers (e.g., AVR)
- LCD (16x2)
- Keypad (4x4)
- DC Motor
- Buzzer
- External EEPROM (e.g., AT24CXX series)
- UART Communication setup
- Power Supply

---

## Installation and Setup

1. Clone the repository or copy the source files.
2. Load the HMI and Control ECU source files into their respective microcontroller projects.
3. Configure the hardware connections as described in the `main.c` files.
4. Compile and flash the code onto the microcontrollers.
5. Power the system and interact with the HMI module.

---

## Future Enhancements

- Add support for biometric authentication.
- Integrate a real-time clock for logging access times.
- Implement a mobile app interface for remote control.
- Expand the system to control multiple doors.

---

## Author
**Basel Dawoud**  
Developed as a demonstration of embedded systems and secure access control.
Contact: baseldawoud2003@gmail.com
