
///////// DIFFERENT TASK FOR SERIAL COMMUNICATION //////////
void sendMotorAPos(){
  Serial.println(encA.getAngPos(),4);
}
void sendMotorAVel(){
  Serial.println(encA.getAngVel(),4);
}
void sendMotorAEncFreq(){
  Serial.println(encA.frequency,4);
}
void sendMotorATickCount(){
  Serial.println(encA.tickCount);
}


void sendMotorBPos(){
  Serial.println(encB.getAngPos(),4);
}
void sendMotorBVel(){
  Serial.println(encB.getAngVel(),4);
}
void sendMotorBEncFreq(){
  Serial.println(encB.frequency,4);
}
void sendMotorBTickCount(){
  Serial.println(encB.tickCount);
}




void sendBothMotorData(){
  Serial.print(encA.getAngPos(),4);
  Serial.print(",");
  Serial.print(encA.getAngVel(),4);
  Serial.print(",");
  Serial.print(encB.getAngPos(),4);
  Serial.print(",");
  Serial.println(encB.getAngVel(),4);
}

void sendMotorAData(){
  Serial.print(encA.getAngPos(),4);
  Serial.print(",");
  Serial.println(encA.getAngVel(),4);
}

void sendMotorBData(){
  Serial.print(encB.getAngPos(),4);
  Serial.print(",");
  Serial.println(encB.getAngVel(),4);
}

void sendFullMotorAData(){
  Serial.print(encA.tickCount);
  Serial.print(",");
  Serial.print(encA.getAngPos(),4);
  Serial.print(",");
  Serial.print(encA.frequency,4);
  Serial.print(",");
  Serial.println(encA.getAngVel(),4);
}

void sendFullMotorBData(){
  Serial.print(encB.tickCount);
  Serial.print(",");
  Serial.print(encB.getAngPos(),4);
  Serial.print(",");
  Serial.print(encB.frequency,4);
  Serial.print(",");
  Serial.println(encB.getAngVel(),4);
}




void receiveMotorAPwm(int val){
  motorA.sendPWM(val);
  Serial.println('1');
}
void receiveMotorBPwm(int val){
  motorB.sendPWM(val);
  Serial.println('1');
}

void receiveBothMotorPwm(int valA, int valB){
  motorB.sendPWM(valA);
  motorB.sendPWM(valB);
  Serial.println('1');
}




void receiveMotorATargetVal(float val){
  targetA = val;
//  Serial.println('1');
  Serial.println(val, 4);
}

void receiveMotorBTargetVal(float val){
  targetB = val;
//  Serial.println('1');
  Serial.println(val, 4);
}

void receiveBothMotorTargetVals(float valA, float valB){
  targetA = valA;
  targetB = valB;
  Serial.println('1');
}
///////////////////////////////////////////////////////




///////////// API for updating EEPROM Parameters //////////////

void setEncAppr(int ppr){
  if(!pidMode){
    setPPR_A(ppr);
    encA_ppr = getPPR_A();
    Serial.println(encA_ppr);
  }
  else Serial.println(-1);
  
}

void setEncBppr(int ppr){
  if(!pidMode){
    setPPR_B(ppr);
    encB_ppr = getPPR_B();
    Serial.println(encB_ppr);
  }
  else Serial.println(-1);
}



void setMotorAkp(float kp){
  if(!pidMode){
    setKP_A(kp);
    kpA = getKP_A();
    Serial.println(kpA, 2);
  }
  else Serial.println(-1);
}

void setMotorAki(float ki){
  if(!pidMode){
    setKI_A(ki);
    kiA = getKI_A();
    Serial.println(kiA, 2);
  }
  else Serial.println(-1);
}

void setMotorAkd(float kd){
  if(!pidMode){
    setKD_A(kd);
    kdA = getKD_A();
    Serial.println(kdA, 2); 
  }
  else Serial.println(-1);
}




void setMotorBkp(float kp){
  if(!pidMode){
    setKP_B(kp);
    kpB = getKP_B();
    Serial.println(kpB, 2);
  }
  else Serial.println(-1);
}

