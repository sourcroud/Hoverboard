//
// Created by sourc on 06.08.2025.
//

#ifndef HOVERBOARD_H
#define HOVERBOARD_H

#include "config.h"
#include <Arduino.h>
//#include "stdint.h"

typedef struct
    {
        uint16_t start;
        int16_t steer;
        int16_t speed;
        uint16_t checksum;
    } SerialCommand;

typedef struct{
        uint16_t start;
        int16_t  cmd1;
        int16_t  cmd2;
        int16_t  speedR_meas;
        int16_t  speedL_meas;
        int16_t  batVoltage;
        int16_t  boardTemp;
        uint16_t cmdLed;
        uint16_t checksum;
    } __attribute__((packed)) SerialFeedback;

class Hoverboard {
private:
    unsigned long lastFeedbackPrint;
    unsigned long lastCommandPrint;
    Stream& _port;
    // Internal data handling
    SerialCommand command;
    SerialFeedback feedback;
    SerialFeedback newFeedback;

    // Global variables
    uint8_t idx;                        // Index for new data pointer
    uint16_t bufStartFrame;             // Buffer Start Frame
    byte *pData;                        // Pointer declaration for the new received data
    byte incomingByte;
    byte incomingBytePrev;

public:
    Hoverboard(Stream& serialPort );
    void sendCommand( int16_t uSpeed, int16_t uSteer );
    void receive();
    int16_t getSpeedR() const;
    int16_t getSpeedL() const;
    float getBatteryVoltage() const;
    int16_t getBoardTemp() const;
    uint16_t getCmdLed() const;
};



#endif //HOVERBOARD_H
