import numpy as np
import matplotlib.pyplot as plt
import serial
import time


# ensure connection with serial port
ser = serial.Serial('/dev/ttyUSB0', 9800, timeout=0.1)
time.sleep(1)

def getMotorPos():
  ser.write(b'p')   # send a single byte

  data = ser.readline().decode().strip()

  if data:
    return float(data)
  else:
    return 0.0


def animate_motor_pos():  
  ## generate parametric data for drawing a circle
  theta = np.linspace( 0 , 2 * np.pi , 90 )
  radius = 0.4
  A = radius * np.cos( theta )
  B = radius * np.sin( theta )
  ###############################################
  
  figure, axes = plt.subplots( 1 )
  
  prev_time = time.time()
  
  while True:
    prev_time = time.time()

    ang_deg = getMotorPos();

    a_data = radius * np.cos( ang_deg * np.pi / 180 )
    b_data = radius * np.sin( ang_deg * np.pi / 180 )

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
    
    plt.pause(0.001) # delay in seconds
      
    print(time.time() - prev_time)
    
  # plt.show()
  
  
if __name__ == '__main__':
  animate_motor_pos()