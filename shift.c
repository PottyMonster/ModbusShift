#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "RS232.h"
#include "string.h"
#include "main.h"
#include "Modbus.h"


void DSWrite(bool Dat){
    // Sets output to 74 594 and pulses SHCP to shift it in
    if(Dat == 1){
        SIPO_DS_SetHigh();
        D2LED_SetHigh();
    }else{
        SIPO_DS_SetLow();
        D2LED_SetLow();
    }
    __delay_ms(250);
    SIPO_SHCP_SetHigh();
    D3LED_SetHigh();
    __delay_ms(250);
    SIPO_SHCP_SetLow();
    D3LED_SetLow();
}

void STCPClock(){
    // pulses STCP to 74 594 to send to output
    SIPO_STCP_SetHigh();
    D4LED_SetHigh();
    __delay_ms(500);    
    SIPO_STCP_SetLow();
    D4LED_SetLow();
}

void SIPOReset(){
    // Pulses SHR and STR low for a period of time to reset
    SIPO_Reset_SetLow();
    D5LED_SetLow();
    __delay_ms(500);
    SIPO_Reset_SetHigh();
    D5LED_SetHigh();
}

void ShiftByte(unsigned int i){
    // Reads in the next byte of Modbus data.

    unsigned int TempRead = MB400xx[i];
    
    printf("TempRead: %x \r\n", MB400xx[i]);
    
    for(int j = 0; j< 8 ; j++){
        
        if((TempRead & 0x0001) == 0x0001){
            DSWrite(1);
        }else{
            DSWrite(0);
        }

        TempRead >>= 1;    
    }
}

void ShiftWrite(void){
    // Reads in MB400xx and shifts the bits out
 
    SIPOReset();
    __delay_ms(500);
    
    for(int i = 0; i< MB306xx[0]; i++){
        ShiftByte(i);
    }
    
    STCPClock();
}