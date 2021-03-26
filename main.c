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

    InitialiseString(0); // Sends initalisation string over RS232
    

    RXMode();
    ClearRxBuff();
    ClearModbusRespon();
    
    
    bool RXStat = 0;
    
    while(1)
    {
        if(ModbusRx() == 1){
            // RS485 Modbus data has been received and ready to process
            
            switch(ModbusData[1])    // check command  
            {
            case 0x03:
                {
                    // printf("Function Code 0x03\r\n");
                    // Reads Multiple Registers
                    // ShiftRead();     // Sam's function to read in shift reg
                    ModbusFC03();
                    break;
                }
            case 0x10:
                {
                    printf("Function Code 0x10\r\n");
                    // Writes to Multiple Registers  
                    printf("Modbus Register Before Update:");
                    PrintMB400();   // Contents before update
                    ModbusFC10();
                    // ShiftWrite();    // Sam's function to write to shift reg 
                    break;
                }
            default:
                {
                    printf("Unsupported Function Code\r\n");
                    // Throw error code as function code not available
                    ModbusError(0x01);
                    break;
                }           
            }
            
            PrintModbus();
            PrintModRespon();
            
            // PrintModRespon2();

            ClearModbusData();   // Needed when complete
            ClearModbusRespon();
            
        }else if(ReadRX232(16) != 0){
            // RS232 Data has been received
            if(ValidateCmd() ==1){
                // Might change this to action successfull. I.E validates and
                // executes at the same time.
                // printf("Valid Command Rx: %s \r\n" , Command);             
             }else{
                // printf("Invalid Command Rx: %s \r\n", Command);
             }
            printf("\r\nEnter Command : ");
            strcpy(Command, "");   // Needed to clear RS232 command
            
        }else{
            // Nothing to do. No data to process.
        }
        
    }
}
/**
 End of File
*/
