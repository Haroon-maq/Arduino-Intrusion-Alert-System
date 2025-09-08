# OSSEC Arduino Intrusion Alert System

## Overview

This project integrates the OSSEC Host-based Intrusion Detection System (HIDS) with an Arduino board to provide a visual alert (LED blinking) when an intrusion is detected. The system uses a Python active response script to send commands to the Arduino over a serial connection.

---

## Components

- **OSSEC HIDS** v3.7.0
- **Arduino Uno** (or compatible)
- **LED** connected to Arduino digital pin 12
- **Python 3** active response script
- Serial connection via `/dev/ttyUSB0` at 9600 baud

---

## Setup

### Arduino Code

The Arduino listens to serial data at 9600 baud. Upon receiving the string `"ALERT\n"`, it blinks the LED three times and sends status messages back over serial for debugging.

---

### OSSEC Configuration

- Edit `/var/ossec/etc/ossec.conf` to add the following active response command:

```xml
<command>
  <name>intrusion_monitor</name>
  <executable>active-response/bin/intrusion_monitor.py</executable>
  <expect>user</expect>
  <timeout_allowed>yes</timeout_allowed>
  <run_as>ossec</run_as>
</command>

<active-response>
  <command>intrusion_monitor</command>
  <location>local</location>
  <level>10</level>
  <timeout>60</timeout>
</active-response>
```
Make sure the Python script intrusion_monitor.py is located at /var/ossec/active-response/bin/ with executable permissions.

Usage & Testing
1. Test Arduino Directly

Configure serial port and send alert command manually:
```
stty -F /dev/ttyUSB0 9600 cs8 -cstopb -parenb
echo -e "ALERT\n" > /dev/ttyUSB0
```
Observe LED blinking and check Arduino output with:

```
minicom -b 9600 -D /dev/ttyUSB0
```
2. Test Python Active Response Script Manually

Run the script as the OSSEC user:
```
sudo -u ossec /usr/bin/env python3 /var/ossec/active-response/bin/intrusion_monitor.py
```
3. Simulate an Intrusion Alert (Trigger OSSEC)

Append a test alert to the monitored log file:
```
3. Simulate an Intrusion Alert (Trigger OSSEC)

Append a test alert to the monitored log file:
```
This should trigger OSSEC to call the active response script, causing the Arduino LED to blink.

Monitoring and Debugging

View Arduino serial output:
```
minicom -b 9600 -D /dev/ttyUSB0
```
Restart OSSEC after config changes:
```
/var/ossec/bin/ossec-control restart
```
