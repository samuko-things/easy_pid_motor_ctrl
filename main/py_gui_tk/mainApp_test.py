from serial_client_api import SerialClient
import time

import customtkinter

customtkinter.set_appearance_mode("System")  # Modes: "System" (standard), "Dark", "Light"
customtkinter.set_default_color_theme("blue")  # Themes: "blue" (standard), "green", "dark-blue"

from appGlobals import g
from encoderA_setup_frame import EncASetupFrame
from encoderB_setup_frame import EncBSetupFrame




class App(customtkinter.CTk):
    def __init__(self):
      super().__init__()

      # configure window
      self.title("encoder_setup_and_view")
      self.geometry(f"{800}x{750}")

      self.encASetupFrame = EncASetupFrame(self)
      self.encASetupFrame.pack(padx=20, pady=20)

      # self.encBSetupFrame = EncBSetupFrame(self)
      # self.encBSetupFrame.pack(padx=20, pady=20)







if __name__ == "__main__":

  #################################################################
  g.serClient = SerialClient('/dev/ttyUSB0', 115200, 0.1)
  time.sleep(4)
  isSuccessful = g.serClient.send("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
  print(isSuccessful)
  #################################################################

  app = App()
  app.mainloop()