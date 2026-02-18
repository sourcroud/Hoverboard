//
// Created by sourc on 07.08.2025.
//

#ifndef IOMASKS_H
#define IOMASKS_H

// ########################## DEFINES ##########################
#define DEBUG_SERIAL
#define HOVER_SERIAL_BAUD   115200      // [-] Baud rate for HoverSerial (used to communicate with the hoverboard)
#define DEBUG_SERIAL_BAUD   115200      // [-] Baud rate for built-in Serial (used for the Serial Monitor)
#define START_FRAME         0xABCD     	// [-] Start frame definition for reliable serial communication
#define TIME_SEND_COMMAND   100         // [ms] Sending command time interval
#define TIME_PRINT_SERIAL   500


// ########################## PIN ASSIGNMENT ##########################

// clock (blue)
#define ps2clock 5
// command (orange)
#define ps2command 4
// attention (yellow)
#define ps2attention 2
// data (brown) via pullup (3.3V)
#define ps2data 3

#endif //IOMASKS_H
