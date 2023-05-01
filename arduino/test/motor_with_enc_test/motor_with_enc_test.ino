
////////////// ENCODERS ////////////////////////////
int encoderA_PinA = 2, encoderA_PinB = 4;
int encoderB_PinA = 3, encoderB_PinB = 9;
volatile long tickCountA = 0, tickCountB = 0;
volatile float angPosA, angPosB;
volatile float frequencyA, frequencyB;
volatile long oldFreqTimeA, oldFreqTimeB, checkFreqTimeA, checkFreqTimeB;
volatile float angVelA, angVelB;
volatile int pprA = 20, pprB = 20; // pulse per rev

void encoderPinsSetup() {
  pinMode(encoderA_PinA, INPUT_PULLUP);
  pinMode(encoderA_PinB, INPUT_PULLUP);

  pinMode(encoderB_PinA, INPUT_PULLUP);
  pinMode(encoderB_PinB, INPUT_PULLUP);

  oldFreqTimeA = micros();
  oldFreqTimeB = micros();

  checkFreqTimeA = millis();
  checkFreqTimeB = millis();

  attachInterrupt(digitalPinToInterrupt(encoderA_PinA), readEncoderA, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoderB_PinA), readEncoderB, FALLING);
}

float round_dp(float val, int dp) {
  float rounded_val = (int)((val * pow(10, dp)) + 0.5);
  return (float)rounded_val / pow(10, dp);
}

float getAngPos(long tickCount, int ppr) {
  return (2 * PI * (float)tickCount) / (float)ppr;
}

float getAngVel(float frequency, int ppr) {
  return (2 * PI * frequency) / (float)ppr;
}

void readEncoderA() {
  frequencyA = round_dp(1000000 / (float)(micros() - oldFreqTimeA), 2);
  oldFreqTimeA = micros();

  if (digitalRead(encoderA_PinB) == HIGH) {
    tickCountA += 1;
    frequencyA *= 1;
  } else {
    tickCountA -= 1;
    frequencyA *= -1;
  }

  angPosA = getAngPos(tickCountA, pprA);
  angVelA = getAngVel(frequencyA, pprA);
  checkFreqTimeA = millis();
}

void resetFrequencyA(){
  if(millis()-checkFreqTimeA > 1000){
    frequencyA = 0;
    angVelA = getAngVel(frequencyA, pprA);
    checkFreqTimeA = millis();
  }
}

void readEncoderB() {
  frequencyB = round_dp(1000000 / (float)(micros() - oldFreqTimeB), 2);
  oldFreqTimeB = micros();

  if (digitalRead(encoderB_PinB) == HIGH) {
    tickCountB += 1;
    frequencyB *= 1;
  } else {
    tickCountB -= 1;
    frequencyB *= -1;
  }

  angPosB = getAngPos(tickCountB, pprB);
  angVelB = getAngVel(frequencyB, pprB);
  checkFreqTimeB = millis();
}

void resetFrequencyB(){
  if(millis()-checkFreqTimeB > 1000){
    frequencyB = 0;
    angVelB = getAngVel(frequencyB, pprB);
    checkFreqTimeB = millis();
  }
}
/////////////////////////////////////////////




////////////////// MOTOR WITH HBRIDGE /////////////////////
// motor A H-Bridge Connection
int IN1 = 7, IN2 = 8, enA = 5;
// motor B H-Bridge Connection
int IN3 = 11, IN4 = 12, enB = 6;
int dirA = 1, dirB = 1;

void motorHbridgeSetup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(enA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enB, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}

