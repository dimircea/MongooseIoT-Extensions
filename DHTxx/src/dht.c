#include <osapi.h>
#include <util.h>
#include "v7/v7.h"
#include "common/platforms/esp8266/esp_missing_includes.h"
#include "fw/platforms/esp8266/user/v7_esp_features.h"
#include "fw/platforms/esp8266/user/esp_gpio.h"

// NOTE: copy this file to: fw/platforms/esp8266/user folder.
#ifdef V7_ESP_ENABLE__DHT

static uint16_t waitLHCycle(uint8_t pin, uint32_t* maxCycles) {
  //expecting to start with high, waiting for low
  uint32_t highStart = *maxCycles;
  while((*maxCycles)-- > 0 && read_gpio_pin(pin) == 1) ;
  uint32_t highLength = highStart - *maxCycles;
  //now it's low, waiting for high
  uint32_t lowStart = *maxCycles;
  while((*maxCycles)-- > 0 && read_gpio_pin(pin) == 0) ;
  uint32_t lowLength = lowStart - *maxCycles;
  return highLength > lowLength;
};

static uint8_t dhtReadByte(uint8_t pin, uint32_t* maxCycles) {
  uint8_t result = 0, bits = 8;
  while(bits-- > 0) result = result << 1 | waitLHCycle(pin, maxCycles);
  return result;
};

bool dhtRead(uint8_t sensorType, uint8_t pin, double* temperature, double* humidity) {
  uint32_t maxCycles = 100000;
  uint8_t dataBytes[5] = {0}, i = 0;
  uint8_t checksum = 0;
  // Send start signal. See DHT datasheet for full signal diagram:
  // http://www.adafruit.com/datasheets/Digital%20humidity%20and%20temperature%20sensor%20AM2302.pdf
  mg_gpio_set_mode(pin, GPIO_MODE_OUTPUT, GPIO_PULL_FLOAT);
  set_gpio(pin, 1);
  os_delay_us(250 * 1000);
  set_gpio(pin, 0);
  os_delay_us(20 * 1000);
  
  set_gpio(pin, 1);
  os_delay_us(40);
  mg_gpio_set_mode(pin, GPIO_MODE_INOUT, GPIO_PULL_PULLUP);
  os_delay_us(10);

  waitLHCycle(pin, &maxCycles);
  waitLHCycle(pin, &maxCycles);
  if (maxCycles <= 0) return false;
  // read the 5 data bytes from the sensor
  for (i = 0; i < 5; i++) dataBytes[i] = dhtReadByte(pin, &maxCycles);
  // extract temperature and humidity data based on sensor type
  if (sensorType == 1) { //DHT11
	*humidity = dataBytes[0];
	*temperature = dataBytes[2];  
  } else if (sensorType == 2 || sensorType == 3) { // DHT21 and DHT22
	*humidity = (dataBytes[0] * 256 + dataBytes[1]) * 0.1;
	*temperature = (dataBytes[2] * 256 + dataBytes[3]) * 0.1;
  } else { // unknown sensor type
	*humidity = -9999;
	*temperature = -9999;  
  }
  // compute checksum
  for (i = 0; i < 4; i++) checksum += dataBytes[i];
  checksum &= 0xFF;
  return (checksum == dataBytes[4] 
	&& (sensorType == 1 || sensorType == 2 || sensorType == 3));
};
#endif /* V7_ESP_ENABLE__DHT */
