import cv2
from cvzone.HandTrackingModule import HandDetector
import math
import numpy as np
import cvzone

# Webcam
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)  # cv2.CAP_DSHOW for faster loading
# Check if the camera opened successfully
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

cap.set(3, 1280)  # width
cap.set(4, 720)  # height

# Hand Detector
detector = HandDetector(detectionCon=0.8, maxHands=1)

# Find Function
# x is the raw distance y is the value in cm
x = [300, 245, 200, 170, 145, 130, 112, 103, 93, 87, 80, 75, 70, 67, 62, 59, 57]
y = [20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]
coff = np.polyfit(x, y, 2)  # y = Ax^2 + Bx + C

# Loop
while True:
    success, original = cap.read()  # Capture the video frame
    img = cv2.flip(original, 1)  # flip the image

    # Check if the frame was captured successfully
    if not success:
        print("Error: Could not read frame.")
        break

    hands, img = detector.findHands(img, draw=False)

    if hands:
        lmList = hands[0]['lmList']
        x, y, w, h = hands[0]['bbox']
        x1, y1 = lmList[5]
        x2, y2 = lmList[17]

        distance = int(math.sqrt((y2 - y1) ** 2 + (x2 - x1) ** 2))
        A, B, C = coff
        distanceCM = A * distance ** 2 + B * distance + C

        # print(distanceCM, distance)

        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 255), 3)
        cvzone.putTextRect(img, f'{int(distanceCM)} cm', (x+5, y-10))

    cv2.imshow("Image", img)

    # Check for the 'q' key to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video capture object and close all windows
cap.release()
cv2.destroyAllWindows()
