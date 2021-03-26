#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "Modbus.h"
#include "stdio.h"
#include "main.h"



// Define and initalise data. Might need to go in Main if global.
int ByteNum = 0;
int ExpectedBytes = 8;
unsigned char rxData[100] = { 0 };      // Taken from USART Buffer
bool RXStat = 0;
volatile eusart1_status_t rxStatus;
int MBResCnt = 0;
unsigned char MBRespon[75] = { 0xFF };    // Works
// unsigned int MBRespon[32] = { 0xFFFF };    
unsigned int MBResCRC = 0xFFFF;
int ByteHi, ByteLo = 0xFF;



void PrintMB400(void){
    // This is just used for debuging to print out the circuit receive registers.
    // Can be used before and after Modbus writes to check it's been updated.
    printf("UpdatedMB400 \r\n");
    int i=0;
    
    for(i=0; i<32; i++ ){
        printf("   Reg: %i Data: 0x%04x \r\n", i, MB400xx[i]);
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
    int i = 0;    
    
    for(i=0l; i<ByteNum; i++){
        ModbusData[ModDataCnt] = rxData[i];
        ModDataCnt++;        
    }
    
    if(Debug ==1){
        printf("Completed Adding rxData Buffer to ModbusData Array\r\n\n");
        printf("ModDataCnt sitting at %i\r\n\n", ModDataCnt);
    }
    
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
    printf("\r\nModbus Received:\r\n");
    
    if(ModbusData[1] == 0x03){
        
        printf("   Byte 00: 0x%02x - Card Address\r\n",ModbusData[0]);
        printf("   Byte 01: 0x%02x - Function Code (Read Multi Reg)\r\n",ModbusData[1]);
        printf("   Byte 02: 0x%02x - 1st Reg Add Hi\r\n",ModbusData[2]);
        printf("   Byte 03: 0x%02x - 1st Reg Add Lo\r\n",ModbusData[3]);
        printf("   Byte 04: 0x%02x - Num of Reg Hi\r\n",ModbusData[4]);
        printf("   Byte 05: 0x%02x - Num of Reg Lo\r\n",ModbusData[5]);
        printf("   Byte 06: 0x%02x - CRC Hi\r\n",ModbusData[6]);
        printf("   Byte 07: 0x%02x - CRC Lo\r\n",ModbusData[7]);
        
    }else if(ModbusData[1] == 0x10){
        
        printf("   Byte 00: 0x%02x - Card Address\r\n",ModbusData[0]);
        printf("   Byte 01: 0x%02x - Function Code (Write Multi Reg)\r\n",ModbusData[1]);
        printf("   Byte 02: 0x%02x - 1st Reg Add Hi\r\n",ModbusData[2]);
        printf("   Byte 03: 0x%02x - 1st Reg Add Lo\r\n",ModbusData[3]);
        printf("   Byte 04: 0x%02x - Num of Reg Hi\r\n",ModbusData[4]);
        printf("   Byte 05: 0x%02x - Num of Reg Lo\r\n",ModbusData[5]);
        printf("   Byte 06: 0x%02x - Num Bytes More\r\n",ModbusData[6]);


        int j = 1;
        for(i=7; i< ModDataCnt -2 ; i++ ){
            printf("   Byte %02i: 0x%02x - Reg %i Hi (Add. 0x%02x%02x / Circuit %i)\r\n", i, ModbusData[i],j, ModbusData[2], ModbusData[3] + j-1,ModbusData[3] + j-1);
            i++;
            printf("   Byte %02i: 0x%02x - Reg %i Lo\r\n", i, ModbusData[i],j);
            j++;
        }

        printf("   Byte %02i: 0x%02x - CRC Hi\r\n",i, ModbusData[i]);
        printf("   Byte %02i: 0x%02x - CRC Lo\r\n",i + 1, ModbusData[i + 1]);        

    }   

    printf("\r\n");
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
  
  if(Debug == 1){
    printf("crcHigh: 0x%02x  crcLow: 0x%02x  \r\n", crcHigh, crcLow);
  }
  
  
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
    bool error = 0;
    
    MBResCnt = 0;
    MBRespon[MBResCnt] = ModbusData[0];    // Address
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[1];    // Function Code
    MBResCnt++;
    MBRespon[MBResCnt] = ModbusData[5] *2;  // Number of bytes more
    MBResCnt++;
    
    // Validate Address Ranges
    switch(ModbusData[2]){
        
        case 0x00:
        {
            printf("Requested Circuit Data\r\n");
            
            if(
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) < 0) ||  
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 32)){
                
                printf("Registers out of range.\r\nValid: 0x0000 to 0x0031.\r\n");
            
                printf("Requested: 0x%04x to 0x%04x\r\n", ModbusData[2] * 256 + ModbusData[3], 
                        ((ModbusData[4] * 256) + ModbusData[5]) + (ModbusData[2] * 256 + ModbusData[3]));
                error = 1;
            }
            break;
        }
        case 0x01:
        {
            printf("Requested Part No.\r\n");
            
            if(
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) < 256) ||  
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 264)){
                
                printf("Registers out of range.\r\nValid: 0x0100 to 0x0108.\r\n");
                
                printf("Requested: 0x%04x to 0x%04x\r\n", ModbusData[2] * 256 + ModbusData[3], 
                    ((ModbusData[4] * 256) + ModbusData[5]) + (ModbusData[2] * 256 + ModbusData[3]));                
                error = 1;
            }
            break;
        }
        case 0x02:
        {
            printf("Requested Revision\r\n");
            if(
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) < 512) ||  
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 512)){
                
                printf("Registers out of range.\r\nValid: 0x0512.\r\n");
                printf("Requested: 0x%04x to 0x%04x\r\n", ModbusData[2] * 256 + ModbusData[3], 
                    ((ModbusData[4] * 256) + ModbusData[5]) + (ModbusData[2] * 256 + ModbusData[3]));                 
                error = 1;
            }               
            break;
        }
        case 0x03:
        {
            printf("Requested Serial No.\r\n");
            if(
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) < 768) ||  
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 772)){
                
                printf("Registers out of range.\r\nValid: 0x0300 to 0x0304.\r\n");
                printf("Requested: 0x%04x to 0x%04x\r\n", ModbusData[2] * 256 + ModbusData[3], 
                    ((ModbusData[4] * 256) + ModbusData[5]) + (ModbusData[2] * 256 + ModbusData[3])); 
                error = 1;
            }
            break;
        }
        case 0x04:
        {
            printf("Requested Compile Date\r\n");
            if(
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) < 1024) ||  
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 1029)){
                
                printf("Registers out of range.\r\nValid: 0x0400 to 0x0405.\r\n");
                
                printf("Requested: 0x%04x to 0x%04x\r\n", ModbusData[2] * 256 + ModbusData[3], 
                    ((ModbusData[4] * 256) + ModbusData[5]) + (ModbusData[2] * 256 + ModbusData[3])); 
                error = 1;
            }
            break;
        }
        case 0x05:
        {
            printf("Requested Compile Time\r\n");
            
            if(
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) < 1280) ||  
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 1283)){
                
                printf("Registers out of range.\r\nValid: 0x0500 to 0x0503.\r\n");
                
                printf("Requested: 0x%04x to 0x%04x\r\n", ModbusData[2] * 256 + ModbusData[3], 
                    ((ModbusData[4] * 256) + ModbusData[5]) + (ModbusData[2] * 256 + ModbusData[3])); 
                error = 1;
            }
            break;
        }
        case 0x06:
        {
            printf("Requested Analogue Inputs\r\n");
            if(
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) < 1536) ||  
                (((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 1538)){
                
                printf("Registers out of range.\r\nValid: 0x0600 to 0x0602.\r\n");
                printf("Requested: 0x%04x to 0x%04x\r\n", ModbusData[2] * 256 + ModbusData[3], 
                    ((ModbusData[4] * 256) + ModbusData[5]) + (ModbusData[2] * 256 + ModbusData[3])); 
                error = 1;
            }
            break;
        }
    }
    
    if(error == 0){
        for(i=0; i< (ModbusData[5]) ; i++ ){

            // Check ModbusData[5] (num registers max is 0x20 (Decimal 32) and
            // when start address ModbusData[3] is less than 0x20 (32)
            // and when adding on Num Registers to base address doesn't go over 32
            if(ModbusData[2] == 0x03){
                // Serial Number Request
                ByteLo = MB303xx[ModbusData[3] +i] & 0x00FF;
                ByteHi = MB303xx[ModbusData[3] +i] >> 8;                        


            }else if(ModbusData[2] == 0x01){

                // Part Number Request
                // if(ModbusData[3] + ModbusData[9] > 0x05){
                   // printf("Requested registers out of range. \r\n");
                // }

                ByteLo = MB301xx[ModbusData[3] +i] & 0x00FF;
                ByteHi = MB301xx[ModbusData[3] +i] >> 8; 

            }
            else if(ModbusData[2] == 0x02){
                // Revision Request
                // if(ModbusData[3] + ModbusData[9] > 0x01){
                    // printf("Requested registers out of range. \r\n");
                // }

                ByteLo = MB302xx[ModbusData[3] +i] & 0x00FF;
                ByteHi = MB302xx[ModbusData[3] +i] >> 8; 

            }else if(ModbusData[2] == 0x04){ 
                // Compiled Date
                ByteLo = MB304xx[ModbusData[3] +i] & 0x00FF;
                ByteHi = MB304xx[ModbusData[3] +i] >> 8;

            }else if(ModbusData[2] == 0x05){ 
                // Compiled Time
                ByteLo = MB305xx[ModbusData[3] +i] & 0x00FF;
                ByteHi = MB305xx[ModbusData[3] +i] >> 8;

            }
            else if(ModbusData[2] == 0x00){
                // Circuit Registers
                ByteLo = MB300xx[ModbusData[3] +i] & 0x00FF;
                ByteHi = MB300xx[ModbusData[3] +i] >> 8;

            }else if(ModbusData[2] == 0x06){
                // Analogue Input Read
                uint16_t convertedValue;
                convertedValue = ADCC_GetSingleConversion(AIP_0);        
                printf("ADC: 0x%04x \r\n", convertedValue);

                ByteLo = convertedValue & 0x00FF;
                ByteHi = convertedValue >> 8;          
            }

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

        // Send Modbus response back to Master.
        UART1_Write_string(MBRespon,MBResCnt);
    }else{
        ModbusError(0x02);
    }
    
}

