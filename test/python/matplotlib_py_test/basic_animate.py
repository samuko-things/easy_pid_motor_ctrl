import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time

fig, ax = plt.subplots()
x, y = [], []
ln, = ax.plot([], [], 'ro')

ang = np.linspace(0,2*np.pi, 360)
idx = 0

def init():
  global ln
  ax.set_xlim(0, 2*np.pi)
  ax.set_ylim(-1, 1)
  return ln,


def update(i):
  global idx, ln, x, y, ang
  prev_time = time.time()
  
  x.append(ang[idx])
  y.append(np.sin(ang[idx]))

  ln.set_data(x, y)

  if idx < 299:
    idx += 1
  else:
    idx = 0

  print(idx, time.time() - prev_time)

  return ln,

ani = FuncAnimation(fig, update, frames=1,
                    init_func=init, blit=True, interval=1, repeat=True)
plt.show()