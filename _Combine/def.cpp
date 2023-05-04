#include "common.h"

/*LED pin*/
int ledB = D3;
int ledR = D6;
int ledG = D5;
int brightness = 0;
int fadeAmount = 5;

/*Sensor Group One */
void read_htaSensor(void)
{
    sensors_event_t humidity, temp;
    register volatile float tempVal = 0.0, humidityVal = 0.0;

    aht.getEvent(&humidity, &temp);

    CHECK_SENSOR(temp.temperature, "Temperature");
    if(sensor_error == ERR)
    {
        Serial.println("Restarting AHT sensor");
        if (!aht.begin())
          {
              Serial.println("Could not restart AHT. Check wiring");
              sensor_error = ERR;
              while (1) delay(10);
          }
        Serial.println("Restarting AHT sensor successful");
        sensor_error = OK;
    }
    CHECK_SENSOR(humidity.relative_humidity, "Humidity");

    tempVal = TO_FAHRENHEIT(temp.temperature);
    humidityVal = humidity.relative_humidity;
   Serial.print("Temperature: "); Serial.print(tempVal); Serial.println(" degrees F");
   Serial.print("Humidity: "); Serial.print(humidityVal); Serial.println("% rH");

    display_oled(&tempVal, &humidityVal);
}

void display_oled(volatile float *temp, volatile float *humidity)
{
    int yaxis = 20;
    u8g2.clearBuffer();                   // clear the internal memory
    u8g2.setFont(u8g2_font_helvB10_tr);   // choose a suitable font

    u8g2.drawStr(1,yaxis,"Temp:");    // write something to the internal memory
    u8g2.setCursor(75, yaxis); // x,y
    u8g2.drawStr(115,yaxis,"F");
    u8g2.print(*temp);

    u8g2.drawStr(1,50,"Humidity");
    u8g2.setCursor(75, 50); // x,y
    u8g2.print(*humidity);
    u8g2.drawStr(115,50,"%");

    u8g2.sendBuffer();
}

/*Sensor Group Two */
void read_touchSensor(void)
{
    long sensorValue = capSensor.capacitiveSensor(30);
    register volatile int ledVal = 0;

    CHECK_SENSOR(sensorValue, "Touch");

    ledVal = map(sensorValue, 0, 2500, 0, 255);
    Serial.print("Captive: "); Serial.println(sensorValue);

    display_led(&ledVal);
}

void display_led(volatile int *ledVal)
{
    analogWrite(ledB, 5 - *ledVal); //this is digital using PWM
    analogWrite(ledR, 10 - *ledVal);
    analogWrite(ledG, 12 - *ledVal);

    brightness = brightness + fadeAmount;

    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;
    }
}

//inline float to_fahrenheit(float celsius) {
//    float fahrenheit = 0.00;
//    asm volatile (
//        "push {lr}\n\t"     // Save the link register on the stack
//        "lsls %0, %0, #3\n\t"   // Multiply Celsius by 9 (shift left by 3 is equivalent to multiplication by 8)
//        "adds %0, %0, %1\n\t"   // Add the result to itself (multiply by 1)
//        "adds %0, %0, #32\n\t"    // Add 32 to the result to convert to Fahrenheit
//        "mov %2, %0\n\t"  // Move the result to the fahrenheit variable
//        "pop {pc}"          // Restore the link register and return
//        : "=r" (fahrenheit)
//        : "r" (celsius), "r" (fahrenheit)
//        : "memory"
//    );
//
//    rt_kprintf("inline asm %f \n", fahrenheit);
//    return fahrenheit;
//}


