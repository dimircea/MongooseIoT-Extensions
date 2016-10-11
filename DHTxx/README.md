# DHT11/21/22 Mongoose-IoT Firmware Extension for ESP8266 based Modules
This extension empowers the ESP8266 Mongoose-IoT firmware with support for DHT11/21/22 sensors.

## JavaScript Usage Example
To read a DHT1 sensor connected on GPIO5 of an Amica NodeMCU v2 ESP8266 based board use the following code:
```
Dht.read(Dht.TypeEL.DHT1, 5);
```
It returns a JSON object with the following format:
```
{"humidity":33,"temperature":22,"type":"DHT11"}
```
The `Dht.TypeEL` enumeration contains the following literals: `DHT11`, `DHT21`, `DHT22`. Make sure that you are using the right one for your sensor otherwise you'll get incorrect readings.

The last parameter of the `read` method represents the GPIO pin number and NOT the pin number marked on the board. 
You may also want to chech the ![GPIO pins mapping of the Amica NodeMCU v2 board](https://github.com/dimircea/MongooseIoT-Extensions/branch/path/to/img.png).


**NOTE:** a complete tutorial containing informations about how to build the firmware and use the Mongoose-IoT Flashing tool for being able to upload the firmware to an ESP8266 module 
is available on our [web-engineering.info portal](http://web-engineering.info/node/65).
