#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "Modbus.h"
#include "stdio.h"

// Define and initalise data. Might need to go in Main if global.
int ByteNum = 0;
int ExpectedBytes = 8;
unsigned char rxData[100] = { 0 };      // Taken from USART Buffer
bool RXStat = 0;
volatile eusart1_status_t rxStatus;

unsigned char MB400xx[32] = { 0 };     // Assigns 32x 16bit Read/Write Registers


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
    
    ModDataCnt = 0;    
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



// unsigned char checkCRC(void){
bool checkCRC(void){
  unsigned int crc = 0xFFFF;
  unsigned int crcHigh = 0;
  unsigned int crcLow = 0;
  int i,j = 0;

    for(i=0;i<ModDataCnt-2;i++){
      crc ^= ModbusData[i];
      for(j=8; j!=0; j--){
        if((crc & 0x0001) != 0){
          crc >>= 1;
          crc ^= 0xA001;
        }
        else{
          crc >>= 1;
        }
      }
    }
  //bytes are wrong way round so doing a swap here..
  crcHigh = (crc & 0x00FF);
  crcLow = (crc & 0xFF00) >>8;
  printf("crcHigh: 0x%02x  crcLow: 0x%02x  \r\n", crcHigh, crcLow);
  if((crcHigh == ModbusData[i])&&(crcLow == ModbusData[i+1]))
  {
    return 1;
  }
  else{
    return 0;
  }
}


bool ModbusRx(){
    RXMode();
    if(EUSART1_is_rx_ready()){
        do{
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
        }while(ModDataCnt != ExpectedBytes);

        D3LED_Toggle();
        
        // generateCRC(ModDataCnt);
        if(checkCRC() == 1)
        {
            printf("CRC Checked Out. \r\n\n");
        }else{
            printf("CRC did NOT check out. \r\n\n");
        }
        // Complete Modbus String ready to process.     
        
        // Generage response
        
        return 1;
    }
    return 0;

}

