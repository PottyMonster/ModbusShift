#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "RS232.h"
#include "string.h"
#include "main.h"
#include "Modbus.h"
#include "ctype.h"


void CardConfigIni(char Name[20], char* RetNum, uint16_t dataeeAddrWrk, int NumBytes){
    // Move card part, ser and rev from EEPROM to Measure Bus registers.
    // Move compiler Date, Time to Measure Bus registers.
    // NumBytes = Number of Modbus Registers

    char readDataOdd, readDataEven;
    int i=0, j=0; 

    // printf("Num Bytes Config: %i \r\n", NumBytes);
    
    // Serial Number to ModBus
   
    for(i = 0; i < NumBytes; i++){
        readDataOdd = DATAEE_ReadByte(dataeeAddrWrk);   // Returns byte from EEPROM
        // printf("readDataOdd: 0x%02x Add: 0x%02x \r\n", readDataOdd,dataeeAddrWrk);
        __delay_ms(20);
        
        // Hides default 0xFF characters so doesn't appear on inialisation printout
        if(readDataOdd != 0xFF){
            RetNum[j] = readDataOdd;
            // printf("ReadDataOdd: %s \r\n", readDataOdd);
            j++;
        }
                
        dataeeAddrWrk++;
        readDataEven = DATAEE_ReadByte(dataeeAddrWrk);
        // printf("readDataEven: 0x%02x Add: 0x%02x \r\n", readDataEven,dataeeAddrWrk);          
        dataeeAddrWrk++;
        __delay_ms(20);

        // Hides default 0xFF characters so doesn't appear on inialisation printout
        if(readDataEven != 0xFF){
            RetNum[j] = readDataEven;
            // printf("readDataEven: %s \r\n", readDataEven);
            j++;
        }
        
        if(!strcmp("Serial",Name)){
            MB303xx[i] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("Part",Name)){
            MB301xx[i] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("Rev",Name)){
            MB302xx[i] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("SIPOL",Name)){
            MB306xx[0] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("PISOL",Name)){
            MB306xx[1] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("SIPOW",Name)){
            MB306xx[2] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }else if(!strcmp("PISOW",Name)){
            MB306xx[3] = readDataOdd *256 + readDataEven;   // Merge to 16bits
        }
        
        
    }
    
    RetNum[j] = '\0';
    
}


void PrintAnIp(unsigned int i){
    // --- NEEDS UPDATING WHEN MORE AN IP USED ---
    uint16_t convertedValue;

    if(i == 1){
        convertedValue = ADCC_GetSingleConversion(AIP_0);
    }else if(i == 2){
        convertedValue = ADCC_GetSingleConversion(AIP_0);    // Currently 0    
    }else if(i == 3){
        convertedValue = ADCC_GetSingleConversion(AIP_0);    // Currently 0    
    }else if(i == 4){
        convertedValue = ADCC_GetSingleConversion(AIP_0);    // Currently 0    
    }else if(i == 5){
        convertedValue = ADCC_GetSingleConversion(AIP_0);    // Currently 0    
    }else{
        convertedValue = 0xFFFF;
    }


    printf("\r\nADC%i: 0x%04x \r\n", i, convertedValue);    
    
}



