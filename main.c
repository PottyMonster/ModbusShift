#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "stdio.h"
#include "Modbus.h"
#include "RS232.h"
#include "main.h"

/*
                         Main application
 */




// int loop;



//11 03 06 AE41 5652 4340 49AD
// unsigned char MBRespon[] = {0x11, 0x03, 0x06, 0xAE, 0x41, 0x56, 0x52, 0x43, 0x40, 0x49, 0xAD};

// 01 03 00 02 00 05
// will reply with
// 01 03 06 07 ff 00 04 00 05 b5 14
// when using default MB300xx[32] array above.


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
    ClearModbusRespon();
    
    
    bool RXStat = 0;
    
    while(1)
    {
        if(ModbusRx() == 1){
            // RS485 Modbus data has been received and ready to process
            
            // if(Debug == 1){
                PrintModbus();   
            // }

            switch(ModbusData[1])    // check command  
            {
            case 0x03:
                {
                    printf("Function Code 0x03\r\n");
                    // Reads Multiple Registers
                    // ShiftRead();     // Sam's function to read in shift reg
                    ModbusFC03();
                    ClearModbusData();   // Needed when complete
                    ClearModbusRespon();
                    break;
                }
            case 0x10:
                {
                    printf("Function Code 0x10\r\n");
                    // Writes to Multiple Registers  
                    PrintMB400();   // Contents before update
                    ModbusFC10();
                    // ShiftWrite();    // Sam's function to write to shift reg 
                    ClearModbusData();   // Needed when complete
                    ClearModbusRespon();
                    break;
                }
            default:
                {
                    printf("Unsupported Function Code\r\n");
                    // Throw error code as function code not available
                    ModbusError(0x01);
                    ClearModbusData();   // Needed when complete
                    ClearModbusRespon();
                    break;
                }
            }
        }else if(ReadRX232(16) != 0){
            // RS232 Data has been received
            
            printf("Nothing on RS232 \r\n");
            // Nothing on the RS232 UART
            if(ValidateCmd() ==1){
                // Might change this to action successfull. I.E validates and
                // executes at the same time.
                // printf("Valid Command Rx: %s \r\n" , Command);             
             }else{
                // printf("Invalid Command Rx: %s \r\n", Command);
             }
            
             strcpy(Command, "");   // Needed to clear RS232 command
            
        }else{
            // Nothing to do. No data to process.
        }
        
    }
}
/**
 End of File
*/
