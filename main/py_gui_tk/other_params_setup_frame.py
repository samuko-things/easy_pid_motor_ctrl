
from serial_client_api import SerialClient

from math import sin, cos, radians, pi
import time
from appGlobals import g, SetDataCardFrame

import tkinter
import tkinter.messagebox
import customtkinter



def setI2Caddress(text):
  try:
    isSuccessful = g.serClient.send("i2c", float(text))
    val = int(g.serClient.get("i2c"))
    g.i2cAddress = val
  except:
    pass
  

  return g.i2cAddress

def resetAllParams():
  isSuccessful = g.serClient.send("reset")
  return isSuccessful







class ParamsSetupFrame(customtkinter.CTkFrame):
  def __init__(self, parent):
    super().__init__(parent, width=500, height=700)

    # add heading
    self.heading = customtkinter.CTkLabel(self, text="OTHER PARAMS SETUP", font=customtkinter.CTkFont(size=25, weight="bold", underline=True))
    self.heading.grid(row=0, column=0, padx=10, pady=(5,25))

    # add set card frame for i2c settings
    self.setPwmCardFrame = SetDataCardFrame(self, "I2C_ADDRESS", int(g.serClient.get("i2c")),
                                            placeHolderText="enter new ADDRESS",
                                            inputBoxWidth=200, set_func=setI2Caddress)
    self.setPwmCardFrame.grid(row=1, column=0, pady=20)

    # add reset button
    self.resetButton = customtkinter.CTkButton(self, text="RESET ALL PARAMETERS TO DEFAULT", font=customtkinter.CTkFont(size=12, weight="bold"),
                                                   fg_color='#9BABB8', text_color='black', hover_color='#EEEEEE',
                                                   command=self.open_reset_dialog_event)
    self.resetButton.grid(row=2, column=0, pady=(50, 20), padx=10, ipadx=10, ipady=10)


  def open_reset_dialog_event(self):
    dialog = customtkinter.CTkInputDialog(text="Enter 'reset' to continue", title="RESET WARNING!!!")
    val = dialog.get_input()
    if val == "reset":
      isSuccessful = resetAllParams()
      if isSuccessful:
        # print(isSuccessful)
        tkinter.messagebox.showinfo("SUCCESS !!!", "Reset was successful. Restart app and controller to take effect")
      else:
        tkinter.messagebox.showinfo("NOT SUCCESFULL !!!", "Attempt to rest was unsuccessful")







# class App(customtkinter.CTk):
#     def __init__(self):
#       super().__init__()

#       # configure window
#       self.title("other params setup")
#       self.geometry(f"{800}x{750}")

#       self.paramsSetupFrame = ParamsSetupFrame(self)
#       self.paramsSetupFrame.pack(padx=20, pady=20)





# if __name__ == "__main__":

#   #################################################################
#   g.serClient = SerialClient('/dev/ttyUSB0', 115200, 0.1)
#   time.sleep(4)
#   isSuccessful = g.serClient.send("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
#   print(isSuccessful)
#   #################################################################

#   app = App()
#   app.mainloop()