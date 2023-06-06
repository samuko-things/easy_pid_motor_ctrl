
import serial
import time
import math

# '/dev/ttyUSB0'

class MotorSerialClient:
  
  def __init__(self, port):
    self.ser = serial.Serial(port, 115200, timeout=0.1)
    self.val = 0

  # def send_msg(self, msg_to_send):
  #   data = ""
  #   while data=="":
  #     self.ser.write(msg_to_send.encode())   # send a single or multiple byte
  #     data = self.ser.readline().decode().strip()
  #   return data

  def send_msg(self, msg_to_send):
    data = ""
    prev_time = time.time()
    while data=="":
      try:
        self.ser.write(msg_to_send.encode())   # send a single or multiple byte    
        data = self.ser.readline().decode().strip()
        if time.time()-prev_time > 2.0:
          raise Exception("Error getting response from arduino nano, wasted much time \n")
      except:
        print("Error getting response from arduino nano, wasted much time \n")
    return data

  
  def send(self, cmd_route, valA, valB):
    cmd_str = cmd_route+","+str(valA)+","+str(valB)
    data = self.send_msg(cmd_str)
    if data == "1":
      return True
    else:
      return False
    
  def sendParam(self, cmd_route, val):
    cmd_str = cmd_route+","+str(val)
    data = self.send_msg(cmd_str)
    if data == "1":
      return True
    else:
      return False
  
  
  def get(self, cmd_route):
    data = self.send_msg(cmd_route).split(',')
    return float(data[0]), float(data[1])

  def getParam(self, cmd_route):
    data = self.send_msg(cmd_route)
    return float(data)
  
  


serClient = MotorSerialClient('/dev/ttyUSB0')
time.sleep(5)

cmd = ""


# isSuccessful = serClient.sendOne("mode", 1) # ativate pid mode (deactivate pwm mode and parameter settings)
# isSuccessful = serClient.send("tag", -2.013, 0.878) # sends targetA, targetB -> input values in 3.dp



isSuccessful = serClient.sendParam("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
print(isSuccessful)

time.sleep(1)

isSuccessful = serClient.send("pwm", -105, 0) # sends  pwmA, pwmB
print(isSuccessful)

time.sleep(1)

# isSuccessful = serClient.sendParam("mode", 1) # ativate pid mode (deactivate pwm mode and parameter settings)

while True:
  posA, posB = serClient.get("pos") # returns angPosA, angPosB
  velA, velB = serClient.get("vel") # returns angVelA, angVelB

  print(posA, velA)
  time.sleep(0.005)



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


###########################################
# val = mySer.send("pwmA", 110)
# print(val)

# while (cmd != "e"):
#   cmd = input("enter cmd: ")
#   val = mySer.get(cmd)
#   print(val)

