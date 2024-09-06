# Tori-Tortoise
Year 10 Personal Project - Arduino Robot Tortoise

This is the code for Tori Tortoise, my year 9 and 10 Personal Project robot. The robot has 8 servos, 2 for each leg. It takes in positional data from an ultrasonic distance sensor, and its actions are reported on an OLED display.

## Materials:
- [Arduino Uno](https://store-usa.arduino.cc/collections/boards/products/arduino-uno-rev3)
- 8 x [micro servos](https://www.jaycar.com.au/arduino-compatible-9g-micro-servo-motor/p/YM2758)
- [HC-SR04 ultrasonic distance sensor](https://core-electronics.com.au/hc-sr04-ultrasonic-module-distance-measuring-sensor.html)
- [Power pack](https://www.miniso-au.com/en-au/product/240555/5000mah-power-bank-with-2-usb-ports-model-mc-029-black)
- [1.3" OLED Display](https://www.jaycar.com.au/duinotech-arduino-compatible-13-inch-monochrome-oled-display/p/XC3728)
- [Arduino prototyping board](https://www.jaycar.com.au/duinotech-arduino-compatible-prototyping-shield/p/XC4482)
You may also need :
1. at least 35 x male header pins to plug components into the prototyping shield
2. lots of female-to-female wires
3. A cable to power the arduino with the battery pack
4. Another cable with one end cut off to provide power direct to the prototyping shield instead of a 9V battery

## Wiring diagram
![image](https://github.com/user-attachments/assets/cf6bc70e-b853-4369-a3f1-472b8bd0936c)

## Assembly instructions
1. Download all files
2. Install NewPing, U8glib and Servo libraries to your Arduino software
3. Assemble the circuit on the prototyping shield, following the wiring in wiring.png
4. 3D print all components, including two of every upper and lower leg file
5. Hot glue parts together
6. Upload the code contained in this sketch on to your Arduino Uno and run!
7. Plug all components onto the prototyping board and place this onto the Arduino to power components
