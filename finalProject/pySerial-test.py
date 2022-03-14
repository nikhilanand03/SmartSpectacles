#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 11 22:30:20 2022

@author: nikhilanand

Assumptions: Firstly we assume accurate data provided by the mics to the Serial. This data is then stored into an array and passed into the algorithm.
Secondly, we assume the algorithm works and provides an accurate angle. This angle can then be passed back to the Serial as an input so that the code
lights up an LED accordingly.
"""

import serial
import time
import csv
import numpy as np
from scipy.fft import fft, fftfreq
from matplotlib import pyplot as plt
import cmath
import webbrowser

input = np.array([[],[],[],[]])
theta = np.array([])
cosk = np.array([])
sink = np.array([])
D1 = np.array([])
D2 = np.array([])
D3 = np.array([])
D4 = np.array([])

mic1 = []
mic2 = []

count = 0

ser = serial.Serial('/dev/cu.usbserial-0001')
ser.flushInput() 

plot_window = 20
y_var = np.array(np.zeros([plot_window]))

#webbrowser.open('http://192.168.4.1/H')

class Arduino():
    """
    Models an Arduino connection
    """

    def __init__(self, serial_port='/dev/ttyACM0', baud_rate=115200,
            read_timeout=5):
        """
        Initializes the serial connection to the Arduino board
        """
        self.conn = serial.Serial(serial_port, baud_rate)
        self.conn.timeout = read_timeout # Timeout for readline()

    def set_pin_mode(self, pin_number, mode):
        """
        Performs a pinMode() operation on pin_number
        Internally sends b'M{mode}{pin_number} where mode could be:
        - I for INPUT
        - O for OUTPUT
        - P for INPUT_PULLUP MO13
        """
        command = (''.join(('M',mode,str(pin_number)))).encode()
        #print 'set_pin_mode =',command,(''.join(('M',mode,str(pin_number))))
        self.conn.write(command)

    def digital_read(self, pin_number):
        """
        Performs a digital read on pin_number and returns the value (1 or 0)
        Internally sends b'RD{pin_number}' over the serial connection
        """
        command = (''.join(('RD', str(pin_number)))).encode()
        self.conn.write(command)
        line_received = self.conn.readline().decode().strip()
        header, value = line_received.split(':') # e.g. D13:1
        if header == ('D'+ str(pin_number)):
            # If header matches
            return int(value)

    def digital_write(self, pin_number, digital_value):
        """
        Writes the digital_value on pin_number
        Internally sends b'WD{pin_number}:{digital_value}' over the serial
        connection
        """
        command = (''.join(('WD', str(pin_number), ':',
            str(digital_value)))).encode()
        self.conn.write(command) 
     
    def analog_read(self, pin_number):
        """
        Performs an analog read on pin_number and returns the value (0 to 1023)
        Internally sends b'RA{pin_number}' over the serial connection
        """
        command = (''.join(('RA', str(pin_number)))).encode()
        self.conn.write(command) 
        line_received = self.conn.readline().decode().strip()
        header, value = line_received.split(':') # e.g. A4:1
        if header == ('A'+ str(pin_number)):
            # If header matches
            return int(value)

    def analog_write(self, pin_number, analog_value):
        """
        Writes the analog value (0 to 255) on pin_number
        Internally sends b'WA{pin_number}:{analog_value}' over the serial
        connection
        """
        command = (''.join(('WA', str(pin_number), ':',
            str(analog_value)))).encode()
        self.conn.write(command) 

    def close(self):
        """
        To ensure we are properly closing our connection to the
        Arduino device. 
        """
        self.conn.close()
        print('Connection to Arduino closed')

arduino = Arduino('/dev/cu.usbserial-0001')

while True:
    try:
        ser_bytes = ser.readline()
        try:
            decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
            print(decoded_bytes)
            if(count%2==0):
                mic1.append(decoded_bytes)
            else:
                mic2.append(decoded_bytes)
            count+=1
            if(count>=500):
                break
        except:
            continue
        #     with open("test_data.csv","a") as f:
        #         writer = csv.writer(f,delimiter=",")
        #         writer.writerow([time.time(),decoded_bytes])
        #     y_var = np.append(y_var,decoded_bytes)
        #     y_var = y_var[1:plot_window+1]
        
    except:
        print("Keyboard Interrupt")
        break

ser.close()

m1 = np.array(mic1)
m2 = np.array(mic2)
#print(m1,m2)

SAMPLE_RATE = 2650  # Hertz
DURATION = 500/2650 # Seconds
SD = 500 #product of Samplerate and duration

S1 = fft(m1)
f1 = fftfreq(((SD)) , 1/SAMPLE_RATE)
S2 = fft(m2)
f2 = fftfreq(((SD)) , 1/SAMPLE_RATE)

yf = fft(m1)
xf = fftfreq(((SD)) , 1/SAMPLE_RATE)

# fig = plt.figure()
# fig.set_figwidth(50)
# fig.set_figheight(50)

# plt.plot(xf, np.abs(yf))
# plt.grid()
# plt.show()

# print("Max-Frequency:")
# print(xf[np.abs(yf).argmax()])

# try:
#     ser = serial.Serial('/dev/cu.usbserial-0001')
#     ser.flushInput()
# except serial.SerialException:
#   serial.Serial("/dev/cu.usbserial-0001", 115200).close()
#   print("Port is closed")
#   ser = serial.Serial("/dev/cu.usbserial-0001",115200)
#   print("Port is open again")


arduino.set_pin_mode(27, 'O');
arduino.set_pin_mode(26, 'O');

f1_sum = np.sum(np.abs(S1))
f2_sum = np.sum(np.abs(S2))
if f1_sum > 1.1*f2_sum:
    print("Towards Microphone 1")
    webbrowser.open('http://192.168.4.1/H')
    
    # ser.write(bytes("mic1", 'utf-8'))
elif f2_sum > 1.1*f1_sum:
    print("Towards Microphone 2")
    webbrowser.open('http://192.168.4.1/L')
    # ser.write(bytes("mic2", 'utf-8'))
else:
    print("Can't find, too difficult")
    #webbrowser.open('http://192.168.4.1/H')
    # arduino.digital_write(26,'1');
    # arduino.digital_write(27,'1');
    # ser.write(bytes("notfound", 'utf-8'))
    
# Now we write this value to the Serial based on the  output.
