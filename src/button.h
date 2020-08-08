#ifndef BUTTON_H
#define	BUTTON_H

#include "matrixblocks.h"

uint8_t buttons[6];

uint8_t *button1;
uint8_t *button2;
uint8_t *button3;
uint8_t *button4;
uint8_t *button5;
uint8_t *button6;


void button_init(void);
void button_tick(void);

bool button_isUp(uint8_t *button);
bool button_isDown(uint8_t *button);
bool button_isReleased(uint8_t *button);
bool button_isPressed(uint8_t *button);

#endif	/* BUTTON_H */

