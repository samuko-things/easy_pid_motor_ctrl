
import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots(2, 2) # figure that contains 4 plot axes 2by2 grid
x = np.linspace(0, 8, 1000)

ax[0, 0].plot(x, np.sin(x), 'g') #row=0, col=0
ax[1, 0].plot(x, np.tan(x), 'k') #row=1, col=0
ax[0, 1].plot(range(100), 'b') #row=0, col=1
ax[1, 1].plot(x, np.cos(x), 'r') #row=1, col=1

plt.show()



## get more info - https://www.geeksforgeeks.org/matplotlib-axes-class/

# import matplotlib.pyplot as plt
# import numpy as np
  
  
# X = np.linspace(-np.pi, np.pi, 15)
# C = np.cos(X)
# S = np.sin(X)
  
# # [left, bottom, width, height]
# ax = plt.axes([0.1, 0.1, 0.8, 0.8]) 
  
# # 'bs:' mentions blue color, square 
# # marker with dotted line.
# ax.plot(X, C, 'bs:') 
  
# #'ro-' mentions red color, circle 
# # marker with solid line.
# ax.plot(X, S, 'ro-') 
  
# ax.legend(labels = ('Cosine Function', 
#                     'Sine Function'), 
#           loc = 'upper left')
  
# ax.set_title("Trigonometric Functions")
  
# plt.show()