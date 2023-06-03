//////////////////// PID CONTROL //////////////////////

class SimplePID {
  public:
    SimplePID(float Kp, float Ki, float Kd, float out_min, float out_max) {
      reset();
      
      kp = Kp;
      ki = Ki;
      kd = Kd;
      outMax = out_max;
      outMin = out_min;
      
      errorPrev = error;
      lastTime = micros();
    }

    void setParameters(float Kp, float Ki, float Kd, float out_min, float out_max) {
      kp = Kp;
      ki = Ki;
      kd = Kd;
      outMax = out_max;
      outMin = out_min;
    }

    void setGains(float Kp, float Ki, float Kd) {
      kp = Kp; 
      ki = Ki; 
      kd = Kd;
    }
    
    void setKp(float Kp) {
      kp = Kp; 
    }

    void setKi(float Ki) {
      ki = Ki; 
    }

    void setKd(float Kd) {
      kd = Kd; 
    }

    void setOutLimit(float out_max, float out_min) {
      outMax = out_max;
      outMin = out_min;
    }

    void begin(){
      reset();
      lastTime = micros();
    }


    float compute(float target, float actual) {
      unsigned long dt = micros() - lastTime;

      error = target - actual;
      
      errorDot = (error - errorPrev) * 1000000.00 / dt;

      if(!isOutputClamped){
        errorInt = errorInt + (error * dt / 1000000.00);
      }

      output = (kp * error) + (ki * errorInt) + (kd * errorDot);
      if(outMin<output && output<outMax){
        isOutputClamped = false;
      } else {
        isOutputClamped = true;
        output = constrain(output, outMin, outMax);
      }
      
      errorPrev = error;
      lastTime = micros();

      return output;
    }

  private:
    float error, errorPrev, errorInt, errorDot, output;
    unsigned long lastTime = 0;
    float kp, ki, kd;
    float outMax, outMin;
    bool isOutputClamped = false;

    void reset() {
      error = 0.0;
      errorPrev = 0.0;
      errorInt = 0.0;
      errorDot = 0.0;
      output = 0.0;
      lastTime = 0;
    }
};




///////////////////////////////////////////////////////

//////////// sample use /////////////////

// // initialize PID with parameters
// float kp = 12, ki = 2, kd = 0.5, outMinPwm = -250.0, outMaxPwm = 250.0; 
// float target = 0.456, output; 
// SimplePID myPID(kp, ki, kd, outMinPwm, outMaxPwm);
//
//unsigned long pidPrevTime, pidSampleTime = 10; // in ms (i.e 1000/pidSampleTime in Hz)
//void setup() {
//  // you may also change the setting of some PID parameters (if u like)
//
//  myPID.begin(); //this is important - the PID start tracking time.
//  pidPrevTime = millis();
//}
//
//
//void loop() {
//
//  if ((millis() - pidPrevTime) >= pidSampleTime) {
//    /* PID CODE SHOULD GO IN HERE*/
//
//    // compute output with target and actual sensor reading
//    pwmOut = myPID.compute(target, actual/*or sensor reading*/); 
//
//    // send output for control
//    sendPWM((int)pwmOut); // e.g a function you wrote to send the output PWM to a motor via an H-Bridge
//    /*########################*/
//
//    pidPrevTime = millis();
//  }
//
//}

//////////////////////////////////////////////////////
