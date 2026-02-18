//
// Created by sourc on 06.08.2025.
//


//#include <HardwareSerial.h>
#include "Hoverboard.h"

Hoverboard::Hoverboard(Stream& serialPort )
    :_port( serialPort )
{
    bufStartFrame = 0;
    idx = 0;
}

void Hoverboard::sendCommand( const int16_t uSpeed, const int16_t uSteer ) {
    // Create command
    command.start    = static_cast<uint16_t>(START_FRAME);
    command.steer    = static_cast<int16_t>(uSteer);
    command.speed    = static_cast<int16_t>(uSpeed);
    command.checksum = static_cast<uint16_t>(command.start ^ command.steer ^ command.speed);

    // Write to Serial
    _port.write(reinterpret_cast<uint8_t*>(&command), sizeof(SerialCommand));
}

void Hoverboard::receive() {
    // Check if new data is available
    while (_port.available()) {

        incomingByte = _port.read();
        // Construct the start frame from previous and current byte
        bufStartFrame = (static_cast<uint16_t>(incomingByte) << 8) | incomingBytePrev;

        // State Machine for protocol
        if (bufStartFrame == START_FRAME) {
            // New Frame found, reset pointer
            pData = reinterpret_cast<byte*>(&newFeedback);
            *pData++ = incomingBytePrev;
            *pData++ = incomingByte;
            idx = 2; // 2 Bytes found already (Start Frame)
        }
        else if (idx >= 2 && idx < sizeof(SerialFeedback)) {
            // Collect data
            *pData++ = incomingByte;
            idx++;
        }

        // Compare checksums when frame is full
        if (idx == sizeof(SerialFeedback)) {
            auto calculatedChecksum = static_cast<uint16_t>(
                newFeedback.start ^ newFeedback.cmd1 ^ newFeedback.cmd2 ^
                newFeedback.speedR_meas ^ newFeedback.speedL_meas ^
                newFeedback.batVoltage ^ newFeedback.boardTemp ^ newFeedback.cmdLed);

            if (newFeedback.start == START_FRAME && calculatedChecksum == newFeedback.checksum) {
                // Valid data received -> copy to main feedback struct
                memcpy(&feedback, &newFeedback, sizeof(SerialFeedback));
            } else {
                // Checksum Error handling (optional)
            }
            idx = 0; // Reset for next loop-entry
        }
        incomingBytePrev = incomingByte;
    }//while()
}

float Hoverboard::getBatteryVoltage() const {
    return static_cast<float>(feedback.batVoltage) / 100.0f;
}

int16_t Hoverboard::getSpeedR() const {
    return feedback.speedR_meas;
}