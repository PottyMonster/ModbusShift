#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "stdio.h"
#include "Modbus.h"
#include "RS232.h"
#include "main.h"
#include "shift.h"


/*
                        Sub Routines
 */

void ToggleStatusLEDs(){
    LED_Good_Toggle();
    LED_Bad_Toggle();
    LED_Action_Toggle();
    LED_Ready_Toggle();
}




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

    


    InitialiseString(0); // Sends initalisation string over RS232
    

    RXMode();
    ClearRxBuff();
    ClearModbusRespon();
    // ClearMBInputReg(void);   // Empties input registers.

    
    SIPO_Reset();
    PISO_Reset();
    
    LED_Good_SetLow();
    LED_Bad_SetLow();
    LED_Ready_SetLow();
    LED_Action_SetLow();    
    
    
    bool RXStat = 0;
    bool ConfGood = 0;  // 0 = Unconfigured, 1 = Configured
    
    printf("Enter Command : ");
    
    while(1)
    {
        if(ModbusRx() == 1){
            // RS485 Modbus data has been received and ready to process
            
            LED_Action_SetHigh();
            
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
                    LED_Bad_SetHigh();
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
            LED_Action_SetLow();
            printf("Enter Command: ");
            
        }else if(ReadRX232(16) != 0){
            // RS232 Data has been received
            
            LED_Action_SetHigh();
            LED_Ready_SetLow();
            LED_Bad_SetLow();
            
            if(ValidateCmd() ==1){
                // Might change this to action successfull. I.E validates and
                // executes at the same time.
                // printf("Valid Command Rx: %s \r\n" , Command);             
             }else{
                // printf("Invalid Command Rx: %s \r\n", Command);
             }
            printf("\r\nEnter Command : ");
            strcpy(Command, "");   // Needed to clear RS232 command
            
        }else if(TMR0_HasOverflowOccured()){
            // This only happens every 100mS
            // printf("TMR0\r\n");
            ConfGood = CheckConfig();
            
            if(ConfGood == 1){
                LED_Ready_Toggle();
                LED_Good_SetLow();
                LED_Bad_SetLow();
                LED_Action_SetLow();
            }else{
                LED_Ready_SetLow();
                LED_Good_SetLow();
                LED_Action_SetLow();
                LED_Bad_Toggle();
            }
            
            TMR0_Initialize();
            // __delay_ms(2000);
            // printf("ConfGood %s \r\n", ConfGood ? "true" : "false");
                        
        }
        
    }
}
/**
 End of File
*/
