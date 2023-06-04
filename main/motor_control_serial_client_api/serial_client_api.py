
import serial
import time
import math

# '/dev/ttyUSB0'

class MotorSerialClient:
  
  def __init__(self, port):
    self.ser = serial.Serial(port, 115200, timeout=0.1)
    self.val = 0

  def send(self, cmd_route, valA, valB):
    cmd_str = cmd_route+","+str(valA)+","+str(valB)
    self.ser.write(cmd_str.encode())   # send a single or multiple byte
    # check if task was successful
    data = self.ser.readline().decode().strip()
    if data == "1":
      return True
    else:
      return False
    
  def sendOne(self, cmd_route, val):
    cmd_str = cmd_route+","+str(val)
    self.ser.write(cmd_str.encode())   # send a single or multiple byte
    # check if task was successful
    data = self.ser.readline().decode().strip()
    if data == "1":
      return True
    else:
      return False
  
  
  def get(self, cmd_route):
    self.ser.write(cmd_route.encode())   # send a single or multiple byte
    try:
      data = self.ser.readline().decode().strip().split(',')
      return float(data[0]), float(data[1])
    except:
      return 0.000, 0.000

  def getOne(self, cmd_route):
    self.ser.write(cmd_route.encode())   # send a single or multiple byte
    try:
      data = self.ser.readline().decode().strip()
      return float(data)
    except:
      return 0.000
  
  


motorClient = MotorSerialClient('/dev/ttyUSB0')
time.sleep(3)

cmd = ""


# isSuccessful = motorClient.sendOne("mode", 1) # ativate pid mode (deactivate pwm mode and parameter settings)
# isSuccessful = motorClient.send("tag", -2.013, 0.878) # sends targetA, targetB -> input values in 3.dp


isSuccessful = False
while not isSuccessful:
  isSuccessful = motorClient.sendOne("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
  print(isSuccessful)

time.sleep(1)

isSuccessful = motorClient.send("pwm", -105, 0) # sends  pwmA, pwmB
print(isSuccessful)

time.sleep(1)

# isSuccessful = motorClient.sendOne("mode", 1) # ativate pid mode (deactivate pwm mode and parameter settings)

while True:
  posA, posB = motorClient.get("pos") # returns angPosA, angPosB
  velA, velB = motorClient.get("vel") # returns angVelA, angVelB

  # val = motorClient.getOne("pprA")
  print(posA, velA)
  time.sleep(0.005)

# while True:
#   val = motorClient.getOne("velA")
#   print(val)
#   time.sleep(0.01)

# while True:
#   pwm = -90
#   while pwm>=-250:
#     mySer.send("pwmA", pwm)
#     val = mySer.get("posA")
#     print(val)
#     pwm-=5
#     time.sleep(0.01)
      

#   pwm = -250
#   while pwm<=-90:
#     mySer.send("pwmA", pwm)
#     val = mySer.get("posA")
#     print(val)
#     pwm+=5
#     time.sleep(0.01)

#   pwm = 90
#   while pwm<=250:
#     mySer.send("pwmA", pwm)
#     val = mySer.get("posA")
#     print(val)
#     pwm+=5
#     time.sleep(0.01)
      

#   pwm = 250
#   while pwm>=90:
#     mySer.send("pwmA", pwm)
#     val = mySer.get("posA")
#     print(val)
#     pwm-=5
#     time.sleep(0.01)



# val = mySer.send("pwmA", 110)
# print(val)

# while (cmd != "e"):
#   cmd = input("enter cmd: ")
#   val = mySer.get(cmd)
#   print(val)

