#include <util/atomic.h>
#include <Wire.h>
#include "global_params_eeprom.h"

///////// my sepcial delay function ///////////////
void delayMs(int ms) {
  for (int i = 0; i < ms; i += 1) {
    delayMicroseconds(1000);
  }
}
//////////////////////////////////////////////////





////////// encoder setup ///////////
#include "encoder_setup.h"

int encA_clkPin = 2, encA_dirPin = 4; // encA_ppr parameter is decleared globally in the global_params_eeprom.h file.
int encB_clkPin = 3, encB_dirPin = 9; // encB_ppr parameter is decleared globally in the global_params_eeprom.h file.

QuadEncoder encA(encA_clkPin, encA_dirPin, encA_ppr);
QuadEncoder encB(encB_clkPin, encB_dirPin, encB_ppr);

void encoderInit() {
  encA.setPulsePerRev(encA_ppr);
  encA.setPulsePerRev(encA_ppr);
  
  attachInterrupt(digitalPinToInterrupt(encA.clkPin), readEncoderA, FALLING);
  attachInterrupt(digitalPinToInterrupt(encB.clkPin), readEncoderB, FALLING);
}

void readEncoderA() {
  encA.freqPerTick = 1000000.00 / (float)(micros() - encA.oldFreqTime);
  encA.oldFreqTime = micros();

  if (digitalRead(encA.dirPin) > 0) {
    encA.tickCount += 1;
    encA.frequency = encA.freqPerTick / (float)encA.pulsePerRev;
  } else {
    encA.tickCount -= 1;
    encA.frequency = -1.00 * encA.freqPerTick / (float)encA.pulsePerRev;
  }

}

void readEncoderB() {
  encB.freqPerTick = 1000000.00 / (float)(micros() - encB.oldFreqTime);
  encB.oldFreqTime = micros();

  if (digitalRead(encB.dirPin) > 0) {
    encB.tickCount += 1;
    encB.frequency = encB.freqPerTick / (float)encB.pulsePerRev;
  } else {
    encB.tickCount -= 1;
    encB.frequency = -1.00 * encB.freqPerTick / (float)encB.pulsePerRev;
  }

}
////////////////////////////////////////////////////////////////






////////// motor bridge control ////////////
#include "motor_bridge_control.h"
// motor A H-Bridge Connection
int IN1 = 7, IN2 = 8, enA = 5;
MotorControl motorA(IN1, IN2, enA);

// motor B H-Bridge Connection
int IN3 = 11, IN4 = 12, enB = 6;
MotorControl motorB(IN3, IN4, enB);
/////////////////////////////////////////////







////////// simple pid control ////////////
#include "simple_pid_control.h"

// parameters are decleared globally in the global_params_eeprom.h file.

// motorA pid control
SimplePID pidMotorA(kpA, kiA, kdA, outMinA, outMaxA);

// motorA pid control
SimplePID pidMotorB(kpB, kiB, kdB, outMinB, outMaxB);

void pidInit() {
  pidMotorA.setParameters(kpA, kiA, kdA, outMinA, outMaxA);
  pidMotorB.setParameters(kpB, kiB, kdB, outMinB, outMaxB);
  pidMotorA.begin();
  pidMotorB.begin();
}
/////////////////////////////////////////////




//////////////////////////////////////
#include "serial_i2c_comm_api.h"
//////////////////////////////////////














unsigned long prevSerialAPIComTime, sampleSerialAPIComTime = 10; //ms -> (1000/sampleTime) hz
unsigned long pidPrevTime, pidSampleTime = 100; // in ms (i.e 1000/pidSampleTime in Hz)


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2);
  
  // update global params with eeprom contents
//  updateGlobalParamsFromEERPOM();
  /////////////////////////////////////////////
  
  Wire.begin(i2cAddress);                
  Wire.onReceive(i2cSlaveReceiveData);
  Wire.onRequest(i2cSlaveSendData);

  initLed();
  offLed();
  delay(1000);
  onLed();
  delay(2000);
  offLed();
  
  encoderInit();
  pidInit();
  /* motor needs no initialization as it used no global variable dependent on eeprom*/
//  Serial.println("setup finished");
  prevSerialAPIComTime = millis();
  pidPrevTime = millis();

  //  motorB.sendPWM(60);
}


void loop() {
  ///// do not touch ////////
  ///// useful for velocity reading to check when rotation has stopped
  encA.resetFrequency();
  encB.resetFrequency();
  ///////////////////////////


////////// using the serial communiaction API ////////////////////////
  if ((millis() - prevSerialAPIComTime) >= sampleSerialAPIComTime) {
    serialReceiveAndSendData();
    prevSerialAPIComTime = millis();
  }
/////////////////////////////////////////////////////////////////////


  if ((millis() - pidPrevTime) >= pidSampleTime) {
    /* CODE SHOULD GO IN HERE*/
    
//     encA.test();
//     encB.test();

    /* compute PID output with and send control command*/
    
//    if (pidMode){
//      outputA = pidMotorA.compute(targetA, encA.getAngPos()); // targetA is among the global params
//      outputB = pidMotorB.compute(targetB, encB.getAngPos()); // targetB is among the global params
//  
//      motorA.sendPWM((int)outputA);
//      motorB.sendPWM((int)outputB); 
//    }

    /*########################*/

    pidPrevTime = millis();
  }

}
