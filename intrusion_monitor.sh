#!/bin/bash

LOG_FILE="/var/ossec/logs/active-responses.log"
SERIAL_PORT="/dev/ttyUSB0"

echo "Intrusion monitor triggered at $(date)" >> "$LOG_FILE"

# Configure the serial port
stty -F "$SERIAL_PORT" 9600 cs8 -cstopb -parenb

# Always send ALERT (ignore OSSEC parameters)
echo "ALERT" > "$SERIAL_PORT"

echo "ALERT sent at $(date)" >> "$LOG_FILE"
