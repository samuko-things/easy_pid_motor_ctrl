
// i2c master uno
#include <Wire.h>

#include "i2c_client_api.h"
int slaveAddress = 4;
I2CAPI motorApi(slaveAddress);


void setup()
{
  Wire.begin();                 
  Serial.begin(115200);
}

void loop()
{
  float val = motorApi.get("posA");
  //bool val = motorApi.send("pwmA", 120);
  Serial.println(val,4);
  Serial.println();
  
  delay(20);
}
