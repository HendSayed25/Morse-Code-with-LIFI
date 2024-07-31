import os
import tkinter as tk
from tkinter import ttk
import serial
import threading
import pyttsx3

# Configure the serial connection
ser = serial.Serial('COM6', 9600)  # Replace 'COM6' with the correct port for your system
FONT = ('Tahoma', 25, 'bold')

# Initialize the pyttsx3 engine
engine = pyttsx3.init()
# initialize engine
engine.setProperty('rate', 125)  # speed of talking
engine.setProperty('volume', 2.0)  # sound
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[1].id)  # female sound


def read_from_serial():
    sound = ""
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip('\r\n')
            if line and sound!=line:  # Ensure line is not empty
                root.after(0, update_label_and_speak, line) # Schedule the update on the main thread
                sound=line


def update_label_and_speak(data):
    text_label.config(text=data)
    if (data):
        play_sound(data)


def play_sound(data):
    engine.say(data)
    engine.runAndWait()


# Set up the GUI
root = tk.Tk()
root.title("Morse Code Translator Using Lifi :)")

# Set the background color to pink
root.configure(bg='pink')

# Set the size of the frame
frame_width = 500
frame_height = 400

# Center the main frame and set its size and background color
main_frame = tk.Frame(root, bg='pink', width=frame_width, height=frame_height)
main_frame.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

# Create and configure the label
text_label = ttk.Label(main_frame, text="Waiting for data...", background='pink', font=FONT)
text_label.grid(row=0, column=0, pady=10)

# Set the initial window size and center it on the screen
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
x_cordinate = int((screen_width / 2) - (frame_width / 2))
y_cordinate = int((screen_height / 2) - (frame_height / 2))
root.geometry(f"{frame_width}x{frame_height}+{x_cordinate}+{y_cordinate}")

# Start the serial reading in a separate thread
thread = threading.Thread(target=read_from_serial)
thread.daemon = True  # Ensure the thread exits when the program does
thread.start()

root.mainloop()
ser.close() #closing the serial
