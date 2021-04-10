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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

// get/set AIP_0 aliases
#define AIP_0_TRIS                 TRISAbits.TRISA0
#define AIP_0_LAT                  LATAbits.LATA0
#define AIP_0_PORT                 PORTAbits.RA0
#define AIP_0_WPU                  WPUAbits.WPUA0
#define AIP_0_OD                   ODCONAbits.ODCA0
#define AIP_0_ANS                  ANSELAbits.ANSELA0
#define AIP_0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define AIP_0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define AIP_0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define AIP_0_GetValue()           PORTAbits.RA0
#define AIP_0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define AIP_0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define AIP_0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define AIP_0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define AIP_0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define AIP_0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define AIP_0_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define AIP_0_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RX_ENA aliases
#define RX_ENA_TRIS                 TRISAbits.TRISA3
#define RX_ENA_LAT                  LATAbits.LATA3
#define RX_ENA_PORT                 PORTAbits.RA3
#define RX_ENA_WPU                  WPUAbits.WPUA3
#define RX_ENA_OD                   ODCONAbits.ODCA3
#define RX_ENA_ANS                  ANSELAbits.ANSELA3
#define RX_ENA_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RX_ENA_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RX_ENA_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RX_ENA_GetValue()           PORTAbits.RA3
#define RX_ENA_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RX_ENA_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RX_ENA_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define RX_ENA_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define RX_ENA_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define RX_ENA_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define RX_ENA_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define RX_ENA_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set D2LED aliases
#define D2LED_TRIS                 TRISAbits.TRISA4
#define D2LED_LAT                  LATAbits.LATA4
#define D2LED_PORT                 PORTAbits.RA4
#define D2LED_WPU                  WPUAbits.WPUA4
#define D2LED_OD                   ODCONAbits.ODCA4
#define D2LED_ANS                  ANSELAbits.ANSELA4
#define D2LED_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define D2LED_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define D2LED_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define D2LED_GetValue()           PORTAbits.RA4
#define D2LED_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define D2LED_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define D2LED_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define D2LED_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define D2LED_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define D2LED_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define D2LED_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define D2LED_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set D3LED aliases
#define D3LED_TRIS                 TRISAbits.TRISA5
#define D3LED_LAT                  LATAbits.LATA5
#define D3LED_PORT                 PORTAbits.RA5
#define D3LED_WPU                  WPUAbits.WPUA5
#define D3LED_OD                   ODCONAbits.ODCA5
#define D3LED_ANS                  ANSELAbits.ANSELA5
#define D3LED_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define D3LED_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define D3LED_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define D3LED_GetValue()           PORTAbits.RA5
#define D3LED_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define D3LED_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define D3LED_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define D3LED_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define D3LED_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define D3LED_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define D3LED_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define D3LED_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set D4LED aliases
#define D4LED_TRIS                 TRISAbits.TRISA6
#define D4LED_LAT                  LATAbits.LATA6
#define D4LED_PORT                 PORTAbits.RA6
#define D4LED_WPU                  WPUAbits.WPUA6
#define D4LED_OD                   ODCONAbits.ODCA6
#define D4LED_ANS                  ANSELAbits.ANSELA6
#define D4LED_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define D4LED_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define D4LED_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define D4LED_GetValue()           PORTAbits.RA6
#define D4LED_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define D4LED_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define D4LED_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define D4LED_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define D4LED_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define D4LED_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define D4LED_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define D4LED_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set D5LED aliases
#define D5LED_TRIS                 TRISAbits.TRISA7
#define D5LED_LAT                  LATAbits.LATA7
#define D5LED_PORT                 PORTAbits.RA7
#define D5LED_WPU                  WPUAbits.WPUA7
#define D5LED_OD                   ODCONAbits.ODCA7
#define D5LED_ANS                  ANSELAbits.ANSELA7
#define D5LED_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define D5LED_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define D5LED_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define D5LED_GetValue()           PORTAbits.RA7
#define D5LED_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define D5LED_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define D5LED_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define D5LED_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define D5LED_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define D5LED_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define D5LED_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define D5LED_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSELB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set TX_ENA aliases
#define TX_ENA_TRIS                 TRISDbits.TRISD0
#define TX_ENA_LAT                  LATDbits.LATD0
#define TX_ENA_PORT                 PORTDbits.RD0
#define TX_ENA_WPU                  WPUDbits.WPUD0
#define TX_ENA_OD                   ODCONDbits.ODCD0
#define TX_ENA_ANS                  ANSELDbits.ANSELD0
#define TX_ENA_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define TX_ENA_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define TX_ENA_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define TX_ENA_GetValue()           PORTDbits.RD0
#define TX_ENA_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define TX_ENA_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define TX_ENA_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define TX_ENA_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define TX_ENA_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define TX_ENA_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define TX_ENA_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define TX_ENA_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

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