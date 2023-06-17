#include <Wire.h>

float maxFloat = 99999.888, minFloat = -99999.888;
long maxLong =  2147000000, minLong = -2147000000;

void initLed(){
  pinMode(LED_BUILTIN, OUTPUT);
}

void onLed(){
  digitalWrite(LED_BUILTIN, HIGH);
}

void offLed(){
  digitalWrite(LED_BUILTIN, LOW);
}

///////// DIFFERENT TASK FOR SERIAL AND I2C COMMUNICATION //////////
String sendMotorsTick(){
  String data = String(constrain(encA.tickCount, minLong, maxLong));
  data += ",";
  data += String(constrain(encB.tickCount, minLong, maxLong));
  return data;
}


String sendMotorsFreq(){
  String data = String(constrain(encA.frequency, minFloat, maxFloat), 3);
  data += ",";
  data += String(constrain(encB.frequency, minFloat, maxFloat), 3);
  return data;
}


String sendMotorsPos(){
  String data = String(constrain(encA.getAngPos(), minFloat, maxFloat), 3);
  data += ",";
  data += String(constrain(encB.getAngPos(), minFloat, maxFloat), 3);
  return data;
}


String sendMotorsVel(){
  String data = String(constrain(encA.getAngVel(), minFloat, maxFloat), 3);
  data += ",";
  data += String(constrain(encB.getAngVel(), minFloat, maxFloat), 3);
  return data;
}


String sendMotorAData(){
  String data = String(constrain(encA.getAngPos(), minFloat, maxFloat), 3);
  data += ",";
  data += String(constrain(encA.getAngVel(), minFloat, maxFloat), 3);
  return data;
}


String sendMotorBData(){
  String data = String(constrain(encB.getAngPos(), minFloat, maxFloat), 3);
  data += ",";
  data += String(constrain(encB.getAngVel(), minFloat, maxFloat), 3);
  return data;
}


String setMotorsPwm(int valA, int valB){
  if(!pidMode){
    motorA.sendPWM(valA);
    motorB.sendPWM(valB);
    return "1";
  }
  else return "0";
}


String setMotorsTarget(float valA, float valB){
  if (pidMode){
    targetA = valA;
    targetB = valB;
    return "1";
  }
  else return "0";
}


String setPidMode(int mode){
  if(mode == 0){
    pidMode = false;
    motorA.sendPWM(0);
    motorB.sendPWM(0);
    targetA = 0.00;
    targetB = 0.00;
    onLed();
    return "1";
  } else if (mode == 1) {
    pidMode = true;
    motorA.sendPWM(0);
    motorB.sendPWM(0);
    targetA = 0.00;
    targetB = 0.00;
    offLed();
    return "1";
  }
  else {
    return "0";
  }
}
String sendPidMode(){
  return String(pidMode);
}


String setEncAppr(int ppr){
  if(!pidMode){
    setPPR_A(ppr);
    encA_ppr = getPPR_A();
    return "1";
  }
  else return "0";
}
String sendEncAppr(){ 
  return String(encA_ppr);
}


String setEncBppr(int ppr){
  if(!pidMode){
    setPPR_B(ppr);
    encB_ppr = getPPR_B();
    return "1";
  }
  else return "0";
}
String sendEncBppr(){ 
  return String(encB_ppr);
}


String setMotorAkp(float kp){
  if(!pidMode){
    setKP_A(kp);
    kpA = getKP_A();
    return "1";
  }
  else return "0";
}
String sendMotorAkp(){
  return String(kpA,3);
}


String setMotorAki(float ki){
  if(!pidMode){
    setKI_A(ki);
    kiA = getKI_A();
    return "1";
  }
  else return "0";
}
String sendMotorAki(){
  return String(kiA,3);
}


String setMotorAkd(float kd){
  if(!pidMode){
    setKD_A(kd);
    kdA = getKD_A();
    return "1"; 
  }
  else return "0";
}
String sendMotorAkd(){
  return String(kdA,3);
}


