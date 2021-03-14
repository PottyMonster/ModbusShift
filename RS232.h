/* 
 * File:   rx232.h
 * Author: danie
 *
 * Created on 10 March 2021, 17:10
 */

char Command[16];    // Array where command builds up


int ReadRX232(int NumChars);
void InitialiseString(void);
void Initalisation(void);


bool ValidateCmd(void);

#ifndef RX232_H
#define	RX232_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RX232_H */

