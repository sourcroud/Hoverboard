//
// Created by sourc on 07.08.2025.
//

#ifndef IOMASKS_H
#define IOMASKS_H

// ########################## DEFINES ##########################
#define HOVER_SERIAL_BAUD   115200      // [-] Baud rate for HoverSerial (used to communicate with the hoverboard)
#define SERIAL_BAUD         115200      // [-] Baud rate for built-in Serial (used for the Serial Monitor)
#define START_FRAME         0xABCD     	// [-] Start frame definition for reliable serial communication
#define TIME_SEND           100         // [ms] Sending time interval
#define SPEED_MAX_TEST      300         // [-] Maximum speed for testing
#define SPEED_STEP          20          // [-] Speed step
// #define DEBUG_RX                     // [-] Debug received data. Prints all bytes to serial (comment-out to disable)


//SoftwareSerial-Pins:
#define softwareSerial_RX 7
#define softwareSerial_TX 8

//GamePad-Pins:
// clock (blue)
#define ps2clock 12
// command (orange)
#define ps2command 13
// attention (yellow)
#define ps2attention 3
// data (brown) via pullup
#define ps2data 4

#endif //IOMASKS_H
