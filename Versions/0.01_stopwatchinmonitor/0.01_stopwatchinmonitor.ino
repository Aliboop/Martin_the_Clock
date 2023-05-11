
// library for clock functions
#include <TimeLib.h>

// library for touchscreen funtions
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

// Connecting the touchscreen to the arduino 
// (so I don't have to type out the specifics every time)
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Adding readable names to 16-bit colors
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Not quite sure how this helps but it seems quite important
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

}

unsigned long stopwatch() {
  tft.fillscreen(BLACK);
  tft.setCursor(0,0);
  tft.setTextColor(WHITE);
  tft.setTextSize(7);
  tft.println();
}


void loop() {
  long val;

  // put your main code here, to run repeatedly:

  val = hour();
  if (val < 10) {
    Serial.print("0");
  }
  Serial.print(val);
  Serial.print(":");

  val = minute();
  if (val < 10) {
    Serial.print("0");
  }
  Serial.print(val);
  Serial.print(":");

  val = second();
  if (val < 10) {
    Serial.print("0");
  }
  Serial.println(val);

  delay(1000);
}