void InitialiseString(bool Partial){

    char readDataOdd, readDataEven;
    
    char SerialNum[11] = { '\0' };        
    CardConfigIni("Serial", SerialNum,0x0120,5);    // Name, Variable, EEMPROM Address, Num Mod Registers
    
    char PartNum[19] = { '\0' };    
    CardConfigIni("Part", PartNum,0x0100,8);    
    
    char RevNum[3] = { '\0' };    
    CardConfigIni("Rev", RevNum,0x0110,1);

    char SIPOL[3] = { '\0' };    
    CardConfigIni("SIPOL", SIPOL,0x0130,1);
    
    char PISOL[3] = { '\0' };    
    CardConfigIni("PISOL", PISOL,0x0132,1);
    
    char SIPOW[3] = { '\0' };    
    CardConfigIni("SIPOW", SIPOW,0x0134,1);
    
    char PISOW[3] = { '\0' };    
    CardConfigIni("PISOW", PISOW,0x0136,1);    


    // Send Initalisation String

    printf("\r\nDan's Modbus GPIO Expansion\r\n"); 
    
    // Needs to read EEPROM and update Mdbus registers too.
    
    printf("Card Ser No. %s \r\n",SerialNum);
    printf("Card Part No. %s \r\n",PartNum);
    printf("Card Revision. %s \r\n",RevNum);
    printf("Card Address. 0x05 \r\n");
    printf("Compiled on %s at %s by XC8 version %u\r\n\n",
            __DATE__, __TIME__, __XC8_VERSION);
    printf("SIPO Length: %d \r\n", MB306xx[0]);
    printf("SIPO Bits: %d \r\n", MB306xx[2]);
    printf("PISO Length: %d \r\n", MB306xx[1]);
    printf("PISO Bits: %d \r\n\n", MB306xx[3]);
       
    
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
        printf("Modbus Function Codes Supported:\r\n\n"); 
        printf("   0x04 - Read Multiple 16bit Registers\r\n");
        printf("      Add 0x0000 to 0x0031 - 32x Circuit Get Status (lower 8bits only)\r\n");    
        printf("      Add 0x0100 to 0x0108 - Part Number (ASCII)\r\n");
        printf("      Add 0x0200 - Revision (ASCII)\r\n");
        printf("      Add 0x0300 to 0x0304 - Serial Number (ASCII)\r\n");
        printf("      Add 0x0400 to 0x0405 - Compile Date (ASCII)\r\n");
        printf("      Add 0x0500 to 0x0504 - Compile Time - (ASCII)\r\n");
        printf("      Add 0x0600 - Serial In Parallel Out Count (SIPO) \r\n");
        printf("      Add 0x0601 - Parallel In Serial Out Count (PISO) \r\n");
        printf("      Add 0x0602 - Serial In Parallel Out Num of Bits (SIPO) \r\n");
        printf("      Add 0x0603 - Parallel In Serial Out Num of Bits (PISO) \r\n");        
        printf("      Add 0x0700 to 0x0704 - 5x Analogue Inputs (0x000 to 0x03ff)\r\n\n"); 
        printf("   0x10 - Write Multiple Output Holding Registers (Max 32x 16bit)\r\n");
        printf("      Add 0x0000 to 0x0031 - 32x Circuit Set Status  (lower 8bits only)\r\n\n");
        printf("   0x03 - Read Multiple Output Holding Registers (Max 32x 16bit)\r\n");
        printf("      Add 0x0000 to 0x0031 - 32x Circuit Get Status  (lower 8bits only)\r\n\n");
        
        
        printf("Commands Supported:\r\n"); 
        printf("   ? - Initalise and display card details\r\n"); 
        printf("   an - Print all analogue inputs\r\n");
        printf("   an1 - an5 - Print specific analogue input\r\n");
        printf("   serial - Set card serial number\r\n");
        printf("   part - Set card part number\r\n");
        printf("   rev - Set card part number\r\n");
        printf("   sipo l - Length of SIPO chain (1 - 32)\r\n");
        printf("   sipo b - SIPO Number of bits (8 or 16)\r\n");
        printf("   piso l - Length of PISO chain (1 - 32)\r\n");
        printf("   piso b - PISO Number of bits (8 or 16)\r\n");
        printf("   mod h - Print Modbus Circuit Holding Registers\r\n");
        printf("   mod i - Print Modbus Circuit Input Registers\r\n");        
        printf("   debug - Toggles trace outputs. Slows down time device can respond between commands. DEFAULT ON!\r\n\n");
 
        /*
        uint16_t convertedValue;
        convertedValue = ADCC_GetSingleConversion(AIP_0);        
        printf("ADC0: 0x%04x \r\n\n", convertedValue);
        */
        
        PrintAnIp(1);
        PrintAnIp(2);
        PrintAnIp(3);
        PrintAnIp(4);
        PrintAnIp(5);
        
        if(CheckConfig() == 1){
            ConfGood = 1;
            printf("Initalisation Complete - Ready\r\n\n");   
        }else{
            printf("--- Configuration Required --- \r\n\n");
        }

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
        int CommandLength = strlen(Command);        // Should this have return infront of it?        
        printf("\r\n\n");
        return CommandLength;        

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
    
    // printf("Clearing EEPROM from Address: 0x%04x for num bytes: %i \r\n", StartAdd, NumBytes);
        
    for(int i = 0; i<NumBytes; i++){
        DATAEE_WriteByte(StartAdd +i, 0xFF);
        // printf("Clearing EEPROM from Address: 0x%04x \r\n", StartAdd +i);
    }
    
}


