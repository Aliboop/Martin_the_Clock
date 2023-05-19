
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

// Addding some variables that relate to time

// This creates an array! It holds nine characters 
//(including the \0 used to terminate it) all with the type char (one character)
char bufTime[9]; 

// This creates a variable of type time_t (which is used to store expressions of time)
// And we named it currTime!
time_t currTime;

long h; // We create a variable named h of type long, which is like int but can hold larger integers)
long m; // Same as above but we call the variable m, for minutes instead of h, which will store the hour
long s; // Same as above but we call the variable s, for seconds

void initScreen() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  // the computer determines what kind of screen the user has then changes pinout configuration
  #ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
#endif
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  // reset screen.
  tft.reset();

  // determines the LCD chip the screen is using
  uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;
  }
  
  // starts the screen
  tft.begin(identifier);

  // sets the screen to landscape mode
  tft.setRotation(1);

  // clears the screen by making it black
  tft.fillScreen(BLACK);
}

void updateCurrTime() {
  // This function will update the variable currTime with the values of hours minutes and seconds all at once
  // We will do this using the now() function. This makes all three consistent, so they change at the same time.

  currTime = now(); // Update the variable currTime to the value now, changing the hours minutes and seconds that it holds
  h = hour(currTime); // Grabs the hour value from the variable currTime and sets the variable h to its value
  m = minute(currTime); // Grabs the minute value from the variable currTime and sets the variable m to its value
  s = second(currTime); // Grabs the second value from the variable currTime and sets the variable s to its value

  // use sprintf to format the output into the array character buffer
  // note that to use sprintf you need ints not longs, so cast values to int type
  sprintf(bufTime, "%02d:%02d:%02d", (int)h, (int)m, (int)s);

  // print to monitor for debugging purposes
  Serial.println(bufTime);
}

void displayCurrTime() {
  // print the stopwatch time to the screen

  // erase the old time by drawing over it.
  tft.fillRect(0, 0, 300, 70, BLACK);

  // tell the screen where to start printing
  tft.setCursor(10, 10);

  tft.setTextColor(BLUE);
  tft.setTextSize(6);
  tft.println(bufTime);

}

void setup() {
  // initialize serial connection for debugging.
  Serial.begin(9600);

  // populate the character buffer with null characters.
  // in other words, set the array so it is at 00 : 00 : 00
  int i;
  for (i = 0; i < 10; i++) {
    bufTime[i] = NULL;
  }

  // initialize the screen
  initScreen();
}

void loop() {
  // put your main code here, to run repeatedly:

  // runs the functions.
  updateCurrTime();
  displayCurrTime();

  // waits 1 second.
  delay(1000);
  
}
