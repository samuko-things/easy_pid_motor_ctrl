import serial
import time


ser = serial.Serial('/dev/ttyUSB0', 9800, timeout=1)
time.sleep(2)


def getName():
  ser.write(b'n')
  name = ser.readline().decode().strip()
  return name


while True:
  print(getName())
  print(time.time())
  time.sleep(0.001) # wait 1 seconds

ser.close()