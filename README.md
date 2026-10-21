# 📡 Wi-Fi Honey-Pot Simulator
---
> ### ⚠️ **Disclaimer:** 
> *This project is strictly for educational and authorized cybersecurity research; any illegal or unauthorized use, including data theft, OTP interception, or privacy violations, is prohibited. Refer to [DISCLAIMER.md](https://github.com/Abhiram-ARS/WiFi_HoneyPot_Simulator/blob/main/Disclaimer.md) for full legal terms and responsibilities.*

A cybersecurity simulation project that demonstrates how a rogue or honeypot Wi-Fi access point can attract client devices, display a captive portal, collect browser and device metadata, and simulate mobile number verification using an OTP workflow.

## 🚀 Overview

The **Wi-Fi Honey-Pot Simulator** is designed for cybersecurity awareness, network security research, and captive portal testing. It simulates a public Wi-Fi hotspot experience to demonstrate how users interact with unsecured or unfamiliar wireless networks.

The project broadcasts a custom Wi-Fi SSID, redirects connected clients to a captive portal, gathers browser-exposed device information, and presents a mobile number and OTP verification interface.


## ✨ Features

* **📶 Wi-Fi Access Point Simulation**
  Broadcasts a configurable SSID to nearby Wi-Fi-enabled devices.

* **🌐 Captive Portal Redirection**
  Presents a captive portal when a client connects to the simulated access point, subject to device and operating-system behavior.

* **🔎 Browser Fingerprinting / Blueprinting**
  Demonstrates collection of browser-exposed metadata, such as:


* **📱 Mobile Number Verification Interface**
  Provides a form for entering a mobile number as part of the simulated authentication flow.

* **🔐 OTP Verification Workflow**
  Demonstrates one-time-password verification using a test OTP or a legitimate verification service.

## 📃 **Report**
For a detailed explanation of the project, its implementation, workflow, and findings, kindly read the project report.

👉 **[Read the Project Report](https://medium.com/@abhiram--ars/building-wi-fi-evil-twin-honeypot-simulation-cd1d4d9be975?sharedUserId=abhiram--ars)**


## 🧰 Technology Stack

* **ESP32** — Wi-Fi access point and embedded system
* **C++** — Firmware development
   * `<WiFi.h>` — Enables Wi-Fi functionality, such as creating an access point (AP).
   * `<WebServer.h>` — Enables hosting a web server to serve your captive portal pages.
   * `<DNSServer.h>` — Enables DNS server functionality, useful for redirecting domain requests to your captive portal.
* **HTML & CSS** — Web interface and captive portal design
* **Arduino IDE** — Firmware development and uploading



## 🎯 Use Cases

* Cybersecurity awareness demonstrations
* Captive portal usability testing
* Wi-Fi security education
* Browser privacy and fingerprinting research
* Security lab experiments
* Demonstrations of social-engineering risks associated with public Wi-Fi

## 📄 License

Choose an appropriate open-source license, such as the MIT License, and include the corresponding `LICENSE` file in the repository.

---

**Built for cybersecurity education, Wi-Fi security research, and responsible captive portal testing.**
