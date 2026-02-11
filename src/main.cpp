#include <Arduino.h>

#include "iomasks.h"
#include "PS2Controller.h"
#include "Hoverboard.h"

PS2Controller dualshock;
Hoverboard movingObject;
static unsigned long lastCommand = 0;

void setup() {
    delay(1000);
    Serial.begin(SERIAL_BAUD);
    Serial.println("Hoverboard Serial v1.0");

    movingObject.begin();
    pinMode(LED_BUILTIN, OUTPUT);

    do {
        dualshock.init(ps2clock, ps2command, ps2attention, ps2data, false, false);
    } while ( !dualshock.getInitStatus() );
    digitalWrite(LED_BUILTIN, HIGH);
}

void printSerial(const int16_t speed, const int16_t steer) {
    Serial.print("Spd: "); Serial.print(speed);
    Serial.print(" | Str: "); Serial.print(steer);
    Serial.print(" | Batt: "); Serial.print(movingObject.getBatteryVoltage());
    Serial.println(" V");
}

void loop() {
    dualshock.update();
    movingObject.receive();
    if( millis() - lastCommand > TIME_SEND ) {
        lastCommand = millis();
        const int16_t speed = dualshock.getSpeed();
        const int16_t steer = dualshock.getSteer();
        movingObject.sendCommand(speed, steer);
        printSerial(speed, steer);
    }
}