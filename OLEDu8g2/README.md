# Plant Communicator

## 1 Introduction

Plant Communicator project is an opensource project.

## 2 Hardware 

Stm32F402   
Breadboard jumper wires (M-M, F-F, M-F wires)   
OLED Module 12864 128x64 I2C (https://www.amazon.com/dp/B09JWN8K99?psc=1&ref=ppx_yo2ov_dt_b_product_details)


## 3 Configuraiton

Enable RTduino

![alt text](http://url/to/img.png)

Enable u8g2 library

![alt text](http://url/to/img.png)

Note: To setup u8g2, use the correct constructor for your display. The constructor name defines display type, controller, RAM buffer size and communication protocol. 
If your display is not exactly available, try a constructor with the same display controller name.