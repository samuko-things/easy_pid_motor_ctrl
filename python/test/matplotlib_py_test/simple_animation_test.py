
import matplotlib.pyplot as plt
import numpy as np
import time

def animate_graph():
  show_animation = True
  
  X = np.linspace(0, np.pi*4, 500)
  C = np.cos(X)
  S = np.sin(X)
  
  sine_graph_data = list(zip(X,C,S))
  
  x = []
  c = []
  s = []

  prev_time = time.time()
  for idx, (x_data, c_data, s_data) in enumerate(sine_graph_data):
    # print(idx, x_data, c_data, s_data)
    x.append(x_data)
    c.append(c_data)
    s.append(s_data)

    if show_animation:
      # clear all axes
      plt.cla()
      
      # for stopping simulation with the esc key.
      plt.gcf().canvas.mpl_connect('key_release_event',
              lambda event: [exit(0) if event.key == 'escape' else None])
      
      plt.plot(x[-60:], c[-60:], '-b', label="cosine")
      plt.plot(x[-60:], s[-60:], "-r", label="sine")
      
      # plt.xlim(0, 20)
      plt.ylim(-1.5, 1.5)
    
      # plt.axis("equal")
      # plt.grid(True)
      plt.title("Index: " + str(idx))
      
      plt.pause(0.01) # delay in seconds
    
    print(time.time() - prev_time)
    prev_time = time.time()
    
  plt.show()
  
  
if __name__ == '__main__':
  animate_graph()