// NOTE: copy this file to: fw/platforms/esp8266/user folder.
#ifndef DHT_LIBRARY
#define DHT_LIBRARY

#include "v7_esp_features.h"

/* DHT 11/21/22 library */
#ifdef V7_ESP_ENABLE__DHT
/**
 * Read temperature and humidity data. 
 * @param sensorType
 *	the DHT sensor type (1 = DHT11, 2 = DHT21, 3 = DHT22)
 * @param pin 
 *	the GPIO pin number (on the board is marked as GPIOx, so x is the pin number)
 * @param temperature
 *	the sensor read temperature value (pointer to)
 * @param humidity
 *	the sensor read humidity value (pointer to)
 * @return true (1) when checksum data verifies, false (0) otherwise.
 */
bool dhtRead(uint8_t sensorType, uint8_t pin, double* temperature, double* humidity);
#endif

#endif /* DHT_LIBRARY */
