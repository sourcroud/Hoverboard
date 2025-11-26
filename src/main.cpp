#include <Arduino.h>

#include "iomasks.h"

#include "PS2Controller.h"
#include "Hoverboard.h"

PS2Controller dualshock;
Hoverboard movingObject;

void setup() {
    delay(1000);
    pinMode(softwareSerial_TX, OUTPUT);
    digitalWrite(softwareSerial_TX, HIGH);
    Serial.begin(9600);

    do {
        dualshock.init(ps2clock, ps2command, ps2attention, ps2data, false, false);
    } while ( !dualshock.getInitStatus() );
}



void loop() {
    dualshock.update();
    movingObject.sendCommand(dualshock.getSpeed(), dualshock.getSteer());
    printf("Speed: %d\nSteer: %d", dualshock.getSpeed(), dualshock.getSteer());
    //movingObject.sendCommand(100, 0);
    delay(20);
}