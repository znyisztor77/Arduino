int pinsw1 = 5;

#include <FastLED.h>
#define LED_PIN     12
#define NUM_LEDS    100
CRGB leds[NUM_LEDS];

 long colorTable[] = {
//CRGB::AliceBlue,  
//CRGB::Amethyst,  
//CRGB::AntiqueWhite,  
CRGB::Aqua,  
//CRGB::Aquamarine,  
//CRGB::Azure, 
//CRGB::Beige, 
//CRGB::Bisque,  
//CRGB::Black, 
//CRGB::BlanchedAlmond,  
CRGB::Blue,
CRGB::BlueViolet,
CRGB::Brown,
//CRGB::BurlyWood,
CRGB::CadetBlue,
CRGB::Chartreuse,
CRGB::Chocolate,
//CRGB::Coral,
CRGB::CornflowerBlue,
//CRGB::Cornsilk,
//CRGB::Crimson,
CRGB::Cyan,
CRGB::DarkBlue,
CRGB::DarkCyan,
CRGB::DarkGoldenrod,
//CRGB::DarkGray,
CRGB::DarkGreen,
//CRGB::DarkKhaki,
//CRGB::DarkMagenta,
CRGB::DarkOliveGreen,
CRGB::DarkOrange,
//CRGB::DarkOrchid,
CRGB::DarkRed,
//CRGB::DarkSalmon,
//CRGB::DarkSeaGreen,
CRGB::DarkSlateBlue,
CRGB::DarkSlateGray,
CRGB::DarkTurquoise,
//CRGB::DarkViolet,
//CRGB::DeepPink,
CRGB::DeepSkyBlue,
//CRGB::DimGray,
CRGB::DodgerBlue,
CRGB::FireBrick,
//CRGB::FloralWhite,
CRGB::ForestGreen, //nagyon jó
//CRGB::Fuchsia,
//CRGB::Gainsboro,
//CRGB::GhostWhite,
CRGB::Gold,
CRGB::Goldenrod,
//CRGB::Gray,
CRGB::Green,
//CRGB::GreenYellow,
//CRGB::Honeydew,
//CRGB::HotPink,
//CRGB::IndianRed,
CRGB::Indigo,
//CRGB::Ivory,
//CRGB::Khaki,
//CRGB::Lavender,
//CRGB::LavenderBlush,
CRGB::LawnGreen,
//CRGB::LemonChiffon,
//CRGB::LightBlue,
//CRGB::LightCoral,
//CRGB::LightCyan,
//CRGB::LightGoldenrodYellow,
//CRGB::LightGreen,
//CRGB::LightGrey,
//CRGB::LightPink,
//CRGB::LightSalmon,
//CRGB::LightSeaGreen,
CRGB::LightSkyBlue,
CRGB::LightSlateGray,
CRGB::LightSteelBlue,
//RGB::LightYellow,
CRGB::Lime,
CRGB::LimeGreen,
//CRGB::Linen,
CRGB::Magenta,
CRGB::Maroon,
CRGB::MediumAquamarine,
CRGB::MediumBlue,
CRGB::MediumOrchid,
CRGB::MediumPurple,
CRGB::MediumSeaGreen,
CRGB::MediumSlateBlue,
CRGB::MediumSpringGreen,
CRGB::MediumTurquoise,
//CRGB::MediumVioletRed,
CRGB::MidnightBlue,
//CRGB::MintCream,
//CRGB::MistyRose,
//CRGB::Moccasin,
//CRGB::NavajoWhite,
CRGB::Navy,
//CRGB::OldLace,
CRGB::Olive,
CRGB::OliveDrab,
CRGB::Orange,
CRGB::OrangeRed,
CRGB::Orchid,
//CRGB::PaleGoldenrod,
//CRGB::PaleGreen,
//CRGB::PaleTurquoise,
//CRGB::PaleVioletRed,
//CRGB::PapayaWhip,
//CRGB::PeachPuff,
//CRGB::Peru,
//CRGB::Pink,
//CRGB::Plaid,
//CRGB::Plum,
CRGB::PowderBlue,
//CRGB::Purple,
CRGB::Red,
//CRGB::RosyBrown,
CRGB::RoyalBlue,
CRGB::SaddleBrown,
//CRGB::Salmon,
//CRGB::SandyBrown,
CRGB::SeaGreen, //ok
//CRGB::Seashell,
CRGB::Sienna,
//CRGB::Silver,
CRGB::SkyBlue,
CRGB::SlateBlue,
//CRGB::SlateGray,
//CRGB::Snow,
CRGB::SpringGreen,
CRGB::SteelBlue, //nagyon ok
//CRGB::Tan,
CRGB::Teal,
//CRGB::Thistle,
CRGB::Tomato,
CRGB::Turquoise,
//CRGB::Violet,
//CRGB::Wheat,
//CRGB::White,
//CRGB::WhiteSmoke,
CRGB::Yellow,
CRGB::YellowGreen,
  };
int arrayPosition=0;

boolean oldSwitchState = LOW;
boolean newSwitchState = LOW;
byte state = 0;

void setup() {
  LEDS.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  LEDS.setBrightness(200);
  pinMode(pinsw1, INPUT);
  Serial.begin (9600);

}

void loop() {
   Serial.println(arrayPosition);
   
newSwitchState = digitalRead(pinsw1);
  if ( newSwitchState != oldSwitchState ){
     delay(50);
     if(newSwitchState == LOW){
     arrayPosition++;   //incrament this value when the button is pressed
     if(arrayPosition>66){  //reset it if it gets bigger than the array
        arrayPosition=0;
    }
  } 
  for (int i = 0; i <NUM_LEDS; i++) {leds[i] = colorTable[arrayPosition];}
     oldSwitchState = newSwitchState;  
  }
  for (int i = 0; i <NUM_LEDS; i++) {leds[i] = colorTable[arrayPosition];}
  FastLED.show();
}  
