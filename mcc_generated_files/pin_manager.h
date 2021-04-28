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

// get/set PISO_Reset aliases
#define PISO_Reset_TRIS                 TRISBbits.TRISB2
#define PISO_Reset_LAT                  LATBbits.LATB2
#define PISO_Reset_PORT                 PORTBbits.RB2
#define PISO_Reset_WPU                  WPUBbits.WPUB2
#define PISO_Reset_OD                   ODCONBbits.ODCB2
#define PISO_Reset_ANS                  ANSELBbits.ANSELB2
#define PISO_Reset_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define PISO_Reset_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define PISO_Reset_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define PISO_Reset_GetValue()           PORTBbits.RB2
#define PISO_Reset_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define PISO_Reset_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define PISO_Reset_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define PISO_Reset_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define PISO_Reset_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define PISO_Reset_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define PISO_Reset_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define PISO_Reset_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set PISO_SHCP aliases
#define PISO_SHCP_TRIS                 TRISBbits.TRISB3
#define PISO_SHCP_LAT                  LATBbits.LATB3
#define PISO_SHCP_PORT                 PORTBbits.RB3
#define PISO_SHCP_WPU                  WPUBbits.WPUB3
#define PISO_SHCP_OD                   ODCONBbits.ODCB3
#define PISO_SHCP_ANS                  ANSELBbits.ANSELB3
#define PISO_SHCP_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define PISO_SHCP_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define PISO_SHCP_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define PISO_SHCP_GetValue()           PORTBbits.RB3
#define PISO_SHCP_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define PISO_SHCP_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define PISO_SHCP_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define PISO_SHCP_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define PISO_SHCP_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define PISO_SHCP_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define PISO_SHCP_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define PISO_SHCP_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set PISO_Q aliases
#define PISO_Q_TRIS                 TRISBbits.TRISB4
#define PISO_Q_LAT                  LATBbits.LATB4
#define PISO_Q_PORT                 PORTBbits.RB4
#define PISO_Q_WPU                  WPUBbits.WPUB4
#define PISO_Q_OD                   ODCONBbits.ODCB4
#define PISO_Q_ANS                  ANSELBbits.ANSELB4
#define PISO_Q_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define PISO_Q_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define PISO_Q_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define PISO_Q_GetValue()           PORTBbits.RB4
#define PISO_Q_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define PISO_Q_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define PISO_Q_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define PISO_Q_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define PISO_Q_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define PISO_Q_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define PISO_Q_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define PISO_Q_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set PISO_STCP aliases
#define PISO_STCP_TRIS                 TRISBbits.TRISB5
#define PISO_STCP_LAT                  LATBbits.LATB5
#define PISO_STCP_PORT                 PORTBbits.RB5
#define PISO_STCP_WPU                  WPUBbits.WPUB5
#define PISO_STCP_OD                   ODCONBbits.ODCB5
#define PISO_STCP_ANS                  ANSELBbits.ANSELB5
#define PISO_STCP_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define PISO_STCP_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define PISO_STCP_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define PISO_STCP_GetValue()           PORTBbits.RB5
#define PISO_STCP_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define PISO_STCP_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define PISO_STCP_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define PISO_STCP_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define PISO_STCP_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define PISO_STCP_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define PISO_STCP_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define PISO_STCP_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set SIPO_DS aliases
#define SIPO_DS_TRIS                 TRISCbits.TRISC0
#define SIPO_DS_LAT                  LATCbits.LATC0
#define SIPO_DS_PORT                 PORTCbits.RC0
#define SIPO_DS_WPU                  WPUCbits.WPUC0
#define SIPO_DS_OD                   ODCONCbits.ODCC0
#define SIPO_DS_ANS                  ANSELCbits.ANSELC0
#define SIPO_DS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SIPO_DS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SIPO_DS_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SIPO_DS_GetValue()           PORTCbits.RC0
#define SIPO_DS_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SIPO_DS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SIPO_DS_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define SIPO_DS_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define SIPO_DS_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define SIPO_DS_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define SIPO_DS_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define SIPO_DS_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set SIPO_SHCP aliases
#define SIPO_SHCP_TRIS                 TRISCbits.TRISC1
#define SIPO_SHCP_LAT                  LATCbits.LATC1
#define SIPO_SHCP_PORT                 PORTCbits.RC1
#define SIPO_SHCP_WPU                  WPUCbits.WPUC1
#define SIPO_SHCP_OD                   ODCONCbits.ODCC1
#define SIPO_SHCP_ANS                  ANSELCbits.ANSELC1
#define SIPO_SHCP_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SIPO_SHCP_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SIPO_SHCP_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SIPO_SHCP_GetValue()           PORTCbits.RC1
#define SIPO_SHCP_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SIPO_SHCP_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SIPO_SHCP_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define SIPO_SHCP_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define SIPO_SHCP_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define SIPO_SHCP_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define SIPO_SHCP_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define SIPO_SHCP_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set SIPO_STCP aliases
#define SIPO_STCP_TRIS                 TRISCbits.TRISC2
#define SIPO_STCP_LAT                  LATCbits.LATC2
#define SIPO_STCP_PORT                 PORTCbits.RC2
#define SIPO_STCP_WPU                  WPUCbits.WPUC2
#define SIPO_STCP_OD                   ODCONCbits.ODCC2
#define SIPO_STCP_ANS                  ANSELCbits.ANSELC2
#define SIPO_STCP_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SIPO_STCP_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SIPO_STCP_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SIPO_STCP_GetValue()           PORTCbits.RC2
#define SIPO_STCP_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SIPO_STCP_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SIPO_STCP_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SIPO_STCP_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SIPO_STCP_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SIPO_STCP_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SIPO_STCP_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define SIPO_STCP_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set SIPO_Reset aliases
#define SIPO_Reset_TRIS                 TRISCbits.TRISC3
#define SIPO_Reset_LAT                  LATCbits.LATC3
#define SIPO_Reset_PORT                 PORTCbits.RC3
#define SIPO_Reset_WPU                  WPUCbits.WPUC3
#define SIPO_Reset_OD                   ODCONCbits.ODCC3
#define SIPO_Reset_ANS                  ANSELCbits.ANSELC3
#define SIPO_Reset_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SIPO_Reset_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SIPO_Reset_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SIPO_Reset_GetValue()           PORTCbits.RC3
#define SIPO_Reset_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SIPO_Reset_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SIPO_Reset_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SIPO_Reset_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SIPO_Reset_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SIPO_Reset_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SIPO_Reset_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define SIPO_Reset_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

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

// get/set PISO_PL aliases
#define PISO_PL_TRIS                 TRISDbits.TRISD7
#define PISO_PL_LAT                  LATDbits.LATD7
#define PISO_PL_PORT                 PORTDbits.RD7
#define PISO_PL_WPU                  WPUDbits.WPUD7
#define PISO_PL_OD                   ODCONDbits.ODCD7
#define PISO_PL_ANS                  ANSELDbits.ANSELD7
#define PISO_PL_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define PISO_PL_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define PISO_PL_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define PISO_PL_GetValue()           PORTDbits.RD7
#define PISO_PL_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define PISO_PL_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define PISO_PL_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define PISO_PL_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define PISO_PL_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define PISO_PL_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define PISO_PL_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define PISO_PL_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

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