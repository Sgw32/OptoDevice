/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_MLX90614.h"
#include "MS5611.h"

MS5611 ms5611;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int analogPin0 = A0;
int analogPin1 = A1;
int analogPin2 = A2;
int analogPin3 = A3;
int val = 0;


struct Sensors {
  uint16_t val0 = 0;
  uint16_t val1 = 0;
  uint16_t val2 = 0;
  uint16_t val3 = 0;
  double mlxAT;
  double mlxOT;
  uint32_t realPressure;
  double realTemp;
} Sensors;

void setup() {
  Serial.begin(9600);

  Serial.println("Optodevice V1.0");  
  analogReference(INTERNAL);
  mlx.begin();  
  while(!ms5611.begin(MS5611_ULTRA_HIGH_RES))
  {
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    delay(500);
  }
}

void loop() {

  int i;
  for (i=0;i!=16;i++)
  {
    Sensors.mlxAT+=mlx.readAmbientTempC(); 
    Sensors.mlxOT+=mlx.readObjectTempC();
    Sensors.realPressure +=  ms5611.readPressure(true);
    Sensors.realTemp +=  ms5611.readTemperature(true);
    Sensors.val0 += analogRead(analogPin0);  // read the input pin
    Sensors.val1 += analogRead(analogPin1);  // read the input pin
    Sensors.val2 += analogRead(analogPin2);  // read the input pin
    Sensors.val3 += analogRead(analogPin3);  // read the input pin
  }
  Sensors.mlxAT/=16;
  Sensors.mlxOT/=16;
  Sensors.realPressure/=16;
  Sensors.realTemp/=16;
  Sensors.val0/=16;
  Sensors.val1/=16;
  Sensors.val2/=16;
  Sensors.val3/=16;
  
  Serial.print(Sensors.mlxAT); 
  Serial.print("\t"); Serial.print(Sensors.mlxOT);
  Serial.print("\t"); Serial.print(Sensors.realPressure);
  Serial.print("\t"); Serial.print(Sensors.realTemp);
  Serial.print("\t"); Serial.print(Sensors.val0);
  Serial.print("\t"); Serial.print(Sensors.val1);
  Serial.print("\t"); Serial.print(Sensors.val2);
  Serial.print("\t"); Serial.print(Sensors.val3);
  Serial.println();
  //delay(500);
}
