from tkinter import *
import time
from math import sin, cos, radians, pi
import numpy as np
import serial


####### ensure connection with serial port #############
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.1)
##########################################################

################# SERIAL COMMAND #########################
def absAngDeg(incAngRad):
  incAngDeg = incAngRad * 180.0 / pi;
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
  


def getMotorAData():
  angPos, angVel = (0.00,0.00)
  ser.write(b'allA')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    angPos = float(data[0])
    angVel = float(data[1])
    return angPos, angVel
  except:
    return angPos, angVel
def getMotorBData():
  angPos, angVel = (0.00,0.00)
  ser.write(b'allB')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    angPos = float(data[0])
    angVel = float(data[1])
    return angPos, angVel
  except:
    return angPos, angVel
  

def getMotorData():
  angPosA,angVelA, angPosB, angVelB = (0.00,0.00,0.00,0.00)
  ser.write(b'all')   # send a single byte
  
  try:
    allData = ser.readline().decode().strip().split(',')
    angPosA = float(allData[0])
    angVelA = float(allData[1])
    angPosB = float(allData[2])
    angVelB = float(allData[3])
    return angPosA, angVelA, angPosB, angVelB
  except:
    return angPosA, angVelA, angPosB, angVelB
  



def sendPwmA(pwm):
  cmd = 'pwmA,'+str(pwm)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False 
def sendPwmB(pwm):
  cmd = 'pwmB,'+str(pwm)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False
#############################################################












###############################################################

W=500
H=400
# w=300
# h=300

root = Tk()
root.title('draw shapes')
root.geometry(f"{W}x{H}")



motorOnDelay = 2 #sec
motorOnTime = time.time()
motorOn = False
def sendPwmCtrl():
    global motorOn, motorOnTime
    if motorOn:
      isSuccess = sendPwmB(0)
      if isSuccess:
        motorOn = False
        print('Motor off', isSuccess)
    else:
      isSuccess = sendPwmB(100)
      if isSuccess:
        motorOn = True
        motorOnTime = time.time()
        print('Motor On', isSuccess)
    
    

button = Button(root,
	text = 'SEND PULSED CTRL',
	command = sendPwmCtrl)  
button.pack()  



myCanvas = Canvas(root, width=300, height=300, bg='white')
myCanvas.pack(pady=10, padx=10)

circle = myCanvas.create_oval(5,5,295,295, outline="green", width=5)
r = 150 # circle radius
m = 150

min_theta = 0
stepTimeMs = 1
def draw_motor_ang_pos():
  global line, stepTimeMs, t, motorOn, motorOnTime
  if motorOn and motorOnDelay < time.time()-motorOnTime:
      isSuccess = sendPwmB(0)
      if isSuccess:
        motorOn = False
        print('Motor off', isSuccess)
  # root.update_idletasks()
  myCanvas.delete(line)
  angPosA, angVelA, angPosB, angVelB = getMotorData()
  theta = round(absAngDeg(angPosB),2)
  line = myCanvas.create_line(m,m, 
                              m+r*cos(radians(theta)), 
                              m+r*sin(radians(theta)), 
                              fill='blue',width=10)
  # print(time.time()-t)
  t = time.time()
  myCanvas.after(stepTimeMs, draw_motor_ang_pos)


t = time.time()
line = myCanvas.create_line(m,m, m+r*cos(radians(min_theta)), m+r*sin(radians(min_theta)), fill='blue',width=10)
draw_motor_ang_pos()

root.mainloop()

###############################################################



