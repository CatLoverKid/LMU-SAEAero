necessary# LMU SAE Aero Demonstration instructions

## Hardware Requirements
* **Arduino microcontroller**: Any Arduino microcontroller that runs on the ATmega328 will work. For this project, and for all live demonstrations, we used the [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3), the [Arduino Mega](https://store.arduino.cc/usa/arduino-mega-2560-rev3), and the [Arduino Nano](https://store.arduino.cc/usa/arduino-nano). All of which run on the ATmega328-p flavor.
* **XBee S2 Module**: Any Xbee module will work here, so long as it is Series 2. For the final implementation, we will be using a Series 1; however, for this demonstration, we decided to use the cheaper S2 modules.
* **XBee shield**: Any aftermarket XBee shield for connecting to an Arduino will work. For this demonstration we used a [Foca Pro: USB To Serial UART Converter With XBee Interface Socket V2.2](https://www.itead.cc/foca-pro.html)
* **GPS Module**: For our demonstration we used a [Adafruit Ultimate GPS featherwing](https://learn.adafruit.com/adafruit-ultimate-gps-featherwing/overview). The code has not been tested or demonstrated on any other GPS boared, and currently implements the Adafruit_GPS library. Modifications to the code will be required in order to use a different GPS shield.
* **Accelerometer Module**: For this project we used the [Pololu MinIMU-9 v5 Gyro, Accelerometer, and Compass (LSM6DS33 and LIS3MDL Carrier)](https://www.pololu.com/product/2738). The product specifically points to a particular library, and we did not test additional components to potentially replace this one. Changes to the code may be necessary in order to support other product solutions.
* **Servo Motors**: Any standard servo motor will work for this application. For the sake of demonstration, we weren't concerned with acquiring the most powerful servos, and used the ones on hand. Changes to the codebase are not required. However, an additional power supply may be required if the servo draws more than the Arduino can provide. This particular implementation requires two servos
* **100µF capacitor**: A capacitor is required in order to provide the PWM-driven servos with a steady supply of power. Any fluctuations in the supply will cause them to act erratically, so if you experience problematic servos, then a larger capacitor is recommended.
* **USB 2.0 Type A cable**: Any USB 2.0 Type A cable can be used to connect the Arduino to the computer for flashing the internal memory of the Arduino.

## Software Requirements
* **Arduino IDE**: [The Arduino IDE](https://www.arduino.cc/en/Main/Software) is essential for taking the C++ code written in a .ino file, and converting it to Machine code that the ATmega328 can read.
* **OPTIONAL: XCTU**: [XCTU](https://www.digi.com/products/xbee-rf-solutions/xctu-software/xctu) is the software we use to configure and log the output of an XBee module. We use it during our demonstration process in order to inform the audience as to how our device is functioning. If you want to see the output of the XBee log, then you will need an additional XBee and XBee to USB shield.



## INSTRUCTIONS:
1. Assemble the Circuit as shown in the included diagram. Refer above for any necessary hardware substitutions.
2. Download and install [The Arduino IDE](https://www.arduino.cc/en/Main/Software), and ensure that you can properly open DemoCDA.ino
3. Plug the Arduino into your computer, and ensure that the Arduino has LEDs onboard. The name of the LED varies by manufacturer, but you should always see at least one.
4. within the Arduino IDE, with DemoCDA.ino open. Navigate to Tools -> Port -> and Select which port shows an Arduino listed next to it. If the Arduino is not listed among your ports list, check to ensure you have the Arduino connected properly.
5. Navigate to Tools -> Board -> and select the appropriate board from the list. The aforementioned boards are all referred to as "Genuino"
6. If this is your first time running the program, navigate to Sketch -> Include Library -> Manage Libraries, and install the LSM6 Library by Pololu, and the Adafruit_GPS Library by Adafruit.
7. Ensure that the code can compile properly by clicking the large check mark in the top left corner.
8. Flash the program to the Arduino with the blue arrow to the right of the check mark.
9. You will see the TX and RX LEDs onboard the Arduino flash as the code is being written. Once the write is complete, it will begin execution immediately.
10. The Serial monitor can be opened with Ctrl+Shift+M. Provided that the global constant `DEBUG_MODE` is set to `True` in the code, it will allow you to see output from the device here.
11. Feel free to move the Accelerometer from side to side along the X axis, and ensure that the servos are responding properly.
