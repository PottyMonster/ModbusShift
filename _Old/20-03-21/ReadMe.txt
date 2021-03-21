RS232 works if unsigned char MBRespon[32] = { 0xFFFF }
but breaks Modbus response.

unsigned int MBRespon[32] = { 0xFFFF }; 
Modbus works, but breaks RS232.