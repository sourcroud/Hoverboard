#include <Arduino.h>

#include "config.h"
#include "PS2Controller.h"
#include "Hoverboard.h"

PS2Controller dualshock;
Hoverboard hoverboard(Serial1);
static unsigned long lastCommand = 0;

void setup() {
    delay(3000);
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("...");
    Serial.println("Hoverboard Serial v1.0");
    Serial1.begin(HOVER_SERIAL_BAUD);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Initiliazing Controller...");
    while (!dualshock.getInitStatus())
    {
        dualshock.init();
        delay(1000);
    }
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    dualshock.update();
    hoverboard.receive();
    const int16_t speed = dualshock.getSpeed();
    const int16_t steer = dualshock.getSteer();
    if( millis() - lastCommand > TIME_SEND_COMMAND ) {
        lastCommand = millis();
        hoverboard.sendCommand(speed, steer);
    }
}