const int sensorPin = A0; //Photoresistor sensor bekotese https://www.tankonyvtar.hu/hu/tartalom/tamop412A/2011-0010_harsanyi_fizikai_szamitastechnika/ch10s05.html
const int ledPinR = 9; //PWM pin for LEDs (connected in parallel)


void setup () {
  pinMode(ledPinR, OUTPUT);
  
  Serial.begin (9600);
}
void loop () {
  int value = analogRead (sensorPin); //Get the brightness value as determined by the sensor
  //Serial.println (value, DEC);
  value = map(value, 400, 900, 1, 255); //map the low and the high
  value = constrain(value, 1, 255); //constrain any outliers
  Serial.println(value);
  analogWrite(ledPinR, value);
  delay (50);
}
