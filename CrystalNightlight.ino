#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels(3, 3, NEO_GRB+NEO_KHZ800);

const byte redMin[3]    = { 254, 100, 0   };
const byte redMax[3]    = { 255, 255, 1   };
const byte greenMin[3]  = { 0 , 0 , 100 };
const byte greenMax[3]  = { 1 , 255, 255 };
const byte blueMin[3]   = { 0 , 0 , 254 };
const byte blueMax[3]   = { 255, 0 , 255 };

byte r[] = {redMin[0], (redMax[1] + redMin[1])/2, redMax[2]};
bool rp[] = {true, true, false}; // is the red value for each pixel increasing or decreasing?
byte g[] = {greenMin[0], (greenMax[1] + greenMin[1])/2, greenMax[2]};
bool gp[] = {true, false, false};// is the green value for each pixel increasing or decreasing?
byte b[] = {blueMin[0], (blueMax[1] + blueMin[1])/2, blueMax[2]};
bool bp[] = {true, true, false}; // is the blue value for each pixel increasing or decreasing?

#define DELAY_TIME 20

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
  // foreach pixel in the array...
  for(int i=0; i < 3; i++)
  {
    // set the pixel color
    pixels.setPixelColor(i, pixels.Color(r[i], g[i], b[i]));

    // increment or decrement the color values based on the current state
    r[i] = rp[i] ? r[i]+1 : r[i]-1;
    g[i] = gp[i] ? g[i]+1 : g[i]-1;
    b[i] = bp[i] ? b[i]+1 : b[i]-1;

    // alternate the direction of increment/decrement if one of the bounds has been reached.
    if(r[i] >= redMax[i] || r[i] <= redMin[i])
      rp[i] = !rp[i];
    if(g[i] >= greenMax[i] || g[i] <= greenMin[i])
      gp[i] = !gp[i];
    if(b[i] >= blueMax[i] || b[i] <= blueMin[i])
      bp[i] = !bp[i];
  }
  
  // show the pixels
  pixels.show();
  
  delay(DELAY_TIME);
}
