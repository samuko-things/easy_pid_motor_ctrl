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
  encA.freqPerTick = 1000000.00 / (float)(micros() - encA.oldFreqTime);
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
  encB.freqPerTick = 1000000.00 / (float)(micros() - encB.oldFreqTime);
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
  float angPosA = encA.getAbsAngPosDeg();
  float angVelA = encA.getAngVel();

  Serial.print("tickCount = ");
  Serial.print(tickCountA);
  Serial.print("\t frequency_hz = ");
  Serial.println(frequencyA, 4); //4 dp

  Serial.print("angPos_deg = ");
  Serial.print(angPosA);
  Serial.print("\t angVel_radps = ");
  Serial.println(angVelA, 4); //4 dp

  Serial.println();
}

void testEncB() {
  long tickCountB = encB.tickCount;
  float frequencyB = encB.frequency;
  float angPosB = encB.getAbsAngPosDeg();
  float angVelB = encB.getAngVel();

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
////////////////////////////////////////////////////////////









///////// DIFFERENT TASK FOR SERIAL COMMUNICATION //////////
void sendMotorAPos(){
  Serial.println(encA.getAngPos(),4);
}
void sendMotorBPos(){
  Serial.println(encB.getAngPos(),4);
}

void sendMotorAVel(){
  Serial.println(encA.getAngVel(),4);
}
void sendMotorBVel(){
  Serial.println(encB.getAngVel(),4);
}

void sendMotorData(){
  Serial.print(encA.getAngPos(),4);
  Serial.print(",");
  Serial.print(encA.getAngVel(),4);
  Serial.print(",");
  Serial.print(encB.getAngPos(),4);
  Serial.print(",");
  Serial.println(encB.getAngVel(),4);
}

void sendMotorAData(){
  Serial.print(encA.getAngPos(),4);
  Serial.print(",");
  Serial.println(encA.getAngVel(),4);
}

void sendMotorBData(){
  Serial.print(encB.getAngPos(),4);
  Serial.print(",");
  Serial.println(encB.getAngVel(),4);
}

void sendAllMotorAData(){
  Serial.print(encA.tickCount);
  Serial.print(",");
  Serial.print(encA.getAngPos(),4);
  Serial.print(",");
  Serial.print(encA.frequency,4);
  Serial.print(",");
  Serial.println(encA.getAngVel(),4);
}

void sendAllMotorBData(){
  Serial.print(encB.tickCount);
  Serial.print(",");
  Serial.print(encB.getAngPos(),4);
  Serial.print(",");
  Serial.print(encB.frequency,4);
  Serial.print(",");
  Serial.println(encB.getAngVel(),4);
}

void sendMotorAEncFreq(){
  Serial.println(encA.frequency,4);
}
void sendMotorBEncFreq(){
  Serial.println(encB.frequency,4);
}

void ctrlMotorAPwm(int val){
  motorA.sendPWM(val);
  Serial.println('1');
}
void ctrlMotorBPwm(int val){
  motorB.sendPWM(val);
  Serial.println('1');
}

void ctrlMotorPwm(int valA, int valB){
  motorB.sendPWM(valA);
  motorB.sendPWM(valB);
  Serial.println('1');
}



void setMotorATargetPos(float val){
  Serial.println('1');
}
void setMotorBTargetPos(float val){
  Serial.println('1');
}

void setMotorTargetPos(float valA, float valB){
  Serial.println('1');
}



void setMotorATargetVel(float val){
  Serial.println('1');
}
void setMotorBTargetVel(float val){
  Serial.println('1');
}

void setMotorTargetVel(float valA, float valB){
  Serial.println('1');
}
/////////////////////////////////////////////////////////////



///////////////// SERIAL COMMUNICATION //////////////////////
String msg = "", msgBuffer, dataBuffer[3];

void serialGetReqSendRes() {
  int indexPos = 0, i = 0;

  if (Serial.available() > 0) {
    while (Serial.available())
    {
      // if (Serial.available() > 0)
      // {
      //   char c = Serial.read();  //gets one byte from serial buffer
      //   msg += c; //makes the string readString
      // }
      msg = Serial.readString();
    }
    msg.trim();
    if (msg != "") {
      do {
        indexPos = msg.indexOf(',');
        if (indexPos != -1) {
          msgBuffer = msg.substring(0, indexPos);
          msg = msg.substring(indexPos + 1, msg.length());
          dataBuffer[i] = msgBuffer;
          msgBuffer = "";
        }
        else {
          if (msg.length() > 0)
            dataBuffer[i] = msg;
        }
        i += 1;
      } while (indexPos >= 0);
    }

    // Serial.println(dataBuffer[0]);
    // Serial.println("val = "+dataBuffer[1]);

    if (dataBuffer[0] != ""){
      if (dataBuffer[0]=="all") sendMotorData();
      else if (dataBuffer[0]=="ALLA") sendAllMotorAData();
      else if (dataBuffer[0]=="ALLB") sendAllMotorBData();
      else if (dataBuffer[0]=="allA") sendMotorAData();
      else if (dataBuffer[0]=="allB") sendMotorBData();
      else if (dataBuffer[0]=="pwmA") ctrlMotorAPwm(constrain(dataBuffer[1].toInt(), 0, 255));
      else if (dataBuffer[0]=="pwmB") ctrlMotorBPwm(constrain(dataBuffer[1].toInt(), 0, 255));
      else if (dataBuffer[0]=="pwm") ctrlMotorPwm(constrain(dataBuffer[1].toInt(), 0, 255),constrain(dataBuffer[2].toInt(), 0, 255));
      else if (dataBuffer[0]=="posA") setMotorATargetPos(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="posB") setMotorBTargetPos(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="pos") setMotorTargetPos(dataBuffer[1].toFloat(), dataBuffer[2].toFloat());
      else if (dataBuffer[0]=="velA") setMotorATargetVel(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="velB") setMotorBTargetVel(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="vel") setMotorTargetVel(dataBuffer[1].toFloat(), dataBuffer[2].toFloat());
    }

  }

  msg = "";
  msgBuffer = "";
  dataBuffer[0] = "";
  dataBuffer[1] = "";
  dataBuffer[3] = "";
}
//////////////////////////////////////////////////////////////////////////











//pls do not adjust to less than 1000
unsigned long prevSerialComTime, sampleSerialComTime = 5; //ms -> (1000/sampleTime) hz
unsigned long prevExecTime, sampleExecTime = 5; //ms -> (1000/sampleExecTime) hz

void setup() {
  Serial.begin(9600);

  encoderInit();

  //  setupPIDs();

  // encA.freqSampleTime = sampleSerialComTime*3;
  // encB.freqSampleTime = sampleSerialComTime*3;
  Serial.setTimeout(2);
  prevSerialComTime = millis();
  prevExecTime = millis();
  
  //  motorA.sendPWM(90);
  //  motorB.sendPWM(50);
}


void loop() {
  encA.resetFrequency();
  encB.resetFrequency();

  if ((millis() - prevSerialComTime) >= sampleSerialComTime) {
    serialGetReqSendRes();
    prevSerialComTime = millis();
  }

  if ((millis() - prevExecTime) >= sampleExecTime) {
    /* CODE SHOULD GO IN HERE*/
    
    // testEncA();
    // testEncB();

    /* compute PID output with and send control command*/
    //    motorAPosControl(180);
    //    motorBPosControl(180);
    
    /*########################*/

    prevExecTime = millis();
  }

}
