from math import sin, cos, radians, pi
from serial_client_api import SerialClient
import time

import customtkinter

customtkinter.set_appearance_mode("System")  # Modes: "System" (standard), "Dark", "Light"
customtkinter.set_default_color_theme("blue")  # Themes: "blue" (standard), "green", "dark-blue"










class SetCardFrame(customtkinter.CTkFrame):
    def __init__(self, parentFrame, text, initialValue):
      super().__init__(master=parentFrame, width=300, corner_radius=10)

      self.value = initialValue
      self.mainText = text
      self.text = f"{self.mainText} = {self.value}"

      # set card frame
      self.grid_rowconfigure((0,1), weight=0)
      self.grid_columnconfigure((0,1), weight=0)

      self.setTextLabel = customtkinter.CTkLabel(self, text=self.text, font=customtkinter.CTkFont(size=15, weight="bold"))
      self.setTextLabel.grid(row=0, column=0, columnspan=2, padx=(20,5), pady=10, sticky="w")

      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

      # self.setButton = customtkinter.CTkButton(self, text="SET", width=50, command=self.__get_data)
      # self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)


    # def __get_data(self):
    #   self.value = self.setTextEntry.get()
    #   self.text = f"{self.mainText} = {self.value}"

    #   self.setTextLabel.configure(text=self.text)
      
    #   self.setTextEntry.destroy()
    #   self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
    #   self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)












class SetEncPPRACardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "PPR_A", int(serClient.get("pprA")))

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      self.value = self.setTextEntry.get()
      isSuccessful = serClient.send("pprA", float(self.value))
      self.value = int(serClient.get("pprA"))
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)


class SetEncPPRBCardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "PPR_B", int(serClient.get("pprB")))

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      self.value = self.setTextEntry.get()
      isSuccessful = serClient.send("pprB", float(self.value))
      self.value = int(serClient.get("pprB"))
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)















class SetPwmACardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "PWM_A", ctrlPwmA)

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      global ctrlPwmA

      self.value = self.setTextEntry.get()
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

      ctrlPwmA = int(self.value)
      # print(ctrlPwm)


class SetPwmBCardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "PWM_B", ctrlPwmB)

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      global ctrlPwmB

      self.value = self.setTextEntry.get()
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

      ctrlPwmB = int(self.value)















class SetDurationACardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "DURATION_A", motorAOnDuration)

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      global motorAOnDuration

      self.value = self.value = abs(float(self.setTextEntry.get()))
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

      motorAOnDuration = self.value
      # print(motorOnDuration)

class SetDurationBCardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "DURATION_B", motorBOnDuration)

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      global motorBOnDuration

      self.value = abs(float(self.setTextEntry.get()))
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

      motorBOnDuration = self.value
      # print(motorOnDuration)














