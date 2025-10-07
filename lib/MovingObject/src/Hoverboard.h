//
// Created by sourc on 06.08.2025.
//

#ifndef HOVERBOARD_H
#define HOVERBOARD_H

#include "iomasks.h"
#include "stdint.h"
#include "SoftwareSerial.h"

class Hoverboard {
private:
    SoftwareSerial hoverSerial;
public:
    void sendCommand( int16_t speed, int16_t steer );
    Hoverboard();
};



#endif //HOVERBOARD_H
