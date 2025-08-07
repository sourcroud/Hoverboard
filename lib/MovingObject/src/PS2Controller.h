//
// Created by sourc on 06.08.2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "PS2X_lib.h"

class PS2Controller {
private:
    PS2X ps2x;
    int16_t speed;
    int16_t steer;
public:
    void init(int clock, int command, int attention, int data, bool pressures, bool rumble);
    void update();
    int16_t getSpeed() const;
    int16_t getSteer() const;

    PS2Controller();
};



#endif //CONTROLLER_H
