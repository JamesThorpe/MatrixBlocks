/*

This file exists purely to allow development inside Visual Studio Code, 
away from MPLAB X, without a ton of warnings.

*/


#define uint8_t char
#define int8_t char
#define uint16_t unsigned short
#define int16_t short
#define bool uint8_t
#define false 0
#define true 1
#define __interrupt()  

struct vsc_INTCONbits {
    uint8_t GIE;
    uint8_t IPEN;
};

struct vsc_INTCONbits INTCONbits;

struct vsc_LATAbits {
    uint8_t LATA0;
    uint8_t LATA1;
    uint8_t LATA2;
    uint8_t LATA3;
    uint8_t LATA4;
    uint8_t LATA5;
};

struct vsc_LATAbits LATAbits;

struct vsc_LATGbits {
    uint8_t LATG3;
};

struct vsc_LATGbits LATGbits;

struct vsc_PIR0bits {
    uint8_t TMR0IF;
};
struct vsc_PIR0bits PIR0bits;

struct vsc_PIR5bits {
    uint8_t TMR1IF;
};
struct vsc_PIR5bits PIR5bits;

struct vsc_PIE0bits {
    uint8_t TMR0IE;
};
struct vsc_PIE0bits PIE0bits;

struct vsc_PIE5bits {
    uint8_t TMR1IE;
};
struct vsc_PIE5bits PIE5bits;

uint8_t PORTC, PORTF;

uint8_t OSCCON1, OSCCON3, OSCEN, OSCFRQ, OSCTUNE;
uint8_t PMD0, PMD1, PMD2, PMD3, PMD4, PMD5;
uint8_t LATA, LATB, LATC, LATD, LATE, LATF, LATG, LATH;
uint8_t TRISA, TRISB, TRISC, TRISD, TRISE, TRISF, TRISG, TRISH;
uint8_t ANSELA, ANSELB, ANSELD, ANSELE, ANSELF, ANSELG;
uint8_t WPUA, WPUB, WPUC, WPUD, WPUE, WPUF, WPUG, WPUH;
uint8_t ODCONA, ODCONB, ODCONC, ODCOND, ODCONE, ODCONF, ODCONG, ODCONH;
uint8_t SLRCONA, SLRCONB, SLRCONC, SLRCOND, SLRCONE, SLRCONF, SLRCONG, SLRCONH;
uint8_t INLVLA, INLVLB, INLVLC, INLVLD, INLVLE, INLVLF, INLVLG, INLVLH;
uint8_t T0CON1, TMR0H, TMR0L, T0CON0;
uint8_t T1GCON, T1GATE, T1CLK, TMR1H, TMR1L, T1CON;