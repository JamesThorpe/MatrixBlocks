/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F66K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RE0 aliases
#define IO_RE0_TRIS                 TRISEbits.TRISE0
#define IO_RE0_LAT                  LATEbits.LATE0
#define IO_RE0_PORT                 PORTEbits.RE0
#define IO_RE0_WPU                  WPUEbits.WPUE0
#define IO_RE0_OD                   ODCONEbits.ODCE0
#define IO_RE0_ANS                  ANSELEbits.ANSELE0
#define IO_RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define IO_RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define IO_RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define IO_RE0_GetValue()           PORTEbits.RE0
#define IO_RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define IO_RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define IO_RE0_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define IO_RE0_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define IO_RE0_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define IO_RE0_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define IO_RE0_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define IO_RE0_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set IO_RE2 aliases
#define IO_RE2_TRIS                 TRISEbits.TRISE2
#define IO_RE2_LAT                  LATEbits.LATE2
#define IO_RE2_PORT                 PORTEbits.RE2
#define IO_RE2_WPU                  WPUEbits.WPUE2
#define IO_RE2_OD                   ODCONEbits.ODCE2
#define IO_RE2_ANS                  ANSELEbits.ANSELE2
#define IO_RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define IO_RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define IO_RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define IO_RE2_GetValue()           PORTEbits.RE2
#define IO_RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define IO_RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define IO_RE2_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define IO_RE2_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define IO_RE2_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define IO_RE2_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define IO_RE2_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define IO_RE2_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

// get/set IO_RE3 aliases
#define IO_RE3_TRIS                 TRISEbits.TRISE3
#define IO_RE3_LAT                  LATEbits.LATE3
#define IO_RE3_PORT                 PORTEbits.RE3
#define IO_RE3_WPU                  WPUEbits.WPUE3
#define IO_RE3_OD                   ODCONEbits.ODCE3
#define IO_RE3_ANS                  ANSELEbits.ANSELE3
#define IO_RE3_SetHigh()            do { LATEbits.LATE3 = 1; } while(0)
#define IO_RE3_SetLow()             do { LATEbits.LATE3 = 0; } while(0)
#define IO_RE3_Toggle()             do { LATEbits.LATE3 = ~LATEbits.LATE3; } while(0)
#define IO_RE3_GetValue()           PORTEbits.RE3
#define IO_RE3_SetDigitalInput()    do { TRISEbits.TRISE3 = 1; } while(0)
#define IO_RE3_SetDigitalOutput()   do { TRISEbits.TRISE3 = 0; } while(0)
#define IO_RE3_SetPullup()          do { WPUEbits.WPUE3 = 1; } while(0)
#define IO_RE3_ResetPullup()        do { WPUEbits.WPUE3 = 0; } while(0)
#define IO_RE3_SetPushPull()        do { ODCONEbits.ODCE3 = 0; } while(0)
#define IO_RE3_SetOpenDrain()       do { ODCONEbits.ODCE3 = 1; } while(0)
#define IO_RE3_SetAnalogMode()      do { ANSELEbits.ANSELE3 = 1; } while(0)
#define IO_RE3_SetDigitalMode()     do { ANSELEbits.ANSELE3 = 0; } while(0)

