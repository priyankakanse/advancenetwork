import paho.mqtt.client as mqtt
import serial
import time
import string

ser = serial.Serial("/dev/rfcomm4", 9600)

def on_connect(client, userdata, flags, rc): # func for making connection
 print("Connected to MQTT")
 print("Connection returned result: " + str(rc) )
 client.subscribe("Temperature")
 client.subscribe("SoilMoisture")
 
def on_message(client, userdata, msg): # Func for Sending msg
 print(msg.topic+" "+str(msg.payload))
 msgRec = float(msg.payload.decode("utf-8"))
 if msg.topic == "Temperature":
     if msgRec > 30.00:
        ser.write(str.encode('BUZZ_ON\n'))
     else:
        ser.write(str.encode('BUZZ_OFF\n'))
 if msg.topic == "SoilMoisture":
     if msgRec < 300.00:
         ser.write(str.encode('RL_ON\n'))
         ser.write(str.encode('GL_OFF\n'))
         ser.write(str.encode('YL_OFF\n'))
     elif msgRec > 300.00 and msgRec <400.00:
         ser.write(str.encode('YL_ON\n'))
         ser.write(str.encode('RL_OFF\n'))
         ser.write(str.encode('GL_OFF\n'))
     else:
         ser.write(str.encode('GL_ON\n'))
         ser.write(str.encode('YL_OFF\n'))
         ser.write(str.encode('RL_OFF\n'))

     
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("34.238.80.81", 1883, 60)
client.loop_forever()
