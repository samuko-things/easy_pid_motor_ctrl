# animated_line_plot.py

from random import randint

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

import time

## generate parametric data for drawing a circle
theta = np.linspace( 0 , 2 * np.pi , 150 )
radius = 0.4
A = radius * np.cos( theta )
B = radius * np.sin( theta )
circle_data = list(zip(A,B))
#################################################


input_ang_deg = np.linspace( 0 , 360 , 360)

figure, ax = plt.subplots( 1 )

prev_time = time.time()

# function that draws each frame of the animation
def animate(angle_in_deg):
  global prev_time
  
  a_data = radius * np.cos( angle_in_deg * np.pi / 180 )
  b_data = radius * np.sin( angle_in_deg * np.pi / 180 )
  
  ax.clear()
  ax.plot( A, B ) #plt circle
  ax.plot( [0, a_data], [0, b_data] , 'ro-', linewidth=5) # draw line
  ax.set_aspect( 1 )
  
  ax.set_xlim(-0.5, 0.5)
  ax.set_ylim(-0.5, 0.5)
  
  ax.set_title("Angle = " + str(angle_in_deg))
  
  print(time.time() - prev_time)
  prev_time = time.time()
    
# run the animation
ani = FuncAnimation(fig=figure, func=animate, frames=input_ang_deg, interval=10, repeat=False)

plt.show()