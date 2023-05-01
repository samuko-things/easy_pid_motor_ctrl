# animated_line_plot.py

from random import randint

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

import time



X = np.linspace(0, np.pi*4, 500)
C = np.cos(X)
S = np.sin(X)
  
sine_graph_data = list(zip(X,C,S))

x = []
c = []
s = []

idx = 1

# create the figure and axes objects
fig, ax = plt.subplots()

prev_time = time.time()

# function that draws each frame of the animation
def animate(data):
  global idx, prev_time
  
  x_data = data[0]
  c_data = data[1]
  s_data = data[2]
  
  x.append(x_data)
  c.append(c_data)
  s.append(s_data)
  
  ax.clear()
  ax.plot(x[-50:], c[-50:], '-b', label="cosine")
  ax.plot(x[-50:], s[-50:], "-r", label="sine")
  
  # ax.set_xlim(0, 5)
  ax.set_ylim(-1.5, 1.5)

  ax.set_title("Index: " + str(idx))
  idx+=1
  
  print(time.time()-prev_time)
  prev_time = time.time()



if __name__ == '__main__': 
  # run the animation
  ani = FuncAnimation(fig=fig, func=animate, frames=sine_graph_data, interval=10, repeat=False)

  plt.show()