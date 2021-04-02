#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "RS232.h"
#include "string.h"
#include "main.h"
#include "Modbus.h"


void CardConfigIni(char Name[20], char* RetNum, uint16_t dataeeAddrWrk, int NumBytes){
    // Move card part, ser and rev from EEPROM to Measure Bus registers.
    // Move compiler Date, Time to Measure Bus registers.

    char readDataOdd, readDataEven;
    int i=0, j=0; 

    // Serial Number to ModBus
   
    for(i = 0; i < NumBytes; i++){
        readDataOdd = DATAEE_ReadByte(dataeeAddrWrk);   // Returns byte from EEPROM
        // printf("readDataOdd: 0x%02x Add: 0x%02x \r\n", readDataOdd,dataeeAddrWrk);
        __delay_ms(50);
        
        // This doesn't work
        if(readDataOdd != 0xFF){
            RetNum[j] = readDataOdd;
            j++;
        }
                
        dataeeAddrWrk++;
        readDataEven = DATAEE_ReadByte(dataeeAddrWrk);
        // printf("readDataOdd: 0x%02x Add: 0x%02x \r\n", readDataEven,dataeeAddrWrk);          
        dataeeAddrWrk++;
        __delay_ms(50);

        // This doesn't work
        if(readDataEven != 0xFF){
            RetNum[j] = readDataEven;
            j++;
        }
        
        if(!strcmp("Serial",Name)){
            MB303xx[i] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("Part",Name)){
            MB301xx[i] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("Rev",Name)){
            MB302xx[i] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }
        
        
    }
    
    RetNum[j] = '\0';
    
}



void InitialiseString(bool Partial){

    char readDataOdd, readDataEven;
    
    char SerialNum[11] = { '\0' };    
    // SerIni(SerialNum);   
    CardConfigIni("Serial", SerialNum,0x0300,5);    // Name, Variable, EEMPROM Address, Num Mod Registers
    
    char PartNum[19] = { '\0' };    
    CardConfigIni("Part", PartNum,0x0100,8);    
    
    char RevNum[2] = { '\0' };    
    CardConfigIni("Rev", RevNum,0x0200,1);       
    
    // Send Initalisation String

    printf("\r\nDan and Sam's Modbus GPIO Expansion\r\n"); 
    
    // Needs to read EEPROM and update Mdbus registers too.
    
    printf("Card Ser No. %s \r\n",SerialNum);
    printf("Card Part No. %s \r\n",PartNum);
    printf("Card Revision. %s \r\n",RevNum);
    printf("Card Address. 0x05 \r\n");
    printf("Compiled on %s at %s by XC8 version %u\r\n\n",
            __DATE__, __TIME__, __XC8_VERSION);
    
    int j = 0;
    
    // Load Compiled Date in to Modbus registers
    char Date[11] = __DATE__;    
    for(int i=0; i<12; i = i+2){     
        readDataOdd = Date[i];
        readDataEven = Date[i +1];        
        MB304xx[j] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        j++;
    }
    
    // Load Compiled Time in to Modbus registers
    j = 0;
    char Time[8] = __TIME__;
    for(int i=0; i<8; i = i+2){     
        readDataOdd = Time[i];
        readDataEven = Time[i +1];        
        MB305xx[j] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        j++;
    }
      

    if(Partial != 1){
        printf("Initalisation Complete - Ready\r\n\n");   
        printf("Modbus Function Codes Supported:\r\n\n"); 
        printf("   0x04 - Read Multiple 16bit Registers\r\n");
        printf("      Add 0x0000 to 0x0031 - 32x Circuit Get Status (lower 8bits only)\r\n");    
        printf("      Add 0x0100 to 0x0108 - Part Number (ASCII)\r\n");
        printf("      Add 0x0200 - Revision (ASCII)\r\n");
        printf("      Add 0x0300 to 0x0304 - Serial Number (ASCII)\r\n");
        printf("      Add 0x0400 to 0x0405 - Compile Date (ASCII)\r\n");
        printf("      Add 0x0500 to 0x0504 - Compile Time - (ASCII)\r\n");
        printf("      Add 0x0600 to 0x0602 - 3x Analogue Inputs (0x000 to 0x03ff)\r\n\n");    
        printf("   0x10 - Write Multiple Output Holding Registers (Max 32x 16bit)\r\n");
        printf("      Add 0x0000 to 0x0031 - 32x Circuit Set Status  (lower 8bits only)\r\n\n");
        printf("   0x03 - Read Multiple Output Holding Registers (Max 32x 16bit)\r\n");
        printf("      Add 0x0000 to 0x0031 - 32x Circuit Get Status  (lower 8bits only)\r\n\n");
        
        
        printf("Commands Supported:\r\n"); 
        printf("   ? - Initalise and display card details\r\n"); 
        printf("   serial - Set card serial number\r\n");
        printf("   part - Set card part number\r\n");
        printf("   rev - Set card part number\r\n");
        printf("   debug - Toggles trace outputs. Slows down time device can respond between commands. DEFAULT ON!\r\n\n");
 
        uint16_t convertedValue;
        convertedValue = ADCC_GetSingleConversion(AIP_0);        
        printf("ADC0: 0x%04x \r\n", convertedValue);        

    };
}


