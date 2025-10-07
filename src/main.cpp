#include <Arduino.h>

#include "iomasks.h"

#include "PS2Controller.h"
#include "Hoverboard.h"

PS2Controller dualshock;
Hoverboard movingObject;

void setup() {
    Serial.begin(9600);
    dualshock.init(ps2clock, ps2command, ps2attention, ps2data, true, true);
}

void loop() {
    dualshock.update();
    movingObject.sendCommand(dualshock.getSpeed(), dualshock.getSteer());
    delay(20);
}