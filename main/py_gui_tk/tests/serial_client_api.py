
import serial
import time

class SerialClient:
  
  def __init__(self, port, baud, timeOut):
    self.ser = serial.Serial(port, baud, timeout=timeOut)

  def send_msg(self, msg_to_send):
    data = ""
    while data=="":
      self.ser.write(msg_to_send.encode())   # send a single or multiple byte
      data = self.ser.readline().decode().strip()
    return data

  # def send_msg(self, msg_to_send):
  #   data = ""
  #   prev_time = time.time()
  #   while data=="":
  #     try:
  #       self.ser.write(msg_to_send.encode())   # send a single or multiple byte    
  #       data = self.ser.readline().decode().strip()
  #       if time.time()-prev_time > 2.0:
  #         raise Exception("Error getting response from arduino nano, wasted much time \n")
  #     except:
  #       print("Error getting response from arduino nano, wasted much time \n")
  #   return data

  
  def send(self, cmd_route, valA=0, valB=0):
    cmd_str = cmd_route+","+str(valA)+","+str(valB)
    data = self.send_msg(cmd_str)
    if data == "1":
      return True
    else:
      return False
  
  
  def get(self, cmd_route):
    data = self.send_msg(cmd_route).split(',')
    if len(data)==2:
      return float(data[0]), float(data[1])
    elif len(data)==1:
      return float(data[0])
  
  







# serClient = SerialClient('/dev/ttyUSB0', 115200, 0.1)
# time.sleep(5)

# cmd = ""


# # isSuccessful = serClient.send("mode", 1) # activate pid mode (deactivate pwm mode and parameter settings)
# # isSuccessful = serClient.send("tag", -2.013, 0.878) # sends targetA, targetB -> input values in 3.dp



# isSuccessful = serClient.send("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
# print(isSuccessful)

# time.sleep(1)

# isSuccessful = serClient.send("pwm", -120, 0) # sends  pwmA, pwmB
# print(isSuccessful)

# time.sleep(1)

# prev_time = time.time()
# while time.time()-prev_time < 10.0:
#   posA, posB = serClient.get("pos") # returns angPosA, angPosB
#   velA, velB = serClient.get("vel") # returns angVelA, angVelB

#   print(posA, velA)
#   time.sleep(0.005)

# isSuccessful = serClient.send("mode", 1) # ativate pid mode (deactivate pwm mode and parameter settings)
# print(isSuccessful)