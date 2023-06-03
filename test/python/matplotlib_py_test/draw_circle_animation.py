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

circle_data = list(zip(A,B))

a = []
b = []

fig, ax = plt.subplots()
ln, = ax.plot([], [])


def init():
  ax.set_xlim(-0.4, 0.4)
  ax.set_ylim(-0.4, 0.4)
  return ln,



prev_time = time.time()
def update(circle_data):
  global prev_time

  prev_time = time.time()
  
  a.append(circle_data[0])
  b.append(circle_data[1])
  ln.set_data(a, b)

  # ax.plot(a,b)

  print(time.time() - prev_time)
  return ln

ani = FuncAnimation(fig, update, frames=circle_data,
                    init_func=init, blit=True, interval=10)
plt.show()
