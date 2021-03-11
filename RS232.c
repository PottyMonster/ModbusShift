#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "RS232.h"
#include "string.h"
#include "main.h"

char temp[2] = {'Z','\0'};



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


int ReadRX232(int NumChars) 
{    // Capture input string

    /* local variable definition */
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
             }else{
                 // Nothing received so do nothing.
                 // printf("Nothing Received");
                 // __delay_ms(500);
             }

        }while( temp[0] !='\r' );
        printf("\r\n\n");
        return NumChars;
    }

    return 0;

   
}


bool ValidateCmd(void){
    printf("\r\n Validating Command: %s \r\n" , Command);
    
    if(!strcmp(Command,"debug")){
        if(Debug==0){
            Debug =1;
            printf("Debug Enabled\r\n");
        }else{
            Debug =0;
            printf("Debug Disabled\r\n");
        }
        return 1;
    }else if(!strcmp(Command,"?")){
        InitialiseString();
        return 1;
    }else if(!strcmp(Command,"serial")){
        strcpy(Command, "");
        printf("Enter card serial number: ");
        
        // if(ReadRX232(16) != 0)
        while(ReadRX232(16) ==0){
            // hold
        };
        
        printf("\r\nNext Command: %s \r\n", Command);
        
        
        
        // Read input.seri
        return 1;
    }else if(!strcmp(Command,"part")){
        printf("\r\n Enter card part number (e.g. \"AP00070541-01\"): ");
        
        // Read next string as serial number
        
        
        
        
        return 1;
    }else{
        return 0;
    }
    

    
}
