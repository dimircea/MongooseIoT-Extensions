# DHT11/21/22 JavaScript Support for Mongoose-IoT Firmware Running on ESP8266 Modules

This extension allows to read DHT11/21/22 sensors by using JavaScript code, on an ESP8266 board running the Mongoose-IoT javaScript enabled Firmware.

## JavaScript Usage Example

To read a DHT11 sensor connected on GPIO5 of an Amica NodeMCU v2 ESP8266 based board, use the following code:
```
Dht.read( Dht.TypeEL.DHT11, 5);
```
It returns a JSON object with the following format:
```
{"humidity":33,"temperature":22,"type":"DHT11"}
```

The `Dht.TypeEL` enumeration contains the following literals: `DHT11`, `DHT21`, `DHT22`. Make sure that you are using the right one for your sensor, otherwise you'll get wrong readings.

The last parameter of the `read` method represents the GPIO pin number and NOT the pin number marked on the board. In our example, 5 means that we use the GPIO5 pin, as shown in  may also want to chech the following image showing the GPIO pins mapping for the Amica NodeMCU v2 board.


![GPIO pins mapping of an Amica NodeMCU v2 board](docs/img/Amica_NodeMCU_v2_pins.png?raw=true "Amica NodeMCU v2 Pins Mapping").

## Adding the DHTxx Code to Mongoose-IoT Firmware

The `src` folder contains the needed files. Each file contains notes and comments about where should be copied or where its content must be added to an already existing Mongoose-IoT Firmware source file. 

## Build the Mongoose-IoT Firmware

Check our [web-engineering.info tutorial](http://web-engineering.info/node/65) which containis complete information about how to build the Mongoose-IoT Firmware and use the [Mongoose-IoT Flashing Tool](https://github.com/cesanta/mongoose-flashing-tool) to upload it to an ESP8266 module.
