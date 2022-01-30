# BluetoothRobot

## Overview
This project allows for an Arduino robot (or any arduino board) to be controlled by a computer via Bluetooth. 

This project contains Python code and Arduino code. The python code is responsible for detecting nearby bluetooth devices, then connecting to the selected arduino device via bluetooth and then sending data to it. The arduino code is reponsible for listening for incoming data and perform arduino actions in response, such as activating servos or motors to move.

But of course this project be instantly applied to communicate with any arduino board with a bluetooth module and not just an entire robot. 

## Requirements
- Python
- Arduino robot: This is primarily made of an Arduino Uno board and motors/servos.
- Arduino bluetooth module conected to the arduino board. 
- Arduino IDE

## Usage
1. Upload the ble.ino file to your arduino board using the Ardiono IDE
2. Turn on the arduino robot, so that the bluetooth module is active and waiting to pair.
3. Open a terminal and navigate to this project directory
4. Launch the python script: $ python Main.py
5. Follow the on-screen steps by selecting the bluetooth module that has been detected by the python program.
- Note: If the bluettoth module is not detected, restart the python program
6. (Optional) If the bluetooth "Write Characteristic" in the python program is not appropriate to write to for your bluetooth module, then uncomment the code in the setupConnection() method so that you can test sending data to each chracteristic until you find one that works. Then use that charactersitic by setting the variable "writeCharacteristic" to it.
7. Then write keyboard inputs to send to the robot.