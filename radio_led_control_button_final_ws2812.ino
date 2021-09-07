
/* Rádió  és óra 8digit_7 segment kijelzővel ldr fényerőszabályozással
 *  A0 = ldr fotó ellenállás
 *  A RDA5807 rádió és az RTC I2C buson az A4 és A5 pinen
 *  Rotary encoder a D5 és D6 pinen (frekvencia állítás) 
 *  a rotary kapcsolója a fixen beállított állomások kiválasztása.
 *  A WS2812 a D3 pinre csatlakozik egy 470ohm-os ellenállással.
 *  A ledszalag effekt váltás D2 pinen nyomógombal
 *  A rádió és az óra kiválasztása egy billenő kapcsolóval
 *  A kapcsoló D9 HIGH->rádió LOW->Óra 
 *  A kijelzó  DIN, CLK, LOAD(CS) 
 *              11,  12,   10 pin.
 */
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif 

     
#include <LedControl.h>
#include <Wire.h>
#include <DS3231.h>
#include <RDA5807M.h>

#define FIX_BAND     RADIO_BAND_FM   ///< Csak az FM sáv használata
#define FIX_VOLUME   6 ///< Fixen beallított hangerő
RDA5807M radio;

const byte DP = 0b10000000; //pont beállítása a kijelzőn

LedControl lc = LedControl (11,12,10,1);   //  Arduino pins - DIN, CLK, CS, kijelző

DS3231 rtc (SDA, SCL);
Time dt;
 

int ldr_sensor = A0;
int ldr_sensorval ;
int ldr_threshold= 500; //ldr határ érték
int ldr_val;
int buttonState_1 = 0;
int buttonState_2 = 0;

#define BUTTON_PIN   A1
#define PIXEL_PIN    9  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 22  // Number of NeoPixels
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
boolean oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-9

int relay_2 = 8; // Bal csatorna
int relay_1 = 7; // Jobb csatorna
#define pinDT  6  // Connected to DT on KY-040 rotary encoder
#define pinCLK  5  // Connected to CLK on KY-040 rotary encoder
#define swPin  4 // rotary encoder kapcsolója
int function_sw_2 = 3; // funció választó kapcsoló bluetooth
int function_sw_1 = 2; // funció választó kapcsoló rádió
int encoderPosCount = 0;
int pinCLKLast; 
int aVal;
boolean bCW;
int channel = 8900;    // alap állomás
int fm_Petofi = 8900;  //Petőfi rádió
int fm_Radio1 = 9500;  // Rádió 1 rádió
int fm_Retro = 10110;  // Retro rádió
int fm_Best = 10460;   // Best Fm rádió

bool type = 0;
boolean oldSwitchState = LOW;
boolean newSwitchState = LOW;
byte state = 0;


void setup() {
  lc.shutdown (0, false);         // wake up display
  lc.setIntensity (0, 7);        // set brightness level (0 to 15)
  lc.clearDisplay (0);            // clear display register
  
  Wire.begin(); //i2c bus
  Serial.begin(9600); 
  
  rtc.begin(); // rtc 
  //clock.setDateTime(2021, 04, 24, 11, 21, 0); // az rtc beállítása   
    //rtc.setTime(11, 26, 0);
    //rtc.setDate(4, 24, 2021);
      /*Ha fel van töltve a kód akkor a fenti sort
      * megjegyzésbe kell rakni, ellenkező esetben minden 
      * minden alaklommal a fenti sorban beállított idővel indul
      */
  pinMode(pinCLK, INPUT);  
  pinMode(pinDT, INPUT);
  pinMode(swPin, INPUT);
  pinMode(function_sw_1, INPUT); 
  pinMode(function_sw_2, INPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);

  pinMode(BUTTON_PIN, INPUT); //led pin
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
  
  digitalWrite(swPin, HIGH); // rotary kapcsoló
  pinCLKLast = digitalRead(pinCLK);
     
  radio.init(); // rádió inicializálása 
  radio.setBandFrequency(FIX_BAND, 8900); // ezzel indul a rádió (Petőfi)
  radio.setVolume(FIX_VOLUME); // kimenő hangerő beállítása
  radio.setMono(false); //rádió stereo kimenet
  radio.setMute(false); // némítás kikapcsolva
    
}

