#ifndef UNSPRUNG_FIRMWARE_VCU_H
#define UNSPRUNG_FIRMWARE_VCU_H


typedef enum location {
    FRONT_LEFT,
    FRONT_RIGHT,
    REAR_LEFT,
    REAR_RIGHT
} location_t;


/**
 * Initialize CAN communication with vcu.
 */
void vcu_can_init();

/**
 * Send IMU accleration data over CAN. Precision is 0.01 m/s^2.
 * @param accel_x
 * @param accel_y
 * @param accel_z
 * @return error_code
 */
int vcu_send_imu_data(float accel_x, float accel_y, float accel_z);

/**
 * Send wheel speed data over CAN, namely displacement and speed. Precision is 0.01 rad, 0.01 m/s.
 * @param disp
 * @param speed
 * @return error_code
 */
int vcu_send_whs_data(float disp, float speed);

#endif //UNSPRUNG_FIRMWARE_VCU_H