void setMotorBki(float ki){
  if(!pidMode){
    setKI_B(ki);
    kiB = getKI_B();
    Serial.println(kiB, 2); 
  }
  else Serial.println(-1);
}

void setMotorBkd(float kd){
  if(!pidMode){
    setKD_B(kd);
    kdB = getKD_B();
    Serial.println(kdB, 2);
  }
  else Serial.println(-1);
}




void setPIDmode(int pidmode){
  if(pidmode == 0){
    pidMode = false;
    Serial.println(0);
  } else if (pidmode == 1) {
    pidMode = true;
    Serial.println(1);
  }
}

void setI2Caddress(int address){
  if(!pidMode){
    setI2CADDRESS(address);
    i2cAddress = getI2CADDRESS();
    Serial.println(i2cAddress);
  }
  else Serial.println(-1);
}


void resetEEPROM(){
  if(!pidMode){
    setFIRST_TIME(0);
    Serial.println(getFIRST_TIME()); 
  }
  else Serial.println(-1);
}

///////////////////////////////////////////////////////









///////////////// SERIAL COMMUNICATION API //////////////////////
String msg = "", msgBuffer, dataBuffer[3];

void serialGetReqSendRes() {
  int indexPos = 0, i = 0;

  if (Serial.available() > 0) {
    while (Serial.available())
    {
      // if (Serial.available() > 0)
      // {
      //   char c = Serial.read();  //gets one byte from serial buffer
      //   msg += c; //makes the string readString
      // }
      msg = Serial.readString();
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

    // Serial.println(dataBuffer[0]);
    // Serial.println("val = "+dataBuffer[1]);

    if (dataBuffer[0] != ""){
      if (dataBuffer[0]=="all") sendBothMotorData();
      else if (dataBuffer[0]=="allA") sendMotorAData();
      else if (dataBuffer[0]=="allB") sendMotorBData();
      else if (dataBuffer[0]=="ALLA") sendFullMotorAData();
      else if (dataBuffer[0]=="ALLB") sendFullMotorBData();

      else if (dataBuffer[0]=="pwm") receiveBothMotorPwm(constrain(dataBuffer[1].toInt(), 0, 255),constrain(dataBuffer[2].toInt(), 0, 255));
      else if (dataBuffer[0]=="pwmA") receiveMotorAPwm(constrain(dataBuffer[1].toInt(), 0, 255));
      else if (dataBuffer[0]=="pwmB") receiveMotorBPwm(constrain(dataBuffer[1].toInt(), 0, 255));

      else if (dataBuffer[0]=="val") receiveBothMotorTargetVals(dataBuffer[1].toFloat(), dataBuffer[2].toFloat());
      else if (dataBuffer[0]=="valA") receiveMotorATargetVal(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="valB") receiveMotorBTargetVal(dataBuffer[1].toFloat());

      else if (dataBuffer[0]=="pprA") setEncAppr(dataBuffer[1].toInt());
      else if (dataBuffer[0]=="pprB") setEncBppr(dataBuffer[1].toInt());

      else if (dataBuffer[0]=="kpA") setMotorAkp(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="kiA") setMotorAki(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="kdA") setMotorAkd(dataBuffer[1].toFloat());

      else if (dataBuffer[0]=="kpB") setMotorBkp(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="kiB") setMotorBki(dataBuffer[1].toFloat());
      else if (dataBuffer[0]=="kdB") setMotorBkd(dataBuffer[1].toFloat());

      else if (dataBuffer[0]=="pid") setPIDmode(dataBuffer[1].toInt());
      else if (dataBuffer[0]=="i2c") setI2Caddress(dataBuffer[1].toInt());

      else if (dataBuffer[0]=="reset") resetEEPROM();
    }

  }

  msg = "";
  msgBuffer = "";
  dataBuffer[0] = "";
  dataBuffer[1] = "";
  dataBuffer[3] = "";
}
//////////////////////////////////////////////////////////////////////////
