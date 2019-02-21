//#define DEBUG_V  
#include <Wire.h>  //  I2C Library
//#include <DebugUtils.h>
#include "MS561101BA.h"  // Library for the Sensor

MS561101BA baro = MS561101BA();  // Initialize the Sensor
/* The setup() function is called when a sketch starts. It is used to initialize variables, pin   modes, start using libraries, etc. This function will only run once, after each power up or reset of the Arduino board  */

void setup() 
{
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  baro.init(MS561101BA_ADDR_CSB_LOW);   // Suppose that the CSB pin is connected to GND.
}
/* The loop() function is called when the code is to be executed repeated or multiple times. After the specific number of executions, it will terminate itself. */
void loop()
{
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
}
