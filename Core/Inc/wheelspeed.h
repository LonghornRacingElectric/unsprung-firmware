#ifndef UNSPRUNG_FIRMWARE_WHEELSPEED_H
#define UNSPRUNG_FIRMWARE_WHEELSPEED_H
#include "spi.h"
#include "vcu.h"

#define BURST_MODE_ADDR 0x10
#define SINGLE_MODE_ADDR 0x30
#define WAKEUP_MODE_ADDR 0x20
#define READ_VAL_ADDR 0x40
#define STOP_READ_ADDR 0x80
#define FRONT_ADDR_BITS 0x04
#define REAR_ADDR_BITS 0x08
#define CONVERSION_FACTOR 0.0025f
#define FILTER_TIME_CONSTANT 0.006f

typedef struct WheelMagnetValues { //converted to mT
    float field;
} WheelMagnetValues;

void wheelspeed_init(SPI_HandleTypeDef *hspi_init, int location);
void wheelspeed_send_receive(uint8_t addr, uint8_t* received1, uint8_t* received2, size_t recv_size);
int wheelspeed_start();
int wheelspeed_stop();
int wheelspeed_reset();
[[maybe_unused]] int wheelspeed_calculate(WheelMagnetValues* values);
float wheelspeed_periodic(float delta_time);

#endif //UNSPRUNG_FIRMWARE_WHEELSPEED_H

