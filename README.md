# OSSEC Arduino Intrusion Alert System

## Overview

This project integrates the OSSEC Host-based Intrusion Detection System (HIDS) with an Arduino board to provide a visual alert (LED blinking) when an intrusion is detected. The system uses a Python active response script to send commands to the Arduino over a serial connection.

---

## Components

- **OSSEC HIDS** v3.7.0
- **Arduino Uno** (or compatible)
- **LED** connected to Arduino digital pin 12
- **Bash** active response script
- Serial connection via `/dev/ttyUSB0` at 9600 baud

---
## Hardware (Arduino Uno)
![20250908_013635](https://github.com/user-attachments/assets/163026d2-211f-4062-b1ec-d427d85d5ec3)


## Setup

### Arduino Code

The Arduino listens to serial data at 9600 baud. Upon receiving the string `"ALERT\n"`, it blinks the LED three times and sends status messages back over serial for debugging.

---

### OSSEC Configuration

- Edit `/var/ossec/etc/ossec.conf` to add the following active response command:

```xml
<command>
    <name>intrusion_monitor</name>
    <executable>intrusion_monitor.sh</executable>
    <expect></expect>
    <timeout_allowed>yes</timeout_allowed>
  </command>

  <active-response>
    <command>intrusion_monitor</command>
    <location>local</location>
    <level>7</level>
    <timeout>60</timeout>
  </active-response>

```
Run the Ossec:
```
sudo /var/ossec/bin/ossec-control start  
```
<img width="658" height="477" alt="ossec_running" src="https://github.com/user-attachments/assets/b89da9d0-4694-491a-afce-81a4811b063e" />





- **Make sure the Bash script intrusion_monitor.sh is located at /var/ossec/active-response/bin/ with executable permissions.**

### Usage & Testing
1. Test Arduino Directly

Configure serial port and send alert command manually:
```
stty -F /dev/ttyUSB0 9600 cs8 -cstopb -parenb
echo -e "ALERT\n" > /dev/ttyUSB0
```
https://github.com/user-attachments/assets/779a187a-e9a6-45eb-a183-84e0aa2cbe11

Observe LED blinking and check Arduino output with:

```
minicom -b 9600 -D /dev/ttyUSB0
```
https://github.com/user-attachments/assets/8bc490dc-955b-4ecc-8e9e-fd0249867087

3. Simulate an Intrusion Alert (Trigger OSSEC)
   Append a test alert to the monitored log file:
App<img width="1238" height="475" alt="alert_trigger" src="https://github.com/user-attachments/assets/8dad67d7-ac24-44ad-854f-3b899664acf5" />

This should trigger OSSEC to call the active response script, causing the Arduino LED to blink.
Use this command to generate ``` logger -p auth.info "this is a test ALERT_TRIGGER" ```





https://github.com/user-attachments/assets/b99c7666-c71f-4a4d-8583-a8570e40f217