void ModbusFC10(void){
    // Write multiple data
    // and generate Modbus Output
    
    int i = 0;
    int j = 0;
    unsigned int TempData = 0x0000;
    bool error = 0;
    
    if(((ModbusData[2] * 256)  + ModbusData[3]) + ((ModbusData[4] * 256) + ModbusData[5]) > 32){
         printf("Requested registers out of range.  0x0000 to 0x020.\r\n");
         error = 1;
     }
    
    if(error == 0){

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

        UART1_Write_string(MBRespon,MBResCnt);
    }else{
        ModbusError(0x02);
    }
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

void UART1_Write_string(unsigned char * data, int data_len)
{
    TXMode();
    while(!EUSART1_is_tx_ready()); // Hold the program until TX is ready
    for (int i = 0; i < data_len; i++) {
        EUSART1_Write(data[i]);
        while(!EUSART1_is_tx_done()); // Hold until sent
    }

}


void PrintModRespon(){
    // Print out the response for diagnostics over ESUART 2
    int i=0;
    
    printf("Modbus Response:\r\n");

    
    if(MBRespon[1] == 0x03){

            
        printf("   Byte 00: 0x%02x - Card Address\r\n", MBRespon[0]);
        printf("   Byte 01: 0x%02x - Function Code (Read Multi Reg)\r\n", MBRespon[1]);
        printf("   Byte 02: 0x%02x - Num Bytes More\r\n", MBRespon[2]);
        
        
        /* ---- This needs work ---- */
        int j = 1;
        for(i=0; i< MBRespon[2] ; i++ ){
            printf("   Byte %02i: 0x%02x - Reg %i Hi (Add. 0x%02x %02x)\r\n", i+1, MBRespon[i+3],j, ModbusData[2], ModbusData[3] +j-1);
            i++;
            printf("   Byte %02i: 0x%02x - Reg %i Lo\r\n", i+1, MBRespon[i+3],j);
            j++;
        }        
        

        printf("   Byte %02i: 0x%02x - CRC Hi\r\n", i +1 , MBRespon[i + 2 + 1] );
        printf("   Byte %02i: 0x%02x - CRC Lo\r\n", i +2 , MBRespon[i + 2 + 2] );
        
    }else if(MBRespon[1] == 0x10){

            
        printf("   Byte 00: 0x%02x - Card Address\r\n", MBRespon[0]);
        printf("   Byte 01: 0x%02x - Function Code (Read Multi Reg)\r\n", MBRespon[1]);
        printf("   Byte 02: 0x%02x - 1st Reg Add Hi\r\n", MBRespon[2]);
        printf("   Byte 03: 0x%02x - 1st Reg Add Lo\r\n", MBRespon[3]);
        printf("   Byte 04: 0x%02x - Num of Reg Hi\r\n", MBRespon[4]);
        printf("   Byte 05: 0x%02x - Num of Reg Lo\r\n", MBRespon[5]);
        
        
        
        printf("   Byte 06: 0x%02x - CRC Hi\r\n", MBRespon[6]);
        printf("   Byte 07: 0x%02x - CRC Hi\r\n", MBRespon[7]);
        
    }else{
        for(i=0; i< MBResCnt ; i++ ){
            while(!EUSART2_is_tx_ready()); // Hold the program until TX is ready
            printf("   Byte %02i: 0x%02x \r\n", i, MBRespon[i]);
            while(!EUSART2_is_tx_done());   // Hold until done.
        }
    }
    printf("\r\n\n");
    
}



void ClearModbusRespon(){
    int i = 0;    
    for(i=0; i<32; i++ ){
        MBRespon[i] = 0xFF;
    }  
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
         
    UART1_Write_string(MBRespon,MBResCnt);    
    
}



bool ModbusRx(){
    RXMode();
    if(EUSART1_is_rx_ready()){
        if(Debug ==1){
            printf("Something in ESUART1 \r\n");
        }
        do{
            if(EUSART1_is_rx_ready()){

                while(EUSART1_is_rx_ready()){
                    // While there's something to read out of the RX Buffer
                    rxData[ByteNum] = EUSART1_Read();
                    
                    if(Debug == 1){
                        printf("Read: 0x%02x \r\n",rxData[ByteNum]);
                    }
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
            printf("\r\nReceived Modbus CRC checked out.\r\n");
        }else{
            printf("\r\nReceived Modbus CRC is bad.\r\n");
        }
        // Complete Modbus String ready to process.     
        
        return 1;
    }
    return 0;

}

