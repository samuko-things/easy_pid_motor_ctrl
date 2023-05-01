# Program to plot a Circle
# using Parametric equation of a Circle
 
import numpy as np
import matplotlib.pyplot as plt
import time

def draw_circle():
  show_animation = True
  
  ## generate parametric data for drawing a circle
  theta = np.linspace( 0 , 2 * np.pi , 150 )
  radius = 0.4
  A = radius * np.cos( theta )
  B = radius * np.sin( theta )
  ###############################################

  input_ang_deg = np.linspace( 0 , 360 , 360)
  
  figure, axes = plt.subplots( 1 )
  
  prev_time = time.time()
  
  for idx, ang_deg in enumerate(input_ang_deg):
    
    a_data = radius * np.cos( ang_deg * np.pi / 180 )
    b_data = radius * np.sin( ang_deg * np.pi / 180 )

    if show_animation:
      # clear all axes
      plt.cla()
      
      # for stopping simulation with the esc key.
      plt.gcf().canvas.mpl_connect('key_release_event',
              lambda event: [exit(0) if event.key == 'escape' else None])
      
      axes.plot( A, B )
      axes.plot( [0, a_data], [0, b_data] , 'ro-', linewidth=5)
      axes.set_aspect( 1 )
      
      axes.set_xlim(-0.5, 0.5)
      axes.set_ylim(-0.5, 0.5)
      
      axes.set_title("Angle = " + str(int(ang_deg)))
      
      plt.pause(0.0001) # delay in seconds
      
    print(time.time() - prev_time)
    prev_time = time.time()
    
  plt.show()
  
  
if __name__ == '__main__':
  draw_circle()