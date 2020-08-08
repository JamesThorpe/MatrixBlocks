#include "button.h"

/*
Port C
0: Button 2
1: Button 3
2: Button 6
3: Button 1
4: Unused
5: Unused
6: Button 4
7: Button 5

*/

// Debouncing code based on:
// https://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/
// 0 and 1 are reversed here though, a 0 means the button is down.

uint8_t btnCounter = 0;

void button_init(void) {
    button1 = &buttons[0];
    button2 = &buttons[1];
    button3 = &buttons[2];
    button4 = &buttons[3];
    button5 = &buttons[4];
    button6 = &buttons[5];
}

void button_tick(void) {
    if (++btnCounter < 5) {
        return;
    }
    btnCounter = 0;
    *button1 <<= 1;
    *button2 <<= 1;
    *button3 <<= 1;
    *button4 <<= 1;
    *button5 <<= 1;
    *button6 <<= 1;

    *button1 |= ((PORTC & 0x8) >> 3);
    *button2 |= (PORTC & 0x1);
    *button3 |= ((PORTC & 0x2) >> 1);
    *button4 |= ((PORTC & 0x40) >> 6);
    *button5 |= ((PORTC & 0x80) >> 7);
    *button6 |= ((PORTC & 0x4) >> 2);
}

bool button_isUp(uint8_t *button) {
    return *button == 0xFF;
}

bool button_isDown(uint8_t *button) {
    return *button == 0x0;
}

#define BTNMASK 0xC7 //0b11000111

bool button_isReleased(uint8_t *button) {
    if ((*button & BTNMASK) == 0x7) { //0b00000111
        *button = 0xFF;
        return true;
    }
    return false;
}

bool button_isPressed(uint8_t *button) {
    if ((*button & BTNMASK) == 0xC0) { //0b11000000
        *button = 0;
        return true;
    }
    return false;
}