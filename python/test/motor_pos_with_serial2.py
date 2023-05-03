import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import serial
import time
import math


####### ensure connection with serial port #############
ser = serial.Serial('/dev/ttyUSB0', 9800, timeout=0.1)
time.sleep(1)
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

## generate parametric data for drawing a circle
theta = np.linspace( 0 , 2 * np.pi , 90 )
radius = 0.3
A = radius * np.cos( theta )
B = radius * np.sin( theta )
# circle_data = list(zip(A,B))
#--------------------------------------------

figure, ax = plt.subplots( 1 )

def init():
  ax.set_xlim(-0.4, 0.4)
  ax.set_ylim(-0.4, 0.4)
  ax.set_aspect( 1 )

# function that draws each frame of the animation
def animate_motor_pos(data):
  prev_time = time.time()

  tickCount, angPos, frequency, angVel = getAllMotorBData()
  
  a_data = radius * np.cos( round(absAngDeg(angPos),2) * np.pi / 180 )
  b_data = radius * np.sin( round(absAngDeg(angPos),2) * np.pi / 180 )
  
  # ax.clear()
  ax.plot( A, B ) #plt circle
  ax.plot( [0, a_data], [0, b_data] , 'ro-', linewidth=5) # draw line
  
  ax.set_title("Angle = " + str(round(absAngDeg(angPos),2)))
  
  print(time.time() - prev_time)

######################################################################





if __name__ == '__main__':
  # run the animation
  ani = FuncAnimation(fig=figure, func=animate_motor_pos, frames=1, init_func=init, blit=True, interval=5, repeat=True) # interval in ms

  plt.show()