const int buttonPin = 2;
int ledPins[] = { 2, 7, 10, 11};
// pinCount = 4;
int pinCount = 4;

void setup() {
   Serial.begin(9600);
   
  
for (int thisPin = 0; thisPin < pinCount; thisPin++) 
    { pinMode(ledPins[thisPin], OUTPUT); // acces the elements of the array 
         pinMode(buttonPin, INPUT); } // initialize the pushbutton pin as an input:
  
  if (digitalRead(buttonPin) == HIGH) 
    {digitalWrite(ledPins[1], HIGH); }
    else {digitalWrite(ledPins[1], LOW);
  }
}

void loop(){
  }
