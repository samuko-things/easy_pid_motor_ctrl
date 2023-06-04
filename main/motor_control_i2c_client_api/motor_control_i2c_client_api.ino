
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

const int A=0, B=1;
float angPosData[2]; //motorA, motorB
float angVelData[2]; //motorA, motorB
float pwmValue[2];  //motorA, motorB
float targetValue[2];  //motorA, motorB


unsigned long execPrevTime, execSampleTime = 10; // in ms (i.e 1000/execSampleTime in Hz)
bool toogle = true;

void setup()
{
  Wire.begin();                 
  Serial.begin(115200);

  delay(2000);

  isSuccessful = false;
  while (!isSuccessful){
    isSuccessful = motorClient.sendOne("mode", 0);
    Serial.println(isSuccessful);
  }

  delay(1000);

  isSuccessful = false;
  pwmValue[A] = -105;
  isSuccessful = motorClient.send("pwm", pwmValue);
  Serial.println(isSuccessful);
  
  delay(1000);

//  isSuccessful = motorClient.sendOne("mode", 1);
//  Serial.println(isSuccessful);

  execPrevTime = millis();
}


 
void loop()
{  
  
  if ((millis() - execPrevTime) >= execSampleTime) {
    /* CODE SHOULD GO IN HERE*/

    motorClient.get("vel", angVelData); // get
    Serial.println(angVelData[A]); // use

//    motorClient.get("pos", angPosData); // get
//    Serial.println(angPosData[A]); // use

//    Serial.println(motorClient.getOne("mode"));
    
    execPrevTime = millis();
  }

}












//void loop()
//{
//  
//  for (int pwmVal = -250; pwmVal <= 255; pwmVal += 5) {
//    pwmValue[A] = pwmVal; // update
//    isSuccessful = motorClient.send("pwm", pwmValue); // send
//    motorClient.get("vel", angVelData); // get
//    Serial.println(angVelData[A]); // use
//
////    isSuccessful = motorClient.send("pwm", pwmValue);
////    motorClient.get("pos", angPosData);
////    Serial.println(angPosData[A]);
//    delayMs(10);
//   }
//  for (int pwmVal = 255; pwmVal >= -255; pwmVal -= 5) {
//    pwmValue[A] = pwmVal; // update
//    isSuccessful = motorClient.send("pwm", pwmValue); // send
//    motorClient.get("vel", angVelData); // get
//    Serial.println(angVelData[A]); // use
//
////    isSuccessful = motorClient.send("pwm", pwmValue);
////    motorClient.get("pos", angPosData);
////    Serial.println(angPosData[A]);
//    delayMs(10);
//  }
//  
//  if ((millis() - execPrevTime) >= execSampleTime) {
//    /* CODE SHOULD GO IN HERE*/
//
//    if (toogle){
//      isSuccessful = motorClient.send("pwmA", 110);
//    Serial.println(isSuccessful);
//    toogle = false;
//    } else {
//      isSuccessful = motorClient.send("pwmA", -110);
//    Serial.println(isSuccessful);
//    toogle = true;
//    }
//    
//    execPrevTime = millis();
//  }
//}
