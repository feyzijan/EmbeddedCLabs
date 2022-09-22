# Sources:
# Py Serial documentation https://pyserial.readthedocs.io/en/latest/pyserial_api.html
# Starting Example:  https://maker.pro/pic/tutorial/introduction-to-python-serial-ports

# TODO: Add Code to store the RGB data we read in csv files for later analysis

import serial

serialPort = serial.Serial(port = "COM3", baudrate=9600, parity=serial.PARITY_NONE,
                           bytesize=serial.EIGHTBITS, timeout=3, stopbits=serial.STOPBITS_ONE)

# Common Functions:
# open(): Open the serial port ( automatically opened when we pass in the port parameter to the serial.Serial object
# close(): Close the serial port
# readline(): Read a string
# read(size): Read n bytes
# write(data):  Write to serial port
# in_waiting: Return number of bytes in the buffer

while(1):

    throw = serialPort.read(2)
    serialString = serialPort.read(size=40) #  We are tryin to read: " test "
    #serialString = serialPort.readline()  # We are tryin to read: " test "
    print(serialString.decode('Ascii')) # This print works better
    #print(serialString)


