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
int MBResCnt = 0;
unsigned int MBRespon[32] = { 0xFFFF };
unsigned int MBResCRC = 0xFFFF;
int ByteHi, ByteLo = 0xFF;

unsigned int MB300xx[32] = { 0x0000,0x0007,0x07FF,0x0004,0x0005,0x0006,0x0007,0x0008,
                            0x0009,0x000a,0x000b,0x000c,0x000d,0x000e,0x000f,
                            0x0010,0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,
                            0x0017,0x0018,0x0019,0x0020,0x0021,0x0022,0x0023,
                            0x0024,0x0025, 0x0026};     // Assigns 32x 16bit Read Registers


unsigned int MB400xx[32] = { 0x0000,0x0007,0x07FF,0x0004,0x0005,0x0006,0x0007,0x0008,
                            0x0009,0x000a,0x000b,0x000c,0x000d,0x000e,0x000f,
                            0x0010,0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,
                            0x0017,0x0018,0x0019,0x0020,0x0021,0x0022,0x0023,
                            0x0024,0x0025, 0x0026};     // Assigns 32x 16bit Read Registers


void PrintMB400(void){
    
    printf("UpdatedMB400 \r\n");
    int i=0;
    
    for(i=0; i<32; i++ ){
        printf("Reg: %i Data: 0x%04x \r\n", i, MB400xx[i]);
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


void ModbusFC03(){
    // Read 16bit Output registers
    // and generate Modbus Output
    int i = 0;
    
    MBResCnt = 0;
    MBRespon[MBResCnt] = ModbusData[0];    // Address
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[1];    // Function Code
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[5] *2;  // Number of bytes more
    MBResCnt++;
    for(i=0; i< (ModbusData[5]) ; i++ ){

        // Check ModbusData[5] (num registers max is 0x20 (Decimal 32) and
        // when start address ModbusData[3] is less than 0x20 (32)
        // and when adding on Num Registers to base address doesn't go over 32

        ByteLo = MB300xx[ModbusData[3] +i] & 0x00FF;
        ByteHi = MB300xx[ModbusData[3] +i] >> 8;
        MBRespon[MBResCnt] = ByteHi;                   
        MBResCnt++;
        MBRespon[MBResCnt] = ByteLo;
        MBResCnt++;
    }

    ByteHi = generateCRC(MBResCnt, 1);  // CRC Hi
    ByteLo = generateCRC(MBResCnt, 0);  // CRC Lo

    MBRespon[MBResCnt] = ByteHi;
    MBRespon[MBResCnt +1] = ByteLo;
    MBResCnt = MBResCnt +2;

    PrintModRespon();   // Slows the response down.          
    UART1_Write_string(MBRespon,MBResCnt);
 
    
}

void ModbusFC10(void){
    // Write multiple data
    // and generate Modbus Output
    
    int i = 0;
    int j = 0;
    unsigned int TempData = 0x0000;
    
    MBResCnt = 0;
    MBRespon[MBResCnt] = ModbusData[0];    // Address
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[1];    // Function Code
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[2];    // Address FIrst Reg Hi
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[3];    // Address FIrst Reg Lo
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[4];    // Num Reg Hi
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[5];    // Num Reg Lo
    MBResCnt++;
    
    for(i=0; i< (ModbusData[5]) ; i++ ){
        // For this number of registers
        
        // Check ModbusData[5] (num registers max is 0x20 (Decimal 32) and
        // when start address ModbusData[3] is less than 0x20 (32)
        // and when adding on Num Registers to base address doesn't go over 32

        TempData = ModbusData[7 +j] *256 + ModbusData[8 +j];
        j = j+2;
        MB400xx[ModbusData[3] +i] = TempData;
    }

    ByteHi = generateCRC(MBResCnt, 1);  // CRC Hi
    ByteLo = generateCRC(MBResCnt, 0);  // CRC Lo

    MBRespon[MBResCnt] = ByteHi;
    MBRespon[MBResCnt +1] = ByteLo;
    MBResCnt = MBResCnt +2;

    PrintMB400();
    
    PrintModRespon();   // Slows the response down.          
    UART1_Write_string(MBRespon,MBResCnt);

}


// unsigned char checkCRC(void){
unsigned int generateCRC(int MessCnt, bool HiOrLo){
  unsigned int crc = 0xFFFF;
  unsigned int crcHigh = 0;
  unsigned int crcLow = 0;
  int i,j = 0;

    for(i=0;i<MessCnt;i++){
      crc ^= MBRespon[i];
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
    
    if(HiOrLo == 1){
        return crcHigh;
    }else{
        return crcLow;
    }
    
}

void UART1_Write_string(unsigned int * data, int data_len)
{
    TXMode();
    while(!EUSART1_is_tx_ready()); // Hold the program until TX is ready
    for (int i = 0; i < data_len; i++) {
        EUSART1_Write(data[i]);
        while(!EUSART1_is_tx_done()); // Hold until sent
    }

}



void PrintModRespon(){

    int i=0;
    printf("Modbus Response:\r\n");
    for(i=0; i< MBResCnt ; i++ ){
        printf("   Byte %i : 0x%02x \r\n", i, MBRespon[i]);
    }
    printf("\r\n\n");
     
}

void ClearModbusRespon(){
    int i = 0;    
    for(i=0; i<32; i++ ){
        MBRespon[i] = 0xFFFF;
    }  
}


void PrintModbus(){
    // Prints out the entire Modbus string when captured as many bytes as
    // expected by ExpectedBytes

    int i=0;
    printf("Modbus Data Capture Complete:\r\n");
    for(i=0; i< ModDataCnt ; i++ ){
        printf("   Byte %i : 0x%02x \r\n", i, ModbusData[i]);
    }
    printf("\r\n\n");
    
}


void ModbusError(int ErrorCode){
    // Function to respond with a error code

    int i = 0;
    
    MBResCnt = 0;
    MBRespon[MBResCnt] = ModbusData[0];    // Address
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[1] + 128;    // Function Code
    MBResCnt++;
    MBRespon[MBResCnt] = ErrorCode;  // Error Code
    MBResCnt++;    

    ByteHi = generateCRC(MBResCnt, 1);  // CRC Hi
    ByteLo = generateCRC(MBResCnt, 0);  // CRC Lo

    MBRespon[MBResCnt] = ByteHi;
    MBRespon[MBResCnt +1] = ByteLo;
    MBResCnt = MBResCnt +2;

    PrintModRespon();   // Slows the response down.          
    UART1_Write_string(MBRespon,MBResCnt);    
    
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
        
        return 1;
    }
    return 0;

}

