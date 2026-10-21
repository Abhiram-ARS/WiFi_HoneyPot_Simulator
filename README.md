# 📡 Wi-Fi Honey-Pot Simulator
---
> ### **Disclaimer:** 
> *This project is strictly for educational and authorized cybersecurity research; any illegal or unauthorized use, including data theft, OTP interception, or privacy violations, is prohibited. Refer to [DISCLAIMER.md]([https://github.com/Abhiram-ARS/WiFi_HoneyPot_Simulator/Disclaimer.md](https://github.com/Abhiram-ARS/WiFi_HoneyPot_Simulator/blob/main/Disclaimer.md)) for full legal terms and responsibilities.*

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

  * Browser and user-agent information
  * Operating system hints
  * Screen resolution
  * Preferred language
  * Time zone
  * Device capabilities exposed by browser APIs

* **📱 Mobile Number Verification Interface**
  Provides a form for entering a mobile number as part of the simulated authentication flow.

* **🔐 OTP Verification Workflow**
  Demonstrates one-time-password verification using a test OTP or a legitimate verification service.

* **📊 Security Awareness and Analysis**
  Helps demonstrate how captive portals may request information and why users should verify the legitimacy of public Wi-Fi networks.

## 🔄 How It Works

1. **Access Point Initialization**
   The application configures a Wi-Fi access point and broadcasts the configured SSID.

2. **Client Connection**
   A nearby device discovers the SSID and attempts to connect.

3. **Captive Portal Display**
   Network configuration and captive portal detection direct the client to the portal landing page.

4. **Browser Metadata Collection**
   With appropriate notice and consent, the browser provides permitted metadata for demonstration and analysis.

5. **Mobile Number Entry**
   The portal presents a mobile number form.

6. **OTP Verification**
   The user completes a test or legitimate OTP verification flow.

7. **Session Completion**
   The application displays a success or failure status and records only the minimum necessary test data.

## 🧰 Technology Stack

The implementation may use the following technologies, depending on the hardware and platform:

* **Wireless Access Point:** Linux with hostapd or compatible access-point hardware
* **Network Configuration:** dnsmasq or an equivalent DHCP/DNS service
* **Backend:** Python with Flask or FastAPI
* **Frontend:** HTML, CSS, and JavaScript
* **Browser Metadata:** Standard browser APIs and user-agent information
* **OTP Verification:** Mock OTP service or a legitimate verification provider

*These are suggested components; the final stack depends on the implementation.*

## 🛠️ Setup

### Prerequisites

* A compatible Wi-Fi adapter or access-point-capable device
* A Linux environment with the required wireless drivers, if using hostapd
* Python 3
* A supported web browser
* Administrative privileges for authorized access-point configuration

### Installation

Clone the repository:

```bash
git clone https://github.com/<your-username>/wifi-honey-pot-simulator.git
cd wifi-honey-pot-simulator
```

Create and activate a virtual environment:

```bash
python3 -m venv venv
source venv/bin/activate
```

Install dependencies, if a `requirements.txt` file is provided:

```bash
pip install -r requirements.txt
```

Configure the SSID, network interface, portal settings, and test verification mode according to the project's configuration.

Start the application using the command documented by the implementation.

> **Note:** The commands above cover the general application setup. Access-point configuration, network routing, and captive portal integration require platform-specific setup.

## 🔒 Security and Privacy

This project should follow responsible security-testing practices:

* Use only networks and hardware you own or are authorized to administer.
* Display a clear notice before collecting browser or device metadata.
* Request explicit consent before collecting mobile numbers.
* Use mock OTPs or a legitimate verification provider in test environments.
* Never collect, store, or reuse real authentication codes unnecessarily.
* Minimize data collection and retention.
* Do not impersonate real organizations, public hotspots, or trusted login portals.
* Do not capture credentials or sensitive device data without explicit authorization.

## 🎯 Use Cases

* Cybersecurity awareness demonstrations
* Captive portal usability testing
* Wi-Fi security education
* Browser privacy and fingerprinting research
* Security lab experiments
* Demonstrations of social-engineering risks associated with public Wi-Fi

## 🗺️ Future Enhancements

* [ ] Configurable SSID and portal branding
* [ ] Consent screen and privacy notice
* [ ] Device metadata dashboard
* [ ] Mock OTP verification mode
* [ ] Session analytics with anonymized data
* [ ] Exportable lab reports
* [ ] Automatic cleanup of temporary session data
* [ ] Documentation for supported operating systems and hardware

## ⚖️ Legal Disclaimer

This software is provided for educational and authorized cybersecurity research purposes. The maintainers are not responsible for unauthorized deployment, privacy violations, or misuse. Users are responsible for complying with applicable laws, regulations, and consent requirements.

## 🤝 Contributing

Contributions that improve usability, security, documentation, and privacy protections are welcome.

1. Fork the repository.
2. Create a feature branch.
3. Commit your changes.
4. Open a pull request describing the changes.

## 📄 License

Choose an appropriate open-source license, such as the MIT License, and include the corresponding `LICENSE` file in the repository.

---

**Built for cybersecurity education, Wi-Fi security research, and responsible captive portal testing.**
