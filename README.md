# 🔐 Secure Access Control System with Multi-Level Authentication

## 📌 Project Overview

The **Secure Access Control System with Multi-Level Authentication** is an embedded security system designed to prevent unauthorized access by verifying a user through **three levels of authentication**:

**User ID → Password → Fingerprint**

Access is granted only when all three authentication levels are successfully verified. The system is developed using the **LPC2148 ARM7 microcontroller** and integrates a keypad, LCD, EEPROM, fingerprint module, UART communication, and motor-based door mechanism.

### 🖼️ Project Overview

![Secure Access Control System](a_clean_infographic_readme_style_project_poster.png)

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

## 🧩 System Block Diagram

![System Block Diagram](a_clean_infographic_readme_style_project_poster.png)

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

These hardware requirements are specified in the project document.

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

The project document specifies that failed authentication results in a failure message on the LCD and the system returns to waiting for User ID input.

---

## 🔧 Password Management

The system also supports password modification.

The password editing process is:

```text
Enter Current Password
          ↓
   Verify Password
          ↓
   Enter New Password
          ↓
 Confirm New Password
          ↓
 New Password == Confirm?
       ┌──┴──┐
      YES    NO
       │      │
       ↓      ↓
 Save to    Keep Old
 EEPROM     Password
```

The new password is stored in EEPROM only when the new password and confirmation password match.

---

## 👆 Fingerprint Management

The system supports fingerprint management through:

* **Fingerprint Enrollment**
* **Fingerprint Deletion**
* **Fingerprint Search/Verification**

During enrollment, the fingerprint image is captured, converted into a character file, and stored as a template in the fingerprint module's flash library.

---

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

The software requirements listed in the project document are Embedded C, Keil-C compiler, and Flash Magic.
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

## 👨‍💻 Project Summary

This project demonstrates how **Embedded C, ARM7 microcontrollers, EEPROM, UART communication, keypad interfacing, fingerprint authentication, and motor control** can be integrated to build a practical embedded security system.

The main security concept is simple:

> **Access is granted only when the User ID, Password, and Fingerprint are successfully verified.**

---

### 📌 Project Type

**Embedded Systems | ARM7 | Embedded C | Security | Biometric Authentication | Access Control**