void SaveCardDat(char Name[20], unsigned int MBAddress, uint16_t dataeeAddr, int NumBytes){
    
    // printf("\r\n SaveCardDat Name: %s MBAddress: 0x%04x dataeeAddr: 0x%04x NumBytes: %i \r\n", Name, MBAddress, dataeeAddr, NumBytes);
    
    int i = 0;
    unsigned char Conf, readData;
    uint16_t dataeeAddrWrk = dataeeAddr;
    
    if(!strcmp("PISO Length",Name)){
        printf("\r\nEnter number of PISO registers (1 - 32) : ");
    }else if(!strcmp("PISO Bits",Name)){
        printf("\r\nPISO 8 or 16 bits? : ");
    }else if(!strcmp("SIPO Length",Name)){
        printf("\r\nEnter number of SIPO registers (1 - 32) : ");
    }else if(!strcmp("SIPO Bits",Name)){
        printf("\r\nSIPO 8 or 16 bits? : ");
    }else{
        printf("\r\nEnter card %s (max %i characters): ", Name, NumBytes);
    }
    
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
        // printf("Num Chars: %i \r\n", strlen(Command));

        
        /* Might need to clear EEPROM data */
        ClearEEAddRange(dataeeAddr,NumBytes);

   
        if((    !strcmp("SIPO Length",Name)) 
                || (!strcmp("PISO Length",Name)) 
                || (!strcmp("SIPO Bits",Name)) 
                || (!strcmp("PISO Bits",Name))
            ){
            // Convert ASCII input from RS232 to integer for saving.
            int num = atoi(Command);
            // printf("Saving 0x00 in 0x%04x \r\n",Command, dataeeAddrWrk);
            DATAEE_WriteByte(dataeeAddrWrk, 0x00);
            dataeeAddrWrk++;
            // printf("Saving Command: %s as Int %i in 0x%04x \r\n",Command, num, dataeeAddrWrk);            
            DATAEE_WriteByte(dataeeAddrWrk, num);
        }else{
            // Leave ASCII input from RS232 as ASCII for saving.
            // Save data to EEPROM
            for (i = 0; i < strlen(Command); i++){              
                DATAEE_WriteByte(dataeeAddrWrk, Command[i]);     
                // printf("Saving Command: %s in 0x%04x \r\n",Command, dataeeAddrWrk);                
                dataeeAddrWrk++;
                __delay_ms(20);
            }
        }       

        printf("%s Saved. \r\n",Name);
        LED_Bad_SetHigh();
        LED_Good_SetHigh();
        LED_Ready_SetHigh();
        LED_Action_SetHigh();
        __delay_ms(200);
        LED_Bad_SetLow();
        LED_Good_SetLow();
        LED_Ready_SetLow();
        LED_Action_SetLow();
        __delay_ms(100);
        LED_Bad_SetHigh();
        LED_Good_SetHigh();
        LED_Ready_SetHigh();
        LED_Action_SetHigh();
        __delay_ms(200);
        LED_Bad_SetLow();
        LED_Good_SetLow();
        LED_Ready_SetLow();
        LED_Action_SetLow();
        
        // Clear RS232 Command 
        strcpy(Command, "");  
        
    }else if(Conf == 0x4e || Conf == 0x6e){
        printf("Not saved\r\n");
        LED_Bad_SetHigh();
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
        SaveCardDat(ConfName,0x0300,0x0120,MaxChars);  
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
        SaveCardDat(ConfName,0x0200,0x0110,MaxChars);
        InitialiseString(1);
        return 1;
    }else if((!strcmp(Command,"SIPO L")) || (!strcmp(Command,"sipo l"))){
        char ConfName[20] = "SIPO Length";
        int MaxChars = 2;
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0600,0x0130,MaxChars);
        InitialiseString(1);
        return 1;
    }else if((!strcmp(Command,"PISO L")) || (!strcmp(Command,"piso l"))){
        char ConfName[20] = "PISO Length";
        int MaxChars = 2;
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0601,0x0132,MaxChars);
        InitialiseString(1);
        return 1;
    }else if((!strcmp(Command,"SIPO B")) || (!strcmp(Command,"sipo b"))){
        char ConfName[20] = "SIPO Bits";
        int MaxChars = 2;
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0602,0x0134,MaxChars);
        InitialiseString(1);
        return 1;
    }else if((!strcmp(Command,"PISO B")) || (!strcmp(Command,"piso b"))){
        char ConfName[20] = "PISO Bits";
        int MaxChars = 2;
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0603,0x0136,MaxChars);
        InitialiseString(1);
        return 1;
    }else if((!strcmp(Command,"MOD H")) || (!strcmp(Command,"mod h"))){
        PrintHolding();
        return 1;
    }else if((!strcmp(Command,"MOD I")) || (!strcmp(Command,"mod i"))){
        PrintInput();
        return 1;
    }else if((!strcmp(Command,"AN1")) || (!strcmp(Command,"an1"))){
        PrintAnIp(1);
        return 1;
    }else if((!strcmp(Command,"AN2")) || (!strcmp(Command,"an2"))){
        PrintAnIp(2);
        return 1;
    }else if((!strcmp(Command,"AN3")) || (!strcmp(Command,"an3"))){
        PrintAnIp(3);
        return 1;
    }else if((!strcmp(Command,"AN4")) || (!strcmp(Command,"an4"))){
        PrintAnIp(4);
        return 1;
    }else if((!strcmp(Command,"AN5")) || (!strcmp(Command,"an5"))){
        PrintAnIp(5);
        return 1;
    }else if((!strcmp(Command,"AN")) || (!strcmp(Command,"an"))){
        PrintAnIp(1);
        PrintAnIp(2);
        PrintAnIp(3);
        PrintAnIp(4);
        PrintAnIp(5);
        return 1;
    }else{
        return 0;
    }
    
    return 0;
    
}