void loop() {
  
  // Fényerő beállítás
  ldr_sensorval = analogRead(ldr_sensor);
  Serial.println(ldr_sensorval);
      if(ldr_sensorval<ldr_threshold)
      ldr_val = 1;
      else ldr_val = 15;

  lc.setIntensity (0, ldr_val);

  //Led vezérlés
  boolean newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // Yes, still low
      if(++mode > 8) mode = 0; // Advance to next mode, wrap around after #8
      switch(mode) {           // Start the new animation...
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
        case 1:
          colorWipe(strip.Color(  255,   69,   0), 50);    // Red
          break;
        case 2:
          colorWipe(strip.Color(  255,    0,   0), 50);    // RedOrange
          break;
        case 3:
          colorWipe(strip.Color(   0,     0,  255), 50);    // Blue
          break;
        case 4:
          colorWipe(strip.Color(  25,   25,   112), 50);    // Midnightblue
          break;
        case 5:
          colorWipe(strip.Color(  255,   255, 255), 50);    //White
          break;
        case 6:
         colorWipe(strip.Color(   255,   108,  24), 50);    // Warm White
          break;
        case 7:
          colorWipe(strip.Color(  255,   137,    0), 50);    // Orange
          break;
        case 8:
          colorWipe(strip.Color(  0,   255,     0), 50);    //Green
          break;
      }
    }
  }
// Set the last-read button state to the old state.
  oldState = newState;
 
  
  // Frekvencia állítás
  aVal = digitalRead(pinCLK);
   if (aVal != pinCLKLast){ // Means the knob is rotating

     if (digitalRead(pinDT) != aVal) { 
       encoderPosCount ++;
       bCW = true;
       channel = channel + 10 ;
     } else {
       bCW = false;
       encoderPosCount--;
       channel = channel - 10 ;
     }
   
     Serial.print ("Rotated: ");
     if (bCW){
       Serial.println ("clockwise");
     }else{
       Serial.println("counterclockwise");
     }
     Serial.print("FM Freqquency: ");
     Serial.println(channel);
     radio.setFrequency(channel);
    
   }
   pinCLKLast = aVal;

 // Előre beállított frekvenciák (memória)
   newSwitchState = digitalRead(swPin);
  if ( newSwitchState != oldSwitchState )
  {
    
    if ( newSwitchState == HIGH )
    {
      state++;
      if (state > 4) {
        state = 0;
      }
     
      if (state == 1) {
        channel = fm_Petofi;
      }
      if (state == 2) {
        channel = fm_Radio1;
      }
      if (state == 3) {
        channel = fm_Retro;
      }
       if (state == 4) {
        channel = fm_Best;
      }
      radio.setFrequency(channel);
    }
    radio.setFrequency(channel);
    oldSwitchState = newSwitchState;
  }
 
  // Funkcióválasztó kapcsoló
  buttonState_1 = digitalRead(function_sw_1); 
   buttonState_2 = digitalRead(function_sw_2); 
    if (buttonState_1 == HIGH && buttonState_2 == HIGH){
      ora_7segment(); 
      radio.setMute(true);
      digitalWrite(relay_1, HIGH);
      digitalWrite(relay_2, HIGH); 
     }

    if (buttonState_1 == LOW){
       radio.setMute(false);
       radio_7segment();
     } 

    if (buttonState_2 == LOW && buttonState_1 == HIGH){
       bt_7segment();
       digitalWrite(relay_1, LOW);
       digitalWrite(relay_2, LOW);
       radio.setMute(true);  
     }
   /*buttonState_2 = digitalRead(function_sw_2);
    if (buttonState_2 == LOW){
       bt_7segment();
       digitalWrite(relay_1, LOW);
       digitalWrite(relay_2, LOW);
       radio.setMute(true); 
     } */
} 
void ora_7segment(){   // Óra kijelzése  
    
  dt = rtc.getTime();
  lc.setChar(0, 7, dt.hour/10,false);
  lc.setChar(0, 6, dt.hour%10,false);
  lc.setChar(0, 5, '-', false);
  lc.setChar(0, 4, dt.min/10,false);
  lc.setChar(0, 3, dt.min%10,false);
  lc.setChar(0, 2, '-', false);
  lc.setChar(0, 1, dt.sec/10,false);
  lc.setChar(0, 0, dt.sec%10,false);
  
 }

void radio_7segment(){   //Rádió kijelzése

   lc.setChar(0, 7, '-', false);
   lc.setChar(0, 6, '-', false);
   lc.setChar(0, 5, (channel / 10000) % 10, false);
   lc.setChar(0, 4, (channel / 1000) % 10 ,false);
   lc.setChar(0, 3, (channel / 100) % 10,true);
   lc.setChar(0, 2, (channel / 10) % 10, false);
   lc.setChar(0, 1, '-', false);
   lc.setChar(0, 0, '-', false);
 
 }  

 void bt_7segment(){   //bt kijelzése

   lc.setChar(0, 7, '-', false);
   lc.setChar(0, 6, '-', false);
   lc.setChar(0, 5, 'b', false);
   lc.setChar(0, 4, 'l', false);
   lc.setRow(0, 3, 0x1C);
   lc.setChar(0, 2, 'e', false);
   lc.setChar(0, 1, '-', false);
   lc.setChar(0, 0, '-', false);
   
 } 
 void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
} 

 
   
