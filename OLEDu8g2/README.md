# Plant Communicator

## 1 Introduction

u8g2 is an opensource Arduino powerful library which also runs on RT-Thread RTOS. 

Reference:
https://github.com/olikraus/u8g2/wiki

## 2 Hardware 

Stm32F402   
Breadboard jumper wires (M-M, F-F, M-F wires)   
OLED Module 12864 128x64 I2C (https://www.amazon.com/dp/B09JWN8K99?psc=1&ref=ppx_yo2ov_dt_b_product_details)


## 3 Configuraiton

Enable RTduino

![Diagram 1](https://github.com/RTduino/PlantCommunicator/blob/master/OLEDu8g2/RTduino.jpg?raw=true)

Enable u8g2 library

![Diagram 2](https://github.com/RTduino/PlantCommunicator/blob/master/OLEDu8g2/u8g2.jpg?raw=true)

Note: To setup u8g2, use the correct constructor for your display. The constructor name defines display type, controller, RAM buffer size and communication protocol. 
If your display is not exactly available, try a constructor with the same display controller name.


