from math import sin, cos, radians, pi
from serial_client_api import SerialClient
import time

import customtkinter

customtkinter.set_appearance_mode("System")  # Modes: "System" (standard), "Dark", "Light"
customtkinter.set_default_color_theme("blue")  # Themes: "blue" (standard), "green", "dark-blue"





class g():
  serClient = None

  motorOnDuration = 5.0 #sec

  motorAOnStartTime = time.time()
  motorAIsOn = False
  ctrlPwmA = 120
  pprA = 20

  initialThetaA = 90.0
  thetaA = 0.0
  angPosA = 0.0
  angVelA = 0.0






def setPulseDuration(text):
  val = abs(float(text))
  if val > 20.0:
    g.motorOnDuration = 20.0
  else:
    g.motorOnDuration = val

  return g.motorOnDuration







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












class SetDataCardFrame(customtkinter.CTkFrame):
  def __init__(self, parentFrame, text, initialValue, set_func):
    super().__init__(master=parentFrame, width=300, corner_radius=10)

    self.value = initialValue
    self.mainText = text
    self.text = f"{self.mainText} = {self.value}"

    self.set_func = set_func

    # set card frame
    self.grid_rowconfigure((0,1), weight=0)
    self.grid_columnconfigure((0,1), weight=0)

    self.setTextLabel = customtkinter.CTkLabel(self, text=self.text, font=customtkinter.CTkFont(size=15, weight="bold"))
    self.setTextLabel.grid(row=0, column=0, columnspan=2, padx=(20,5), pady=10, sticky="w")

    self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
    self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

    self.setButton = customtkinter.CTkButton(self, text="SET", width=50, command=self.set_data_func)
    self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)


  def set_data_func(self):
    self.value = self.set_func(self.setTextEntry.get())
    self.text = f"{self.mainText} = {self.value}"

    self.setTextLabel.configure(text=self.text)
    
    self.setTextEntry.destroy()
    self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
    self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

    print(g.motorOnDuration)
















class MotorAPosCanvas(customtkinter.CTkFrame):
  def __init__(self, parentFrame):
    super().__init__(parentFrame)

    # self.grid_rowconfigure((0,1), weight=0)
    # self.grid_columnconfigure((0,1), weight=0)
    
    self.myCanvas = customtkinter.CTkCanvas(master=self, width=400, height=360, bg='white')
    self.r = 170 # circle radius
    self.m = (200, 180) #x, y
    self.circle = self.myCanvas.create_oval(32, 12, 368, 348, outline="green", width=5)
    self.line = self.myCanvas.create_line(self.m[0], self.m[1], 
                                  self.m[0]+self.r*cos(radians(g.thetaA-g.initialThetaA)), 
                                  self.m[1]+self.r*sin(radians(g.thetaA-g.initialThetaA)), 
                                  fill='blue',width=15)
    self.mid_circle = self.myCanvas.create_oval(180, 160, 220, 200, fill="green", outline="blue")

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
                                  fill='blue',width=15)
    self.mid_circle = self.myCanvas.create_oval(180, 160, 220, 200, fill="green", outline="blue")

    self.angPosDisplayLabelVal.configure(text=f"{g.angPosA}")
    self.angVelDisplayLabelVal.configure(text=f"{g.angVelA}")

    self.myCanvas.after(1, self.draw_motor_ang_pos)

  def absAngDeg(self, incAngRad):
    incAngDeg = incAngRad * 180.0 / pi
    return incAngDeg % 360.0


















class EncASetupFrame(customtkinter.CTkFrame):
  def __init__(self, parent):
    super().__init__(parent)

    self.grid_columnconfigure((0,1,2), weight=0)
    self.grid_rowconfigure((0,1,2,3,4,5), weight=0)


    # add set card frame
    self.setPwmCardFrame = SetDataCardFrame(self, "PPR_A", g.serClient.get("pprA"), set_func=setEncAppr)
    self.setPwmCardFrame.grid(row=0, column=0, padx=(20,10), pady=10)

    self.setPwmCardFrame = SetDataCardFrame(self, "PWM_A", g.ctrlPwmA, set_func=setPwmValA)
    self.setPwmCardFrame.grid(row=0, column=1, padx=10, pady=10)

    self.setDurationCardFrame = SetDataCardFrame(self, "DURATION", g.motorOnDuration, set_func=setPulseDuration)
    self.setDurationCardFrame.grid(row=0, column=2, padx=10, pady=10)


    # add buttons
    self.resetHandButton = customtkinter.CTkButton(self, text="RESET HAND", command=resetInitialThetaA)
    self.resetHandButton.grid(row=1, column=0, columnspan=2, padx=(20,5) , pady=(100, 10), ipadx=5, ipady=5)

    self.sendPulsedCmdButton = customtkinter.CTkButton(self, text="SEND PULSED COMMAND", command=sendPwmCtrlA)
    self.sendPulsedCmdButton.grid(row=1, column=2, padx=20, pady=(100, 10), ipadx=5, ipady=5)

    # add canvas
    self.motorAPosCanvas = MotorAPosCanvas(self)
    self.motorAPosCanvas.grid(row=2, column=0, columnspan=3, padx=5, pady=5)











class App(customtkinter.CTk):
    def __init__(self):
      super().__init__()

      # configure window
      self.title("encoder_setup_and_view")
      self.geometry(f"{800}x{750}")

      self.encASetupFrame = EncASetupFrame(self)
      self.encASetupFrame.pack(padx=20, pady=20)










if __name__ == "__main__":

  #################################################################
  g.serClient = SerialClient('/dev/ttyUSB0', 115200, 0.1)
  time.sleep(4)
  isSuccessful = g.serClient.send("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
  print(isSuccessful)
  #################################################################

  app = App()
  app.mainloop()