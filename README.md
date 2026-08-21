# 🔐 Secure Access Control System with Multi-Level Authentication

## 📌 Project Overview

The **Secure Access Control System with Multi-Level Authentication** is an embedded security system designed to prevent unauthorized access by verifying a user through **three levels of authentication**:

**User ID → Password → Fingerprint**

Access is granted only when all three authentication levels are successfully verified. The system is developed using the **LPC2148 ARM7 microcontroller** and integrates a keypad, LCD, EEPROM, fingerprint module, UART communication, and motor-based door mechanism.

---

## 🎯 Objectives

* Prevent unauthorized access using multi-level authentication.
* Verify the user's **User ID** through a keypad.
* Verify the user's **password** stored in EEPROM.
* Authenticate the user using a **fingerprint matching process**.
* Control a door mechanism after successful authentication.
* Provide user feedback through an LCD display.
* Allow authorized users to modify passwords and fingerprints.

---
## 🧩 System Block Diagram

<img width="1536" height="1024" alt="bloclk_dig" src="https://github.com/user-attachments/assets/8a85b714-95cb-4a7f-86d5-9ab0b9887a54" />

---

## 🔑 Authentication Process

The system performs authentication in the following sequence:

```text
             ┌───────────────┐
             │    USER ID    │
             └───────┬───────┘
                     ↓
             ┌───────────────┐
             │   PASSWORD    │
             └───────┬───────┘
                     ↓
             ┌───────────────┐
             │  FINGERPRINT  │
             └───────┬───────┘
                     ↓
          ┌─────────────────────┐
          │ AUTHENTICATION      │
          │     SUCCESS?        │
          └──────┬───────┬──────┘
                 │ YES   │ NO
                 ↓       ↓
          ┌──────────┐  ┌──────────┐
          │  ACCESS  │  │  ACCESS  │
          │ GRANTED  │  │  DENIED  │
          └────┬─────┘  └──────────┘
               ↓
          ┌──────────┐
          │DOOR/MOTOR│
          │ ACTIVATED│
          └──────────┘
```

---

### Main Components

| Component                   | Function                                           |
| --------------------------- | -------------------------------------------------- |
| **LPC2148**                 | Main controller of the system                      |
| **4×4 Keypad**              | User ID and password input                         |
| **R305 Fingerprint Module** | Fingerprint enrollment and verification            |
| **AT25C256 EEPROM**         | Stores the password                                |
| **16×2 LCD**                | Displays system messages and authentication status |
| **L293D**                   | Controls the DC motor                              |
| **DC Motor**                | Simulates the door locking/unlocking mechanism     |
| **Switch**                  | Used for system/menu operations                    |
| **USB-to-UART Converter**   | Used for fingerprint module communication/testing  |

---

## ⚙️ Working Principle

### 1. User ID Verification

Initially, the system waits for the user to enter a **User ID using the 4×4 keypad**.

### 2. Password Verification

After receiving the User ID, the system requests the password.

The entered password is compared with the password stored in **AT25C256 EEPROM**. If the passwords match, the system proceeds to fingerprint authentication.

### 3. Fingerprint Verification

The R305 fingerprint module captures the user's fingerprint and searches its stored fingerprint library for a matching template.

The fingerprint process includes:

1. Capture fingerprint image.
2. Generate a character file.
3. Search the fingerprint library.
4. Compare the captured fingerprint with stored templates.

If the fingerprint matches the specified ID, authentication is successfully completed.

### 4. Door Control

After successful authentication at all three levels, the system activates the door mechanism.

The **DC motor rotates forward to represent door opening**. Reverse rotation represents door closing/locked status.

---

## 🔄 Authentication Flow

```text
        START
          │
          ↓
   Initialize System
          │
          ↓
      Enter User ID
          │
          ↓
   User ID Accepted?
      ┌───┴───┐
     NO      YES
      │        │
      │        ↓
      │   Enter Password
      │        │
      │        ↓
      │  Password Match?
      │     ┌──┴──┐
      │    NO    YES
      │     │      │
      │     │      ↓
      │     │ Fingerprint Scan
      │     │      │
      │     │      ↓
      │     │ Fingerprint Match?
      │     │    ┌──┴──┐
      │     │   NO    YES
      │     │    │      │
      ↓     ↓    ↓      ↓
    Retry  Retry Deny  GRANT
                     │
                     ↓
                 Door Opens
                     │
                     ↓
                 Door Closes
```

