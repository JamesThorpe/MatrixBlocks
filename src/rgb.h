#ifndef rgb_h
#define rgb_h

#include "common.h"

#define RGB_FPS 24
#define RGB_ANIMATION_BUFFERSIZE 5

typedef struct rgb_animation {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint16_t time;
    bool repeat;
} rgb_animation;

typedef struct rgb_led {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint16_t elapsed;
    uint8_t redStart;
    uint8_t greenStart;
    uint8_t blueStart;
    rgb_animation animations[RGB_ANIMATION_BUFFERSIZE];
    int8_t animation;
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