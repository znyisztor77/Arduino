#include <RGBLed.h> //https://github.com/manghao/RGBLed
 int sensorPin = A0;  //Photoresistor Pin  Analog A0

RGBLed led(9, 10, 11, COMMON_CATHODE); //PWM pin leds  Digital pins  D9, D10, D11

void setup() {
  Serial.begin (9600);
  

}

void loop() {
  int value = analogRead (sensorPin);  //Get the brightness value as determined by the sensor
  value = map(value, 400, 900, 5, 255);  //map the low and the high
  value = constrain(value, 1, 255);  //constrain any outliers
  Serial.println(value);
  led.brightness(255, 0, 0, value);  //red
  delay(100);
  led.brightness(0, 255, 0, value);  //green
  delay(100);
  led.brightness(0, 0, 255, value);  //blue
  delay(100);
   led.brightness(255, 255, 0, value); //yellow
  delay(100);
   led.brightness(80 ,0, 80, value);  //purple
  delay(100);
   led.brightness(0, 255, 255, value);  //aqua
  delay(100);
   led.brightness(255 ,255, 255, value); //white
  delay(100);
  
}
