#include <LiquidCrystal.h>
 
#define IN_LEFT    A4  // analog input for left channel
#define IN_RIGHT   A5  // analog input for right channel
 
#define T_REFRESH    25
#define T_PEAKHOLD   (50 * T_REFRESH)
 
LiquidCrystal lcd(7,  // RS
                  8,  // E
                  3,  // DB4
                  4,  // DB5
                  5,  // DB6
                  6   // DB7
                  );
 
byte  fill[6] = {0x20, 0x00, 0x01, 0x02, 0x03, 0xFF};
byte  peak[7] = {0x20, 0x00, 0x04, 0x05, 0x06, 0x07, 0x20};
byte block[8][8]=
{
  {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
  {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
  {0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C},
  {0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E},
 
  {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
  {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
  {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
  {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
};
 
int lmax[2];
int dly[2];
 
long lastT = 0;
 
void  bar(int row, int lev) {
 
    lcd.setCursor(0, row);
    lcd.write(row ? 'R' : 'L');
 
    for(int i = 1; i < 16; i++) {
        int f = constrain(lev-i*5, 0, 5);
        int p = constrain(lmax[row]-i*5, 0, 6);
        if(f)
            lcd.write(fill[f]);
        else
            lcd.write(peak[p]);
    }
 
    if(lev > lmax[row]) {
        lmax[row] = lev;
        dly[row]  = -(T_PEAKHOLD) / T_REFRESH;
    }
    else {
        if(dly[row] > 0)
            lmax[row] -= dly[row];
 
        if(lmax[row] < 0)
            lmax[row] = 0;
        else
            dly[row]++;
    }
}
 
void  setup() {
 
    byte fillbar[8] = {
    B00000,
    B01000,
    B01100,
    B01010,
    B01001,
    B01010,
    B01100,
    B01000
    };
 
    byte mark[8] = {
    B00000,
    B01010,
    B10001,
    B10101,
    B10001,
    B01010,
    B00000,
    B00000
    };
 
    lcd.begin(16, 2);
 
    lcd.createChar(0, fillbar);
    lcd.createChar(1, mark);
 
    lcd.setCursor(2, 0);
    lcd.print("WAHYU AUDIO");
    lcd.setCursor(16, 0);
    lcd.write(1);
 
    for(int i = 0; i < 16; i++) {
        lcd.setCursor(i, 1);
        lcd.write((byte)0);
 
        delay(125);
    }
 
    lcd.clear();
 
    for(int j = 0; j < 8; j++)
        lcd.createChar(j, block[j]);
}
 
void  loop() {
 
    if(millis() < lastT)
        return;
 
    lastT += T_REFRESH;
 
    int anL = map(sqrt(analogRead(IN_LEFT)*16), 0, 128, 0, 100);
    int anR = map(sqrt(analogRead(IN_RIGHT)*16), 0, 128, 0, 100);
     
    bar(0, anL);
    bar(1, anR);
}
