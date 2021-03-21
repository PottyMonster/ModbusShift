# ModbusShift
Reading data in via Modbus and reading or setting shift registers.

You might need to delete the /nbproject/Makefile-default.mk to get it to build. Let me know.

Uses PIC18F46K40 in Microchip Curiosity HPC dev board.

Curiosity HPC Click Module 1 needs RS485 5 Click fitted. Wired to PC USB with DS_USB_RS485_CABLES. Black wire (0V) to "-" terminal, Orange to "A" terminal, Yellow to "B" terminal. Ensure the red wire (+5V) doesn't touch anything.

Curiosity HPC Click Module 2 needs USB FT232 UART Click fitted, solder jumpers on RC0 and RC1 removed (next to the module), then wire links from RC0 of FT232 Module (TX) to RB7 of PIC (RX), and RC1 (RX) to RB6 of PIC (TX).

Set up two instances of Putty. One instance connects to RS485 module, second instance to FT232 for diagnostics.

Type a character in to the RS485 instance of Putty and you should see it echo'd back, with the status of the process appearing on the FT232 istance of Putty.
