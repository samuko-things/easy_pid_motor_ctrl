
import serial
import time
import math

# '/dev/ttyUSB0'


ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.1)
time.sleep(5)

cmd_str = "mode,0"
data = ""
while data == "":
  ser.write(cmd_str.encode())   # send a single or multiple byte
  data = ser.readline().decode().strip()
print(data)

cmd_str = "pwm,90,0"
data = ""
while data == "":
  ser.write(cmd_str.encode())   # send a single or multiple byte
  data = ser.readline().decode().strip()
print(data)

time.sleep(2)

cmd_str = "pos"
data = ""
while data == "":
  ser.write(cmd_str.encode())   # send a single or multiple byte
  data = ser.readline().decode().strip()
print(data)

cmd_str = "pwm,250,0"
data = ""
while data == "":
  ser.write(cmd_str.encode())   # send a single or multiple byte
  data = ser.readline().decode().strip()
print(data)

time.sleep(2)

cmd_str = "pos"
data = ""
while data == "":
  ser.write(cmd_str.encode())   # send a single or multiple byte
  data = ser.readline().decode().strip()
print(data)

time.sleep(2)

cmd_str = "mode,1"
data = ""
while data == "":
  ser.write(cmd_str.encode())   # send a single or multiple byte
  data = ser.readline().decode().strip()
print(data)