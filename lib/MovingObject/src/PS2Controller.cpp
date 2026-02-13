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
        Serial.println("Found Controller, configured successfully.");
    }

    else if(error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if(error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if(error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

    if( error == 0 ) {
        this->isInitialized = true;
        type = ps2x.readType();
        switch(type) {
            case 0:
                Serial.println("Unknown controller type.");
                break;
            case 1:
                Serial.println("DualShock-Controller found.");
                break;
            case 2:
                Serial.println("GuitarHero-Controller found.");
                break;
        }
        Serial.println("Go to www.billporter.info for updates and to report bugs.");
    } else this->isInitialized = false;
}


void PS2Controller::update() {

    ps2x.read_gamepad();
    // Deadmanshandle due to missing boolean return statement of PS2X::read_gamepad()
    if ( !ps2x.Button(PSB_L2) ) {
        speed = 0;
        steer = 0;
        return;
    }
    const int x = ps2x.Analog(PSS_LX); // Left stick X-Axis
    const int y = ps2x.Analog(PSS_LY); // Left stick Y-Axis

    // Normalize analog values (128 equals zero position)
    if( x > 138 ) {
        // Stick moved RIGHT
        steer = map( x, 138, 255, 0, 1000);
    } else if( x < 118 ) {
        // Stick moved LEFT
        steer = map( x, 118, 0, 0, -1000 );
    } else steer = 0;
    // Y-Axis inverted
    if( y > 138 ) {
        // Stick moved UP
        speed = map( y, 138, 255, 0, -1000);
    } else if ( y < 118 ) {
        // Stick moved DOWN
        speed = map( y, 118, 0, 0, 1000);
    } else speed = 0;
}

int16_t PS2Controller::getSpeed() const {
    return speed;
}

int16_t PS2Controller::getSteer() const {
    return steer;
}

bool PS2Controller::getInitStatus() const {
    return this->isInitialized;
}







