#ifndef UNSPRUNG_FIRMWARE_VCU_H
#define UNSPRUNG_FIRMWARE_VCU_H

#include "wheelspeed.h"
#include "imu.h"

typedef enum location {
    FRONT_LEFT,
    FRONT_RIGHT,
    BACK_LEFT,
    BACK_RIGHT
} Location;

void vcu_init(Location loc);
void vcu_periodic(WheelMagnetValues* values, xyz* imu);

#endif //UNSPRUNG_FIRMWARE_VCU_H