class MotorAPosCanvas(customtkinter.CTkCanvas):
    def __init__(self, parentFrame):
      super().__init__(master=parentFrame, width=400, height=360, bg='white')


      self.r = 170 # circle radius
      self.m = (200, 180) #x, y
      self.circle = self.create_oval(32, 12, 368, 348, outline="green", width=5)
      self.line = self.create_line(self.m[0], self.m[1], 
                                   self.m[0]+self.r*cos(radians(thetaA-initialThetaA)), 
                                   self.m[1]+self.r*sin(radians(thetaA-initialThetaA)), 
                                   fill='blue',width=15)
      self.mid_circle = self.create_oval(180, 160, 220, 200, fill="green", outline="blue")

      # add display label
      self.angPosDisplayLabel = customtkinter.CTkLabel(parentFrame, text="angPosA (rad): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=100)
      self.angPosDisplayLabel.grid(row=2, column=2, padx=(5,5), pady=10, sticky="w")

      self.angPosDisplayLabelVal = customtkinter.CTkLabel(parentFrame, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=100)
      self.angPosDisplayLabelVal.grid(row=3, column=2, padx=(5,5), pady=10, sticky="nw")

      self.angVelDisplayLabel = customtkinter.CTkLabel(parentFrame, text="angVelA (rad/s): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=100)
      self.angVelDisplayLabel.grid(row=4, column=2, padx=(5,5), pady=10, sticky="w")

      self.angVelDisplayLabelVal = customtkinter.CTkLabel(parentFrame, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=100)
      self.angVelDisplayLabelVal.grid(row=5, column=2, padx=(5,5), pady=10, sticky="nw")

      self.after(1, self.draw_motor_ang_posA)

    def draw_motor_ang_posA(self):
      global motorAIsOn, motorAOnDuration, motorAOnStartTime, initialThetaA, thetaA, angPosA, angVelA
      if motorAIsOn and motorAOnDuration < time.time()-motorAOnStartTime:
          isSuccess = serClient.send("pwm", 0, 0)
          if isSuccess:
            motorAIsOn = False
            # print('Motor off', isSuccess)
      self.delete(self.line)
      self.delete(self.mid_circle)
      angPosA, angVelA = serClient.get("dataA")
      thetaA = round(self.absAngDeg(angPosA),2)

      self.line = self.create_line(self.m[0], self.m[1], 
                                   self.m[0]+self.r*cos(radians(thetaA-initialThetaA)), 
                                   self.m[1]+self.r*sin(radians(thetaA-initialThetaA)), 
                                   fill='blue',width=15)
      self.mid_circle = self.create_oval(180, 160, 220, 200, fill="green", outline="blue")

      self.angPosDisplayLabelVal.configure(text=f"{angPosA}")
      self.angVelDisplayLabelVal.configure(text=f"{angVelA}")

      self.after(1, self.draw_motor_ang_posA)

    def absAngDeg(self, incAngRad):
      incAngDeg = incAngRad * 180.0 / pi
      return incAngDeg % 360.0




class MotorBPosCanvas(customtkinter.CTkCanvas):
    def __init__(self, parentFrame):
      super().__init__(master=parentFrame, width=400, height=360, bg='white')


      self.r = 170 # circle radius
      self.m = (200, 180) #x, y
      self.circle = self.create_oval(32, 12, 368, 348, outline="green", width=5)
      self.line = self.create_line(self.m[0], self.m[1], 
                                   self.m[0]+self.r*cos(radians(thetaB-initialThetaB)), 
                                   self.m[1]+self.r*sin(radians(thetaB-initialThetaB)), 
                                   fill='blue',width=15)
      self.mid_circle = self.create_oval(180, 160, 220, 200, fill="green", outline="blue")

      # add display label
      self.angPosDisplayLabel = customtkinter.CTkLabel(parentFrame, text="angPosB (rad): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=100)
      self.angPosDisplayLabel.grid(row=2, column=2, padx=(5,5), pady=10, sticky="w")

      self.angPosDisplayLabelVal = customtkinter.CTkLabel(parentFrame, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=100)
      self.angPosDisplayLabelVal.grid(row=3, column=2, padx=(5,5), pady=10, sticky="nw")

      self.angVelDisplayLabel = customtkinter.CTkLabel(parentFrame, text="angVelB (rad/s): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=100)
      self.angVelDisplayLabel.grid(row=4, column=2, padx=(5,5), pady=10, sticky="w")

      self.angVelDisplayLabelVal = customtkinter.CTkLabel(parentFrame, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=100)
      self.angVelDisplayLabelVal.grid(row=5, column=2, padx=(5,5), pady=10, sticky="nw")

      self.after(1, self.draw_motor_ang_posB)

    def draw_motor_ang_posB(self):
      global motorBIsOn, motorBOnDuration, motorBOnStartTime, initialThetaB, thetaB, angPosB, angVelB
      if motorBIsOn and motorBOnDuration < time.time()-motorBOnStartTime:
          isSuccess = serClient.send("pwm", 0, 0)
          if isSuccess:
            motorBIsOn = False
            # print('Motor off', isSuccess)
      self.delete(self.line)
      self.delete(self.mid_circle)
      angPosB, angVelB = serClient.get("dataB")
      thetaB = round(self.absAngDeg(angPosB),2)

      self.line = self.create_line(self.m[0], self.m[1], 
                                   self.m[0]+self.r*cos(radians(thetaB-initialThetaB)), 
                                   self.m[1]+self.r*sin(radians(thetaB-initialThetaB)), 
                                   fill='blue',width=15)
      self.mid_circle = self.create_oval(180, 160, 220, 200, fill="green", outline="blue")

      self.angPosDisplayLabelVal.configure(text=f"{angPosB}")
      self.angVelDisplayLabelVal.configure(text=f"{angVelB}")

      self.after(1, self.draw_motor_ang_posB)

    def absAngDeg(self, incAngRad):
      incAngDeg = incAngRad * 180.0 / pi
      return incAngDeg % 360.0
    



























class App(customtkinter.CTk):
    def __init__(self):
      super().__init__()

      # configure window
      self.title("encoder_setup_and_view")
      self.geometry(f"{800}x{750}")


      self.tabview = customtkinter.CTkTabview(self, width=250)
      self.tabview.pack()
      self.tabview.add("MOTOR B")
      self.tabview.add("MOTOR A")
      
      self.mainframeA = customtkinter.CTkFrame(master=self.tabview.tab("MOTOR A"))
      self.mainframeA.pack()

      self.mainframeB = customtkinter.CTkFrame(master=self.tabview.tab("MOTOR B"))
      self.mainframeB.pack()


      ########################################### MOTOR A #################################################

      # self.mainframeA.grid_columnconfigure((0,1,2), weight=0)
      # self.mainframeA.grid_rowconfigure((0,1,2,3,4,5), weight=0)

      # # add set card frame
      # self.setEncPPRACardFrame = SetEncPPRACardFrame(self.mainframeA)
      # self.setEncPPRACardFrame.grid(row=0, column=0, padx=(20,10), pady=10)

      # self.setPwmACardFrame = SetPwmACardFrame(self.mainframeA)
      # self.setPwmACardFrame.grid(row=0, column=1, padx=10, pady=10)

      # self.setDurationACardFrame = SetDurationACardFrame(self.mainframeA)
      # self.setDurationACardFrame.grid(row=0, column=2, padx=10, pady=10)

      # # add buttons
      # self.resetHandButtonA = customtkinter.CTkButton(self.mainframeA, text="RESET HAND", command=self.resetInitialThetaA)
      # self.resetHandButtonA.grid(row=1, column=0, columnspan=2, padx=(20,5) , pady=(100, 10), ipadx=5, ipady=5)

      # # self.handRuleButtonA = customtkinter.CTkButton(self.mainframeA, text="RIGHT HAND RULE", command=self.changeHandRuleA)
      # # self.handRuleButtonA.grid(row=1, column=1, padx=(5,20), pady=(100, 10), ipadx=5, ipady=5, sticky="w")

      # self.sendPulsedCmdButtonA = customtkinter.CTkButton(self.mainframeA, text="SEND PULSED COMMAND", command=self.sendPwmCtrlA)
      # self.sendPulsedCmdButtonA.grid(row=1, column=2, padx=20, pady=(100, 10), ipadx=5, ipady=5)

      # # add canvas
      # self.motorAPosCanvas = MotorAPosCanvas(self.mainframeA)
      # self.motorAPosCanvas.grid(row=2, column=0, rowspan=4, columnspan=2, pady=(10, 20))

      ###################################################################################################





      ########################################### MOTOR B #################################################
      

      self.mainframeB.grid_columnconfigure((0,1,2), weight=0)
      self.mainframeB.grid_rowconfigure((0,1,2,3,4,5), weight=0)

      # add set card frame
      self.setEncPPRBCardFrame = SetEncPPRBCardFrame(self.mainframeB)
      self.setEncPPRBCardFrame.grid(row=0, column=0, padx=(20,10), pady=10)

      self.setPwmBCardFrame = SetPwmBCardFrame(self.mainframeB)
      self.setPwmBCardFrame.grid(row=0, column=1, padx=10, pady=10)

      self.setDurationBCardFrame = SetDurationBCardFrame(self.mainframeB)
      self.setDurationBCardFrame.grid(row=0, column=2, padx=10, pady=10)

      # add buttons
      self.resetHandButtonB = customtkinter.CTkButton(self.mainframeB, text="RESET HAND", command=self.resetInitialThetaB)
      self.resetHandButtonB.grid(row=1, column=0, columnspan=2, padx=(20,5) , pady=(100, 10), ipadx=5, ipady=5)

      # self.handRuleButtonB = customtkinter.CTkButton(self.mainframeB, text="RIGHT HAND RULE", command=self.changeHandRuleB)
      # self.handRuleButtonB.grid(row=1, column=1, padx=(5,20), pady=(100, 10), ipadx=5, ipady=5, sticky="w")

      self.sendPulsedCmdButtonB = customtkinter.CTkButton(self.mainframeB, text="SEND PULSED COMMAND", command=self.sendPwmCtrlB)
      self.sendPulsedCmdButtonB.grid(row=1, column=2, padx=20, pady=(100, 10), ipadx=5, ipady=5)

      # add canvas
      self.motorBPosCanvas = MotorBPosCanvas(self.mainframeB)
      self.motorBPosCanvas.grid(row=2, column=0, rowspan=4, columnspan=2, pady=(10, 20))

      ###################################################################################################

      


    def sendPwmCtrlA(self):
        global motorAIsOn, motorAOnStartTime, ctrlPwmA
        if motorAIsOn:
          isSuccess = serClient.send("pwm", 0, 0)
          if isSuccess:
            motorAIsOn = False
            # print('Motor off', isSuccess)
        else:
          isSuccess = serClient.send("pwm", ctrlPwmA, 0)
          if isSuccess:
            motorAIsOn = True
            motorAOnStartTime = time.time()
            # print('Motor On', isSuccess)

    def resetInitialThetaA(self):
        global initialThetaA, thetaA
        initialThetaA = thetaA + 90



    def sendPwmCtrlB(self):
        global motorBIsOn, motorBOnStartTime, ctrlPwmB
        if motorBIsOn:
          isSuccess = serClient.send("pwm", 0, 0)
          if isSuccess:
            motorBIsOn = False
            # print('Motor off', isSuccess)
        else:
          isSuccess = serClient.send("pwm", 0, ctrlPwmB)
          if isSuccess:
            motorBIsOn = True
            motorBOnStartTime = time.time()
            # print('Motor On', isSuccess)

    def resetInitialThetaB(self):
        global initialThetaB, thetaB
        initialThetaB = thetaB + 90

        
        














if __name__ == "__main__":

  motorAOnDuration = 5 #sec
  motorAOnStartTime = time.time()
  motorAIsOn = False
  ctrlPwmA = 120
  initialThetaA = 90.0
  thetaA = 0.0
  angPosA = 0.0
  angVelA = 0.0


  motorBOnDuration = 5 #sec
  motorBOnStartTime = time.time()
  motorBIsOn = False
  ctrlPwmB = 120
  initialThetaB = 90.0
  thetaB = 0.0
  angPosB = 0.0
  angVelB = 0.0


  #################################################################
  serClient = SerialClient('/dev/ttyUSB0', 115200, 0.1)
  time.sleep(4)
  isSuccessful = serClient.send("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
  print(isSuccessful)
  #################################################################

  app = App()
  app.mainloop()