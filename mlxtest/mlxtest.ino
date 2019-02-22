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
#include "MS561101BA.h"  // Library for the Sensor

MS561101BA baro = MS561101BA();  // Initialize the Sensor

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int analogPin0 = A0;
int analogPin1 = A1;
int analogPin2 = A2;
int analogPin3 = A3;
int val = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  
  analogReference(INTERNAL);
  mlx.begin();  
  baro.init(MS561101BA_ADDR_CSB_LOW);   // Suppose that the CSB pin is connected to GND.
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.println();

  val = analogRead(analogPin0);  // read the input pin
  Serial.println(val);          // debug value
  val = analogRead(analogPin1);  // read the input pin
  Serial.println(val);          // debug value
  val = analogRead(analogPin2);  // read the input pin
  Serial.println(val);          // debug value
  val = analogRead(analogPin3);  // read the input pin
  Serial.println(val);          // debug value

  float temperature = NULL, pression = NULL;   // Initialize Temperature and Pression
  Serial.print("temp: ");  // Print Temperature        
  while (temperature == NULL)      // When temperature is NULL (No values)
  {
    temperature = baro.getTemperature(MS561101BA_OSR_4096);   // Get Temperature Values
  }
  Serial.print(temperature);    //  Print Temperature values
  Serial.print(" degC pres: ");  // Print values in degree C
  while (pression == NULL)   // When Pressure is NULL (No values)
  {
    pression = baro.getPressure(MS561101BA_OSR_4096);  // Get Pressure Values
  }
  Serial.print(pression);   // Print Pressure Values
  Serial.println(" mbar");  // Print values in mbar
  delay(500);
}
