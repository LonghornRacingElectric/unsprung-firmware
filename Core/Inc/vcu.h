#ifndef UNSPRUNG_FIRMWARE_VCU_H
#define UNSPRUNG_FIRMWARE_VCU_H

#include "imu.h"

#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define BACK_RIGHT 2
#define BACK_LEFT 3

void vcu_init(int loc);
void vcu_periodic(float magnetValue, xyz* imu);

#endif //UNSPRUNG_FIRMWARE_VCU_H
