//
// Created by sourc on 06.08.2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "PS2X_lib.h"
#include "config.h"

class PS2Controller {
private:
    PS2X ps2x;
    int16_t speed;
    int16_t steer;
    bool isInitialized;
public:
    void init();
    void update();
    int16_t getSpeed() const;
    int16_t getSteer() const;
    bool getInitStatus() const;
    bool isConnected() const;
    PS2Controller();
};



#endif //CONTROLLER_H
