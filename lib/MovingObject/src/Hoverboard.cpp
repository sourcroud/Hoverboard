//
// Created by sourc on 06.08.2025.
//

#include "Hoverboard.h"

void sendCommand( const int16_t speed, const int16_t steer ) {
    uint16_t checksum = 0xAAAA ^ (uint16_t)steer ^ (uint16_t)speed;
    uint8_t packet[8];
    packet[0] = 0xAA;
    packet[1] = 0xAA;
    packet[2] = steer & 0xFF;
    packet[3] = (steer >> 8) & 0xFF;
    packet[4] = speed & 0xFF;
    packet[5] = (speed >> 8) & 0xFF;
    packet[6] = checksum & 0xFF;
    packet[7] = (checksum >> 8) & 0xFF;

    Serial1.write( packet, sizeof(packet) );
}