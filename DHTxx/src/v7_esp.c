// NOTE: add the following code in the fw/platforms/esp8266/user/v7_esp_features.h file, as part of the directive: 
//       #ifdef MG_ENABLE_JS  
//       ... 
//       #endif
//
// Pay attention to the notes from init_v7 method! 

#include "fw/platforms/esp8266/user/dht.h"

#ifdef V7_ESP_ENABLE__DHT
static enum v7_err DHT_read(struct v7 *v7, v7_val_t *result) {
  v7_val_t sensorTypeArg = v7_arg(v7, 0);
  v7_val_t pinArg = v7_arg(v7, 1);
  
  if (!v7_is_number(sensorTypeArg) || 
	  (v7_get_double(v7, sensorTypeArg) != 1 
	   && v7_get_double(v7, sensorTypeArg) != 2 
	   && v7_get_double(v7, sensorTypeArg) != 3)) return v7_throwf(v7, "Error", 
	"Required sensor type (param 1) - Dht.TypeEL.DHTxx (e.g., Dht.TypeEL.DHT22).");
  if (!v7_is_number(pinArg)) return v7_throwf(v7, "Error", 
	"Required GPIO number (param 2) - a positive integer (e.g., 5 for GPIO5).");

  uint8_t pin = v7_get_int(v7, pinArg);
  uint8_t sType = v7_get_int(v7, sensorTypeArg);
  double temperature = 0.0;
  double humidity = 0.0;
  const char* sTypeName = (sType == 1 ? "DHT11" : (sType == 2 ? "DHT21" : "DHT22"));
  if (!dhtRead(sType, pin, &temperature, &humidity)) {
    *result = v7_mk_null();
    return V7_OK;
  }
  *result = v7_mk_object(v7);
  v7_set(v7, *result, "type", 4, v7_mk_string(v7, sTypeName, 5, 1));
  v7_set(v7, *result, "temperature", 11, v7_mk_number(v7, temperature));
  v7_set(v7, *result, "humidity", 8, v7_mk_number(v7, humidity));
  return V7_OK;
}
#endif /* V7_ESP_ENABLE__DHT */


void init_v7(void *stack_base) {
  //NOTE: the following lines of code must be added at the end of this (init_v7) method, 
  //      while the rest of the code already existing as part of the init_v7 method 
  //      must NOT be changed, otherwise the code may not compile or not behave correctly!
  
  #ifdef V7_ESP_ENABLE__DHT
    v7_val_t dht = v7_mk_object(v7);
    v7_val_t typeEL = v7_mk_object(v7);
    // create the Dht object accessible in JS code
    v7_set(v7, v7_get_global(v7), "Dht", 3, dht);
    // add the read method to the DHT JS object
    v7_set_method(v7, dht, "read", DHT_read);
    // define the Dht.TypeEL enumeration property
    v7_def(v7, dht, "TypeEL", 6, (V7_DESC_WRITABLE(0) | V7_DESC_ENUMERABLE(1)), typeEL);
    // create the Dht.TypeEL.DHT11 enumeration literal - {enumerable: true, writable: false}
    v7_def(v7, typeEL, "DHT11", 5, (V7_DESC_WRITABLE(0) | V7_DESC_ENUMERABLE(1)), v7_mk_number(v7, 1));
    // create the Dht.TypeEL.DHT21 enumeration literal - {enumerable: true, writable: false}
    v7_def(v7, typeEL, "DHT21", 5, (V7_DESC_WRITABLE(0) | V7_DESC_ENUMERABLE(1)), v7_mk_number(v7, 2));
    // create the Dht.TypeEL.DHT22 enumeration literal - {enumerable: true, writable: false}
    v7_def(v7, typeEL, "DHT22", 5, (V7_DESC_WRITABLE(0) | V7_DESC_ENUMERABLE(1)), v7_mk_number(v7, 3));
  #endif /* V7_ESP_ENABLE__DHT */
}