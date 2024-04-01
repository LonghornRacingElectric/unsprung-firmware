#include "vcu.h"
#include "angel_can.h"

CanOutbox outbox_magnet;
CanOutbox outbox_imu;
Location this_loc;

void vcu_init(const Location loc){
  this_loc = loc;
  if(loc == FRONT_LEFT) {
    can_addOutbox(UNSFL_VCU_MAGNET, 0.003f, &outbox_magnet);
    can_addOutbox(UNSFL_VCU_IMU, 0.003f, &outbox_imu);
  }
  else if(loc == FRONT_RIGHT) {
    can_addOutbox(UNSFR_VCU_MAGNET, 0.003f, &outbox_magnet);
    can_addOutbox(UNSFR_VCU_IMU, 0.003f, &outbox_imu);
  }
  else if(loc == BACK_RIGHT) {
    can_addOutbox(UNSBR_VCU_MAGNET, 0.003f, &outbox_magnet);
    can_addOutbox(UNSBR_VCU_IMU, 0.003f, &outbox_imu);
  }
  else if(loc == BACK_LEFT) {
    can_addOutbox(UNSBL_VCU_MAGNET, 0.003f, &outbox_magnet);
    can_addOutbox(UNSBL_VCU_IMU, 0.003f, &outbox_imu);
  }
}

static void vcu_sendMagnets(WheelMagnetValues* values){
  can_writeFloat(int16_t, &outbox_magnet, 0, 0, 0.00714f); // Write null values as placeholders
  if(this_loc == FRONT_LEFT || this_loc == FRONT_RIGHT){ // use X or Y value
    can_writeFloat(int16_t, &outbox_magnet, 0, values->fieldX, 0.00714f);
  }
  else if(this_loc == BACK_LEFT || this_loc == BACK_RIGHT){ // use Z value
    can_writeFloat(int16_t, &outbox_magnet, 0, values->fieldZ, 0.00714f);
  }
  outbox_magnet.dlc = 2;
  outbox_magnet.isRecent = true;
}

static void vcu_sendIMU(xyz* imu_accel){
  can_writeFloat(int16_t, &outbox_imu, 0, imu_accel->x, 0.01f);
  can_writeFloat(int16_t, &outbox_imu, 2, imu_accel->y, 0.01f);
  can_writeFloat(int16_t, &outbox_imu, 4, imu_accel->z, 0.01f);
  outbox_imu.dlc = 6;
  outbox_imu.isRecent = true;
}

void vcu_periodic(WheelMagnetValues* values, xyz* imu){
  vcu_sendMagnets(values);
  vcu_sendIMU(imu);
}