// Motor A
void setForwardDirectionA() {
  dirA = 1;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
void setReverseDirectionA() {
  dirA = 0;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void setHaltA() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void sendPwmA(int pwmVal) {
  if (pwmVal > 0) {
    analogWrite(enA, abs(pwmVal));
    setForwardDirectionA();
  } else if (pwmVal < 0) {
    analogWrite(enA, abs(pwmVal));
    setReverseDirectionA();
  } else {
    analogWrite(enA, 0);
    setHaltA();
  }
}

// Motor B
void setForwardDirectionB() {
  dirB = 1;
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void setReverseDirectionB() {
  dirB = 0;
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void setHaltB() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void sendPwmB(int pwmVal) {
  if (pwmVal > 0) {
    analogWrite(enB, abs(pwmVal));
    setForwardDirectionB();
  } else if (pwmVal < 0) {
    analogWrite(enB, abs(pwmVal));
    setReverseDirectionB();
  } else {
    analogWrite(enB, 0);
    setHaltB();
  }
}
///////////////////////////////////////////////////////




//////////////////// PID CONTROL //////////////////////
long prevPidTime;

float errorA_pos, errorPrevA_pos, errorDotA_pos, errorIntA_pos;
float kpA_pos = 0, kiA_pos = 0, kdA_pos = 0;
float errorIntMinA_pos = 0, errorIntMaxA_pos = 0;

float errorA_vel, errorPrevA_vel, errorDotA_vel, errorIntA_vel;
float kpA_vel = 0, kiA_vel = 0, kdA_vel = 0;
float errorIntMinA_vel = 0, errorIntMaxA_vel = 0;

float errorB_pos, errorPrevB_pos, errorDotB_pos, errorIntB_pos;
float kpB_pos = 0, kiB_pos = 0, kdB_pos = 0;
float errorIntMinB_pos = 0, errorIntMaxB_pos = 0;

float errorB_vel, errorPrevB_vel, errorDotB_vel, errorIntB_vel;
float kpB_vel = 0, kiB_vel = 0, kdB_vel = 0;
float errorIntMinB_vel = 0, errorIntMaxB_vel = 0;

float pwmValMax = 100.0, pwmValMin = -100.0;

void computePositionPID(float targetAngPosA, float targetAngPosB) {
  float dt = micros() - prevPidTime;

  errorA_pos = targetAngPosA - angPosA;
  errorB_pos = targetAngPosB - angPosB;

  errorDotA_pos = ((errorA_pos - errorPrevA_pos) * 1000000) / dt;
  errorDotA_pos = ((errorA_pos - errorPrevA_pos) * 1000000) / dt;

  errorIntA_pos = errorIntA_pos + ((errorA_pos * dt) / 1000000);
  errorIntB_pos = errorIntB_pos + ((errorB_pos * dt) / 1000000);

  float pwmValA = (kpA_pos * errorA_pos) + (kiA_pos * errorIntA_pos) + (kdA_pos * errorDotA_pos);
  float pwmValB = (kpB_pos * errorB_pos) + (kiB_pos * errorIntB_pos) + (kdB_pos * errorDotB_pos);

  sendPwmA(pwmValA);
  sendPwmB(pwmValB);
}

void computeVelocityPID(float targetAngVelA, float targetAngVelB) {
  float dt = micros() - prevPidTime;

  errorA_vel = targetAngVelA - angVelA;
  errorB_vel = targetAngVelB - angVelB;

  errorDotA_vel = ((errorA_vel - errorPrevA_vel) * 1000000) / dt;
  errorDotA_vel = ((errorA_vel - errorPrevA_vel) * 1000000) / dt;

  errorIntA_vel = errorIntA_vel + ((errorA_vel * dt) / 1000000);
  errorIntB_vel = errorIntB_vel + ((errorB_vel * dt) / 1000000);

  float pwmValA = (kpA_vel * errorA_vel) + (kiA_vel * errorIntA_vel) + (kdA_vel * errorDotA_vel);
  float pwmValB = (kpB_vel * errorB_vel) + (kiB_vel * errorIntB_vel) + (kdB_vel * errorDotB_vel);

  sendPwmA(pwmValA);
  sendPwmB(pwmValB);
}
///////////////////////////////////////////////////////

void delayMs(int ms) {
  for (int i = 0; i < ms; i += 1) {
    delayMicroseconds(1000);
  }
}










void setup() {
  Serial.begin(9600);

  motorHbridgeSetup();

  encoderPinsSetup();

  prevPidTime = micros();

  sendPwmA(50.30);
}


void loop() {
  resetFrequencyA();
  resetFrequencyB();
  
  //    for (int pwmVal = -100; pwmVal <= 100; pwmVal += 5) {
  //      sendPwmA(float(pwmVal));
  //      delayMs(500);
  //    }
  //    for (int pwmVal = 100; pwmVal >= -100; pwmVal -= 5) {
  //      sendPwmA(float(pwmVal));
  //      delayMs(500);
  //    }
  
  Serial.println("tickCount = " + String(tickCountA) + ", " + "frequency = " + String(frequencyA));
  Serial.println("angularPos = " + String(angPosA) + ", " + "angularVel = " + String(angVelA));
  
  delayMs(20);
}
