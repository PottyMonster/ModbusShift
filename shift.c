#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "RS232.h"
#include "string.h"
#include "main.h"
#include "Modbus.h"


void SIPO_DSWrite(bool Dat){
    // Sets output to 74 594 and pulses SHCP to shift it in
    if(Dat == 1){
        SIPO_DS_SetHigh();
        D2LED_SetHigh();
    }else{
        SIPO_DS_SetLow();
        D2LED_SetLow();
    }
    // __delay_ms(5);
    SIPO_SHCP_SetHigh();
    D3LED_SetHigh();
    // __delay_ms(5);
    SIPO_SHCP_SetLow();
    D3LED_SetLow();
    // __delay_ms(5);    
}

void SIPO_STCPClock(){   
    // __delay_ms(5);
    SIPO_STCP_SetHigh();
    D4LED_SetHigh();   
    
    // __delay_ms(5);
    SIPO_STCP_SetLow();
    D4LED_SetLow();
}

void SIPO_Reset(){
    // Pulses SHR and STR low for a period of time to reset
    
    SIPO_Reset_SetLow();
    D5LED_SetLow();
    SIPO_STCPClock();
    // __delay_ms(500);
    SIPO_Reset_SetHigh();
    D5LED_SetHigh();
    

}

void SIPO_ShiftByte(unsigned int i){
    // Reads in the next byte of Modbus data.

    unsigned int TempRead = MB400xx[i]; 
    
    // unsigned int TempRead = MB400xx[MB306xx[0] - i];  // -- Need something like this to reverse
    
    // printf("TempRead: %x \r\n", MB400xx[i]);
    
    // MB306xx how many bits of Modbus data to shift through. 
    // Either 8 for just using single lower byte of Modbus data
    // or 16 if using full 2x bytes for talking to Analogue Output.
    // When using both bytes output to 8 x2 shift registers before clocking
    // out.
    // SIPOW sets this (either 8 or 16), saved in EEPROM and can be read through
    // Modbus address 0x0602
    
    for(int j = 0; j< MB306xx[2] ; j++){
        
        if((TempRead & 0x0001) == 0x0001){
            SIPO_DSWrite(1);
        }else{
            SIPO_DSWrite(0);
        }

        TempRead >>= 1;    
    }
}

void SIPO_ShiftWrite(void){
    // Reads in MB400xx and shifts the bits out
 
    SIPO_Reset();
    // __delay_ms(500);
    
    for(int i = 0; i< MB306xx[0]; i++){
        SIPO_ShiftByte(i);
    }
    
    
    SIPO_STCPClock();
}


void PISO_STCPClock(void){
    
    // Latches the inputs
    
    // __delay_ms(500);
    PISO_STCP_SetHigh();
    D3LED_SetHigh();   
    
    // __delay_ms(500);
    PISO_STCP_SetLow();
    D3LED_SetLow(); 
}

void PISO_Reset(void){

    PISO_Reset_SetLow();
    D2LED_SetLow();
    PISO_STCPClock();
    // __delay_ms(500);
    PISO_Reset_SetHigh();
    D2LED_SetHigh();
    
}


void PISO_PL(void){
    // Loads input latches to output shift register
    
    PISO_PL_SetLow();
    D4LED_SetHigh();   
    
    // __delay_ms(5);
    PISO_PL_SetHigh();
    D4LED_SetLow();     
    
}



void PISO_SHCPClock(void){
    // Clocks the output shift register
    // __delay_ms(500);
    PISO_SHCP_SetHigh();
    D5LED_SetHigh();   
    
    // __delay_ms(500);
    PISO_SHCP_SetLow();
    D5LED_SetLow(); 
}


void PISO_ReadByte(unsigned int i){
    // Read in some bits and load them in to the associated MB register

    
    // MB306xx how many bits of Modbus data to shift through. 
    // Either 8 for just using single lower byte of Modbus data
    // or 16 if using full 2x bytes for talking to Analogue Output.
    // When using both bytes output to 8 x2 shift registers before clocking
    // out.
    // SIPOW sets this (either 8 or 16), saved in EEPROM and can be read through
    // Modbus address 0x0602
    
    // printf("Currently contains Mod300xx[%i]: 0x%04x \r\n",i, MB300xx[i]);
    MB300xx[i] = 0x0000;
    // printf("After Clearing Mod300xx[%i]: 0x%04x \r\n",i, MB300xx[i]);
    
    for(int j = 0; j< MB306xx[3]; j++){
        
        if (j != 0){
            MB300xx[i] <<= 1;
        }
        
        if(PISO_Q_GetValue() == 1){
            MB300xx[i] = MB300xx[i] + 1;
            // printf("Q = 1 \r\n");
        }else{
            // printf("Q = 0 \r\n");
        }
        // printf("Mod300xx[%i]: 0x%04x \r\n",i, MB300xx[i]);
                
        PISO_SHCPClock();

    }
    
}


void PISO_ShiftRead(void){
    // Reads in all of the PISO registers to the Modbus input register
 
    PISO_Reset();
    // __delay_ms(500);
    
    PISO_STCPClock();   // Captures inputs in to input registers
    PISO_PL();          // Parallel loads in to output registers
    
    // MB306xx[i] = Num of PISO registers
    for(int i = 0; i< MB306xx[1]; i++){
        PISO_ReadByte(i);
    }
    
    
}

