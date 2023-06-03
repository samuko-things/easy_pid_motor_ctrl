#include <Wire.h>

// i2c slave uno

#include <Wire.h>
void setup()
{
  Wire.begin(4);                
  Wire.onReceive(slaveReceiveData);
  Wire.onRequest(slaveSendData);
  
  Serial.begin(9600);
}

void loop()
{
  delay(5);
}






///////////////////////////////////////////
float posA = 35.8934, posB = 2.6734;
float velA = 3.1234, velB = 0.1236;



String sendMotorAPos(){
  return String(posA, 4);
}
String sendMotorBPos(){
  return String(posB, 4);
}
String sendMotorAVel(){
  return String(velA, 4);
}
String sendMotorBVel(){
  return String(velA, 4);
}


String setMotorAPwm(int val){
  Serial.print(val);
  return "true";
}
String setMotorBPwm(int val){
  Serial.print(val);
  return "true";
}
String setMotorATarget(float val){
  Serial.print(val);
  return "true";
}
String setMotorBTarget(float val){
  Serial.print(val);
  return "true";
}


String setMotorPwm(int valA, int valB){
  Serial.print(valA);
  return "true";
}
String setMotorTarget(float valA, float valB){
  Serial.print(valA);
  return "true";
}


String setPidMode(int mode){
  Serial.print(mode);
  return "true";
}
///////////////////////////////////////////






/////////////// I2C COMMUNICATION /////////////////

String myMsg = "";

void slaveSendData(/*String msg*/){
  String _msg = "";
  if (myMsg != ""){
    _msg = myMsg;
    myMsg = "";
  }
  else {
    _msg = "false";
  }
  char charArray[10];
  _msg.toCharArray(charArray, _msg.length() + 1);
  Wire.write(charArray, _msg.length());                
}




String msg = "", msgBuffer, dataBuffer[2];

void slaveReceiveData(int dataSizeInBytes){
  int indexPos = 0, i=0;
 
  for(int i=0; i<dataSizeInBytes; i+=1){
    char c = Wire.read();
    msg += c; 	
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
  
  if(dataBuffer[0] == "posA"){
    myMsg = sendMotorAPos();
  }
  else if (dataBuffer[0] == "posB") {
    myMsg = sendMotorBPos();
  }
  else if (dataBuffer[0] == "velA") {
    myMsg = sendMotorAVel();
  }
  else if (dataBuffer[0] == "velB") {
    myMsg = sendMotorBVel();
  }
  else if (dataBuffer[0] == "pwmA") {
    myMsg = setMotorAPwm(constrain(dataBuffer[1].toInt(), 0, 255));
  }
  else if (dataBuffer[0] == "pwmB") {
    myMsg = setMotorBPwm(constrain(dataBuffer[1].toInt(), 0, 255));
  }
  else if (dataBuffer[0] == "tagA") {
    myMsg = setMotorATarget(dataBuffer[1].toFloat());
  }
  else if (dataBuffer[0] == "tagB") {
    myMsg = setMotorBTarget(dataBuffer[1].toFloat());
  }
  else if (dataBuffer[0] == "pwm") {
    myMsg = setMotorPwm(constrain(dataBuffer[1].toInt(), 0, 255), constrain(dataBuffer[2].toInt(), 0, 255));
  }
  else if (dataBuffer[0] == "tag") {
    myMsg = setMotorTarget(dataBuffer[1].toFloat(), dataBuffer[2].toFloat());
  }
  else if (dataBuffer[0] == "mode") {
    myMsg = setPidMode(dataBuffer[1].toInt());
  }
  
  msg = "";
  msgBuffer = "";
  dataBuffer[0] = "";
  dataBuffer[1] = "";
  dataBuffer[3] = "";
}

///////////////////////////////////////////////////////////////
