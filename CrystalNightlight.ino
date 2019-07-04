#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels(3, 3, NEO_GRB+NEO_KHZ800);

#define redMin    10
#define redMax    255
#define greenMin  96
#define greenMax  255
#define blueMin   180
#define blueMax   255

byte r[] = {redMin, (redMax + redMin)/2, redMax};
bool rp[] = {true, true, false};
byte g[] = {greenMin, (greenMax + greenMin)/2, greenMax};
bool gp[] = {true, false, false};
byte b[] = {blueMin, (blueMax + blueMin)/2, blueMax};
bool bp[] = {true, true, false};

#define DELAY_TIME 50

void setup() 
{
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() 
{
  for(int i=0; i < 3; i++)
  {
    // set the pixel color
    pixels.setPixelColor(i, pixels.Color(r[i], g[i], b[i]));

    // increment or decrement the color values based on the current state
    r[i] = rp[i] ? r[i]+1 : r[i]-1;
    g[i] = gp[i] ? g[i]+1 : g[i]-1;
    b[i] = bp[i] ? b[i]+1 : b[i]-1;

    // alternate the direction of increment/decrement if one of the bounds has been reached.
    if(r[i] == redMax || r[i] == redMin)
      rp[i] = !rp[i];
    if(g[i] == greenMax || g[i] == greenMin)
      gp[i] = !gp[i];
    if(b[i] == blueMax || b[i] == blueMin)
      bp[i] = !bp[i];
  }
  
  // show the pixels
  pixels.show();
  
  delay(DELAY_TIME);
}
