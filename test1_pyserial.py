import cv2
from cvzone.HandTrackingModule import HandDetector
import math
import numpy as np
import cvzone

import serial
import time

# Webcam
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)  # cv2.CAP_DSHOW for faster loading
cap.set(3, 960)  # width
cap.set(4, 640)  # height

#Error handling if webcam is not deteced
if not cap.isOpened():
    print("Error: Could not open the camera.")
    exit()
    
# Hand Detector
detector = HandDetector(detectionCon=0.8, maxHands=2)

# Find Function
# x is the raw distance y is the value in cm
x = [300, 245, 200, 170, 145, 130, 112, 103, 93, 87, 80, 75, 70, 67, 62, 59, 57]
y = [20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]
coff = np.polyfit(x, y, 2)  # y = Ax^2 + Bx + C

# Loop
while True:
    success, img = cap.read()       # Capture the video frame
    flipped = cv2.flip(img, 1)      # flip the video frame

    hands, img = detector.findHands(flipped,flipType=False)

    if hands:
        lmList = hands[0]['lmList']
        x, y, w, h = hands[0]['bbox']
        
        x1, y1, c1 = lmList[5]
        x2, y2, c2 = lmList[17]
        
        distance = int(math.sqrt((y2 - y1) ** 2 + (x2 - x1) ** 2))
        A, B, C = coff
        distanceCM = A * distance ** 2 + B * distance + C

        #print(distanceCM, distance)

        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 255), 3)
        cvzone.putTextRect(img, f'{int(distanceCM)} cm', (x+5, y-10))

    cv2.imshow("Image", flipped)

    # Check for the 'q' key to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video capture object and close all windows
cap.release()
cv2.destroyAllWindows()

# Define the serial port (change this to match your Arduino's port)
serial_port = 'COM10'  # On Linux, it might look like this '/dev/ttyUSB0'
# For Windows, it may look like: 'COM1'

# Define the baud rate to match the Arduino sketch
baud_rate = 9600

try:
    # Open the serial port
    arduino = serial.Serial(serial_port, baud_rate, timeout=1)
    time.sleep(0.5)  # Wait for the Arduino to initialize

    while True:
        # Send the user's command to the Arduino
        arduino.write(distanceCM.encode())
        time.sleep(1)  # Wait for the Arduino to respond

        arduino.flush()  # Flush the serial buffer
        time.sleep(1)  # Allow some time for the Arduino to respond

        #arduino_response = arduino.readline().decode().strip()  # Read Arduino's response
        #print(f"Arduino: {arduino_response}")

        #arduino_data = arduino.readline().decode().strip()
        #print(arduino_data)

except serial.SerialException as e:
    print(f"An error occurred: {str(e)}")
finally:
    # Close the serial port when done
    if 'arduino' in locals():
        arduino.close()
