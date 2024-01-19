#include "vcu.h"
#include "angel_can_ids.h"
#include "angel_can.h"
#include <algorithm>

static CanOutbox whs_fr_inbox;
static CanOutbox whs_fl_inbox;
static CanOutbox whs_br_inbox;
static CanOutbox whs_bl_inbox;
static CanOutbox imu_fr_inbox;
static CanOutbox imu_fl_inbox;
static CanOutbox imu_br_inbox;
static CanOutbox imu_bl_inbox;

location_t location;

void vcu_can_init(location_t loc) {
    switch(loc) {
        case FRONT_LEFT:
            can_addOutbox(WHS_VCU_DISP_1, 0.250, &whs_fl_inbox);
            can_addOutbox(WHS_VCU_IMU_1, 0.250, &imu_fl_inbox);
            break;
        case FRONT_RIGHT:
            can_addOutbox(WHS_VCU_DISP_2, 0.250, &whs_fr_inbox);
            can_addOutbox(WHS_VCU_IMU_2, 0.250, &imu_fr_inbox);
            break;
        case REAR_LEFT:
            can_addOutbox(WHS_VCU_DISP_3, 0.250, &whs_bl_inbox);
            can_addOutbox(WHS_VCU_IMU_3, 0.250, &imu_bl_inbox);
            break;
        case REAR_RIGHT:
            can_addOutbox(WHS_VCU_DISP_4, 0.250, &whs_br_inbox);
            can_addOutbox(WHS_VCU_IMU_4, 0.250, &imu_br_inbox);
            break;
        default:
            break;
    }
    location = loc;
}

int vcu_send_imu_data(float accel_x, float accel_y, float accel_z){
    uint8_t data[8];
    can_writeBytes(data, 0, 1, (int16_t) (accel_x * 100));
    can_writeBytes(data, 2, 3, (int16_t) (accel_y * 100));
    can_writeBytes(data, 4, 5, (int16_t) (accel_z * 100));
    switch(location){
        case FRONT_LEFT:
            imu_fl_inbox.isRecent = true;
            std::copy(data, data + 6, imu_fl_inbox.data);
            break;
        case FRONT_RIGHT:
            imu_fr_inbox.isRecent = true;
            std::copy(data, data + 6, imu_fr_inbox.data);
            break;
        case REAR_LEFT:
            imu_bl_inbox.isRecent = true;
            std::copy(data, data + 6, imu_bl_inbox.data);
            break;
        case REAR_RIGHT:
            imu_br_inbox.isRecent = true;
            std::copy(data, data + 6, imu_br_inbox.data);
            break;
        default:
            return 1;
    }
    return 0;
}

int vcu_send_whs_data(float disp, float speed){
    uint8_t data[8];
    can_writeBytes(data, 0, 1, (int16_t) (disp * 100));
    can_writeBytes(data, 2, 3, (int16_t) (speed * 100));
    switch(location){
        case FRONT_LEFT:
            whs_fl_inbox.isRecent = true;
            std::copy(data, data + 4, whs_fl_inbox.data);
            break;
        case FRONT_RIGHT:
            whs_fr_inbox.isRecent = true;
            std::copy(data, data + 4, whs_fr_inbox.data);
            break;
        case REAR_LEFT:
            whs_bl_inbox.isRecent = true;
            std::copy(data, data + 4, whs_bl_inbox.data);
            break;
        case REAR_RIGHT:
            whs_br_inbox.isRecent = true;
            std::copy(data, data + 4, whs_br_inbox.data);
            break;
        default:
            return 1;
    }
    return 0;
}
