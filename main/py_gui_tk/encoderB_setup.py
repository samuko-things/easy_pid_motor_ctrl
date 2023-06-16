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


class SetEncPPRCardFrame(SetCardFrame):
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



class SetPwmCardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "PWM_B", ctrlPwm)

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      global ctrlPwm

      self.value = self.setTextEntry.get()
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

      ctrlPwm = int(self.value)
      # print(ctrlPwm)


class SetDurationCardFrame(SetCardFrame):
    def __init__(self, parentFrame):
      super().__init__(parentFrame, "DURATION", motorOnDuration)

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.__get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

    def __get_data(self):
      global motorOnDuration

      self.value = self.setTextEntry.get()
      self.text = f"{self.mainText} = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

      motorOnDuration = float(self.value)
      # print(motorOnDuration)















class MotorPosCanvas(customtkinter.CTkCanvas):
    def __init__(self, parentFrame):
      super().__init__(master=parentFrame, width=400, height=360, bg='white')


      self.r = 170 # circle radius
      self.m = (200, 180) #x, y
      self.circle = self.create_oval(32, 12, 368, 348, outline="green", width=5)
      self.line = self.create_line(self.m[0], self.m[1], 
                                   self.m[0]+self.r*cos(radians(theta-initialTheta)), 
                                   self.m[1]+self.r*sin(radians(theta-initialTheta)), 
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

      self.after(1, self.draw_motor_ang_pos)

    def draw_motor_ang_pos(self):
      global motorIsOn, motorOnDuration, motorOnStartTime, initialTheta, theta, angPosB, angVelB
      if motorIsOn and motorOnDuration < time.time()-motorOnStartTime:
          isSuccess = serClient.send("pwm", 0, 0)
          if isSuccess:
            motorIsOn = False
            # print('Motor off', isSuccess)
      self.delete(self.line)
      self.delete(self.mid_circle)
      angPosB, angVelB = serClient.get("dataB")
      theta = round(self.absAngDeg(angPosB),2)

      self.line = self.create_line(self.m[0], self.m[1], 
                                   self.m[0]+self.r*cos(radians(theta-initialTheta)), 
                                   self.m[1]+self.r*sin(radians(theta-initialTheta)), 
                                   fill='blue',width=15)
      self.mid_circle = self.create_oval(180, 160, 220, 200, fill="green", outline="blue")

      self.angPosDisplayLabelVal.configure(text=f"{angPosB}")
      self.angVelDisplayLabelVal.configure(text=f"{angVelB}")

      self.after(1, self.draw_motor_ang_pos)

    def absAngDeg(self, incAngRad):
      incAngDeg = incAngRad * 180.0 / pi
      return incAngDeg % 360.0














class App(customtkinter.CTk):
    def __init__(self):
      super().__init__()

      self.motorOnDuration = 2 #sec
      self.motorOnStartTime = time.time()
      self.motorIsOn = False

      self.value = 345
      self.text = f"VALUE = {self.value}"

      # configure window
      self.title("encoder_setup_and_view")
      self.geometry(f"{800}x{750}")

      self.mainframe = customtkinter.CTkFrame(master=self)
      self.mainframe.pack(padx=40, pady=40)

      self.mainframe.grid_columnconfigure((0,1,2), weight=0)
      self.mainframe.grid_rowconfigure((0,1,2,3,4,5), weight=0)

      # add set card frame
      self.setEncPPRCardFrame = SetEncPPRCardFrame(self.mainframe)
      self.setEncPPRCardFrame.grid(row=0, column=0, padx=(20,10), pady=10)

      self.setPwmCardFrame = SetPwmCardFrame(self.mainframe)
      self.setPwmCardFrame.grid(row=0, column=1, padx=10, pady=10)

      self.setDurationCardFrame = SetDurationCardFrame(self.mainframe)
      self.setDurationCardFrame.grid(row=0, column=2, padx=10, pady=10)

      # add buttons
      self.resetHandButton = customtkinter.CTkButton(self.mainframe, text="RESET HAND", command=self.resetInitialTheta)
      self.resetHandButton.grid(row=1, column=0, columnspan=2, padx=(20,5) , pady=(100, 10), ipadx=5, ipady=5)

      # self.handRuleButton = customtkinter.CTkButton(self.mainframe, text="RIGHT HAND RULE", command=self.changeHandRule)
      # self.handRuleButton.grid(row=1, column=1, padx=(5,20), pady=(100, 10), ipadx=5, ipady=5, sticky="w")

      self.sendPulsedCmdButton = customtkinter.CTkButton(self.mainframe, text="SEND PULSED COMMAND", command=self.sendPwmCtrl)
      self.sendPulsedCmdButton.grid(row=1, column=2, padx=20, pady=(100, 10), ipadx=5, ipady=5)

      # add canvas
      self.motorPosCanvas = MotorPosCanvas(self.mainframe)
      self.motorPosCanvas.grid(row=2, column=0, rowspan=4, columnspan=2, pady=(10, 20))

      


    def sendPwmCtrl(self):
        global motorIsOn, motorOnStartTime, ctrlPwm
        if motorIsOn:
          isSuccess = serClient.send("pwm", 0, 0)
          if isSuccess:
            motorIsOn = False
            # print('Motor off', isSuccess)
        else:
          isSuccess = serClient.send("pwm", 0, ctrlPwm)
          if isSuccess:
            motorIsOn = True
            motorOnStartTime = time.time()
            # print('Motor On', isSuccess)

    def resetInitialTheta(self):
        global initialTheta, theta
        initialTheta = theta + 90

        
        














if __name__ == "__main__":
  motorOnDuration = 5 #sec
  motorOnStartTime = time.time()
  motorIsOn = False
  ctrlPwm = 120
  initialTheta = 90.0
  theta = 0.0
  # rightHandRule = True
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