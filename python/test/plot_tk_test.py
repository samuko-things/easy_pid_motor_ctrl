from tkinter import *
import time
from math import sin, cos, radians, pi
import numpy as np



W=640
H=700
w=600
h=400

root = Tk()
root.title('draw shapes')
root.geometry(f"{W}x{H}")


doPlotDelay = 2.0 #sec
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

button = Button(root, text = 'START PLOT', command = tryPlot)  
button.pack() 



########## TEST DATA #############
idx = 0
valData = np.linspace(0,2*np.pi, 360)

def getVal():
  global idx, valData
  if idx >= len(valData):
    idx = 0
  val = valData[idx]
  idx+=1
  return val
##################################



myCanvas = Canvas(root, width=w, height=h, bg='white')
myCanvas.pack(pady=100, padx=((W-w)/2))

plotLineBuffer = []

loopSpeedMs = 1
def plot_graph():
  global line, idx, x, y, t, doPlotTime, doPlot, doPlotDelay
  global clearPlot, xScale, yScale, x, plotLineBuffer
  global current_time, current_val, prev_time, prev_val
  global motorOn
  
  if doPlot and doPlotDelay < time.time()-doPlotTime:
    doPlot = False 
    clearPlot = True
    button['text'] = 'CLEAR PLOT'
    current_val =0
    prev_val = 0
    current_time = 0
    prev_time = 0
    t = time.time()
    print('stop plot')
    idx = 0
    myCanvas.after(loopSpeedMs, plot_graph)

  elif doPlot:
    current_val = getVal()
    current_time = time.time()-t

    line = myCanvas.create_line(50+(prev_time*xScale),-yScale*sin(prev_val)+h/2, 50+(current_time*xScale), -yScale*sin(current_val)+h/2, fill="blue",width=2)
    plotLineBuffer.append(line)

    # print(current_time - prev_time)

    prev_val = current_val
    prev_time = current_time
    # t = time.time()
    myCanvas.after(loopSpeedMs, plot_graph)

  else:
    current_val =0
    prev_val = 0
    current_time = 0
    prev_time = 0
    t = time.time()
    myCanvas.after(loopSpeedMs, plot_graph)



current_val =0
prev_val = 0
current_time = 0
prev_time = 0


xAxisLength = 0.95*w
yAxisLength = 0.95*h

xLen = w-(50+(0.05*w))
yLen = 0.95*h/2

maxXVal = doPlotDelay
maxYVal = 1.1

xScale = xLen/maxXVal
yScale = yLen/maxYVal

yline = myCanvas.create_line(50, 0.05*h/2, 50, yAxisLength+(0.05*h/2), fill="black",width=2)
yline = myCanvas.create_line(0.05*w/2, h/2, xAxisLength+(0.05*w/2), h/2, fill="black",width=2)

line = myCanvas.create_line(50, h/2, 50, h/2, fill="blue",width=2) # starting point

t = time.time()
plot_graph()

root.mainloop()