## 👆 Fingerprint Management

The system supports fingerprint management through:

* **Fingerprint Enrollment**
* **Fingerprint Deletion**
* **Fingerprint Search/Verification**

During enrollment, the fingerprint image is captured, converted into a character file, and stored as a template in the fingerprint module's flash library.

---
## 📸 Project Demonstration

## 1. Title

<img width="811" height="262" alt="image" src="https://github.com/user-attachments/assets/26253c2e-89d3-40d6-ac04-643dade9bc4b" />

## 2. Main Menu

<img width="934" height="360" alt="image" src="https://github.com/user-attachments/assets/61b000fd-7e76-4a5d-8c6b-f14dc39487a6" />

## 3. Enter UserID

<img width="994" height="360" alt="image" src="https://github.com/user-attachments/assets/4c52a935-280d-45ca-bd24-bfc5f54e9340" />

## 4. Password Verification

<img width="1025" height="368" alt="image" src="https://github.com/user-attachments/assets/fc7e2765-59cf-4ea2-b343-4ade02a208ec" />

## 5. Fingerprint Verification

<img width="1058" height="547" alt="image" src="https://github.com/user-attachments/assets/9bc44acd-19d0-4e71-8ec1-9289071a3b50" />

## 6. Access Granted(Door open)

<img width="1077" height="608" alt="image" src="https://github.com/user-attachments/assets/0774eefb-6d23-4a10-99a7-273d53e1bed7" />

## 7. Door Close

<img width="1135" height="759" alt="image" src="https://github.com/user-attachments/assets/dc421947-5e55-4ab7-8d0b-e80260575c17" />

## 8. Edit Menu

<img width="953" height="334" alt="image" src="https://github.com/user-attachments/assets/63178d11-8f60-45f3-a781-8dc9945923e2" />


## 🛠️ Technologies Used

* **Microcontroller:** LPC2148 ARM7
* **Programming Language:** Embedded C
* **Compiler:** Keil C
* **Programming Tool:** Flash Magic
* **Fingerprint Module:** R305
* **Memory:** AT25C256 EEPROM
* **Display:** 16×2 LCD
* **Input:** 4×4 Keypad
* **Communication:** UART
* **Motor Driver:** L293D
* **Actuator:** DC Motor

---

## ⭐ Key Features

* 🔐 Three-level authentication
* 👤 User ID verification
* 🔑 Password authentication
* 👆 Fingerprint verification
* 💾 EEPROM-based password storage
* 🖥️ LCD-based user interface
* ⌨️ 4×4 keypad input
* 📝 Password modification
* 👆 Fingerprint enrollment and deletion
* 🚪 Motor-based door control
* 🔄 Automatic authentication flow

---

## 📚 Project Applications

This concept can be adapted for:

* Smart door-lock systems
* Office access control
* Laboratory security
* Restricted-area access
* Secure rooms and cabinets
* Industrial access-control systems

---

## 🚀 Future Enhancements

Possible future improvements include:

* Adding an access log with date and time.
* Adding remote monitoring.
* Adding network-based authentication.
* Adding mobile application integration.
* Adding multiple user profiles and access levels.
* Adding encrypted communication between modules.

---

## 👩‍💻 Author

Muktha Bejjaram

B.Tech – Electronics and Communication Engineering

---

## 👨‍💻 Project Summary

This project demonstrates how **Embedded C, ARM7 microcontrollers, EEPROM, UART communication, keypad interfacing, fingerprint authentication, and motor control** can be integrated to build a practical embedded security system.

The main security concept is simple:

> **Access is granted only when the User ID, Password, and Fingerprint are successfully verified.**

---

### 📌 Project Type

**Embedded Systems | ARM7 | Embedded C | Security | Biometric Authentication | Access Control**
