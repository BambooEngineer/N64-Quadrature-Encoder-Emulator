# AVR Atmega168/328 N64-Quadrature-Encoder-Emulator
This Sketch emulates the N64 controller's quadrature encoder. If using a 5 Volt microcontroller there needs to be a logic level converter between the GPIO outputs and the Quadrature Encoder input pins on the N64 controller. 

The N64 controller has 6 quadrature encoder pins, this is the pinout from the front view of the original controller PCB from left to right for the quadrature encoder. 

X-, Voltage, GND, X+, Y+, Y- 

GPIO : 9, 6, 5, 3

The GPIO output pins are wired to the AXIS pins Left to Right. Ground has to be shared across the controller and microcontroller.


