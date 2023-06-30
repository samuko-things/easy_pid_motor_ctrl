from math import sin, cos, radians, pi
import time
from appGlobals import g, setPulseDuration, SetDataCardFrame
import customtkinter




def setPwmValB(text):
  val = int(text)
  if val > 255:
    g.ctrlPwmB = 255
  elif val < -255:
    g.ctrlPwmB = -255
  else:
    g.ctrlPwmB = val

  return g.ctrlPwmB


def setEncBppr(text):
  isSuccessful = g.serClient.send("pprB", float(text))
  val = int(g.serClient.get("pprB"))
  g.pprB = val

  return g.pprB


def sendPwmCtrlB():
  if g.motorBIsOn:
    isSuccess = g.serClient.send("pwm", 0, 0)
    if isSuccess:
      g.motorBIsOn = False
      # print('Motor off', isSuccess)
  else:
    isSuccess = g.serClient.send("pwm", 0, g.ctrlPwmB)
    if isSuccess:
      g.motorBIsOn = True
      g.motorBOnStartTime = time.time()
      # print('Motor On', isSuccess)


def resetInitialThetaB():
  g.initialThetaB = g.thetaB + 90










class MotorBPosCanvas(customtkinter.CTkFrame):
  def __init__(self, parentFrame):
    super().__init__(parentFrame)

    # self.grid_rowconfigure((0,1), weight=0)
    # self.grid_columnconfigure((0,1), weight=0)
    
    self.myCanvas = customtkinter.CTkCanvas(master=self, width=400, height=360, bg='white')
    self.r = 170 # circle radius
    self.m = (200, 180) #x, y
    self.circle = self.myCanvas.create_oval(32, 12, 368, 348, outline="grey", width=5)
    self.line = self.myCanvas.create_line(self.m[0], self.m[1], 
                                  self.m[0]+self.r*cos(radians(g.thetaB-g.initialThetaB)), 
                                  self.m[1]+self.r*sin(radians(g.thetaB-g.initialThetaB)), 
                                  fill='#434242',width=15)
    self.mid_circle = self.myCanvas.create_oval(180, 160, 220, 200, fill="grey", outline="#434242")

    self.myCanvas.grid(row=0, rowspan=4, column=0, columnspan=2, padx=(5,5), pady=10)

    # add display label
    self.angPosDisplayLabel = customtkinter.CTkLabel(self, text="angPosB (rad): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=250)
    self.angPosDisplayLabel.grid(row=0, column=2, padx=(5,5), pady=10, sticky="w")

    self.angPosDisplayLabelVal = customtkinter.CTkLabel(self, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=250)
    self.angPosDisplayLabelVal.grid(row=1, column=2, padx=(5,5), pady=10, sticky="nw")

    self.angVelDisplayLabel = customtkinter.CTkLabel(self, text="angVelB (rad/s): ", font=customtkinter.CTkFont(size=15, weight="bold"), width=250)
    self.angVelDisplayLabel.grid(row=2, column=2, padx=(5,5), pady=10, sticky="w")

    self.angVelDisplayLabelVal = customtkinter.CTkLabel(self, text="0.0", font=customtkinter.CTkFont(size=14, weight="bold"), width=250)
    self.angVelDisplayLabelVal.grid(row=3, column=2, padx=(5,5), pady=10, sticky="nw")

    self.myCanvas.after(1, self.draw_motor_ang_pos)

  def draw_motor_ang_pos(self):
    try:
      if g.motorBIsOn and g.motorOnDuration < time.time()-g.motorBOnStartTime:
          isSuccess = g.serClient.send("pwm", 0, 0)
          if isSuccess:
            g.motorBIsOn = False
            # print('Motor off', isSuccess)
      self.myCanvas.delete(self.line)
      self.myCanvas.delete(self.mid_circle)
      g.angPosB, g.angVelB = g.serClient.get("dataB")
      g.thetaB = round(self.absAngDeg(g.angPosB),2)

      self.line = self.myCanvas.create_line(self.m[0], self.m[1], 
                                    self.m[0]+self.r*cos(radians(g.thetaB-g.initialThetaB)), 
                                    self.m[1]+self.r*sin(radians(g.thetaB-g.initialThetaB)),  
                                    fill='#434242',width=15)
      self.mid_circle = self.myCanvas.create_oval(180, 160, 220, 200, fill="grey", outline="#434242")

      self.angPosDisplayLabelVal.configure(text=f"{g.angPosB}")
      self.angVelDisplayLabelVal.configure(text=f"{g.angVelB}")
    except:
      pass
    
    self.myCanvas.after(1, self.draw_motor_ang_pos)

  def absAngDeg(self, incAngRad):
    incAngDeg = incAngRad * 180.0 / pi
    return incAngDeg % 360.0


















class EncBSetupFrame(customtkinter.CTkFrame):
  def __init__(self, parent):
    super().__init__(parent)

    self.grid_columnconfigure((0,1,2), weight=0)
    self.grid_rowconfigure((0,1,2,3,4,5,6), weight=0)

    # add heading
    self.heading = customtkinter.CTkLabel(self, text="MOTOR B ENCODER SETUP", font=customtkinter.CTkFont(size=25, weight="bold", underline=True))
    self.heading.grid(row=0, column=0, columnspan=3, padx=10, pady=(5,25))

    # add set card frame
    self.setPwmCardFrame = SetDataCardFrame(self, "PPR_B", g.serClient.get("pprB"), set_func=setEncBppr)
    self.setPwmCardFrame.grid(row=1, column=0, padx=(20,10), pady=10)

    self.setPwmCardFrame = SetDataCardFrame(self, "PWM_B", g.ctrlPwmB, set_func=setPwmValB)
    self.setPwmCardFrame.grid(row=1, column=1, padx=10, pady=10)

    self.setDurationCardFrame = SetDataCardFrame(self, "DURATION", g.motorOnDuration, set_func=setPulseDuration)
    self.setDurationCardFrame.grid(row=1, column=2, padx=10, pady=10)


    # add buttons
    self.resetHandButton = customtkinter.CTkButton(self, text="RESET HAND", 
                                                   fg_color='#9BABB8', text_color='black', hover_color='#EEEEEE',
                                                   command=resetInitialThetaB)
    self.resetHandButton.grid(row=2, column=0, columnspan=2, padx=(20,5) , pady=(100, 10), ipadx=5, ipady=5)

    self.sendPulsedCmdButton = customtkinter.CTkButton(self, text="SEND PULSED COMMAND", 
                                                       fg_color='#256D85', text_color='white',
                                                       command=sendPwmCtrlB)
    self.sendPulsedCmdButton.grid(row=2, column=2, padx=20, pady=(100, 10), ipadx=5, ipady=5)

    # add canvas
    self.motorBPosCanvas = MotorBPosCanvas(self)
    self.motorBPosCanvas.grid(row=3, column=0, columnspan=3, padx=5, pady=5)
