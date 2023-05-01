//////////////////// PID CONTROL //////////////////////

class SimplePID {
  public:
    SimplePID() {
      reset();
      errorPrev = error;
      lastTime = micros();
    }

    void setAllParameters(float Kp, float Ki, float Kd, float out_max, float out_min, float i_max, float i_min) {
      kp = Kp; ki = Ki; kd = Kd;
      outMax = out_max; outMin = out_min;
      iMin = i_min; iMax = i_max;
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

    void setIntLimit(float i_max, float i_min) {
      iMin = i_min;
      iMax = i_max;
    }


    float computePID(float target, float actual) {
      unsigned long dt = micros() - lastTime;

      error = target - actual;
      errorDot = (error - errorPrev) * 1000000.00 / dt;
      errorInt = errorInt + (error * dt / 1000000.00);
      if (iMax != 0 && iMin != 0) {
        errorInt = constrain(errorInt, iMin, iMax);
      }

      output = (kp * error) + (ki * errorInt) + (kd * errorDot);
      if (outMax != 0 && outMin != 0) {
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
    float iMax, iMin;

    void reset() {
      error = 0.0;
      errorPrev = 0.0;
      errorInt = 0.0;
      errorDot = 0.0;
      output = 0.0;
      outMax = 0.0; outMin = 0.0;
      iMax = 0.0; iMin = 0.0;
      lastTime = 0;
    }
};

///////////////////////////////////////////////////////

//////////// sample use /////////////////

//unsigned long prevTime, sampleTime = 10; // in ms
//
//void setup() {
//  // initialize necessary PID parameters
//  prevTime = millis();
//}
//
//
//void loop() {
//
//  if ((millis() - prevTime) >= sampleTime) {
//    /* CODE SHOULD GO IN HERE*/
//
//    // compute output with target and actual sensor reading
//    pwmOut = myPID.computePID(target, actual); 
//
//    // send output for control
//    sendPWM((int)pwmOut); 
//    /*########################*/
//
//    prevTime = millis();
//  }
//
//}

//////////////////////////////////////////////////////
