import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time

fig, ax = plt.subplots()
xdata, ydata = [], []
ln, = ax.plot([], [], 'ro')

def init():
  ax.set_xlim(0, 2*np.pi)
  ax.set_ylim(-1, 1)
  return ln,

prev_time = time.time()
def update(frame):
  global prev_time

  prev_time = time.time()
  
  xdata.append(frame)
  ydata.append(np.sin(frame))
  ln.set_data(xdata, ydata)

  print(time.time() - prev_time)

  return ln,

ani = FuncAnimation(fig, update, frames=np.linspace(0, 2*np.pi, 128),
                    init_func=init, blit=True)
plt.show()