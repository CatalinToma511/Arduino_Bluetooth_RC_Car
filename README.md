# Arduino_Bluetooth_RC_Car
A simple RC car made with an Arduino Nano board, a Bluetooth module controlled with smartphone.

Car controller is an Android smartphone with this application: https://play.google.com/store/apps/details?id=com.electro_tex.bluetoothcar&hl=en&gl=US

The car was made using:
-a cheap toy car
-12V battery
-Arduino Uno
-HC-05 Bluetooth module
-4 independent TT motors(1)
-L293N motor driver
-MG996R servo for steering
-modified MG90S servo as a winch(2)
-LEDs, resistors and transistors
(1) the front axle and steering was made using PCV pipe
(2) the potentiometer of the servo's controller was replaced with a voltage divider made from 2x 2.5 kOhm resistors, so now it acts as a bidirectional brushed ESC

Features:
-proportional steering (*it can be done with a better controller app*)
-proportional acceleration
-torque vectoring (*depending of steering, the inside wheels will spin at a lower speed than the outside wheels*)
-day running lights, low beam, high beam (2x 1W LED), off-road projectors (4x 1W LED)
-turning lights
-brake lights, reverse lights
-winch
-underglow
-tank steering mode (*left wheels will spin in one direction and the right wheels will spin in the other direction allowing the car to rotate without moving forwards or backwards*)
