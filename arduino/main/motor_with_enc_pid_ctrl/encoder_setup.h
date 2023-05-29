////////////// ENCODERS ////////////////////////////
class QuadEncoder {
public:
  int clkPin, dirPin, pulsePerRev;
  volatile long tickCount;
  float prevAngPos, angPos, angVel, freqPerTick, frequency;
  volatile unsigned long oldFreqTime, checkFreqTime, freqSampleTime=1000;

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

  void setPPR(int ppr){
     pulsePerRev = ppr;
  }

  float getAngPos() {  // in radians
    return (2.00 * PI * (float)tickCount) / (float)pulsePerRev;
  }

  float getAbsAngPosDeg() { // in deg -> from 0 to 360
    return absAngDeg((2.00 * PI * (float)tickCount) / (float)pulsePerRev);
  }

  float getAngVel() {  // in rad/sec
    return 2.00 * PI * frequency;
  }

  void tryResetFrequency() {
    if (millis() - checkFreqTime >= freqSampleTime) {
      if (abs(tickCount-testTickCount)==0){
        frequency = 0; 
      }
      testTickCount = tickCount;
      checkFreqTime = millis();
    }
  }


private:
  float absAngDeg(float incAngRad) {
    float incAngDeg = incAngRad * 180.0 / PI;
    return (int)incAngDeg % 360;
  }
};



//////////////////////////////////////////////////////////////////////////////////
int encA_clkPin = 2, encA_dirPin = 4, encA_pulsePerRev = 20;
int encB_clkPin = 3, encB_dirPin = 9, encB_pulsePerRev = 20;

QuadEncoder enc[2] {
  QuadEncoder(encA_clkPin, encA_dirPin, encA_pulsePerRev),
  QuadEncoder(encB_clkPin, encB_dirPin, encB_pulsePerRev)
};

template <int i>
void readEncoder() {
  enc[i].freqPerTick = 1000000.00 / (float)(micros() - enc[i].oldFreqTime);
  enc[i].oldFreqTime = micros();

  if (digitalRead(enc[i].dirPin) > 0) {
    enc[i].tickCount += 1;
    enc[i].frequency = enc[i].freqPerTick / (float)enc[i].pulsePerRev;
  } else {
    enc[i].tickCount -= 1;
    enc[i].frequency = -1.00 * enc[i].freqPerTick / (float)enc[i].pulsePerRev;
  }

//  enc[i].checkFreqTime = millis();
}
///////////////////////////////////////////////////////////////////////////////////////////////








//////////// encoder setup ///////////
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
//  encA.freqPerTick = 1000000.00 / (float)(micros() - encA.oldFreqTime);
//  encA.oldFreqTime = micros();
//
//  if (digitalRead(encA.dirPin) == HIGH) {
//    encA.tickCount += 1;
//    encA.frequency = encA.freqPerTick / (float)encA.pulsePerRev;
//  } else {
//    encA.tickCount -= 1;
//    encA.frequency = -1.00 * encA.freqPerTick / (float)encA.pulsePerRev;
//  }
//
//  encA.checkFreqTime = millis();
//}
//
//void readEncoderB() {
//  encB.freqPerTick = 1000000.00 / (float)(micros() - encB.oldFreqTime);
//  encB.oldFreqTime = micros();
//
//  if (digitalRead(encB.dirPin) == HIGH) {
//    encB.tickCount += 1;
//    encB.frequency = encB.freqPerTick / (float)encB.pulsePerRev;
//  } else {
//    encB.tickCount -= 1;
//    encB.frequency = -1.00 * encB.freqPerTick / (float)encB.pulsePerRev;
//  }
//
//  encB.checkFreqTime = millis();
//}
//
// // after void setup()
//void loop() {
//  encA.resetFrequency();
//  encB.resetFrequency();
//
// // other codes
//}
//////////////////////////////////////////////////////////////////
