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










W=640
H=700
w=600
h=400

root = Tk()
root.title('draw shapes')
root.geometry(f"{W}x{H}")


doPlotDelay = 2 #sec
doPlotTime = time.time()
doPlot = False

clearPlot = False

def tryPlot():
    global doPlot, doPlotTime, clearPlot
    if clearPlot:
        deletePlot(plotLineBuffer)
        button['text'] = 'START PLOT'
        clearPlot = False
        time.sleep(0.5)

    elif doPlot:
        doPlot = False 
        print('stop plot')
    else:
        doPlot = True 
        doPlotTime = time.time()
        print('start plot')
    

def deletePlot(lines):
    for line in lines:
        myCanvas.delete(line)
        root.update_idletasks()

button = Button(root,
	text = 'START PLOT',
	command = tryPlot)  
button.pack() 

motorOn = False
def sendPwmCtrl():
    global motorOn
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




myCanvas = Canvas(root, width=w, height=h, bg='white')
myCanvas.pack(pady=100, padx=((W-w)/2))

plotLineBuffer = []

speed = 1
def plot_graph():
    global line, idx, x, y, t, doPlotTime, doPlot, doPlotDelay
    global clearPlot, xScale, yScale, x, plotLineBuffer
    global current_time, current_theta, prev_time, prev_theta
    global motorOn
    
    if doPlot and doPlotDelay < time.time()-doPlotTime:
        if motorOn:
          isSuccess = sendPwmB(0)
          if isSuccess:
            motorOn = False
            print('Motor off', isSuccess)
        doPlot = False 
        clearPlot = True
        button['text'] = 'CLEAR PLOT'
        current_theta =0
        prev_theta = 0
        current_time = 0
        prev_time = 0
        t = time.time()
        print('stop plot')
        myCanvas.after(speed, plot_graph)

    elif doPlot:
        if not motorOn:
          isSuccess = sendPwmB(150)
          if isSuccess:
            motorOn = True
            print('Motor on', isSuccess)

        angPosA, angVelA, angPosB, angVelB = getMotorData()

        # current_theta = angVelB
        current_theta = round(absAngDeg(angPosB),2)
        current_time = time.time()-t

        line = myCanvas.create_line(50+(prev_time*xScale),-yScale*prev_theta+h/2, 50+(current_time*xScale), -yScale*current_theta+h/2, fill="blue",width=2)
        plotLineBuffer.append(line)
        # root.update_idletasks()

        prev_theta = current_theta
        prev_time = current_time
        # t = time.time()
        myCanvas.after(speed, plot_graph)

    else:
        if motorOn:
          isSuccess = sendPwmB(0)
          if isSuccess:
            clearPlot = True
            button['text'] = 'CLEAR PLOT'
            motorOn = False
            print('Motor off', isSuccess)
        current_theta =0
        prev_theta = 0
        current_time = 0
        prev_time = 0
        t = time.time()
        myCanvas.after(speed, plot_graph)



current_theta =0
prev_theta = 0
current_time = 0
prev_time = 0


xAxisLength = 0.95*w
yAxisLength = 0.95*h

xLen = w-(50+(0.05*w))
yLen = 0.95*h/2

maxXVal = doPlotDelay
maxYVal = 360

xScale = xLen/maxXVal
yScale = yLen/maxYVal

yline = myCanvas.create_line(50, 0.05*h/2, 50, yAxisLength+(0.05*h/2), fill="black",width=2)
yline = myCanvas.create_line(0.05*w/2, h/2, xAxisLength+(0.05*w/2), h/2, fill="black",width=2)

line = myCanvas.create_line(50, h/2, 50, h/2, fill="blue",width=2) # starting point

t = time.time()
plot_graph()

root.mainloop()