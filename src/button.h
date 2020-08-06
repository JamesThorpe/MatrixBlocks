#ifndef BUTTON_H
#define	BUTTON_H

#include "matrixblocks.h"

uint8_t buttons[6];

uint8_t *button1 = &buttons[0],
        *button2 = &buttons[1],
        *button3 = &buttons[2],
        *button4 = &buttons[3],
        *button5 = &buttons[4],
        *button6 = &buttons[5];

void button_init(void);
void button_tick(void);

bool button_isUp(uint8_t *button);
bool button_isDown(uint8_t *button);
bool button_isReleased(uint8_t *button);
bool button_isPressed(uint8_t *button);

#endif	/* BUTTON_H */

