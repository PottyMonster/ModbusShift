/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K40
        Driver Version    :  2.00
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

#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"

/*
                         Main application
 */


char temp[2] = {'Z','\0'}; 
bool Debug = 0;
int i=0;

volatile uint8_t rxData;
volatile eusart1_status_t rxStatus;

//11 03 06 AE41 5652 4340 49AD
unsigned char data1[] = {0x11, 0x03, 0x06, 0xAE, 0x41, 0x56, 0x52, 0x43, 0x40, 0x49, 0xAD};


// https://stackoverflow.com/questions/59882336/how-to-write-a-hex-string-over-uart-for-pic-microcontrollers-in-c
void UART1_Write_string(unsigned char * data, int data_len)
{
    for (int i = 0; i < data_len; i++) {
        EUSART1_Write(data[i]);
    }
}


void TXMode(){    
    TX_ENA_SetHigh();
    RX_ENA_SetHigh();
    // __delay_ms(10);
    D5LED_SetHigh();
    D4LED_SetLow();
    printf("TXMode\r\n\n");
}


void RXMode(){    
    TX_ENA_SetLow();
    RX_ENA_SetLow();
    // __delay_ms(10);
    D5LED_SetLow();
    D4LED_SetHigh();
    // printf("RXMode\r\n\n");
}


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    // UART_PortIdent();
    
    
    // RS454TX_SetHigh();  -- What it should be
    
    D2LED_SetLow();
    D3LED_SetLow();
    D4LED_SetLow();
    D5LED_SetLow();


    volatile uint8_t rxData;

    rxData = 0x31;  // Character 1
 
    // Initialize the device
    
    printf("Initalised\r\n\n");

    while(1)
    {
        RXMode();
         // Initialize the device
        // Logic to echo received data
        if(EUSART1_is_rx_ready())
        {
            printf("EUSART1 received data and is ready to be read.\r\n\n");
            D2LED_SetHigh();
            rxData = EUSART1_Read();
            printf("Read data rxData: %c \r\n\n", rxData);
            if(EUSART1_is_tx_ready())
            {
                printf("EUSART1 TX is Ready\r\n\n");
                TXMode(); 
                // UART1_Write_string(data1, sizeof(data1));
                EUSART1_Write(rxData);
                printf("EUSART1 Write Sent: %c \r\n\n", rxData);              
                D3LED_Toggle();
            }
        }

    }
    

}
/**
 End of File
*/