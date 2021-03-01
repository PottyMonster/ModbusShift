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
#include "stdio.h"

/*
                         Main application
 */


char temp[2] = {'Z','\0'}; 
bool Debug = 0;

int loop;

volatile eusart1_status_t rxStatus;
int ByteNum = 0;

unsigned char rxData[] = {0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc};

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
}


void RXMode(){    
    TX_ENA_SetLow();
    RX_ENA_SetLow();
}


void ClearRxBuff(){
   
    int i = 0;    
    for(i=0; i<50; i++ ){
        rxData[i] = 0xFF;
    }
    
}

void PrintRXBuff(){

    int i=0;

    for(i=0; i<50; i++ ){
        printf("Byte %i. Val: 0x%02x \r\n", i, rxData[i]);
    }
    
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
    
    // RS454TX_SetHigh();  -- What it should be
    
    D2LED_SetLow();
    D3LED_SetLow();
    D4LED_SetLow();
    D5LED_SetLow();


    // Initialize the device
    
    printf("Initalised\r\n\n");

    RXMode();
    ClearRxBuff();
    PrintRXBuff();
    
    while(1)
    {
        if(EUSART1_is_rx_ready()){
            // printf("eusart1RxCount: %08x \r\n", eusart1RxCount);
            // Counter++;           
            // printf("Triggered: %i \r\n\n", Counter);
         
            ByteNum = 0;
            while(EUSART1_is_rx_ready()){
                // While there's something to read out
                rxData[ByteNum] = EUSART1_Read();
                __delay_ms(5);
                ByteNum++;
            }
            printf("EUSART Read Complete.\r\n\n");
            
            PrintRXBuff();
            ClearRxBuff();
            
        /*
         
         
         
        
        // if(EUSART1_is_tx_ready())
        // {
            Counter++;
            
            rxAddress = EUSART1_Read();
            rxFuncCode = EUSART1_Read();
            rxFirstRegHi = EUSART1_Read();
            rxFirstRegLo = EUSART1_Read();

            // These might be function code specific - may need moving.
            rxNumRegHi = EUSART1_Read();    // Number of registers Hi
            rxNumRegLo = EUSART1_Read();    // Number of registers Lo

            if(rxFuncCode == 0x03){
                // printf("Specific stuff for 0x03 - Read Multiple 16bit Register\r\n\n");

                rxCRCHi = EUSART1_Read();    // Number of registers Hi
                rxCRCLo = EUSART1_Read();    // Number of registers Hi

            }


            if(rxFuncCode == 0x10){
                // printf("Specific stuff for 0x10 - Writing Multiple 16bit Registers\r\n\n");
                rxNumBytesMore = EUSART1_Read();    // Number of registers Hi
            }

            if(rxFuncCode == 0x04){
                printf("Specific stuff for 0x04 - Read Single 16bit Register\r\n\n");
            }


            while(EUSART1_is_rx_ready()){
                // Get anything else
                rxData = EUSART1_Read();
                printf("Rest of data next byte: 0x%02x \r\n\n", rxData);            
            }
            
            printf("Counter %i \r\n\n", Counter);
            printf("rxAddress 0x%02x \r\n\n", rxAddress);
            printf("rxFuncCode 0x%02x \r\n\n", rxFuncCode);
            printf("rxFirstRegHi 0x%02x \r\n\n", rxFirstRegHi); 
            printf("rxFirstRegLo 0x%02x \r\n\n", rxFirstRegLo);             
            printf("rxNumRegHi 0x%02x \r\n\n", rxNumRegHi);
            printf("rxNumRegLo 0x%02x \r\n\n", rxNumRegLo);  
            printf("rxCRCHi 0x%02x \r\n\n", rxCRCHi);               
            printf("rxCRCLo 0x%02x \r\n\n", rxCRCLo);              
            printf("rxNumBytesMore 0x%02x \r\n\n", rxNumBytesMore);            
         
         * */
        // }
        }

    }
}
/**
 End of File
*/
