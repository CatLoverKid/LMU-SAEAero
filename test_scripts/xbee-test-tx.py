import random
import sys
import os

from xbee import ZigBee
from serial import Serial
import time

PORT = '/dev/tty.usbserial-DN01ITGT'
BAUD = 9600
DEST_ADDR_LONG = "\x00\x13\xA2\x00\x40\xD5\xD3\xDE"
DEST_ADDR = "\x94\x86"
#DEST_ADDR_LONG = "\x00\x13\xA2\x00\x40\xD5\xD5\xDD"
#DEST_ADDR = "\x17\xF7"

ser = Serial(PORT, BAUD)
xbee = ZigBee(ser, escaped=True)

while True:
    try:
        xbee.tx(dest_addr=DEST_ADDR, dest_addr_long=DEST_ADDR_LONG, data="Test Message")
        time.sleep(1)
    except KeyboardInterrupt:
        break

ser.close()
