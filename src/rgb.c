#include "rgb.h"
#include "interrupts.h"

uint8_t rgbTickCounter;
void updateAnimations(void);

#define RGB_PIN LATGbits.LATG3
#define BRIGHTNESSDIVISOR 3

/*
    At 64 MHz, each clock cycle is 15.625ns.  An instruction takes 4 clock 
    cycles.

    The SK6812 LEDs require a high/low period of 0.6us/0.6us for a 1 and 
    0.3us/0.9us for a 0, all of which only need to be within +/- 0.15us.

    The below gives us delays of 0.310us, 0.620us and 0.930us, which is
    well within parameters.

*/
#define delay60() asm("nop");
#define delay300() delay60() delay60() delay60() delay60() delay60()
#define delay600() delay300() delay300()
#define delay900() delay600() delay300()
    
// Gamma correction lookup table from 
// https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix
const uint8_t gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void rgb_init(void) {

    for (uint8_t x = 0; x < 19; x++) {
        rgb_leds[x].red = 0;
        rgb_leds[x].green = 0;
        rgb_leds[x].blue = 0;
        rgb_leds[x].elapsed = 0;
        rgb_leds[x].animation = -1;
        for (uint8_t y = 0; y < RGB_ANIMATION_BUFFERSIZE; y++) {
            rgb_leds[x].animations[y].time = 0;
        }
        
    }

    rgb_center = &rgb_leds[0];
    rgb_innerRing = &rgb_leds[1];
    rgb_outerRing = &rgb_leds[7];
    rgbTickCounter = 0;
}

void rgb_sendUpdate(void) {
    updateAnimations();
    //prepare all data
    uint8_t ledData[19*4];
    uint8_t ledBase = 0;
    uint8_t white;
    uint8_t x = 0;
    for (x = 0; x < 19; x++) {
        uint8_t r, g, b;
        r = gamma8[rgb_leds[x].red] / BRIGHTNESSDIVISOR;
        g = gamma8[rgb_leds[x].green] / BRIGHTNESSDIVISOR;
        b = gamma8[rgb_leds[x].blue] / BRIGHTNESSDIVISOR;

        if (r < g) {
            white = r;
        } else {
            white = g;
        }
        if (b < white) {
            white = b;
        }
        ledData[ledBase] = g - white;
        ledData[ledBase+1] = r - white;
        ledData[ledBase+2] = b - white;
        ledData[ledBase+3] = white;
        ledBase += 4;
    }


    
    interrupts_disableGlobalInterrupts();
    //send it
    for(ledBase = 0; ledBase < 76; ledBase++) {
        for (uint8_t ledBit = 8; ledBit > 0; ) {
            ledBit--;
            if (ledData[ledBase] & (1<<ledBit)) {
                RGB_PIN = 1;
                delay600();
                RGB_PIN = 0;
                delay600();
            } else {
                RGB_PIN = 1;
                delay300();
                RGB_PIN = 0;
                delay900();
            }
        }

    }

    interrupts_enableGlobalInterrupts();
    RGB_PIN = 0;
    rgbTickCounter = 0;
}


void rgb_setled(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
    rgb_leds[led].red = r;
    rgb_leds[led].green = g;
    rgb_leds[led].blue = b;
}

void rgb_tick(void) {
    rgbTickCounter++;
}
void rgb_animateled(uint8_t led, uint8_t r, uint8_t g, uint8_t b, uint16_t time) {
    if (time == 0) {
        time = 1;
    }
    int8_t anim;
    if (rgb_leds[led].animation >= 0) {
        anim = rgb_leds[led].animation + 1;
        while (anim < RGB_ANIMATION_BUFFERSIZE) {
            if (rgb_leds[led].animations[anim].time == 0) {
                break;
            }
            anim++;
        }
        if (anim >= RGB_ANIMATION_BUFFERSIZE) {
            return;
        }
    } else {
        anim = 0;
        rgb_leds[led].animation = 0;
        rgb_leds[led].redStart = rgb_leds[led].red;
        rgb_leds[led].greenStart = rgb_leds[led].green;
        rgb_leds[led].blueStart = rgb_leds[led].blue;
        rgb_leds[led].elapsed = 0;
    }
    rgb_leds[led].animations[anim].red = r;
    rgb_leds[led].animations[anim].green = g;
    rgb_leds[led].animations[anim].blue = b;
    rgb_leds[led].animations[anim].time = time;
}
void updateAnimations() {
    for (uint8_t x = 0; x < 19; x++) {
        rgb_led* led = &rgb_leds[x];
        if (led->animation != -1) {
            led->elapsed += rgbTickCounter;
            if (led->elapsed >= led->animations[led->animation].time) {
                led->red = led->animations[led->animation].red;
                led->green = led->animations[led->animation].green;
                led->blue = led->animations[led->animation].blue;

                led->animations[led->animation].time = 0;

                int8_t anim = led->animation + 1;
                if (anim < RGB_ANIMATION_BUFFERSIZE && led->animations[anim].time != 0) {
                    led->animation = anim;
                    led->redStart = led->red;
                    led->greenStart = led->green;
                    led->blueStart = led->blue;
                    led->elapsed = 0;
                } else {
                    led->animation = -1;
                }
            } else {
                float animAmount = ((float)led->elapsed / (float)led->animations[led->animation].time);
                led->red = led->redStart - (((int16_t)(led->redStart) - (int16_t)(led->animations[led->animation].red)) * animAmount);
                led->green = led->greenStart - (((int16_t)(led->greenStart) - (int16_t)(led->animations[led->animation].green)) * animAmount);
                led->blue = led->blueStart - (((int16_t)(led->blueStart) - (int16_t)(led->animations[led->animation].blue)) * animAmount);
            }
        }
    }
}

bool rgb_updateDue(void) {
    return rgbTickCounter >= (1000 / RGB_FPS);
}