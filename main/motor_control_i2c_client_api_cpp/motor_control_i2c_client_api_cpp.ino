
// i2c master uno
#include <Wire.h>
#include "motor_control_i2c_client.h"

///////// my sepcial delay function ///////////////
void delayMs(int ms) {
  for (int i = 0; i < ms; i += 1) {
    delayMicroseconds(1000);
  }
}
//////////////////////////////////////////////////


int MotorSlaveAddress = 4;
MotorI2cClient motorClient(MotorSlaveAddress);

bool isSuccessful;
float posA, posB; //motorA, motorB
float velA, velB; //motorA, motorB
float paramData;

//float pwmA, pwmB;  //motorA, motorB
//float targetA, targetB;  //motorA, motorB


unsigned long execPrevTime, execSampleTime = 10; // in ms (i.e 1000/execSampleTime in Hz)
bool toogle = true;

void setup()
{
  Wire.begin();                 
  Serial.begin(115200);

  delay(5000);

  isSuccessful = motorClient.sendParam("mode", 0);
  Serial.println(isSuccessful);

  delay(1000);

  isSuccessful = false;
 
  isSuccessful = motorClient.send("pwm", 0, 120);
  Serial.println(isSuccessful);
  
  delay(1000);

//  isSuccessful = motorClient.sendParam("mode", 1);
//  Serial.println(isSuccessful);

  execPrevTime = millis();
}


 
void loop()
{  
  
  if ((millis() - execPrevTime) >= execSampleTime) {
    /* CODE SHOULD GO IN HERE*/

    motorClient.get("vel", velA, velB); // get velocity data and store in velA and velB
    Serial.println(velB); 

//    motorClient.get("pos", posA, posB); // get position data and store in posA and posB
//    Serial.println(posB); 

//    Serial.println(motorClient.getParam("mode", paramData)); // get mode param data and store in paramData
    
    execPrevTime = millis();
  }

}
