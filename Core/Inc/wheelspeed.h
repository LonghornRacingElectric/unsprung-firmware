#ifndef UNSPRUNG_FIRMWARE_WHEELSPEED_H
#define UNSPRUNG_FIRMWARE_WHEELSPEED_H
#include "spi.h"

#define BURST_MODE_ADDR 0x1E
#define SINGLE_MODE_ADDR 0x3E
#define WAKEUP_MODE_ADDR 0x2E
#define READ_VAL_ADDR 0x4E
#define STOP_READ_ADDR 0x80
#define CONVERSION_FACTOR 0.00714f

typedef struct WheelMagnetValues { //converted to uT
    float fieldX;
    float fieldY;
    float fieldZ;
} WheelMagnetValues;

void wheelspeed_init(SPI_HandleTypeDef* hspi_init);
void wheelspeed_send_receive(uint8_t addr, uint8_t* received, size_t recv_size);
int wheelspeed_start();
int wheelspeed_stop();
int wheelspeed_reset();
[[maybe_unused]] int wheelspeed_calculate(WheelMagnetValues* values);
void wheelspeed_periodic(WheelMagnetValues* values);

#endif //UNSPRUNG_FIRMWARE_WHEELSPEED_H