String setMotorBkp(float kp){
  if(!pidMode){
    setKP_B(kp);
    kpB = getKP_B();
    return "1";
  }
  else return "0";
}
String sendMotorBkp(){
  return String(kpB,3);
}


String setMotorBki(float ki){
  if(!pidMode){
    setKI_B(ki);
    kiB = getKI_B();
    return "1"; 
  }
  else return "0";
}
String sendMotorBki(){
  return String(kiB,3);
}


String setMotorBkd(float kd){
  if(!pidMode){
    setKD_B(kd);
    kdB = getKD_B();
    return "1";
  }
  else return "0";
}
String sendMotorBkd(){
  return String(kdB,3);
}


String setI2Caddress(int address){
  if(!pidMode){
    setI2CADDRESS(address);
    i2cAddress = getI2CADDRESS();
    Wire.begin(i2cAddress);                
    return "1";
  }
  else return "0";
}
String sendI2Caddress(){
  return String(i2cAddress);
}


String resetEEPROM(){
  if(!pidMode){
    setFIRST_TIME(0);
//    return String(getFIRST_TIME()); 
    return "1";
  }
  else return "0";
}
///////////////////////////////////////////
















/////////////////////////////////////////////
//#include <Wire.h>
//void setup()
//{
//  Wire.begin(4);                
//  Wire.onReceive(i2cSlaveReceiveData);
//  Wire.onRequest(i2cSlaveSendData);
//}



/////////////// I2C COMMUNICATION /////////////////

String i2c_msg = "";

void i2cSlaveSendData(){
  String msg = "";
  if (i2c_msg != ""){
    msg = i2c_msg;
    i2c_msg = "";
  }
  else {
    msg = "0";
    i2c_msg = "";
  }
  char charArray[msg.length() + 1];
  msg.toCharArray(charArray, msg.length() + 1);
  Wire.write(charArray, msg.length());                
}



String i2cMsg = "", i2cMsgBuffer, i2cDataBuffer[3];

void i2cSlaveReceiveData(int dataSizeInBytes){
  int indexPos = 0, i=0;
 
  for(int i=0; i<dataSizeInBytes; i+=1){
    char c = Wire.read();
    i2cMsg += c;   
  }
  
  i2cMsg.trim();
  
  if (i2cMsg != "") {
    do {
      indexPos = i2cMsg.indexOf(',');
      if (indexPos != -1) {
        i2cMsgBuffer = i2cMsg.substring(0, indexPos);
        i2cMsg = i2cMsg.substring(indexPos + 1, i2cMsg.length());
        i2cDataBuffer[i] = i2cMsgBuffer;
        i2cMsgBuffer = "";
      }
      else {
        if (i2cMsg.length() > 0)
          i2cDataBuffer[i] = i2cMsg;
      }
      i += 1;
     } while (indexPos >= 0);
  }

  
  if(i2cDataBuffer[0] == "pos"){
    i2c_msg = sendMotorsPos();
  } 
  
  else if (i2cDataBuffer[0] == "vel") {
    i2c_msg = sendMotorsVel();
  }
  
  else if (i2cDataBuffer[0] == "pwm") {
    i2c_msg = setMotorsPwm(constrain(i2cDataBuffer[1].toInt(), -255, 255), constrain(i2cDataBuffer[2].toInt(), -255, 255));
  }

  else if (i2cDataBuffer[0] == "tag") {
    i2c_msg = setMotorsTarget(i2cDataBuffer[1].toFloat(), i2cDataBuffer[2].toFloat());
  }

  else if (i2cDataBuffer[0] == "mode") {
    if (i2cDataBuffer[1]=="") i2c_msg = sendPidMode();
    else i2c_msg = setPidMode(i2cDataBuffer[1].toInt());
  }

  
  i2cMsg = "";
  i2cMsgBuffer = "";
  i2cDataBuffer[0] = "";
  i2cDataBuffer[1] = "";
  i2cDataBuffer[3] = "";
}

