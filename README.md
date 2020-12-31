# __A4988__
A4988 motor driver library
* Constant speed movement
* Movement by degrees and millimetres
* Movement in local and absolute coordinate systems
* Microstepping
# __Microstepping__
The library can handle all microstepping modes supported by A4988 driver (up to 1/16)  
__Warning:__ high RPM + high microstep might not work properly as there is a speed limit for every motor.
# __Motor__
Motor should be a 4-wire stepper motor or a 6-wire stepper motor in 4-wire configuration (leaving central wires out)
# __Connection__
![Configuration](https://user-images.githubusercontent.com/76576112/103371182-6830a100-4b01-11eb-9a4c-b20d923c33a0.jpg)
# __Wiring__
This pin-out works for the example (located in ./examples). All of these can be changed.
* Driver to Arduino:
    * DIR - D9
    * STEP - D10
    * MS1 - 3
    * MS2 - 5
    * MS3 - 6
    * GND - Arduino GND
    * GND - Motor power supply GND
    * VMOT - Motor power supply
    * VDD - Arduino 5V
* Driver to stepper motor (1A,1B,2A,2B, these vary on every motor, check coil specifications of your motor)
* 100 uF capacitor between VMOT - GND
* Make sure the motor power supply voltage is within the range supported by the driver board
# __Code__
The sample code and its explanation are located in ./examples folder.
__To open it:__
* Launch your Arduino IDE
* Go to File > Examples
* Find the A4988 library on the list and open the desired example file.
# __Hardware__
All you need is:
* Arduino board
* A4988 stepper motor driver
* Stepper Motor
* 100 uF capacitor
# __To-do__
* Add linear (accelerated) movement mode