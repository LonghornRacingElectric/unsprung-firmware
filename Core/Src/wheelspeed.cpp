#include "wheelspeed.h"


SPI_HandleTypeDef* hspi;


void wheelspeed_init(SPI_HandleTypeDef* hspi_init) {
  hspi = hspi_init;
  wheelspeed_start();
}

void wheelspeed_send_receive(uint8_t addr, uint8_t* received, size_t recv_size) {
  uint8_t buffer[1] = {addr};
  HAL_GPIO_WritePin(SPI_CS_WS1_GPIO_Port, SPI_CS_WS1_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, buffer, 1, 100);
  HAL_SPI_Receive(&hspi1, received, recv_size , 100);
  HAL_GPIO_WritePin(SPI_CS_WS1_GPIO_Port, SPI_CS_WS1_Pin, GPIO_PIN_SET);

}

int wheelspeed_start() {
  uint8_t status[1] = {0xFF};
  wheelspeed_send_receive(BURST_MODE_ADDR, status, 1);
  wheelspeed_send_receive(BURST_MODE_ADDR, status, 1);
  wheelspeed_send_receive(BURST_MODE_ADDR, status, 1);
  if (status[0] == 0xFF) {
    // not updated error
    return 1;
  }
  if(status[0] & 0x08){
    // This flag is set in case a communication error is detected. It can be that a wrong command is set (or too
    // early), or a command which was not allowed on a specific operating mode.
    return 1;
  }
  return 0;
}

int wheelspeed_stop() {
  uint8_t status[1] = {0xFF};
  wheelspeed_send_receive(STOP_READ_ADDR, status, 1);
  if (status[0] == 0xFF) {
    // not updated error
    return 1;
  }
  if(status[0] & 0x08){
    // This flag is set in case a communication error is detected. It can be that a wrong command is set (or too
    // early), or a command which was not allowed on a specific operating mode.
    return 1;
  }
  return 0;
}

int wheelspeed_reset() {
  int error = wheelspeed_stop();
  error += wheelspeed_start();
  return error;
}

void wheelspeed_periodic(WheelMagnetValues* values) {
  uint8_t results[8] = {0};
  results[0] = 0xFF;
  wheelspeed_send_receive(READ_VAL_ADDR, results, 8);

  uint8_t status = results[0];
  auto fieldX = (int16_t) (results[1] << 8 | results[2]);
  auto fieldY = (int16_t) (results[3] << 8 | results[4]);
  auto fieldZ = (int16_t) (results[5] << 8 | results[6]);
  uint8_t crc = results[7]; // Maybe something fun to ruin someone's life later, but i don't rly care rn

  if((status & 0x08) || (status == 0xFF)){
    // This flag is set in case a communication error is detected. It can be that a wrong command is set (or too
    // early), or a command which was not allowed on a specific operating mode.
    wheelspeed_reset();
    return;
  }
  if(status & 0x04){
//    If set, it indicates that the MSBit of the ADC (bit 18) is set. This situation should not occur, and could indicate
//    a failure in the analog front-end of the IC.
    wheelspeed_reset();
    return;
  }
  if(status & 0x01){
    // This flag is set to 1 to indicate that new data is ready (not yet read), or when it is the first time that this data
    // is being read. This flag is updated after the measurement is done.
    values->fieldX = fieldX * CONVERSION_FACTOR;
    values->fieldY = fieldY * CONVERSION_FACTOR;
    values->fieldZ = fieldZ * CONVERSION_FACTOR;
    return;
  }
}
