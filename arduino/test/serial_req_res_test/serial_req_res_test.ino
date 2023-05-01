// Arduino IDE:
// File -> Examples -> 04.Communication -> PhysicalPixel

const int ledPin = 13;  // pin the LED is attached to
int incomingByte;       // variable stores  serial data



void sendName(){
  Serial.println(String(34546.78));
}

void turnOnLed(){
  digitalWrite(ledPin, HIGH);
  Serial.println('1');
}

void turnOffLed(){
  digitalWrite(ledPin, LOW);
  Serial.println('1');
}



String msg = "";
void serialGetReqSendRes() {
  if (Serial.available() > 0) {
    while (Serial.available()) {
      if (Serial.available() > 0) {
        char c = Serial.read();  //gets one byte from serial buffer
        msg += c;                //makes the string readString
      }
    }
    msg.trim();
    msg.toUpperCase();

    if (msg != ""){
      if(msg=="H") turnOnLed();
      else if (msg=="L") turnOffLed();
      else if (msg=="N") sendName();
    }
  }

  msg = "";
}




unsigned long prevTime, sampleTime = 5;
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  prevTime = millis();
}

void loop() {

  if ((millis() - prevTime) >= sampleTime) {
    serialGetReqSendRes();
    prevTime = millis();
  }
}