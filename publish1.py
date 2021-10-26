import paho.mqtt.publish as publish
import serial
import time
import string
import blynklib

blynk = blynklib.Blynk('xlKWLrpC2PpTsmhLaZsVXmG402bUNRul')
ser = serial.Serial("/dev/rfcomm2", 9600)

while True:
    blynk.run()
    if ser.in_waiting > 0:
        rawserial = ser.readline()
        cookedserial = rawserial.decode('utf-8').strip('\r\n')
        message = cookedserial.strip().split()
        publish.single("Temperature", message[1], hostname="34.238.80.81")
        publish.single("SoilMoisture", message[3], hostname="34.238.80.81")
        print(message)
        
        temp = message[1]
        soil = message[3]
        humi = message[5]
        blynk.virtual_write(0, temp)
        blynk.virtual_write(1, humi)
        blynk.virtual_write(2, soil)
        if float(temp) > 30.00:
            blynk.notify(" Time to save your plant")