// get/set IO_RE4 aliases
#define IO_RE4_TRIS                 TRISEbits.TRISE4
#define IO_RE4_LAT                  LATEbits.LATE4
#define IO_RE4_PORT                 PORTEbits.RE4
#define IO_RE4_WPU                  WPUEbits.WPUE4
#define IO_RE4_OD                   ODCONEbits.ODCE4
#define IO_RE4_ANS                  ANSELEbits.ANSELE4
#define IO_RE4_SetHigh()            do { LATEbits.LATE4 = 1; } while(0)
#define IO_RE4_SetLow()             do { LATEbits.LATE4 = 0; } while(0)
#define IO_RE4_Toggle()             do { LATEbits.LATE4 = ~LATEbits.LATE4; } while(0)
#define IO_RE4_GetValue()           PORTEbits.RE4
#define IO_RE4_SetDigitalInput()    do { TRISEbits.TRISE4 = 1; } while(0)
#define IO_RE4_SetDigitalOutput()   do { TRISEbits.TRISE4 = 0; } while(0)
#define IO_RE4_SetPullup()          do { WPUEbits.WPUE4 = 1; } while(0)
#define IO_RE4_ResetPullup()        do { WPUEbits.WPUE4 = 0; } while(0)
#define IO_RE4_SetPushPull()        do { ODCONEbits.ODCE4 = 0; } while(0)
#define IO_RE4_SetOpenDrain()       do { ODCONEbits.ODCE4 = 1; } while(0)
#define IO_RE4_SetAnalogMode()      do { ANSELEbits.ANSELE4 = 1; } while(0)
#define IO_RE4_SetDigitalMode()     do { ANSELEbits.ANSELE4 = 0; } while(0)

// get/set IO_RE5 aliases
#define IO_RE5_TRIS                 TRISEbits.TRISE5
#define IO_RE5_LAT                  LATEbits.LATE5
#define IO_RE5_PORT                 PORTEbits.RE5
#define IO_RE5_WPU                  WPUEbits.WPUE5
#define IO_RE5_OD                   ODCONEbits.ODCE5
#define IO_RE5_ANS                  ANSELEbits.ANSELE5
#define IO_RE5_SetHigh()            do { LATEbits.LATE5 = 1; } while(0)
#define IO_RE5_SetLow()             do { LATEbits.LATE5 = 0; } while(0)
#define IO_RE5_Toggle()             do { LATEbits.LATE5 = ~LATEbits.LATE5; } while(0)
#define IO_RE5_GetValue()           PORTEbits.RE5
#define IO_RE5_SetDigitalInput()    do { TRISEbits.TRISE5 = 1; } while(0)
#define IO_RE5_SetDigitalOutput()   do { TRISEbits.TRISE5 = 0; } while(0)
#define IO_RE5_SetPullup()          do { WPUEbits.WPUE5 = 1; } while(0)
#define IO_RE5_ResetPullup()        do { WPUEbits.WPUE5 = 0; } while(0)
#define IO_RE5_SetPushPull()        do { ODCONEbits.ODCE5 = 0; } while(0)
#define IO_RE5_SetOpenDrain()       do { ODCONEbits.ODCE5 = 1; } while(0)
#define IO_RE5_SetAnalogMode()      do { ANSELEbits.ANSELE5 = 1; } while(0)
#define IO_RE5_SetDigitalMode()     do { ANSELEbits.ANSELE5 = 0; } while(0)

// get/set IO_RE6 aliases
#define IO_RE6_TRIS                 TRISEbits.TRISE6
#define IO_RE6_LAT                  LATEbits.LATE6
#define IO_RE6_PORT                 PORTEbits.RE6
#define IO_RE6_WPU                  WPUEbits.WPUE6
#define IO_RE6_OD                   ODCONEbits.ODCE6
#define IO_RE6_ANS                  ANSELEbits.ANSELE6
#define IO_RE6_SetHigh()            do { LATEbits.LATE6 = 1; } while(0)
#define IO_RE6_SetLow()             do { LATEbits.LATE6 = 0; } while(0)
#define IO_RE6_Toggle()             do { LATEbits.LATE6 = ~LATEbits.LATE6; } while(0)
#define IO_RE6_GetValue()           PORTEbits.RE6
#define IO_RE6_SetDigitalInput()    do { TRISEbits.TRISE6 = 1; } while(0)
#define IO_RE6_SetDigitalOutput()   do { TRISEbits.TRISE6 = 0; } while(0)
#define IO_RE6_SetPullup()          do { WPUEbits.WPUE6 = 1; } while(0)
#define IO_RE6_ResetPullup()        do { WPUEbits.WPUE6 = 0; } while(0)
#define IO_RE6_SetPushPull()        do { ODCONEbits.ODCE6 = 0; } while(0)
#define IO_RE6_SetOpenDrain()       do { ODCONEbits.ODCE6 = 1; } while(0)
#define IO_RE6_SetAnalogMode()      do { ANSELEbits.ANSELE6 = 1; } while(0)
#define IO_RE6_SetDigitalMode()     do { ANSELEbits.ANSELE6 = 0; } while(0)

