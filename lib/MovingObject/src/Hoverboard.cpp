//
// Created by sourc on 06.08.2025.
//


//#include <HardwareSerial.h>
#include "Hoverboard.h"

Hoverboard::Hoverboard()
    :hoverSerial(softwareSerial_RX, softwareSerial_TX)
{
}
void Hoverboard::begin()
{
    hoverSerial.begin(HOVER_SERIAL_BAUD);
}

void Hoverboard::sendCommand( const int16_t uSpeed, const int16_t uSteer ) {
    // Create command
    command.start    = static_cast<uint16_t>(START_FRAME);
    command.steer    = static_cast<int16_t>(uSteer);
    command.speed    = static_cast<int16_t>(uSpeed);
    command.checksum = static_cast<uint16_t>(command.start ^ command.steer ^ command.speed);

    // Write to Serial
    hoverSerial.write(reinterpret_cast<uint8_t*>(&command), sizeof(SerialCommand));

}

void Hoverboard::receive() {
    // Check if new data is available
    if (hoverSerial.available()) {
        incomingByte = hoverSerial.read();
        // Construct the start frame from previous and current byte
        bufStartFrame = (static_cast<uint16_t>(incomingByte) << 8) | incomingBytePrev;
    } else {
        return;
    }

    // State Machine für das Protokoll
    if (bufStartFrame == START_FRAME) {
        // Neuer Frame erkannt, Reset Pointer
        pData = reinterpret_cast<byte*>(&newFeedback);
        *pData++ = incomingBytePrev;
        *pData++ = incomingByte;
        idx = 2; // Wir haben schon 2 Bytes (Start Frame)
    }
    else if (idx >= 2 && idx < sizeof(SerialFeedback)) {
        // Daten sammeln
        *pData++ = incomingByte;
        idx++;
    }

    // Wenn Frame voll ist, Checksumme prüfen
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
        idx = 0; // Reset für nächsten Durchlauf
    }

    incomingBytePrev = incomingByte;
}

float Hoverboard::getBatteryVoltage() const {
    // Rückgabewert ist meistens in ADC-Werten oder 100*Volt,
    // das hängt von der Firmware-Einstellung ab.
    // Oft ist es Volt * 100.
    return static_cast<float>(feedback.batVoltage) / 100.0f;
}

int16_t Hoverboard::getSpeedR() const {
    return feedback.speedR_meas;
}