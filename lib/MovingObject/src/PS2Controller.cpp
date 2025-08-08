//
// Created by sourc on 06.08.2025.
//

#include "PS2Controller.h"

PS2Controller::PS2Controller()
    :ps2x()
{
    speed = 0;
    steer = 0;
}

void PS2Controller::init(int clock, int command, int attention, int data, bool pressures, bool rumble) {
    int error = 0;
    byte type = 0;
    byte vibrate = 0;
    error = ps2x.config_gamepad(clock, command, attention, data, pressures, rumble);   //GamePad(clock, command, attention, data, Pressures?, Rumble?)

    if(error == 0){
        Serial.println("Found Controller, configured successful");
        Serial.println("Go to www.billporter.info for updates and to report bugs.");
    }

    else if(error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if(error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if(error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

    type = ps2x.readType();
    switch(type) {
        case 0:
            Serial.println("Unknown Controller type");
        break;
        case 1:
            Serial.println("DualShock Controller Found");
        break;
        case 2:
            Serial.println("GuitarHero Controller Found");
        break;
    }
}


void PS2Controller::update() {

    ps2x.read_gamepad();
    int x = ps2x.Analog(PSS_LX); // Left stick X-Axis
    int y = ps2x.Analog(PSS_LY); // Left stick Y-Axis

    // Normalize analog values (128 = full stop)
    steer = map( x, 0, 255, -1000, 1000 );
    speed = map( y, 255, 0, -1000, 1000);
}

int16_t PS2Controller::getSpeed() const {
    return speed;
}

int16_t PS2Controller::getSteer() const {
    return steer;
}







