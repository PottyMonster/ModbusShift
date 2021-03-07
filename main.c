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
int ByteHi, ByteLo = 0xFF;

unsigned int MB300xx[32] = { 0x0000,0x0007,0x07FF,0x0004,0x0005,0x0006,0x0007,0x0008,
                            0x0009,0x000a,0x000b,0x000c,0x000d,0x000e,0x000f,
                            0x0010,0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,
                            0x0017,0x0018,0x0019,0x0020,0x0021,0x0022,0x0023,
                            0x0024,0x0025, 0x0026};     // Assigns 32x 16bit Read Registers


unsigned int MBRespon[32] = { 0xFFFF };

// int loop;



//11 03 06 AE41 5652 4340 49AD
// unsigned char MBRespon[] = {0x11, 0x03, 0x06, 0xAE, 0x41, 0x56, 0x52, 0x43, 0x40, 0x49, 0xAD};

// 01 03 00 02 00 05
// will reply with
// 01 03 06 07 ff 00 04 00 05 b5 14
// when using default MB300xx[32] array above.

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
