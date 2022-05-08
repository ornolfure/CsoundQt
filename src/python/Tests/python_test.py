import sys
from Tkinter import *

root = Tk()

t =  "Python Information\n"
t += f"executable: {sys.executable}" + "\n"
t += f"version: {sys.version}" + "\n"
t += f"prefix: {sys.prefix}" + "\n"
t += f"exec_prefix: {sys.exec_prefix}" + "\n"

w = Label(root, text=t)
w.pack()
button = Button(root, text="OK", fg="black", command=root.quit)
button.pack()

root.mainloop()
