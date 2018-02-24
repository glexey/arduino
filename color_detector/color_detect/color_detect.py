# Receive R, G, B values over a serial COM port
# and display the corresponding color

import serial
import time
import sys
import os
from tkinter import *

# Find COM port (highest-numbered one)
port = 9
while True:
    try:
        ser = serial.Serial('COM%d'%port, 9600, timeout=10)
        break
    except serial.serialutil.SerialException:
        port -= 1
        if port == 0:
            raise

def task():
    # This procedure reads a string from a serial port
    # and configures main window with corresponding
    # background color
    try:
        data = map(int, ser.readline(100).strip().split())
        print ">>>", data
        root.configure(background="#%02x%02x%02x"%tuple(data[3:6]))
    except:
        pass
    root.after(20, task) # repeat after a small pause

root = Tk()
root.after(20, task) # schedule to run a main task
root.mainloop()
