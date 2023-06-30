from math import sin, cos, radians, pi
import time
from appGlobals import g, setPulseDuration, SetDataCardFrame
import customtkinter


def setPwmValA(text):
  val = int(text)
  if val > 255:
    g.ctrlPwmA = 255
  elif val < -255:
    g.ctrlPwmA = -255
  else:
    g.ctrlPwmA = val

  return g.ctrlPwmA


def setEncAppr(text):
  isSuccessful = g.serClient.send("pprA", float(text))
  val = int(g.serClient.get("pprA"))
  g.pprA = val

  return g.pprA


def sendPwmCtrlA():
  if g.motorAIsOn:
    isSuccess = g.serClient.send("pwm", 0, 0)
    if isSuccess:
      g.motorAIsOn = False
      # print('Motor off', isSuccess)
  else:
    isSuccess = g.serClient.send("pwm", g.ctrlPwmA, 0)
    if isSuccess:
      g.motorAIsOn = True
      g.motorAOnStartTime = time.time()
      # print('Motor On', isSuccess)


def resetInitialThetaA():
  g.initialThetaA = g.thetaA + 90











class MotorAPosCanvas(customtkinter.CTkFrame):
  def __init__(self, parentFrame):
    super().__init__(parentFrame)

    # self.grid_rowconfigure((0,1), weight=0)
    # self.grid_columnconfigure((0,1), weight=0)
    
    self.myCanvas = customtkinter.CTkCanvas(master=self, width=400, height=360, bg='white')
    self.r = 170 # circle radius
    self.m = (200, 180) #x, y
    self.circle = self.myCanvas.create_oval(32, 12, 368, 348, outline="grey", width=5)
    self.line = self.myCanvas.create_line(self.m[0], self.m[1], 
                                  self.m[0]+self.r*cos(radians(g.thetaA-g.initialThetaA)), 
                                  self.m[1]+self.r*sin(radians(g.thetaA-g.initialThetaA)), 
                                  fill='#434242',width=15)
    self.mid_circle = self.myCanvas.create_oval(180, 160, 220, 200, fill="grey", outline="#434242")

    self.myCanvas.grid(row=0, rowspan=4, column=0, columnspan=2, padx=(5,5), pady=10)

    # add display label
    self.angPosDisplayLabel = customtkinter.CTkLabel(self, text="angPosA (rad): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=250)
    self.angPosDisplayLabel.grid(row=0, column=2, padx=(5,5), pady=10, sticky="w")

    self.angPosDisplayLabelVal = customtkinter.CTkLabel(self, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=250)
    self.angPosDisplayLabelVal.grid(row=1, column=2, padx=(5,5), pady=10, sticky="nw")

    self.angVelDisplayLabel = customtkinter.CTkLabel(self, text="angVelA (rad/s): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=250)
    self.angVelDisplayLabel.grid(row=2, column=2, padx=(5,5), pady=10, sticky="w")

    self.angVelDisplayLabelVal = customtkinter.CTkLabel(self, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=250)
    self.angVelDisplayLabelVal.grid(row=3, column=2, padx=(5,5), pady=10, sticky="nw")

    self.myCanvas.after(1, self.draw_motor_ang_pos)

  def draw_motor_ang_pos(self):
    try:
      if g.motorAIsOn and g.motorOnDuration < time.time()-g.motorAOnStartTime:
          isSuccess = g.serClient.send("pwm", 0, 0)
          if isSuccess:
            g.motorAIsOn = False
            # print('Motor off', isSuccess)
      self.myCanvas.delete(self.line)
      self.myCanvas.delete(self.mid_circle)
      g.angPosA, g.angVelA = g.serClient.get("dataA")
      g.thetaA = round(self.absAngDeg(g.angPosA),2)

      self.line = self.myCanvas.create_line(self.m[0], self.m[1], 
                                    self.m[0]+self.r*cos(radians(g.thetaA-g.initialThetaA)), 
                                    self.m[1]+self.r*sin(radians(g.thetaA-g.initialThetaA)),  
                                    fill='#434242',width=15)
      self.mid_circle = self.myCanvas.create_oval(180, 160, 220, 200, fill="grey", outline="#434242")

      self.angPosDisplayLabelVal.configure(text=f"{g.angPosA}")
      self.angVelDisplayLabelVal.configure(text=f"{g.angVelA}")
    except:
      pass

    self.myCanvas.after(1, self.draw_motor_ang_pos)

  def absAngDeg(self, incAngRad):
    incAngDeg = incAngRad * 180.0 / pi
    return incAngDeg % 360.0


















class EncASetupFrame(customtkinter.CTkFrame):
  def __init__(self, parent):
    super().__init__(parent)

    self.grid_columnconfigure((0,1,2), weight=0)
    self.grid_rowconfigure((0,1,2,3,4,5,6), weight=0)

    # add heading
    self.heading = customtkinter.CTkLabel(self, text="MOTOR A ENCODER SETUP", font=customtkinter.CTkFont(size=25, weight="bold", underline=True))
    self.heading.grid(row=0, column=0, columnspan=3, padx=10, pady=(5,25))

    # add set card frame
    self.setPwmCardFrame = SetDataCardFrame(self, "PPR_A", g.serClient.get("pprA"), set_func=setEncAppr)
    self.setPwmCardFrame.grid(row=1, column=0, padx=(20,10), pady=10)

    self.setPwmCardFrame = SetDataCardFrame(self, "PWM_A", g.ctrlPwmA, set_func=setPwmValA)
    self.setPwmCardFrame.grid(row=1, column=1, padx=10, pady=10)

    self.setDurationCardFrame = SetDataCardFrame(self, "DURATION", g.motorOnDuration, set_func=setPulseDuration)
    self.setDurationCardFrame.grid(row=1, column=2, padx=10, pady=10)


    # add buttons
    self.resetHandButton = customtkinter.CTkButton(self, text="RESET HAND", 
                                                   fg_color='#9BABB8', text_color='black', hover_color='#EEEEEE',
                                                   command=resetInitialThetaA)
    self.resetHandButton.grid(row=2, column=0, columnspan=2, padx=(20,5) , pady=(100, 10), ipadx=5, ipady=5)

    self.sendPulsedCmdButton = customtkinter.CTkButton(self, text="SEND PULSED COMMAND", 
                                                       fg_color='#256D85', text_color='white',
                                                       command=sendPwmCtrlA)
    self.sendPulsedCmdButton.grid(row=2, column=2, padx=20, pady=(100, 10), ipadx=5, ipady=5)

    # add canvas
    self.motorAPosCanvas = MotorAPosCanvas(self)
    self.motorAPosCanvas.grid(row=3, column=0, columnspan=3, padx=5, pady=5)











# class App(customtkinter.CTk):
#     def __init__(self):
#       super().__init__()

#       # configure window
#       self.title("encoder_setup_and_view")
#       self.geometry(f"{800}x{750}")

#       self.encASetupFrame = EncASetupFrame(self)
#       self.encASetupFrame.pack(padx=20, pady=20)










# if __name__ == "__main__":

#   #################################################################
#   g.serClient = SerialClient('/dev/ttyUSB0', 115200, 0.1)
#   time.sleep(4)
#   isSuccessful = g.serClient.send("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
#   print(isSuccessful)
#   #################################################################

#   app = App()
#   app.mainloop()