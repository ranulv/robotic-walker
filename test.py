import cv2

# Define the video capture object with desired settings
cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)

# Check if the camera opened successfully
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

# Define the window for displaying the video feed
cv2.namedWindow('Video Feed', cv2.WINDOW_NORMAL)
cv2.resizeWindow('Video Feed', 640, 480)  # Set your desired window size

while True:
    # Capture the video frame
    ret, frame = cap.read()

    # Check if the frame was captured successfully
    if not ret:
        print("Error: Could not read frame.")
        break

    # Display the resulting frame
    cv2.imshow('Video Feed', frame)

    # Check for the 'q' key to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video capture object and close all windows
cap.release()
cv2.destroyAllWindows()