// get/set IO_RE7 aliases
#define IO_RE7_TRIS                 TRISEbits.TRISE7
#define IO_RE7_LAT                  LATEbits.LATE7
#define IO_RE7_PORT                 PORTEbits.RE7
#define IO_RE7_WPU                  WPUEbits.WPUE7
#define IO_RE7_OD                   ODCONEbits.ODCE7
#define IO_RE7_ANS                  ANSELEbits.ANSELE7
#define IO_RE7_SetHigh()            do { LATEbits.LATE7 = 1; } while(0)
#define IO_RE7_SetLow()             do { LATEbits.LATE7 = 0; } while(0)
#define IO_RE7_Toggle()             do { LATEbits.LATE7 = ~LATEbits.LATE7; } while(0)
#define IO_RE7_GetValue()           PORTEbits.RE7
#define IO_RE7_SetDigitalInput()    do { TRISEbits.TRISE7 = 1; } while(0)
#define IO_RE7_SetDigitalOutput()   do { TRISEbits.TRISE7 = 0; } while(0)
#define IO_RE7_SetPullup()          do { WPUEbits.WPUE7 = 1; } while(0)
#define IO_RE7_ResetPullup()        do { WPUEbits.WPUE7 = 0; } while(0)
#define IO_RE7_SetPushPull()        do { ODCONEbits.ODCE7 = 0; } while(0)
#define IO_RE7_SetOpenDrain()       do { ODCONEbits.ODCE7 = 1; } while(0)
#define IO_RE7_SetAnalogMode()      do { ANSELEbits.ANSELE7 = 1; } while(0)
#define IO_RE7_SetDigitalMode()     do { ANSELEbits.ANSELE7 = 0; } while(0)

// get/set IO_RG3 aliases
#define IO_RG3_TRIS                 TRISGbits.TRISG3
#define IO_RG3_LAT                  LATGbits.LATG3
#define IO_RG3_PORT                 PORTGbits.RG3
#define IO_RG3_WPU                  WPUGbits.WPUG3
#define IO_RG3_OD                   ODCONGbits.ODCG3
#define IO_RG3_ANS                  ANSELGbits.ANSELG3
#define IO_RG3_SetHigh()            do { LATGbits.LATG3 = 1; } while(0)
#define IO_RG3_SetLow()             do { LATGbits.LATG3 = 0; } while(0)
#define IO_RG3_Toggle()             do { LATGbits.LATG3 = ~LATGbits.LATG3; } while(0)
#define IO_RG3_GetValue()           PORTGbits.RG3
#define IO_RG3_SetDigitalInput()    do { TRISGbits.TRISG3 = 1; } while(0)
#define IO_RG3_SetDigitalOutput()   do { TRISGbits.TRISG3 = 0; } while(0)
#define IO_RG3_SetPullup()          do { WPUGbits.WPUG3 = 1; } while(0)
#define IO_RG3_ResetPullup()        do { WPUGbits.WPUG3 = 0; } while(0)
#define IO_RG3_SetPushPull()        do { ODCONGbits.ODCG3 = 0; } while(0)
#define IO_RG3_SetOpenDrain()       do { ODCONGbits.ODCG3 = 1; } while(0)
#define IO_RG3_SetAnalogMode()      do { ANSELGbits.ANSELG3 = 1; } while(0)
#define IO_RG3_SetDigitalMode()     do { ANSELGbits.ANSELG3 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/