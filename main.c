#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "stdio.h"
#include "Modbus.h"

/*
                         Main application
 */


bool Debug = 0;

// int loop;



//11 03 06 AE41 5652 4340 49AD
unsigned char data1[] = {0x11, 0x03, 0x06, 0xAE, 0x41, 0x56, 0x52, 0x43, 0x40, 0x49, 0xAD};


void InitialiseString(void){
    // Send Initalisation String

    printf("\rDan and Sam's Modbus GPIO Expansion - AP000xxxxx V0.1\r\n"); 
    printf("\rCard Ser No. xxxxxxx \r\n"); 
    printf("\rCompiled on %s at %s by XC8 version %u\r\n\n",
            __DATE__, __TIME__, __XC8_VERSION);
    printf("\rFunction Codes Supported:\r\n"); 
    printf("\r   0x03 - Read Multiple Registers (Max 32x 16bit)\r\n"); 
    printf("\r   0x10 - Write Multiple Registers (Max 32x 16bit)\r\n\n");
    printf("\rInitalisation Complete - Ready\r\n\n");
}

// https://stackoverflow.com/questions/59882336/how-to-write-a-hex-string-over-uart-for-pic-microcontrollers-in-c
void UART1_Write_string(unsigned char * data, int data_len)
{
    for (int i = 0; i < data_len; i++) {
        EUSART1_Write(data[i]);
    }
}



void PrintModbus(){
    // Prints out the entire Modbus string when captured as many bytes as
    // expected by ExpectedBytes

    int i=0;
    printf("\r\nModbus Data Capture Complete:\r\n");
    for(i=0; i< ModDataCnt ; i++ ){
        printf("   Byte Num: %i Val: 0x%02x \r\n", i, ModbusData[i]);
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
        
    D2LED_SetLow();
    D3LED_SetLow();
    D4LED_SetLow();
    D5LED_SetLow();

    InitialiseString(); // Sends initalisation string over RS232
    

    RXMode();
    ClearRxBuff();
    
    bool RXStat = 0;
    
    while(1)
    {
        if(ModbusRx() == 1){
            // Data has been received and ready to process
            PrintModbus();

        
            ClearModbusData();   // Needed when complete
        }
    }
}
/**
 End of File
*/
