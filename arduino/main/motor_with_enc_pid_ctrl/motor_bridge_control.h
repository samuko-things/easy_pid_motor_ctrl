////////////// MOTOR WITH L298N HBRIDGE MODULE ////////////////////////////

class MotorControl {
  public:
    MotorControl(int IN1_pin, int IN2_pin, int en_pin) {
      in1Pin = IN1_pin;
      in2Pin = IN2_pin;
      enPin = en_pin;

      pinMode(in1Pin, OUTPUT);
      pinMode(in2Pin, OUTPUT);
      pinMode(enPin, OUTPUT);

      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
    }

    void sendPWM(int pwmVal) {
      if (pwmVal > 0) {
        analogWrite( enPin, abs(pwmVal) );
        setForwardDirection();
      } else if (pwmVal < 0) {
        analogWrite( enPin, abs(pwmVal) );
        setReverseDirection();
      } else {
        analogWrite( enPin, 0 );
        setHalt();
      }
    }

    int getDirection(){
      return dir;
    }

  private:
    int in1Pin, in2Pin, enPin;
    int dir = 1;

    void setForwardDirection() {
      dir = 1;
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
    }

    void setReverseDirection() {
      dir = 0;
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
    }

    void setHalt() {
      dir = 0;
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
    }

};



//////////////////////////////////////////////////////////////
// motor A H-Bridge Connection
int IN1 = 7, IN2 = 8, enA = 5;
// motor B H-Bridge Connection
int IN3 = 11, IN4 = 12, enB = 6;

MotorControl motor[2] {
  MotorControl(IN1, IN2, enA),
  MotorControl(IN3, IN4, enB)
};
//////////////////////////////////////////////////////////////
