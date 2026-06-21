# IoT Smart Switch via SinricPro (NodeMCU + Arduino)

An internet-of-things (IoT) smart automation project utilizing a **NodeMCU (ESP8266)** alongside an **Arduino Uno/Nano** to control electronic appliances remotely through voice assistants (like Alexa or Google Home) using the cloud platform **SinricPro**.

---

## 🚀 System Architecture & Logic Flow

This system splits its responsibilities across two processing architectures to maximize runtime stability:
1. **NodeMCU (ESP8266):** Handles network requests, maintains Wi-Fi connections, authenticates with SinricPro API web-sockets, and translates changes into string-commands.
2. **Arduino:** Operates completely offline, processes serial strings received from NodeMCU, and safely sets active-low pins for physical mechanical relays.

---

## 🛠️ Hardware Requirements

* **NodeMCU (ESP8266)** - 1x
* **Arduino Board** (Uno, Nano, or Mega) - 1x
* **5V Relay Module** (Active-Low configuration) - 1x
* Jumper wires & power supplies

---

## 📌 Schematic Wiring Matrix

### 1. Inter-Board Serial Communication
To allow communication between both microcontrollers, bridge them together using these precise assignments:

| NodeMCU Pin | Arduino Pin | Description |
| :---: | :---: | :---: |
| **TX** | **RX (D0)** | NodeMCU transmits commands to Arduino |
| **GND** | **GND** | Shared common ground plane reference (**Mandatory**) |

> ⚠️ **Important Warning:** Unplug the **TX-to-RX** connection between the NodeMCU and Arduino whenever you are uploading code via USB from your PC. Leaving them connected will cause communication cross-talk and crash the upload process.

### 2. Arduino to Relay Connection
| Arduino Pin | Relay Terminal Module |
| :---: | :---: |
| **D5** | **IN / Signal** |
| **5V** | **VCC** |
| **GND**| **GND** |

---

## 💻 Installation & Environment Setup

1. Open the **Arduino IDE** and ensure you have installed the **SinricPro** library via the Library Manager (`Sketch` -> `Include Library` -> `Manage Libraries...`).
2. Make sure you have downloaded the **ESP8266 Core boards** extension inside your preferences.
3. Open `NodeMCU_Code.ino` and replace the credentials with your unique wireless configurations and device identifiers:
   ```cpp
   #define WIFI_SSID "Your_Wi-Fi_Name"
   #define WIFI_PASS "Your_Wi-Fi_Password"
   #define APP_KEY   "Your_SinricPro_App_Key"
   #define APP_SECRET "Your_SinricPro_Secret"
   #define device_ID_1 "Your_SinricPro_Device_ID"
   ```
4. **Compile & Upload:** Select the correct board model for each chip (`NodeMCU 1.0` for the ESP8266 and your specific model for the Arduino, such as `Arduino Uno`) along with their respective COM ports, then hit the **Upload** button.

> ⚠️ **Important Reminder:** Ensure the **TX to RX** bridge cable between the two boards is completely disconnected while uploading. If it remains connected, the serial transfer from your PC will fail.

---

## 🛠️ Troubleshooting & Hardware Tips

* **Shared Common Ground:** If the Arduino ignores the commands sent by the NodeMCU, double-check that a ground wire (`GND`) links both boards together. Without a shared ground reference, the serial voltage signals cannot be interpreted correctly.
* **Powering the Relays:** Relays pull significant current when switching. Avoid powering your 5V relay module entirely off the NodeMCU's onboard pins. Let the Arduino handle the relay's 5V/GND power rails directly.
* **SinricPro Status:** Check the Serial Monitor on your NodeMCU (at 9600 baud) during boot. If it stalls or fails to connect, verify your Wi-Fi credentials and ensure your SinricPro tokens exactly match your online dashboard.

---

## 🛡️ License

Developed with ❤️.
