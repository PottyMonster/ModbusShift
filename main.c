#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "stdio.h"
#include "Modbus.h"

/*
                         Main application
 */


bool Debug = 0;
int i = 0;
int MBResCnt = 0;
unsigned int MBResCRC = 0xFFFF;

unsigned char MB300xx[32] = { 0x01,0x07,0xFF,0x04,0x05,0x06,0x07,0x08,
                            0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
                            0x10,0x11,0x12,0x13,0x14,0x15,0x16,
                            0x17,0x18,0x19,0x20,0x21,0x22,0x23,
                            0x24,0x25, 0x26};     // Assigns 32x 16bit Read Registers


unsigned char MBRespon[32] = { 0 };

// int loop;



//11 03 06 AE41 5652 4340 49AD
// unsigned char MBRespon[] = {0x11, 0x03, 0x06, 0xAE, 0x41, 0x56, 0x52, 0x43, 0x40, 0x49, 0xAD};


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
/*
void UART1_Write_string(unsigned char * data){
    TXMode();
    __delay_ms(50);
    int data_len = sizeof(data);
    
    for (int i = 0; i < data_len; i++) {
        EUSART1_Write(data[i]);
    }
}
 */

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
        MBRespon[i] = 0xFF;
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

/*
unsigned int generateCRC(unsigned int messageLength){
    unsigned int crc = 0xFFFF;
    unsigned int crcHigh = 0;
    unsigned int crcLow = 0;
    int i,j = 0;

      for(i=0;i<messageLength-2;i++){
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
    crcHigh = (crc & 0x00FF) <<8;
    crcLow = (crc & 0xFF00) >>8;
    crcHigh |= crcLow;
    crc = crcHigh;
    // printf("CRC: %i", crc);
    return crc;
    
   //
   //     crc = generateCRC(8);
   //     Need to use it like this
   //     response[6] = crc >> 8;
   //     response[7] = crc;

    
}
*/




// unsigned char checkCRC(void){
unsigned int generateCRCHI(int MessCnt){
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
    // crcHigh |= crcLow;
    // printf("Send CRC crcHigh: 0x%02x  crcLow: 0x%02x  \r\n", crcHigh, crcLow);    
    crc = crcHigh;
  return crc;
}

unsigned int generateCRCLo(int MessCnt){
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
    // crcHigh |= crcLow;
    // printf("Send CRC crcHigh: 0x%02x  crcLow: 0x%02x  \r\n", crcHigh, crcLow);    
    crc = crcLow;
  return crc;
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
    ClearModbusRespon();
    
    
    bool RXStat = 0;
    
    while(1)
    {
        if(ModbusRx() == 1){
            // Data has been received and ready to process
            PrintModbus();

            if(ModbusData[1] == 0x03)
            {
                /*
                 * Need to do some error checking of the incoming message. E.G
                 * Valid address , or address + offset not over 100;
                 */
                
                
                // Read 16bit Output registers
                
                // Function to shift in values from shift registers to MB300xx
                MBResCnt = 0;
                MBRespon[0] = ModbusData[0];    // Address
                MBRespon[1] = ModbusData[1];    // Function Code
                MBRespon[2] = ModbusData[5] *2;  // Number of bytes more
                MBResCnt = MBResCnt + 3;
                for(i=0; i< (ModbusData[5]*2) ; i++ ){
                    MBRespon[i +3] = MB300xx[ModbusData[3] +i -1];
                    // Response[3] = MB300xx[02]
                MBResCnt++;
                }
                // MBRespon[i +3] = 0x49;              // CRC Hi
                // MBRespon[i +4] = 0xAD;              // CRC Hi
                
                // MBResCRC = generateCRC(MBResCnt);
                // MBRespon[i +3] = MBResCRC >> 8;
                // MBRespon[i +4] = MBResCRC;
                
                // https://unserver.xyz/modbus-guide/#modbus-rtu-data-frame-section
                
                
                MBRespon[i +3] = generateCRCHI(MBResCnt);
                MBRespon[i +4] = generateCRCLo(MBResCnt);

                MBResCnt =  MBResCnt +2;                
                
                PrintModRespon();
                
                UART1_Write_string(MBRespon,MBResCnt);

            }else{
                printf("Function Code is: 0x%02x \r\n", ModbusData[1]);
                
            }
        
            ClearModbusData();   // Needed when complete
            ClearModbusRespon();
        }
    }
}
/**
 End of File
*/
