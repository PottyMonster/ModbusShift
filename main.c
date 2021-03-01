#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "stdio.h"

/*
                         Main application
 */



bool Debug = 0;

int loop;

volatile eusart1_status_t rxStatus;
int ByteNum = 0;

unsigned char rxData[100] = { 0 };

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
    for(i=0; i<ByteNum; i++ ){
        rxData[i] = 0xFF;
    }
    
}

void PrintRXBuff(){

    int i=0;

    for(i=0; i< ByteNum ; i++ ){
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
    
    bool RXStat = 0;
    
    while(1)
    {
        if(EUSART1_is_rx_ready()){
            // printf("eusart1RxCount: %08x \r\n", eusart1RxCount);
            // Counter++;           
            // printf("Triggered: %i \r\n\n", Counter);
            
            while(EUSART1_is_rx_ready()){
                // While there's something to read out
                rxData[ByteNum] = EUSART1_Read();
                __delay_ms(2);
                ByteNum++;
            }
            // printf("EUSART Read Complete.\r\n\n");
            RXStat = 1;
        }

        if(RXStat ==1){
            // Received a bunch of data.
            ByteNum--;
            PrintRXBuff();
            ClearRxBuff();
            RXStat = 0;
            ByteNum = 0;
            D2LED_Toggle();
        }else
        {
            //
        }

        
    }
}
/**
 End of File
*/
