#ifndef rgb_h
#define rgb_h

#include "matrixblocks.h"

#define RGB_FPS 24


typedef struct rgb_animation {
    uint8_t r_s;
    uint8_t r_e;
    uint8_t g_s;
    uint8_t g_e;
    uint8_t b_s;
    uint8_t b_e;
    uint16_t time;
    uint16_t elapsed;
} rgb_animation;

typedef struct rgb_led {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    rgb_animation animation;
} rgb_led;

rgb_led rgb_leds[19];
rgb_led* rgb_center;
rgb_led* rgb_innerRing;
rgb_led* rgb_outerRing;

void rgb_init(void);

void rgb_sendUpdate(void);
void rgb_tick(void);

void rgb_setled(uint8_t led, uint8_t r, uint8_t g, uint8_t b);

void rgb_animateled(uint8_t led, uint8_t r, uint8_t g, uint8_t b, uint16_t time);

bool rgb_updateDue(void);

#endif