import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import serial
import time
import math


####### ensure connection with serial port #############
ser = serial.Serial('/dev/ttyUSB0', 9800, timeout=0.1)
# time.sleep(1)
##########################################################




################# SERIAL COMMAND #########################
def absAngDeg(incAngRad):
  incAngDeg = incAngRad * 180.0 / math.pi;
  return incAngDeg % 360.0;

def getAllMotorAData():
  tickCount, angPos, frequency, angVel = (0.00,0.00,0.00,0.00)
  ser.write(b'ALLA')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    tickCount = float(data[0])
    angPos = float(data[1])
    frequency = float(data[2])
    angVel = float(data[3])
    return tickCount, angPos, frequency, angVel
  except:
    return tickCount, angPos, frequency, angVel
  
def getAllMotorBData():
  tickCount, angPos, frequency, angVel = (0.00,0.00,0.00,0.00)
  ser.write(b'ALLB')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    tickCount = float(data[0])
    angPos = float(data[1])
    frequency = float(data[2])
    angVel = float(data[3])
    return tickCount, angPos, frequency, angVel
  except:
    return tickCount, angPos, frequency, angVel
#############################################################




######################## ANIMATION ##########################

fig, ax = plt.subplots()
x, y = [], []
ln, = ax.plot([], [], 'r-')


x_min=0; x_max=2
y_min=-5; y_max=5
TICKS = 10
PAN = 10
start = 0; end = 0
def init():
  global ln, xmin, x_max, y_min, y_max, TICKS, PAN, start, end
  ax.set_xlim(0, PAN)
  start, end = ax.get_xlim()
  ax.xaxis.set_ticks(np.linspace(start, end, TICKS))
  ax.set_ylim(y_min, y_max)
  return ln,


Dt = 0.0; t = time.time()
t0 = time.time();dt = 0.0
def update(i):
  global dt, t, x_min, x_max, y_min, y_max, start, end, TICKS, PAN
  tickCount, angPos, frequency, angVel = getAllMotorBData()

  x.append(dt)
  y.append(angVel)

  start = x[max(i-150+1, 0)] 
  end = start + PAN

  ax.set_xlim(start, end)

  ax.xaxis.set_ticks(np.linspace(start, end, TICKS))

  ln.set_data(x[0:i+1], y[0:i+1])

  dt = time.time()-t

  print(angVel, dt)

  return ln,

ani = FuncAnimation(fig, update, frames=2000,
                    init_func=init, blit=True, interval=1, repeat=False)
plt.show()