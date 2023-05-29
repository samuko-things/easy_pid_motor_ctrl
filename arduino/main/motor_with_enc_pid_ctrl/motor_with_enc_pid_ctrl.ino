
const int A=0;
const int B=1;

#include "motor_bridge_control.h"

#include "encoder_setup.h"

void testEncB() {
  long tickCountB = enc[B].tickCount;
  float frequencyB = enc[B].frequency;
  float angPosB = enc[B].getAbsAngPosDeg();
  float angVelB = enc[B].getAngVel();

  Serial.print("tickCount = ");
  Serial.print(tickCountB);
  Serial.print("\t frequency_hz = ");
  Serial.println(frequencyB, 4); //4 dp

  Serial.print("angPos_deg = ");
  Serial.print(angPosB);
  Serial.print("\t angVel_radps = ");
  Serial.println(angVelB, 4); //4 dp

  Serial.println();
}





unsigned long pidPrevTime, pidSampleTime = 100; // in ms (i.e 1000/pidSampleTime in Hz)

void setup() {
  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(enc[A].clkPin),readEncoder<A>,RISING);
  attachInterrupt(digitalPinToInterrupt(enc[B].clkPin),readEncoder<B>,RISING);
 
  pidPrevTime = millis();
}


void loop() {
  enc[A].tryResetFrequency();
  enc[B].tryResetFrequency();
  
  if ((millis() - pidPrevTime) >= pidSampleTime) {
    /* PID CODE SHOULD GO IN HERE*/

    testEncB();

    pidPrevTime = millis();
  }

}
