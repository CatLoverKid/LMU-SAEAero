import random
import sys
import os

from serial import Serial
from xbee import ZigBee

PORT = '/dev/tty.usbserial-DN01ITGV'
BAUD = 9600

ser = Serial(PORT, BAUD)
xbee = ZigBee(ser, escaped=True)

while True:
    try:
        print(xbee.wait_read_frame())
    except KeyboardInterrupt:
        break

ser.close()
