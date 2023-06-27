# Gimbal Control System
This project implements a gimbal control system using an Arduino board and an MPU6050 sensor. The gimbal system is designed to stabilize and control the movement of a camera or other mounted device. It uses a PID (Proportional-Integral-Derivative) controller to calculate the appropriate angles for the gimbal servos based on the sensor readings.

# Features
Real-time stabilization: The system continuously measures the orientation of the MPU6050 sensor and adjusts the angles of the gimbal servos to maintain stability.
PID control: The PID controller calculates the control signals based on the error between the desired setpoint and the actual sensor readings, providing smooth and accurate control.
Servo control: The gimbal control system interfaces with standard servos to control the pan and tilt angles of the gimbal.
# Hardware Requirements
Arduino board (e.g., Arduino Uno)
MPU6050 sensor module
Servo motors (2x) for pan and tilt control
Wires and connectors for connections
# Software Requirements
Arduino IDE (Integrated Development Environment)
Libraries: I2Cdev, MPU6050 (included in the project)


https://user-images.githubusercontent.com/67618917/224310565-0cfa44cb-ffe0-4cea-8333-2a06cf00d2d3.mp4



https://user-images.githubusercontent.com/67618917/224312109-73484b9c-53d3-48a8-b1ff-5049252bcd68.mp4

