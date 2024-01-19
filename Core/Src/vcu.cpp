#include "vcu.h"
#include "angel_can_ids.h"
#include "angel_can.h"

static CanOutbox whs_fr_inbox;
static CanOutbox whs_fl_inbox;
static CanOutbox whs_br_inbox;
static CanOutbox whs_bl_inbox;

location_t location;

void vcu_can_init(location_t loc) {
    can_addOutbox(WHS_VCU_DISP_1, 250, &whs_fr_inbox);
    can_addOutbox(WHS_VCU_DISP_2, 250, &whs_fl_inbox);
    can_addOutbox(WHS_VCU_DISP_3, 250, &whs_br_inbox);
    can_addOutbox(WHS_VCU_DISP_4, 250, &whs_bl_inbox);

    location = loc;
}

static uint32_t get_location_imu(){
    switch(location){
        case FRONT_LEFT:
            return WHS_VCU_IMU_1;
        case FRONT_RIGHT:
            return WHS_VCU_IMU_2;
        case REAR_LEFT:
            return WHS_VCU_IMU_3;
        case REAR_RIGHT:
            return WHS_VCU_IMU_4;
        default:
            return INT32_MAX;
    }
}

static uint32_t get_location_whs(){
    switch(location){
        case FRONT_LEFT:
            return WHS_VCU_DISP_1;
        case FRONT_RIGHT:
            return WHS_VCU_DISP_2;
        case REAR_LEFT:
            return WHS_VCU_DISP_3;
        case REAR_RIGHT:
            return WHS_VCU_DISP_4;
        default:
            return INT32_MAX;
    }
}

int vcu_send_imu_data(float accel_x, float accel_y, float accel_z){
    uint8_t data[8];
    can_writeBytes(data, 0, 1, (int16_t) (accel_x * 100));
    can_writeBytes(data, 2, 3, (int16_t) (accel_y * 100));
    can_writeBytes(data, 4, 5, (int16_t) (accel_z * 100));
    return (int) can_send(get_location_imu(), 8, data);
}

int vcu_send_whs_data(float disp, float speed){
    uint8_t data[8];
    can_writeBytes(data, 0, 1, (int16_t) (disp * 100));
    can_writeBytes(data, 2, 3, (int16_t) (speed * 100));
    return (int) can_send(get_location_whs(), 8, data);
}
