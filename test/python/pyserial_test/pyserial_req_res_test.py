import serial
import time
import math
########################################################

# generally, we receive data from arduino serial as byte string
# we then decode it to unicode string
# use the unicode string in the python program

# # if you intend on sending info back to the microcontroller
# # then first convert to byte string before ou send via serial.

# # what we/the python program understand
# unicodeStr = 'samuko'
# print(type(unicodeStr))

# # what the microcontroller understands
# byteStr = b'samuko'
# print(type(byteStr))

# #convert unicode to byte string
# bStr_from_uStr = unicodeStr.encode()
# print(type(bStr_from_uStr))

# #convert byte string to unicode
# uStr_from_bStr = byteStr.decode()
# print(type(uStr_from_bStr))

# #########################################################



ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.1)
time.sleep(1)
serCommSpeed = 0.05

# def turnOnLed():
#   ser.write(b'h')   # send a single byte

#   # check if task was successful
#   if(ser.readline().decode().strip()): 
#     return True
#   else:
#     return False

# def turnOffLed():
#   ser.write(b'l')   # send a single byte

#   # check if task was successful
#   if(ser.readline().decode().strip()):
#     return True
#   else:
#     return False
  

def absAngDeg(incAngRad):
  incAngDeg = incAngRad * 180.0 / math.pi;
  return incAngDeg % 360.0;


def sendPwmA(pwm):
  cmd = 'pwmA,'+str(pwm)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False 
def sendPwmB(pwm):
  cmd = 'pwmB,'+str(pwm)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False


def sendPwm(pwmA, pwmB):
  cmd = 'pwm,'+str(pwmA)+','+str(pwmB)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False
  



def sendTargetPosA(pos):
  cmd = 'posA,'+str(pos)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False
def sendTargetPosB(pos):
  cmd = 'posB,'+str(pos)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False
  
def sendTargetPos(posA, posB):
  cmd = 'pos,'+str(posA)+','+str(posB)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False
  



def sendTargetVelA(vel):
  cmd = 'velA,'+str(vel)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False
def sendTargetVelB(vel):
  cmd = 'velB,'+str(vel)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False

def sendTargetVel(velA, velB):
  cmd = 'vel,'+str(velA)+','+str(velB)
  ser.write(cmd.encode())   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False



# def getMotorAPos():
#   ser.write(b'POSA')   # send a single byte

#   pos = ser.readline().decode().strip()
#   if pos: 
#     return float(pos)
#   else:
#     return 0.0
# def getMotorBPos():
#   ser.write(b'POSB')   # send a single byte

#   pos = ser.readline().decode().strip()
#   if pos: 
#     return float(pos)
#   else:
#     return 0.0
  


# def getMotorAVel():
#   time.sleep(serCommSpeed);
#   ser.write(b'VELA')   # send a single byte

#   vel = ser.readline().decode().strip()
#   if vel: 
#     return float(vel)
#   else:
#     return 0.0
# def getMotorBVel():
#   time.sleep(serCommSpeed);
#   ser.write(b'VELB')   # send a single byte

#   vel = ser.readline().decode().strip()
#   if vel: 
#     return float(vel)
#   else:
#     return 0.0





# def getMotorAFreq():
#   time.sleep(serCommSpeed);
#   ser.write(b'FRQA')   # send a single byte

#   freq = ser.readline().decode().strip()
#   if freq: 
#     return float(freq)
#   else:
#     return 0.0
# def getMotorBFreq():
#   time.sleep(serCommSpeed);
#   ser.write(b'FRQB')   # send a single byte

#   freq = ser.readline().decode().strip()
#   if freq: 
#     return float(freq)
#   else:
#     return 0.0
  


def getMotorAData():
  angPos, angVel = (0.00,0.00)
  ser.write(b'allA')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    angPos = float(data[0])
    angVel = float(data[1])
    return angPos, angVel
  except:
    return angPos, angVel
def getMotorBData():
  angPos, angVel = (0.00,0.00)
  ser.write(b'allB')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    angPos = float(data[0])
    angVel = float(data[1])
    return angPos, angVel
  except:
    return angPos, angVel



def getAllMotorAData():
  tickCount, angPos, frequency, angVel = (0.00,0.00,0.00,0.00)
  ser.write(b'ALLA')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    tickCount = float(data[0])
    angPos = float(data[1])
    frequency = float(data[2])
    angVel = float(data[3])
    return tickCount, angPos, frequency, angVel
  except:
    return tickCount, angPos, frequency, angVel
def getAllMotorBData():
  tickCount, angPos, frequency, angVel = (0.00,0.00,0.00,0.00)
  ser.write(b'ALLB')   # send a single byte
  
  try:
    data = ser.readline().decode().strip().split(',')
    tickCount = float(data[0])
    angPos = float(data[1])
    frequency = float(data[2])
    angVel = float(data[3])
    return tickCount, angPos, frequency, angVel
  except:
    return tickCount, angPos, frequency, angVel




def getMotorData():
  angPosA,angVelA, angPosB, angVelB = (0.00,0.00,0.00,0.00)
  ser.write(b'all')   # send a single byte
  
  try:
    allData = ser.readline().decode().strip().split(',')
    angPosA = float(allData[0])
    angVelA = float(allData[1])
    angPosB = float(allData[2])
    angVelB = float(allData[3])
    return angPosA, angVelA, angPosB, angVelB
  except:
    return angPosA, angVelA, angPosB, angVelB
  






### PWM CONTROL TEST ##############
# pwm_cmd = '100'
# while True:
#   try:
#     pwm_cmd = input('enter a pww val between 0-255, q = quit :' )
#     if pwm_cmd == 'q':
#       break;
#     sendPwmB(int(pwm_cmd))
#   except:
#     print('wrong pwm value')
  

# print('q entered. Exiting the program')
# ser.close()
###########################################



for i in range(1000):
  t = time.time()
  tickCount, angPos, frequency, angVel = getAllMotorBData()
  print('motor B data = ',tickCount, angPos, frequency, angVel)
  print(time.time()-t)
  

print('q entered. Exiting the program')
ser.close()