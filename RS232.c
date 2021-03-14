#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "RS232.h"
#include "string.h"
#include "main.h"
#include "Modbus.h"



void Initalisation(void){
    // Move card part, ser and rev from EEPROM to MB401xx
    // Move compiler Date, Time, XC8 Version to MB401

}


void InitialiseString(void){
       
    // Send Initalisation String

    printf("\rDan and Sam's Modbus GPIO Expansion - AP00070125-01 Rev -\r\n"); 

    Initalisation();
    
    // Needs to read EEPROM and update Mdbus registers too.
    
    printf("\rCard Ser No. 2109002 \r\n"); 
    printf("\rCard Address. 0x05 \r\n");
    printf("\rCompiled on %s at %s by XC8 version %u\r\n\n",
            __DATE__, __TIME__, __XC8_VERSION);
    printf("\rFunction Codes Supported:\r\n"); 
    printf("\r   0x03 - Read Multiple Registers (Max 32x 16bit)\r\n"); 
    printf("\r   0x10 - Write Multiple Registers (Max 32x 16bit)\r\n\n");
    printf("\rInitalisation Complete - Ready\r\n\n");
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

                
                EUSART2_Write(temp[0]);  // send a byte to TX  (from Rx)
                
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
        printf("Debug Enabled\r\n");
    }else{
        Debug =0;
        printf("Debug Disabled\r\n");
    }    
    
}


void ClearEEAddRange(unsigned int StartAdd, unsigned int NumBytes){
    // Writes 0xFF in to EEPROM address space
    
    printf("Clearing EEPROM from Address: 0x%04x, Num Bytes: %i \r\n", StartAdd, NumBytes);
    
    int i = 0;
    
    for(i=0; i<NumBytes; i++){
        DATAEE_WriteByte(StartAdd, 0xFF);
        StartAdd++;
    }
    
}


void SaveCardDat(char Name[20], unsigned int MBAddress, uint16_t dataeeAddr, int NumBytes){
    
    int i = 0;
    unsigned char Conf, readData;
    uint16_t dataeeAddrWrk = dataeeAddr;
    
    printf("Saving Card Data\r\n");
    printf("Name: %s  MBAddress: 0x%04x   dataeeAddr: 0x%04x   NumBytes: %i \r\n", Name, MBAddress, dataeeAddr, NumBytes);
   
    printf("Enter card %s (max %i characters): ", Name, NumBytes);
    
    strcpy(Command, "");
    
    while(ReadRX232(NumBytes) == 0){};
    printf("\r\nEntered: %s \r\n Confirm  Y|N?: ", Command);    

    // Wait for reply
    while(!EUSART2_is_rx_ready());

    Conf = EUSART2_Read();

    // 0x59 = "Y" and 0x79 = "y"
    if(Conf == 0x79 || Conf == 0x59){
        Conf = 0xFF;
        printf("Y\r\nSaving Serial Number \r\n");
        printf("Num Chars: %i \r\n", strlen(Command));

        
        /* Might need to clear EEPROM data */
        ClearEEAddRange(dataeeAddr,NumBytes);
        
        // Save data to EEPROM
        for (i = 0; i < strlen(Command); i++){              
            printf("Char 0x%02x in 0x%02x \r\n", Command[i], dataeeAddrWrk);
            DATAEE_WriteByte(dataeeAddrWrk, Command[i]);
            dataeeAddrWrk++;
            __delay_ms(50);
        }
        
        printf("Serial Number Saved. \r\n");
        
        // This but just reads it back out for checking it's worked.
        dataeeAddrWrk = dataeeAddr;
         __delay_ms(50);        
        

        for(i = 0; i < strlen(Command); i++){
            readData = DATAEE_ReadByte(dataeeAddrWrk);
            printf("EEPROM: 0x%02x Add: 0x%02x \r\n", readData,dataeeAddrWrk);           
            dataeeAddrWrk++;
            __delay_ms(50);
        }

        // Clear RS232 Command 
        strcpy(Command, "");

        
        // Save to Modbus Registers
        
        
        
        
    }

    
}


bool ValidateCmd(void){
    
    int i = 0;

    
    printf("\r\n Validating Command: %s \r\n" , Command);
    
    if(!strcmp(Command,"debug")){
        TogDebug();
        return 1;
    }else if(!strcmp(Command,"?")){
        InitialiseString();
        return 1;
    }else if(!strcmp(Command,"serial")){

        char ConfName[20] = "Serial Number";
        int MaxChars = 10;
        // Change Serial Number
        // RecSerNum(); // Temp replaced with new function SaveCardDat below
        
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0300,0x0300,MaxChars);   
        return 1;


    }else if(!strcmp(Command,"part")){
        
        char ConfName[20] = "Part Number";
        int MaxChars = 16;
        SaveCardDat(ConfName,0x0100,0x0100,MaxChars);
        
        
        // Read next string as serial number

        return 1;
    }else if(!strcmp(Command,"rev")){

        char ConfName[20] = "Revision";
        int MaxChars = 2;
        
        // Parameter, MB ADdress, EEProm Address, Max Chars
        SaveCardDat(ConfName,0x0200,0x0200,MaxChars);
        
    
    }else{
        return 0;
    }
    

    
}