

import random
import sys
import os

from xbee import ZigBee
from serial import Serial
import time

PORT = '/dev/ttyUSB1'
BAUD = 9600
DEST_ADDR_LONG = "\x00\x13\xA2\x00\x40\xD5\xD3\xD7"
DEST_ADDR = "\xE5\x3F"
#DEST_ADDR_LONG = "\x00\x13\xA2\x00\x40\xD5\xD5\xDD"
#DEST_ADDR = "\x17\xF7"

ser = Serial(PORT, BAUD)
xbee = ZigBee(ser, escaped=True)
while True:
	try:
	        packet = xbee.wait_read_frame()
		if 'rf_data' in packet:
			if packet['rf_data'] == "Transmitting":
				print packet['rf_data']
				xbee.tx(dest_addr = DEST_ADDR, dest_addr_long = DEST_ADDR_LONG, data = "Acknowledgment")

	except KeyboardInterrupt:
		break

ser.close()
