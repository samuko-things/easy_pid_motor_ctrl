import serial
import time
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



ser = serial.Serial('/dev/ttyUSB0', 9800, timeout=0.1)
time.sleep(1)

def turnOnLed():
  ser.write(b'h')   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()): 
    return True
  else:
    return False



def turnOffLed():
  ser.write(b'l')   # send a single byte

  # check if task was successful
  if(ser.readline().decode().strip()):
    return True
  else:
    return False



delay = 0.005
prev_time = time.time()

while time.time()-prev_time < 3.0:
  isSuccess = turnOnLed();
  print('on')
  time.sleep(delay)        
  isSuccess = turnOffLed();
  print('off')
  time.sleep(delay)

ser.close()



# print('This program allows a user to turn an LED on and off')
# print('type H to turn the LED on')
# print('type L to turn the LED off')
# print('type q to quit')

# user_input = 'L'
# while user_input != 'q':
#   user_input = input('H = on, L = off, q = quit :' )
#   byte_command = user_input.encode()
#   ser.write(byte_command)   # send a single byte
#   print(ser.readline().decode().strip())
#   time.sleep(0.001) # wait 0.5 seconds

# print('q entered. Exiting the program')
# ser.close()