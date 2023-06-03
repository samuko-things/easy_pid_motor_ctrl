#include <Wire.h>

///////// DIFFERENT TASK FOR SERIAL AND I2C COMMUNICATION //////////
String sendMotorATick(){
  return String(encA.tickCount);
}
String sendMotorBTick(){
  return String(encB.tickCount);
}
String sendMotorAFreq(){
  return String(encA.frequency, 4);
}
String sendMotorBFreq(){
  return String(encB.frequency, 4);
}

String sendMotorAPos(){
  return String(encA.getAngPos(), 4);
}
String sendMotorBPos(){
  return String(encB.getAngPos(), 4);
}
String sendMotorAVel(){
  return String(encA.getAngVel(), 4);
}
String sendMotorBVel(){
  return String(encB.getAngVel(), 4);
}


String setMotorAPwm(int val){
  if(!pidMode){
    motorA.sendPWM(val);
    return String(val);
  }
  else return "false";
  
}
String setMotorBPwm(int val){
  if(!pidMode){
    motorB.sendPWM(val);
    return String(val);
  }
  else return "false";
}
String setMotorATarget(float val){
  if(pidMode){
    targetA = val;
    return String(val, 4);
  }
  else return "false";
  
}
String setMotorBTarget(float val){
  if (pidMode){
    targetB = val;
    return String(val, 4);
  }
  else return "false";
  
}


//String setMotorPwm(int valA, int valB){
//  motorA.sendPWM(valA);
//  motorB.sendPWM(valB);
//  return "true";
//}
//String setMotorTarget(float valA, float valB){
//  targetA = valA;
//  targetB = valB;
//  return "true";
//}


String setPidMode(int mode){
  if(mode == 0){
    pidMode = false;
    motorA.sendPWM(0);
    motorB.sendPWM(0);
    targetA = 0.00;
    targetB = 0.00;
    return "true";
  } else if (mode == 1) {
    pidMode = true;
    motorA.sendPWM(0);
    motorB.sendPWM(0);
    targetA = 0.00;
    targetB = 0.00;
    return "true";
  }
  else {
    return "false";
  }
}





String setEncAppr(int ppr){
  if(!pidMode){
    setPPR_A(ppr);
    encA_ppr = getPPR_A();
    return String(encA_ppr);
  }
  else return "false";
  
}

String setEncBppr(int ppr){
  if(!pidMode){
    setPPR_B(ppr);
    encB_ppr = getPPR_B();
    return String(encB_ppr);
  }
  else return "false";
}



String setMotorAkp(float kp){
  if(!pidMode){
    setKP_A(kp);
    kpA = getKP_A();
    return String(kpA, 2);
  }
  else return "false";
}

String setMotorAki(float ki){
  if(!pidMode){
    setKI_A(ki);
    kiA = getKI_A();
    return String(kiA, 2);
  }
  else return "false";
}

String setMotorAkd(float kd){
  if(!pidMode){
    setKD_A(kd);
    kdA = getKD_A();
    return String(kdA, 2); 
  }
  else return "false";
}




String setMotorBkp(float kp){
  if(!pidMode){
    setKP_B(kp);
    kpB = getKP_B();
    return String(kpB, 2);
  }
  else return "false";
}

String setMotorBki(float ki){
  if(!pidMode){
    setKI_B(ki);
    kiB = getKI_B();
    return String(kiB, 2); 
  }
  else return "false";
}

String setMotorBkd(float kd){
  if(!pidMode){
    setKD_B(kd);
    kdB = getKD_B();
    return String(kdB, 2);
  }
  else return "false";
}


String setI2Caddress(int address){
  if(!pidMode){
    setI2CADDRESS(address);
    i2cAddress = getI2CADDRESS();
    Wire.begin(i2cAddress);                
    return String(i2cAddress);
  }
  else return "false";
}


String resetEEPROM(){
  if(!pidMode){
    setFIRST_TIME(0);
    return String(getFIRST_TIME()); 
  }
  else return "false";
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
    msg = "false";
  }
  char charArray[10];
  msg.toCharArray(charArray, msg.length() + 1);
  Wire.write(charArray, msg.length());                
}



