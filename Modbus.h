/* 
 * File:   Modbus.h
 * Author: danie
 *
 * Created on 02 March 2021, 22:48
 */

/**
  Section: Included Files
*/

unsigned char ModbusData[100] = { 0 };  // Received Modbus Data
int ModDataCnt = 0;

// Part Number
unsigned int MB301xx[7] = { 0x4150,0x3030,0x3036,0x3033,0x3033,0x2d30,0x3200};

// Revision
unsigned int MB302xx[1] = { 0x004 };

// Serial
unsigned int MB303xx[5] = { 0x3132,0x3334,0x3536,0x3738,0x3930 };

// Date
unsigned int MB304xx[5] = { 0x4155,0x4720,0x3039,0x3230,0x3231 };

// Time
unsigned int MB305xx[3] = { 0x3137,0x3335,0x3439 };

// Compiler Version
unsigned int MB306xx[2] = { 0x004d,0x3030 };

// Analogue Inputs
unsigned int MB307xx[3] = { 0x045a, 0x00f1, 0x01c4 };

/**
  @Summary
    Sets RS485 transceiver to Transmit mode so data can be sent back to RS485 master.

  @Description
    When using RS485 in a Simplex configuration the Transceiver needs to be told
    to enter TX mode so data sent from the UART is transmitted back to the RS485 master.
    This function sets the MAX485 control lines to the states to enable serial transmission.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    Uses pin names: 
        TX_ENA_SetHigh();
        RX_ENA_SetHigh();
    Must be matches in MCC or changes in function implementation.
 
*/
void TXMode(void);

/**
  @Summary
    Sets RS485 transceiver to Receiver mode so data can be received from the RS485 master.

  @Description
    When using RS485 in a Simplex configuration the Transceiver needs to be told
    to enter RX mode so data received from the UART is transmitted back to the PIC UARTr.
    This function sets the MAX485 control lines to the states to enable serial reception.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    Uses pin names: 
        TX_ENA_SetHigh();
        RX_ENA_SetHigh();
    Must be matches in MCC or changes in function implementation.
 
*/
void RXMode(void);


/**
  @Summary
    Clears all data from the ModbusData[] array.

  @Description
    When processing of Modbus data is complete, this function clears the Modbus
    buffer containing the last received command string from the Modbus master.

  @Preconditions
    ModbusData[] must exist.

  @Param
    None

  @Returns
    None

  @Comment
    None
 
*/
void ClearModbusData(void);


/**
  @Summary
    Clears the rxData buffer containing the last UART RX data.

  @Description
    Clears the rxData array which is used to take data out of the UART receive
    buffer. This function should be called after the data has been copied out of
    rxData and in to the global ModbusData[] array by the AddRxBuffToModBus() function,
    or if there has been a error during receiving data.

  @Preconditions
    rxData[] must exist.

  @Param
    None

  @Returns
    None

  @Comment
    None
 
*/
void ClearRxBuff(void);




/**
  @Summary
    Adds serial data received by the rxData buffer and to the ModbusData
    array.

  @Description
    When all data that was available in the UART Receiver Buffer has been read out
    to the rxData buffer this function is triggered which moves all of that available
    data in to the ModbusData array to build up the complete message.
 
    This doesn't mean all of the Modbus message has been received, it just means enough
    data has been read out that the UART Receive Buffer is now empty. To work out 
    if all of the data has been received there is a ExpectedBytes integer which is
    compared to the number of bytes counted in the ModDataCnt currently in the 
    ModbusData array.
  
    ExpectedBytes is calculated dynamically depending on the type of function code
    received. The "number of bytes further" in the message is used to calculate how many
    byte to expect.

  @Preconditions
    ExpectedBytes counter exists and contains the number of bytes expected to be received in total.
    ModDataCnt counter exists to track how many bytes of Modbus data has been received.
    rxData[] contains data pulled from the UART receive buffer.
    ModbusData[] exists for the rxData to be added to

  @Param
    None

  @Returns
    None

  @Comment
    None
 
*/
void AddRxBuffToModBus(void);



/**
  @Summary
    Validates the received Modbus data CRC

  @Description
    Reads the Modbus command received and validates the CRC is correct for the
    command bytes.

  @Preconditions
    A complete Modbus message must exist  in the ModbusData array, and the length
    of the message contained in ModDataCnt.

  @Param
    None

  @Returns
    None

  @Comment
    None
 
*/
// unsigned char checkCRC(void);
bool checkCRC(void);


/**
  @Summary
    Receives a Modbus input string from EUSART1.

  @Description
    Starts capturing input data from the EUSART1 RX buffer when something has been received
    then adds it to the ModbusData array for processing later.

  @Preconditions
    ExpectedBytes counter exists and contains the number of bytes expected to be received in total.
    ModDataCnt counter exists to track how many bytes of Modbus data has been received.
    rxData[] contains data pulled from the UART receive buffer.
    ModbusData[] exists for the rxData to be added to

  @Param
    RXStat is a boolean flag to indiciate when the EUSART1 RX buffer has had everything
    read out.
    ByteNum counts the number of bytes that have been read out of the EUSART1 RX Buffer.
    rxData[] contains the data read out of the EUSART1 RX Buffer.
    ModDataCnt is a integer count of the number of bytes that have been copied over from
    rxData to the ModbusData array.
    ExpectedBytes is a integer count of the number of bytes expected to be received.
    This is a sum of the standard Modbus protocol data and the ammount of data packets.

  @Returns
    return 1 if successful

  @Comment
    Function Code 10 = Write Multiple 16bit values to Modbus data register.
        Byte Num        Function
            1               Device Address
            2               Function Code (i.e. 0x10)
            3 - 4           Address of first Register to write to
            5 - 6           Number of registers to write to after first address
            2x nBytes       The data to be writted to the address. 16 bits. Hi first then lo
            Last 2x Bytes   Checksum CRC
 
*/
bool ModbusRx(void);
void PrintModbus();
void ClearModbusRespon();
void PrintModRespon();
void UART1_Write_string(unsigned int * data, int data_len);
unsigned int generateCRC(int MessCnt, bool HiOrLo);
void ModbusFC03(void);
bool checkCRC(void);
void ModbusError(int ErrorCode);
void ModbusFC10(void);
void PrintMB400(void);


#ifndef MODBUS_H
#define	MODBUS_H


#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* MODBUS_H */

