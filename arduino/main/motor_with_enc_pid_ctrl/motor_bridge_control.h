////////////// MOTOR WITH HBRIDGE ////////////////////////////

class MotorControl {
  public:
    int dir = 1;
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

  private:
    int in1Pin, in2Pin, enPin;

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
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
    }

};
