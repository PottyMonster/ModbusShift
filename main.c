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
int ModDataCnt = 0;
int ExpectedBytes = 8;

unsigned char rxData[100] = { 0 };      // Taken from USART Buffer
unsigned char ModbusData[100] = { 0 };  // Received Modbus Data

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


void TXMode(){    
    TX_ENA_SetHigh();
    RX_ENA_SetHigh();
}


void RXMode(){    
    TX_ENA_SetLow();
    RX_ENA_SetLow();
}


void ClearModbusData(){
    int i = 0;    
    for(i=0; i<99; i++ ){
        ModbusData[i] = 0xFF;
    }
}


void ClearRxBuff(){
   
    int i = 0;    
    for(i=0; i<ByteNum; i++ ){
        rxData[i] = 0xFF;
    }
    
}

void AddRxBuffToModBus(){
    // This needs to change to copying in to ModbusData[i]
    // ModDataCnt contains how much data has been copied over.

    int i = 0;    
    
    for(i=0l; i<ByteNum; i++){
        ModbusData[ModDataCnt] = rxData[i];
        ModDataCnt++;        
    }
    
    // printf("Completed Adding rxData Buffer to ModbusData Array\r\n\n");
    // printf("ModDataCnt sitting at %i\r\n\n", ModDataCnt);
    
    if(ModbusData[1] == 0x0F){
        ExpectedBytes = ModbusData[6] + 9;        
    }else if (ModbusData[1] == 0x10){
        ExpectedBytes = ModbusData[6] + 9;
    }else{
        ExpectedBytes = 8;
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
    
    ModDataCnt = 0;
    
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
        if(EUSART1_is_rx_ready()){
           
            while(EUSART1_is_rx_ready()){
                // While there's something to read out of the RX Buffer
                rxData[ByteNum] = EUSART1_Read();
                ByteNum++;
            }
            
            RXStat = 1; // Flag for buffer is empty
        }

        if(RXStat ==1){
            // Received a bunch of data with buffer loaded
            // in to rxData. Now Add Buffer to ModBus array.
            AddRxBuffToModBus();   // Adds rxData to ModbusData Array
            ClearRxBuff();  // Emptry rxData ready for next load
            RXStat = 0;     // rxData has everything flag
            ByteNum = 0;    // Reset num bytes in buffer to 0
            D2LED_Toggle();
        }

        if(ModDataCnt == ExpectedBytes){ 
            PrintModbus();
        }

        
    }
}
/**
 End of File
*/
