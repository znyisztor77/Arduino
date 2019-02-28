#include <RGBLed.h>  //https://github.com/manghao/RGBLed

RGBLed led(9, 10, 11, COMMON_CATHODE); //PWM pin leds  Digital pins  D9, D10, D11

void setup() { }

void loop() {
	
  led.fadeIn(255, 0, 0, 5, 200); //red
  led.fadeOut(255, 0, 0, 5, 200); // red
  
  led.fadeIn(0, 255, 0, 5, 200); //green
  led.fadeOut(0, 255, 0, 5, 200); //green

  led.fadeIn(0, 0, 255, 5, 200); //green
  led.fadeOut(0, 0, 255, 5, 200); //green

  led.fadeIn(255, 255, 0, 5, 200); //yellow
  led.fadeOut(255, 255, 0, 5, 200); //yellow

  led.fadeIn(80, 0, 80, 5, 200); //purple
  led.fadeOut(80, 0, 80, 5, 200); //purple

  led.fadeIn(0, 255, 255, 5, 200); //aqua
  led.fadeOut(0, 255, 255, 5, 200); //aqua

  led.fadeIn(255, 255, 255, 5, 200); //white
  led.fadeOut(255, 255, 255, 5, 200); //white

  


	

	
}
