////////////// ENCODERS ////////////////////////////

class QuadEncoder {
public:
  int clkPin, dirPin, pulsePerRev;
  volatile long tickCount;
  float prevAngPos, angPos, angVel, freqPerTick, frequency;
  volatile unsigned long oldFreqTime, checkFreqTime, freqSampleTime=200;
  long testTickCount = 0;

  QuadEncoder(int clk_pin, int dir_pin, int ppr) {
    clkPin = clk_pin;
    dirPin = dir_pin;
    pulsePerRev = ppr;

    pinMode(clkPin, INPUT_PULLUP);
    pinMode(dirPin, INPUT_PULLUP);

    oldFreqTime = micros();
    checkFreqTime = millis();
  }

  void setPulsePerRev(int ppr){
    pulsePerRev = ppr;
  }

  float getAngPos() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
      return (2.00 * PI * (float)tickCount) / (float)pulsePerRev;
    }  
  }

  float getAbsAngPosDeg() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
      return absAngDeg((2.00 * PI * (float)tickCount) / (float)pulsePerRev);
    }
  }

  float getAngVel() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
      return 2.00 * PI * frequency;
    }
  }

  void resetFrequency() {
    if (millis() - checkFreqTime >= freqSampleTime) {
      if (abs(tickCount-testTickCount)==0){
        frequency = 0; 
      }
      testTickCount = tickCount;
      checkFreqTime = millis();
    }
//    if (millis() - checkFreqTime >= freqSampleTime) {
//      frequency = 0;
//      checkFreqTime = millis();
//    }
  }

  void test() {
    Serial.print("tickCount = ");
    Serial.print(tickCount);
    Serial.print("\t frequency_hz = ");
    Serial.println(frequency, 4); //4 dp
    Serial.println();
  
    Serial.print("angPos_deg = ");
    Serial.print(getAbsAngPosDeg());
    Serial.print("\t angVel_radps = ");
    Serial.println(getAngVel(), 4); //4 dp
  
    Serial.println();
    Serial.println();
  }

  void plotAngPos(){
    Serial.println(getAngPos(), 4); //4 dp
  }

  void plotAngVel(){
    Serial.println(getAngVel(), 4); //4 dp
  }


private:
  float absAngDeg(float incAngRad) {
    float incAngDeg = incAngRad * 180.0 / PI;
    return (int)incAngDeg % 360;
  }
};




//#include "encoder_setup.h"
//
//int encA_clkPin = 2, encA_dirPin = 4, encA_pulsePerRev = 20;
//int encB_clkPin = 3, encB_dirPin = 9, encB_pulsePerRev = 20;
//
//QuadEncoder encA(encA_clkPin, encA_dirPin, encA_pulsePerRev);
//QuadEncoder encB(encB_clkPin, encB_dirPin, encB_pulsePerRev);
//
//void encoderInit() {
//  attachInterrupt(digitalPinToInterrupt(encA.clkPin), readEncoderA, FALLING);
//  attachInterrupt(digitalPinToInterrupt(encB.clkPin), readEncoderB, FALLING);
//}
//
//void readEncoderA() {
//  encA.freqPerTick = 1000000 / (float)(micros() - encA.oldFreqTime);
//  encA.oldFreqTime = micros();
//
//  if (digitalRead(encA.dirPin) == HIGH) {
//    encA.tickCount += 1;
//    encA.frequency = encA.freqPerTick/(float)encA.pulsePerRev;
//  } else {
//    encA.tickCount -= 1;
//    encA.frequency = -1.00*encA.freqPerTick/(float)encA.pulsePerRev;
//  }
//
//}
//
//void readEncoderB() {
//  encB.freqPerTick = 1000000 / (float)(micros() - encB.oldFreqTime);
//  encB.oldFreqTime = micros();
//
//  if (digitalRead(encB.dirPin) == HIGH) {
//    encB.tickCount += 1;
//    encB.frequency = encB.freqPerTick/(float)encB.pulsePerRev;
//  } else {
//    encB.tickCount -= 1;
//    encB.frequency = -1.00*encB.freqPerTick/(float)encB.pulsePerRev;
//  }
//
//}
//
//void setup() {
//  
//  encoderInit(); // intialize encoders with interrupt
//  
//}
//
//
//void loop() {
//  ///// do not touch ////////
//  ///// useful for velocity reading to check when rotation has stopped /////
//  encA.resetFrequency();
//  encB.resetFrequency();
//  ///////////////////////////
//
//  //// other codes goes here /////
//}
/////////////////////////////////////////////