int ReadRX232(int NumChars) 
{    /* Capture input string of max NumChars
      * After max NumChars starts to loop round
      */
    
    /* local variable definition */    
    char temp[2] = {'Z','\0'};
    
    
    if(EUSART2_is_rx_ready()) 
    {
        /* do loop execution */
        do {
         // printf("NumChars %s \r\n" , NumChars);

             if(EUSART2_is_rx_ready()) 
             {   

                temp[0]=EUSART2_Read();

                
                EUSART2_Write(temp[0]);  // Echo back
                
                if(temp[0]!='\r'){
                    strcat(Command, temp);
                };

                if(strlen(Command)>NumChars)
                {
                    // delete first character of string and left shift the rest   
                    memmove(Command, Command+1, strlen(Command));
                    // printf("Del First Char, now contains %s \r\n" , Command);
                };

                if(temp[0]=='\r'){
                      // printf("Received Return \r\n");
                    temp[0]='z'; // Load some junk in there to stop looping again when comes back.
                    return NumChars;
                };    
            }
        }while( temp[0] !='\r' );
        
        Command[strlen(Command)-1] = '\0';  // Remove return character from string
        
        printf("\r\n\n");
        // return NumChars;
        strlen(Command);
    }

    return 0;

   
}


void TogDebug(void){

    if(Debug==0){
        Debug =1;
        printf("\r\nDebug Enabled\r\n");
    }else{
        Debug =0;
        printf("\r\nDebug Disabled\r\n");
    }    
    
}


void ClearEEAddRange(unsigned int StartAdd, unsigned int NumBytes){
    // Writes 0xFF in to EEPROM address space
    
    printf("Clearing EEPROM from Address: 0x%04x for num bytes: %i \r\n", StartAdd, NumBytes);
        
    for(int i = 0; i<NumBytes; i++){
        DATAEE_WriteByte(StartAdd +i, 0xFF);
    }
    
}


void SaveCardDat(char Name[20], unsigned int MBAddress, uint16_t dataeeAddr, int NumBytes){
    
    int i = 0;
    unsigned char Conf, readData;
    uint16_t dataeeAddrWrk = dataeeAddr;
    
    printf("\r\nEnter card %s (max %i characters): ", Name, NumBytes);
    
    strcpy(Command, "");
    
    while(ReadRX232(NumBytes) == 0){};
    printf("\r\nEntered: %s \r\n Confirm  Y|N?: ", Command);    

    // Wait for reply
    while(!EUSART2_is_rx_ready());

    Conf = EUSART2_Read();

    // 0x59 = "Y" and 0x79 = "y"
    if(Conf == 0x79 || Conf == 0x59){
        Conf = 0xFF;
        printf("Y\r\nSaving %s\r\n", Name);
        printf("Num Chars: %i \r\n", strlen(Command));

        
        /* Might need to clear EEPROM data */
        ClearEEAddRange(dataeeAddr,NumBytes);
        
        // Save data to EEPROM
        for (i = 0; i < strlen(Command); i++){              
            DATAEE_WriteByte(dataeeAddrWrk, Command[i]);
            dataeeAddrWrk++;
            __delay_ms(50);
        }
        
        printf("%s Saved. \r\n",Name);
        
        // Clear RS232 Command 
        strcpy(Command, "");  
        
    }else if(Conf == 0x4e || Conf == 0x6e){
        printf("Not saved\r\n");
    }

    
}


bool ValidateCmd(void){
    
    int i = 0;

    // printf("Validating Command: %s \r\n" , Command);
    
    if(!strcmp(Command,"debug")){
        TogDebug();
        return 1;
    }else if(!strcmp(Command,"?")){
        InitialiseString(0);
        return 1;
    }else if(!strcmp(Command,"serial")){
        char ConfName[20] = "Serial Number";
        int MaxChars = 10;
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0300,0x0300,MaxChars);  
        InitialiseString(1);
        return 1;
    }else if(!strcmp(Command,"part")){
        char ConfName[20] = "Part Number";
        int MaxChars = 16;
        SaveCardDat(ConfName,0x0100,0x0100,MaxChars);
        InitialiseString(1);
        return 1;
    }else if(!strcmp(Command,"rev")){
        char ConfName[20] = "Revision";
        int MaxChars = 2;
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0200,0x0200,MaxChars);
        InitialiseString(1);
        return 1;
    
    }else{
        return 0;
    }
    
    return 0;
    
}