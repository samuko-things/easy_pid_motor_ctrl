# Program to plot a Circle
# using Parametric equation of a Circle
 
import numpy as np
import matplotlib.pyplot as plt
import time

def draw_circle():
  show_animation = True
  
  theta = np.linspace( 0 , 2 * np.pi , 150 )
 
  radius = 0.4
  
  A = radius * np.cos( theta )
  B = radius * np.sin( theta )
  
  circle_data = list(zip(A,B))
  
  a = []
  b = []

  figure, axes = plt.subplots( 1 )
  
  prev_time = time.time()
  
  for idx, (a_data, b_data) in enumerate(circle_data):
    # print(idx, a_data, b_data)
    a.append(a_data)
    b.append(b_data)

    if show_animation:
      # clear all axes
      plt.cla()
      
      # for stopping simulation with the esc key.
      plt.gcf().canvas.mpl_connect('key_release_event',
              lambda event: [exit(0) if event.key == 'escape' else None])
      
      axes.plot( a, b )
      axes.set_aspect( 1 )
      
      axes.set_xlim(-0.5, 0.5)
      axes.set_ylim(-0.5, 0.5)
      
      plt.pause(0.001) # delay in seconds
      
    print(time.time() - prev_time)
    prev_time = time.time()
    
  plt.show()
  
  
if __name__ == '__main__':
  draw_circle()