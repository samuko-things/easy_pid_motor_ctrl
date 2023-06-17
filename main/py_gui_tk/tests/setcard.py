import tkinter
import tkinter.messagebox
import customtkinter

customtkinter.set_appearance_mode("System")  # Modes: "System" (standard), "Dark", "Light"
customtkinter.set_default_color_theme("dark-blue")  # Themes: "blue" (standard), "green", "dark-blue"


# class App(customtkinter.CTk):
#     def __init__(self):
#       super().__init__()

#       self.value = 345
#       self.text = f"VALUE = {self.value}"

#       # configure window
#       self.title("set card example")
#       self.geometry(f"{500}x{500}")

#       # set card frame
#       self.setCardFrame = customtkinter.CTkFrame(self, width=300, corner_radius=10)
#       self.setCardFrame.grid_rowconfigure((0,1), weight=0)
#       self.setCardFrame.grid_columnconfigure((0,1), weight=0)

#       self.setTextLabel = customtkinter.CTkLabel(self.setCardFrame, text=self.text, font=customtkinter.CTkFont(size=15, weight="bold"))
#       self.setTextLabel.grid(row=0, column=0, columnspan=2, padx=(20,5), pady=10, sticky="w")

#       self.setTextEntry = customtkinter.CTkEntry(self.setCardFrame, placeholder_text="enter new value", width=120)
#       self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

#       self.setButton = customtkinter.CTkButton(self.setCardFrame, text="SET", width=30, command=self.get_data)
#       self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

#       self.setCardFrame.pack()


#     def get_data(self):
#       self.value = self.setTextEntry.get()
#       self.text = f"VALUE = {self.value}"

#       self.setTextLabel.configure(text=self.text)
      
#       self.setTextEntry.destroy()
#       self.setTextEntry = customtkinter.CTkEntry(self.setCardFrame, placeholder_text="enter new value", width=120)
#       self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)


# class App(customtkinter.CTk):
#     def __init__(self):
#       super().__init__()

#       self.value = 345
#       self.text = f"VALUE = {self.value}"

#       # configure window
#       self.title("set card example")
#       self.geometry(f"{500}x{500}")

#       # set card frame
#       self.setCardFrame = customtkinter.CTkFrame(self, width=300, corner_radius=10)
#       self.setCardFrame.grid_rowconfigure((0,1), weight=0)
#       self.setCardFrame.grid_columnconfigure((0,1), weight=0)

#       self.setTextLabel = customtkinter.CTkLabel(self.setCardFrame, text=self.text, font=customtkinter.CTkFont(size=15, weight="bold"))
#       self.setTextLabel.grid(row=0, column=0, columnspan=2, padx=(20,5), pady=10, sticky="w")

#       self.setTextEntry = customtkinter.CTkEntry(self.setCardFrame, placeholder_text="enter new value", width=120)
#       self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)

#       self.setButton = customtkinter.CTkButton(self.setCardFrame, text="SET", width=30, command=self.get_data)
#       self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)

#       self.setCardFrame.pack()


#     def get_data(self):
#       self.value = self.setTextEntry.get()
#       self.text = f"VALUE = {self.value}"

#       self.setTextLabel.configure(text=self.text)

#       self.setTextEntry.destroy()
#       self.setTextEntry = customtkinter.CTkEntry(self.setCardFrame, placeholder_text="enter new value", width=120)
#       self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)


# if __name__ == "__main__":
#     app = App()
#     app.mainloop()







class SetCardFrameA(customtkinter.CTkFrame):
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

      self.setButton = customtkinter.CTkButton(self, text="SET", width=30, command=self.get_data)
      self.setButton.grid(row=1, column=1, padx=(2,10), pady=5, ipadx=3, ipady=3)


    def get_data(self):
      self.value = self.setTextEntry.get()
      self.text = f"VALUE = {self.value}"

      self.setTextLabel.configure(text=self.text)
      
      self.setTextEntry.destroy()
      self.setTextEntry = customtkinter.CTkEntry(self, placeholder_text=f"enter new {self.mainText}", width=120)
      self.setTextEntry.grid(row=1, column=0, padx=(10,3), pady=5, ipadx=3, ipady=3)


class App(customtkinter.CTk):
    def __init__(self):
      super().__init__()

      self.value = 345
      self.text = f"VALUE = {self.value}"

      # configure window
      self.title("set card example")
      self.geometry(f"{800}x{900}")

      self.mainframe = customtkinter.CTkFrame(master=self)
      self.mainframe.pack(pady=20, padx=60, fill="both", expand=True)

      self.mainframe.grid_columnconfigure((0,1,2), weight=0)
      self.mainframe.grid_rowconfigure((0,1,2,3,4,5), weight=0)

      # add set card frame
      self.setCardFrame1 = SetCardFrameA(self.mainframe, "PPRA", 20)
      self.setCardFrame1.grid(row=0, column=0, padx=(20,10), pady=10)

      self.setCardFrame2 = SetCardFrameA(self.mainframe, "PWM", 110)
      self.setCardFrame2.grid(row=0, column=1, padx=10, pady=10)

      self.setCardFrame3 = SetCardFrameA(self.mainframe, "PULSE", 5.0)
      self.setCardFrame3.grid(row=0, column=2, padx=10, pady=10)


if __name__ == "__main__":
    app = App()
    app.mainloop()