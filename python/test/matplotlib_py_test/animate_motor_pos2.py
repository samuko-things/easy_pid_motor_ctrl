


# Program to plot a Circle
# using Parametric equation of a Circle
 
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time



theta = np.linspace( 0 , 2 * np.pi , 90 )
 
radius = 0.3

A = radius * np.cos( theta )
B = radius * np.sin( theta )

# circle_data = list(zip(A,B))

# a = []
# b = []

input_ang_deg = np.linspace( 0 , 360 , 360)

fig, ax = plt.subplots()

def init():
  ax.set_xlim(-0.4, 0.4)
  ax.set_ylim(-0.4, 0.4)



prev_time = time.time()
def update(angle_in_deg):
  global prev_time

  prev_time = time.time()
  
  a_data = radius * np.cos( angle_in_deg * np.pi / 180 )
  b_data = radius * np.sin( angle_in_deg * np.pi / 180 )

  ax.clear()  
  ax.plot(A,B)
  ax.plot( [0, a_data], [0, b_data] , 'ro-', linewidth=3)

  print(time.time() - prev_time)

ani = FuncAnimation(fig, update, frames=input_ang_deg,
                    init_func=init, blit=True, interval=10)
plt.show()