/////////////////////////////////////////////////////////



























///////////////// SERIAL COMMUNICATION //////////////////////
String ser_msg = "";

String serMsg = "", serMsgBuffer, serDataBuffer[3];

void serialReceiveAndSendData() {
  int indexPos = 0, i = 0;

  if (Serial.available() > 0) {
    while (Serial.available())
    {
      // if (Serial.available() > 0)
      // {
      //   char c = Serial.read();  //gets one byte from serial buffer
      //   msg += c; //makes the string readString
      // }
      serMsg = Serial.readString();
    }
    serMsg.trim();
    if (serMsg != "") {
      do {
        indexPos = serMsg.indexOf(',');
        if (indexPos != -1) {
          serMsgBuffer = serMsg.substring(0, indexPos);
          serMsg = serMsg.substring(indexPos + 1, serMsg.length());
          serDataBuffer[i] = serMsgBuffer;
          serMsgBuffer = "";
        }
        else {
          if (serMsg.length() > 0)
            serDataBuffer[i] = serMsg;
        }
        i += 1;
      } while (indexPos >= 0);
    }


    if (serDataBuffer[0] != ""){
      if(serDataBuffer[0] == "pos"){
        ser_msg = sendMotorsPos();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "vel") {
        ser_msg = sendMotorsVel();
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "tick") {
        ser_msg = sendMotorsTick();
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "freq") {
        ser_msg = sendMotorsFreq();
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "dataA") {
        ser_msg = sendMotorAData();
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "dataB") {
        ser_msg = sendMotorBData();
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "pwm") {
        ser_msg = setMotorsPwm(constrain(serDataBuffer[1].toInt(), -255, 255), constrain(serDataBuffer[2].toInt(), -255, 255));
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "tag") {
        ser_msg = setMotorsTarget(serDataBuffer[1].toFloat(), serDataBuffer[2].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "mode") {
        if (serDataBuffer[1]=="") ser_msg = sendPidMode();
        else ser_msg = setPidMode(serDataBuffer[1].toInt());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "pprA") {
        if (serDataBuffer[1]=="") ser_msg = sendEncAppr();
        else ser_msg = setEncAppr(serDataBuffer[1].toInt());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "pprB") {
        if (serDataBuffer[1]=="") ser_msg = sendEncBppr();
        else ser_msg = setEncBppr(serDataBuffer[1].toInt());
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "kpA") {
        if (serDataBuffer[1]=="") ser_msg = sendMotorAkp();
        else ser_msg = setMotorAkp(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "kiA") {
        if (serDataBuffer[1]=="") ser_msg = sendMotorAki();
        else ser_msg = setMotorAki(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "kdA") {
        if (serDataBuffer[1]=="") ser_msg = sendMotorAkd();
        else ser_msg = setMotorAkd(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }

      else if (serDataBuffer[0] == "kpB") {
        if (serDataBuffer[1]=="") ser_msg = sendMotorBkp();
        else ser_msg = setMotorBkp(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "kiB") {
        if (serDataBuffer[1]=="") ser_msg = sendMotorBki();
        else ser_msg = setMotorBki(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "kdB") {
        if (serDataBuffer[1]=="") ser_msg = sendMotorBkd();
        else ser_msg = setMotorBkd(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
    
      else if (serDataBuffer[0] == "i2c") {
        if (serDataBuffer[1]=="") ser_msg = sendI2Caddress();
        else ser_msg = setI2Caddress(constrain(serDataBuffer[1].toInt(), 0, 127));
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
      else if (serDataBuffer[0] == "reset") {
        ser_msg = resetEEPROM();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      
    } else {
      ser_msg = "0";
      Serial.println(ser_msg);
      ser_msg = "";
    }
  }
  
  serMsg = "";
  serMsgBuffer = "";
  serDataBuffer[0] = "";
  serDataBuffer[1] = "";
  serDataBuffer[3] = "";
}
//////////////////////////////////////////////////////////////////////////
