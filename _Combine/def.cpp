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
    volatile float tempL = 0.0, humidityL = 0.0;

    aht.getEvent(&humidity, &temp);

    CHECK_SENSOR(temp.temperature, "Temperature");
    CHECK_SENSOR(humidity.relative_humidity, "Humidity");

    tempL = TO_FAHRENHEIT(temp.temperature);
    humidityL = humidity.temperature;
    Serial.print("Temperature: "); Serial.print(tempL); Serial.println(" degrees F");
    Serial.print("Humidity: "); Serial.print(humidityL); Serial.println("% rH");

    display_oled(&tempL, &humidityL);
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
    int ledVal;

    ledVal = map(sensorValue, 0, 2500, 0, 255);
    Serial.print("Captive: "); Serial.println(sensorValue);

    display_led(&ledVal);
}

void display_led(int *ledVal)
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

/*this inline assembly function needs a bug fix*/
float to_fahrenheit(float celsius) {
    float fahrenheit = 0.00;
    asm volatile (
        "push {lr}\n\t"   
        "lsls %0, %0, #3\n\t"
        "adds %0, %0, %1\n\t"
        "adds %0, %0, #32\n\t"
        "mov %2, %0\n\t"
        "pop {pc}"
        : "=r" (fahrenheit)
        : "r" (celsius), "r" (fahrenheit)
        : "memory"
    );

    return fahrenheit;
}
