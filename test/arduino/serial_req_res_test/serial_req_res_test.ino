// Arduino IDE:
// File -> Examples -> 04.Communication -> PhysicalPixel

const int ledPin = 13;  // pin the LED is attached to
int incomingByte;       // variable stores  serial data

int pos;


void sendMotorPos(){
  Serial.println(String(pos));
}

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





String msg = "", msgBuffer, dataBuffer[2];

// void serialGetReqSendRes_test() {
//   if (Serial.available() > 0) {
//     while (Serial.available()) {
//       if (Serial.available() > 0) {
//         char c = Serial.read();  //gets one byte from serial buffer
//         msg += c;                //makes the string readString
//       }
//     }
//     msg.trim();
//     msg.toUpperCase();

//     if (msg != ""){
//       if(msg=="H") turnOnLed();
//       else if (msg=="L") turnOffLed();
//       else if (msg=="N") sendName();
//       else if (msg=="P") sendMotorPos();
//     }
//   }

//   msg = "";
// }



void serialGetReqSendRes() {
  int indexPos = 0, i = 0;

  if (Serial.available() > 0) {
    while (Serial.available())
    {
      if (Serial.available() > 0)
      {
        char c = Serial.read();  //gets one byte from serial buffer
        msg += c; //makes the string readString
      }
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

    dataBuffer[0].toUpperCase();
    Serial.println(dataBuffer[0]);
    Serial.println(dataBuffer[1]);

    if (dataBuffer[0] != ""){
      if(dataBuffer[0]=="H") turnOnLed();
      else if (dataBuffer[0]=="L") turnOffLed();
      else if (dataBuffer[0]=="N") sendName();
      else if (dataBuffer[0]=="P") sendMotorPos();
    }

  }

  msg = "";
  msgBuffer = "";
  dataBuffer[0] = "";
  dataBuffer[1] = "";
}














unsigned long prevTime, sampleTime = 5; //ms -> (1000/sampleTime) hz

unsigned long prevExecTime, sampleExecTime = 20; //ms -> (1000/sampleExecTime) hz

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);

  prevTime = millis();
  prevExecTime = millis();
}

void loop() {

  if ((millis() - prevTime) >= sampleTime) {
    serialGetReqSendRes();
    // serialGetReqSendRes_test();
    prevTime = millis();
  }

  if ((millis() - prevExecTime) >= sampleExecTime) {
    if (pos < 360) pos += 1;
    else pos = 0;
    prevExecTime = millis();
  }

}