#include "wheelspeed.h"
#include "LowPassFilter.h"

static SPI_HandleTypeDef* hspi;
static LowPassFilter filter(FILTER_TIME_CONSTANT);
static uint8_t dataBits;


void wheelspeed_init(SPI_HandleTypeDef *hspi_init, int location) {
  hspi = hspi_init;
  if(location == FRONT_LEFT || location == FRONT_RIGHT){
    dataBits = FRONT_ADDR_BITS;
  }
  else {
    dataBits = REAR_ADDR_BITS;
  }
  filter.reset();
  wheelspeed_start();
}

static int wheelspeed_errorhandler(uint8_t status1, uint8_t status2) {
  if ((status1 == 0xFF) && (status2 == 0xFF)) {
    // not updated error
    return 1;
  }
  if((status1 & 0x08) && (status2 & 0x08)){
    // This flag is set in case a communication error is detected. It can be that a wrong command is set (or too
    // early), or a command which was not allowed on a specific operating mode.
    return 1;
  }
  return 0;
}

void wheelspeed_send_receive(uint8_t addr, uint8_t* received1, uint8_t* received2, size_t recv_size) {
  uint8_t buffer[1] = {addr};
  HAL_GPIO_WritePin(SPI_CS_WS1_GPIO_Port, SPI_CS_WS1_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, buffer, 1, 100);
  HAL_SPI_Receive(&hspi1, received1, recv_size , 100);
  HAL_GPIO_WritePin(SPI_CS_WS1_GPIO_Port, SPI_CS_WS1_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(SPI_CS_WS2_GPIO_Port, SPI_CS_WS2_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, buffer, 1, 100);
  HAL_SPI_Receive(&hspi1, received2, recv_size , 100);
  HAL_GPIO_WritePin(SPI_CS_WS2_GPIO_Port, SPI_CS_WS2_Pin, GPIO_PIN_SET);
}

int wheelspeed_start() {
  uint8_t whsResult1[1] = {0xFF};
  uint8_t whsResult2[1] = {0xFF};
  wheelspeed_send_receive(BURST_MODE_ADDR | dataBits, whsResult1, whsResult2, 1);
  wheelspeed_send_receive(BURST_MODE_ADDR | dataBits, whsResult1, whsResult2, 1);
  wheelspeed_send_receive(BURST_MODE_ADDR | dataBits, whsResult1, whsResult2, 1);
  return wheelspeed_errorhandler(whsResult1[0], whsResult2[0]);
}

int wheelspeed_stop() {
  uint8_t status1[1] = {0xFF};
  uint8_t status2[1] = {0xFF};
  wheelspeed_send_receive(STOP_READ_ADDR, status1, status2, 1);
  return wheelspeed_errorhandler(status1[0], status2[0]);
}

int wheelspeed_reset() {
  int error = wheelspeed_stop();
  error += wheelspeed_start();
  filter.reset();
  return error;
}

float wheelspeed_periodic(float delta_time) {
  uint8_t results1[8] = {0};
  results1[0] = 0xFF;
  uint8_t results2[8] = {0};
  results2[0] = 0xFF;
  wheelspeed_send_receive(READ_VAL_ADDR | dataBits, results1, results2, 4);

  uint8_t status1 = results1[0];
  auto field1 = (int16_t) (results1[1] << 8 | results1[2]);

  uint8_t status2 = results2[0];
  auto field2 = (int16_t) (results2[1] << 8 | results2[2]);

  float fieldAverage = static_cast<float>(field1 + field2) * CONVERSION_FACTOR / 2.0f;

  uint8_t crc1 = results1[3]; // Maybe something fun to ruin someone's life later, but i don't rly care rn
  uint8_t crc2 = results2[3]; // Maybe something fun to ruin someone's life later, but i don't rly care rn

  if(wheelspeed_errorhandler(status1, status2)){
//    wheelspeed_reset();
  }
  if((status1 & 0x01) && (status2 & 0x01)){
    // This flag is set to 1 to indicate that new data is ready (not yet read), or when it is the first time that this data
    // is being read. This flag is updated after the measurement is done.
    filter.add(fieldAverage, delta_time);
  }
  return filter.get();
}
