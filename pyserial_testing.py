import serial
import time

# Define the serial port (change this to match your Arduino's port)
serial_port = 'COM11'  # On Linux, it might look like this '/dev/ttyUSB0'
# For Windows, it may look like: 'COM1'

# Define the baud rate to match the Arduino sketch
baud_rate = 9600

try:
    # Open the serial port
    arduino = serial.Serial(serial_port, baud_rate, timeout=1)
    time.sleep(0.5)  # Wait for the Arduino to initialize

    while True:
        # Get a command from the user
        user_input = input("Enter a command (A, B, or Q to quit): ")

        # Check if the user wants to quit
        if user_input.upper() == 'Q':
            break

        # Send the user's command to the Arduino
        arduino.write(user_input.encode())
        #time.sleep(1)  # Wait for the Arduino to respond

        arduino.flush()  # Flush the serial buffer
        #time.sleep(1)  # Allow some time for the Arduino to respond

        arduino_response = arduino.readline().decode().strip()  # Read Arduino's response
        print(f"Arduino: {arduino_response}")

        #arduino_data = arduino.readline().decode().strip()
        #print(arduino_data)

except serial.SerialException as e:
    print(f"An error occurred: {str(e)}")
finally:
    # Close the serial port when done
    if 'arduino' in locals():
        arduino.close()
