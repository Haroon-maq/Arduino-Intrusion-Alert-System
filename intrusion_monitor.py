#!/usr/bin/env python3
import subprocess
import time

LOG_FILE = "/var/ossec/logs/active-responses.log"
SERIAL_PORT = "/dev/ttyUSB0"

def log(msg):
    with open(LOG_FILE, "a") as f:
        f.write(f"{msg} at {time.strftime('%Y-%m-%d %H:%M:%S')}\n")

def send_alert():
    try:
        log("Starting intrusion_monitor.py")

        # Configure the serial port parameters
        subprocess.run(["stty", "-F", SERIAL_PORT, "9600", "cs8", "-cstopb", "-parenb"], check=True)
        log("Serial port configured")

        # Open the serial port directly and write the ALERT string
        with open(SERIAL_PORT, 'w') as ser:
            ser.write("ALERT\n")
        log("ALERT command sent successfully")

    except Exception as e:
        log(f"Error sending alert: {e}")

if __name__ == "__main__":
    send_alert()
                  
