from serial_client_api import SerialClient
import time

import customtkinter

# customtkinter.set_appearance_mode("Light")  # Modes: "System" (standard), "Dark", "Light"
# customtkinter.set_default_color_theme("blue")  # Themes: "blue" (standard), "green", "dark-blue"

from appGlobals import g
from encoderA_setup_frame import EncASetupFrame
from encoderB_setup_frame import EncBSetupFrame





class App(customtkinter.CTk):
  def __init__(self):
    super().__init__()

    # configure window
    self.title("encoder_setup_and_view")
    self.geometry(f"{900}x{720}")


    # create sidebar frame with widgets
    self.sidebarFrame = customtkinter.CTkFrame(self, width=140, corner_radius=0)
    self.sidebarFrame.grid(row=0, column=0, padx=5, pady=0, sticky="nsw")
    # self.sidebarFrame.grid_rowconfigure(4, weight=1)

    self.menuLabel = customtkinter.CTkLabel(self.sidebarFrame, text="MENU", font=customtkinter.CTkFont(size=20, weight="bold"), width=150)
    self.menuLabel.grid(row=0, column=0, padx=20, pady=(20, 10))

    self.encASetupMenuButton = customtkinter.CTkButton(self.sidebarFrame, text="MotorA Enc", corner_radius=5,
                                                        font=customtkinter.CTkFont(size=16, weight="bold"),
                                                        fg_color='transparent', text_color='grey', hover_color='#EEEEEE',
                                                        command= lambda: self.indicate(self.encASetupMenuButton, self.encAsetupPage))
    self.encASetupMenuButton.grid(row=1, column=0, padx=10, pady=(40,20), ipadx=10, ipady=10)

    self.encBSetupMenuButton = customtkinter.CTkButton(self.sidebarFrame, text="MotorB Enc", corner_radius=5,
                                                        font=customtkinter.CTkFont(size=16, weight="bold"),
                                                        fg_color='transparent', text_color='grey', hover_color='#EEEEEE',
                                                        command= lambda: self.indicate(self.encBSetupMenuButton, self.encBsetupPage))
    self.encBSetupMenuButton.grid(row=2, column=0, padx=10, pady=20, ipadx=10, ipady=10)


    self.mainFrame = customtkinter.CTkFrame(self)
    self.mainFrame.grid(row=0, column=1, padx=5, pady=0, ipadx=0, ipady=0, sticky="nsw")


    #####################################################################################
    self.encASetupFrame = EncASetupFrame(self.mainFrame)
    self.encASetupFrame.pack()
    self.encASetupMenuButton.configure(fg_color='transparent', text_color='black')
    #####################################################################################


  def hide_indicators(self):
    self.encASetupMenuButton.configure(fg_color='transparent', text_color='grey')
    self.encBSetupMenuButton.configure(fg_color='transparent', text_color='grey')
  
  def indicate(self, button, page):
    self.hide_indicators()
    button.configure(fg_color='transparent', text_color='black')
    self.delete_pages()
    page()

  def delete_pages(self):
    for frame in self.mainFrame.winfo_children():
      frame.destroy()


  def encAsetupPage(self):
    self.encASetupFrame = EncASetupFrame(self.mainFrame)
    self.encASetupFrame.pack()
  
  def encBsetupPage(self):
    self.encBSetupFrame = EncBSetupFrame(self.mainFrame)
    self.encBSetupFrame.pack()







if __name__ == "__main__":

  #################################################################
  g.serClient = SerialClient('/dev/ttyUSB0', 115200, 0.1)
  time.sleep(5)
  isSuccessful = g.serClient.send("mode", 0) # decativate pid mode (activate pwm mode and parameter settings)
  print(isSuccessful)
  #################################################################

  app = App()
  app.mainloop()