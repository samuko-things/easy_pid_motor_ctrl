////////// encoder setup ///////////
#include "encoder_setup.h"

int encA_clkPin = 2, encA_dirPin = 4, encA_pulsePerRev = 20;
int encB_clkPin = 3, encB_dirPin = 9, encB_pulsePerRev = 20;

QuadEncoder encA(encA_clkPin, encA_dirPin, encA_pulsePerRev);
QuadEncoder encB(encB_clkPin, encB_dirPin, encB_pulsePerRev);

void encoderInit() {
  attachInterrupt(digitalPinToInterrupt(encA.clkPin), readEncoderA, FALLING);
  attachInterrupt(digitalPinToInterrupt(encB.clkPin), readEncoderB, FALLING);
}

void readEncoderA() {
  encA.freqPerTick = 1000000 / (float)(micros() - encA.oldFreqTime);
  encA.oldFreqTime = micros();

  if (digitalRead(encA.dirPin) == HIGH) {
    encA.tickCount += 1;
    encA.frequency = encA.freqPerTick / (float)encA.pulsePerRev;
  } else {
    encA.tickCount -= 1;
    encA.frequency = -1.00 * encA.freqPerTick / (float)encA.pulsePerRev;
  }

  encA.checkFreqTime = millis();
}

void readEncoderB() {
  encB.freqPerTick = 1000000 / (float)(micros() - encB.oldFreqTime);
  encB.oldFreqTime = micros();

  if (digitalRead(encB.dirPin) == HIGH) {
    encB.tickCount += 1;
    encB.frequency = encB.freqPerTick / (float)encB.pulsePerRev;
  } else {
    encB.tickCount -= 1;
    encB.frequency = -1.00 * encB.freqPerTick / (float)encB.pulsePerRev;
  }

  encB.checkFreqTime = millis();
}
////////////////////////////////////////////////////////////////


////////// motor bridge control ////////////
#include "motor_bridge_control.h"
// motor A H-Bridge Connection
int IN1 = 7, IN2 = 8, enA = 5;
// motor B H-Bridge Connection
int IN3 = 11, IN4 = 12, enB = 6;

MotorControl motorA(IN1, IN2, enA);
MotorControl motorB(IN3, IN4, enB);
/////////////////////////////////////////////


////////// PID control ////////////
#include "simple_pid_control.h"

int pwmMin = -255, pwmMax = 255;
float targetA, targetB;

float kp_A = 0.0, ki_A = 0.0, kd_A = 0.0;
float iMin_A = 0.0, iMax_A = 0.0;
SimplePID motorAPID;

float kp_B = 0.0, ki_B = 0.0, kd_B = 0.0;
float iMin_B = 0.0, iMax_B = 0.0;
SimplePID motorBPID;

void setupPIDs() {
  motorAPID.setGains(kp_A, ki_A, kd_A);
  motorAPID.setOutLimit((float)pwmMin, (float)pwmMax);
  motorAPID.setIntLimit(iMin_A, iMax_A);

  motorBPID.setGains(kp_B, ki_B, kd_B);
  motorBPID.setOutLimit((float)pwmMin, (float)pwmMax);
  motorBPID.setIntLimit(iMin_B, iMax_B);
}

void motorAPosControl(int posInDeg) {
  float targetPos = (float)posInDeg * PI / 180.0;
  float pwmOut = motorAPID.computePID(targetPos, encA.getAngPos());
  motorA.sendPWM((int)pwmOut);
}

void motorBPosControl(int posInDeg) {
  float targetPos = (float)posInDeg * PI / 180.0;
  float pwmOut = motorBPID.computePID(targetPos, encB.getAngPos());
  motorB.sendPWM((int)pwmOut);
}
/////////////////////////////////////////////










//////////////////////////////////////////////
void delayMs(int ms) {
  for (int i = 0; i < ms; i += 1) {
    delayMicroseconds(1000);
  }
}
////////////////////////////////////////////


//////////////////////////////////////////////
int absAngDeg(float incAngRad) {
  float incAngDeg = incAngRad * 180.0 / PI;
  return (int)incAngDeg % 360;
}
/////////////////////////////////////////////


////////////////// BASIC TEST CODES ////////////////////////
void testMotorA() {
  for (int pwmVal = -255; pwmVal <= 255; pwmVal += 5) {
    motorA.sendPWM(pwmVal);
    delayMs(250);
  }
  for (int pwmVal = 255; pwmVal >= -255; pwmVal -= 5) {
    motorA.sendPWM(pwmVal);
    delayMs(250);
  }
}

void testMotorB() {
  for (int pwmVal = -255; pwmVal <= 255; pwmVal += 5) {
    motorB.sendPWM(pwmVal);
    delayMs(250);
  }
  for (int pwmVal = 255; pwmVal >= -255; pwmVal -= 5) {
    motorB.sendPWM(pwmVal);
    delayMs(250);
  }
}

void testEncA() {
  long tickCountA = encA.tickCount;
  float frequencyA = encA.frequency;
  float angPosA = encA.getAngPos();
  float angVelA = encA.getAngVel();

  Serial.print("tickCount = ");
  Serial.print(tickCountA);
  Serial.print("\t frequency_hz = ");
  Serial.println(frequencyA, 4); //4 dp

  Serial.print("angPos_deg = ");
  Serial.print(absAngDeg(angPosA));
  Serial.print("\t angVel_radps = ");
  Serial.println(angVelA, 4); //4 dp

  Serial.println();
}

void testEncB() {
  long tickCountB = encB.tickCount;
  float frequencyB = encB.frequency;
  float angPosB = encB.getAngPos();
  float angVelB = encB.getAngVel();

  Serial.print("tickCount = ");
  Serial.print(tickCountB);
  Serial.print("\t frequency_hz = ");
  Serial.println(frequencyB, 4); //4 dp

  Serial.print("angPos_deg = ");
  Serial.print(absAngDeg(angPosB));
  Serial.print("\t angVel_radps = ");
  Serial.println(angVelB, 4); //4 dp

  Serial.println();
}
////////////////////////////////////////////////////////////










unsigned long prevTime, sampleTime = 10; // in ms (10ms == 100Hz)

void setup() {
  Serial.begin(9600);

  encoderInit();

  //  setupPIDs();

  prevTime = millis();

  //  motorA.sendPWM(95);
  //  motorB.sendPWM(95);
}


void loop() {
  encA.resetFrequency();
  encB.resetFrequency();

  if ((millis() - prevTime) >= sampleTime) {
    /* CODE SHOULD GO IN HERE*/
    
    // testEncA();
    // testEncB();

    /* compute PID output with and send control command*/
    //    motorAPosControl(180);
    //    motorBPosControl(180);
    
    /*########################*/

    prevTime = millis();
  }

}
