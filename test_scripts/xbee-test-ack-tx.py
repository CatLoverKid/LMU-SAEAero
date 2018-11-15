
import random
import sys
import os

from xbee import ZigBee
from serial import Serial
import time


PORT = '/dev/ttyUSB0'
BAUD = 9600
#DEST_ADDR_LONG = "\x00\x13\xA2\x00\x40\xD5\xD3\xD7"
#DEST_ADDR = "\xE5\x3F"
DEST_ADDR_LONG = "\x00\x13\xA2\x00\x40\xD5\xD5\xDD"
DEST_ADDR = "\x17\xF7"
recieved_ack = True

def message_received(data):
	if 'rf_data' in data:
		if data['rf_data'] == "Acknowledgment":
			print "Acknowledgment received"
			global recieved_ack
			recieved_ack = True

ser = Serial(PORT, BAUD)
xbee = ZigBee(ser, callback=message_received, escaped=True) 



while True:
	try:
		if recieved_ack == True:
			xbee.tx(dest_addr = DEST_ADDR, dest_addr_long = DEST_ADDR_LONG, data = "Transmitting")
			recieved_ack = False
	 	time.sleep(1)

	except KeyboardInterrupt:
	        break
ser.close()

