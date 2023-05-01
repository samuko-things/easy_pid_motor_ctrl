import time
for i in range(20):
  time.sleep(1.0)
  print (i, end="\r")
print ("finished")