//
// Created by sourc on 06.08.2025.
//

#ifndef HOVERBOARD_H
#define HOVERBOARD_H

#include "PS2Controller.h"
#include "stdint.h"

class Hoverboard {
public:
    void sendCommand( int16_t speed, int16_t steer );
};



#endif //HOVERBOARD_H
