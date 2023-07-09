import time
import customtkinter



class g():
  serClient = None

  motorOnDuration = 5.0 #sec

  motorAOnStartTime = time.time()
  motorAIsOn = False
  ctrlPwmA = 120
  pprA = 0

  initialThetaA = 90.0
  thetaA = 0.0
  angPosA = 0.0
  angVelA = 0.0


  motorBOnStartTime = time.time()
  motorBIsOn = False
  ctrlPwmB = 120
  pprB = 0

  initialThetaB = 90.0
  thetaB = 0.0
  angPosB = 0.0
  angVelB = 0.0

  i2cAddress = 0






def setPulseDuration(text):
  val = abs(float(text))
  if val > 20.0:
    g.motorOnDuration = 20.0
  else:
    g.motorOnDuration = val

  return g.motorOnDuration







class SetDataCardFrame(customtkinter.CTkFrame):
  def __init__(self, parentFrame, text, initialValue, set_func, inputBoxWidth=120, placeHolderText='enter'):
    super().__init__(master=parentFrame, width=300, corner_radius=10)

    self.value = initialValue
    self.mainText = text
    self.text = f"{self.mainText} = {self.value}"

    self.placeHolderText = placeHolderText
    self.inputBoxWidth = inputBoxWidth

    self.set_func = set_func

    # set card frame
    self.grid_rowconfigure((0,1), weight=0)
    self.grid_columnconfigure((0,1), weight=0)

    self.setTextLabel = customtkinter.CTkLabel(self, text=self.text, font=customtkinter.CTkFont(size=15, weight="bold"))
    self.setTextLabel.grid(row=0, column=0, columnspan=2, padx=(20,5), pady=10, sticky="w")

    self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=self.placeHolderText, width=self.inputBoxWidth)
    self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

    self.setButton = customtkinter.CTkButton(self, text="SET", corner_radius=5, width=50, 
                                             fg_color='#9BABB8', text_color='black', hover_color='#EEEEEE',
                                             command=self.set_data_func)
    self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)


  def set_data_func(self):
    self.value = self.set_func(self.setTextEntry.get())
    self.text = f"{self.mainText} = {self.value}"

    self.setTextLabel.configure(text=self.text)
    
    self.setTextEntry.destroy()
    self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=self.placeHolderText, width=self.inputBoxWidth)
    self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

