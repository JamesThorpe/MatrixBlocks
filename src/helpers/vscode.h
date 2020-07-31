/*

This file exists purely to allow development inside Visual Studio Code, 
away from MPLAB X, without a ton of warnings.

*/


#define uint8_t char
#define uint16_t unsigned short
#define int16_t short
#define bool uint8_t
#define false 0
#define true 1
#define __interrupt()  

struct vsc_INTCON0bits {
    uint8_t GIE;
    uint8_t IPEN;
};

struct vsc_INTCON0bits INTCON0bits;


struct vsc_LATGbits {
    uint8_t LATG3;
};

struct vsc_LATGbits LATGbits;

uint8_t LATE;