String i2cMsg = "", i2cMsgBuffer, i2cDataBuffer[2];

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
  
  if(i2cDataBuffer[0] == "posA"){
    i2c_msg = sendMotorAPos();
  }
  else if (i2cDataBuffer[0] == "posB") {
    i2c_msg = sendMotorBPos();
  }
  
  else if (i2cDataBuffer[0] == "velA") {
    i2c_msg = sendMotorAVel();
  }
  else if (i2cDataBuffer[0] == "velB") {
    i2c_msg = sendMotorBVel();
  }
  
  else if (i2cDataBuffer[0] == "pwmA") {
    i2c_msg = setMotorAPwm(constrain(i2cDataBuffer[1].toInt(), 0, 255));
  }
  else if (i2cDataBuffer[0] == "pwmB") {
    i2c_msg = setMotorBPwm(constrain(i2cDataBuffer[1].toInt(), 0, 255));
  }
  
  else if (i2cDataBuffer[0] == "tagA") {
    i2c_msg = setMotorATarget(i2cDataBuffer[1].toFloat());
  }
  else if (i2cDataBuffer[0] == "tagB") {
    i2c_msg = setMotorBTarget(i2cDataBuffer[1].toFloat());
  }
  
//  else if (i2cDataBuffer[0] == "pwm") {
//    i2c_msg = setMotorPwm(constrain(i2cDataBuffer[1].toInt(), 0, 255), constrain(i2cDataBuffer[2].toInt(), 0, 255));
//  }
//  else if (i2cDataBuffer[0] == "tag") {
//    i2c_msg = setMotorTarget(i2cDataBuffer[1].toFloat(), i2cDataBuffer[2].toFloat());
//  }

  else if (i2cDataBuffer[0] == "mode") {
    i2c_msg = setPidMode(i2cDataBuffer[1].toInt());
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
      if(serDataBuffer[0] == "posA"){
        ser_msg = sendMotorAPos();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "posB") {
        ser_msg = sendMotorBPos();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "velA") {
        ser_msg = sendMotorAVel();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "velB") {
        ser_msg = sendMotorBVel();
        Serial.println(ser_msg);
        ser_msg = "";
      }



      else if (serDataBuffer[0] == "tickA") {
        ser_msg = sendMotorATick();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "tickB") {
        ser_msg = sendMotorBTick();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "freqA") {
        ser_msg = sendMotorAFreq();
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "freqB") {
        ser_msg = sendMotorBFreq();
        Serial.println(ser_msg);
        ser_msg = "";
      }


      
      else if (serDataBuffer[0] == "pwmA") {
        ser_msg = setMotorAPwm(constrain(serDataBuffer[1].toInt(), 0, 255));
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "pwmB") {
        ser_msg = setMotorBPwm(constrain(serDataBuffer[1].toInt(), 0, 255));
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "tagA") {
        ser_msg = setMotorATarget(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "tagB") {
        ser_msg = setMotorBTarget(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
//      else if (serDataBuffer[0] == "pwm") {
//        ser_msg = setMotorPwm(constrain(serDataBuffer[1].toInt(), 0, 255), constrain(serDataBuffer[2].toInt(), 0, 255));
//        Serial.println(ser_msg);
//        ser_msg = "";
//      }
//      else if (serDataBuffer[0] == "tag") {
//        ser_msg = setMotorTarget(serDataBuffer[1].toFloat(), serDataBuffer[2].toFloat());
//        Serial.println(ser_msg);
//        ser_msg = "";
//      }

      else if (serDataBuffer[0] == "mode") {
        ser_msg = setPidMode(serDataBuffer[1].toInt());
        Serial.println(ser_msg);
        ser_msg = "";
      }

      
      else if (serDataBuffer[0] == "pprA") {
        ser_msg = setEncAppr(serDataBuffer[1].toInt());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "pprB") {
        ser_msg = setEncBppr(serDataBuffer[1].toInt());
        Serial.println(ser_msg);
        ser_msg = "";
      }

    
      else if (serDataBuffer[0] == "kpA") {
        ser_msg = setMotorAkp(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "kiA") {
        ser_msg = setMotorAki(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "kdA") {
        ser_msg = setMotorAkd(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }

    
      else if (serDataBuffer[0] == "kpB") {
        ser_msg = setMotorBkp(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "kiB") {
        ser_msg = setMotorBki(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "kdB") {
        ser_msg = setMotorBkd(serDataBuffer[1].toFloat());
        Serial.println(ser_msg);
        ser_msg = "";
      }

    
      else if (serDataBuffer[0] == "i2c") {
        ser_msg = setI2Caddress(constrain(serDataBuffer[1].toInt(), 0, 127));
        Serial.println(ser_msg);
        ser_msg = "";
      }
      else if (serDataBuffer[0] == "reset") {
        ser_msg = resetEEPROM();
        Serial.println(ser_msg);
        ser_msg = "";
      }
    } else {
      Serial.println("false");
    }
  }
  
  serMsg = "";
  serMsgBuffer = "";
  serDataBuffer[0] = "";
  serDataBuffer[1] = "";
  serDataBuffer[3] = "";
}
//////////////////////////////////////////////////////////////////////////
