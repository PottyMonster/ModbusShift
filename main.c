#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "stdio.h"
#include "Modbus.h"
#include "RS232.h"
#include "main.h"
#include "shift.h"

/*
 
 * Function Code 0x10 writes to 16 bit output holding registers (broadcast enabled)
 * Funciton Code 0x03 reads 16 bit output holding registers
 * Function Code 0x04 reads multiple 16 bit inputs
 * Function Code 0x08 Reset Slave
 
 */

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
    // ClearMBInputReg(void);   // Empties input registers.

    
    SIPO_Reset();
    PISO_Reset();
    
    
    bool RXStat = 0;
    
    printf("Enter Command : ");
    
    while(1)
    {
        if(ModbusRx() == 1){
            // RS485 Modbus data has been received and ready to process
            
            switch(ModbusData[1])    // check command  
            {
            case 0x03:
                {
                    printf("Function Code 0x03 - Read Output Holding Registers\r\n");
                    // Reads Multiple Output Holding Registers
                    ModbusFC03();
                    break;
                }
            case 0x10:
                {
                    printf("Function Code 0x10 - Write to Output Holding Registers \r\n");
                    // Writes to Multiple Registers  
                    if(Debug == 1){
                        printf("Modbus Register Before Update: \r\n");
                        PrintMB400();   // Print Write Register
                    }
                    ModbusFC10();   // Perform Modbus Update of Write register.
                    SIPO_ShiftWrite();
                    if(Debug ==1){
                        printf("Modbus Register After Update: \r\n");
                        PrintMB400();   // Print Write Register
                    }
                    break;
                }
            case 0x04:
                {
                    printf("Function Code 0x04 - Read Input Registers\r\n");
                    // Reads Multiple Input Registers
                    ModbusFC04();
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
            
            if(Debug==1){
                PrintModbus();
                PrintModRespon();
            }
            
            // PrintModRespon2();
            ClearModbusData();   // Needed when complete
            ClearModbusRespon();
            printf("Enter Command: ");
            
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
