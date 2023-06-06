
// i2c master uno
#include <Wire.h>


class MotorI2cClient {
public:
  MotorI2cClient (int slave_addr){
    slaveAddr = slave_addr;
  }
  
  void getParam(String cmd_route, float &paramVal){
    masterSendData(cmd_route);
    String data = masterReceiveData();
    paramVal = data.toFloat();
  }

  void get(String cmd_route, float &valA, float &valB){
    masterSendData(cmd_route);
    dataMsg = masterReceiveDataLarge();
    
    int indexPos = 0, i=0;
    do {
      indexPos = dataMsg.indexOf(',');
      if (indexPos != -1) {
        dataMsgBuffer = dataMsg.substring(0, indexPos);
        dataMsg = dataMsg.substring(indexPos + 1, dataMsg.length());
        dataBuffer[i] = dataMsgBuffer;
        dataMsgBuffer = "";
      }
      else {
        if (dataMsg.length() > 0)
          dataBuffer[i] = dataMsg;
      }
      i += 1;
     } while (indexPos >= 0);

    valA = dataBuffer[0].toFloat();
    valB = dataBuffer[1].toFloat();

    dataMsg = "";
    dataMsgBuffer = "";
    dataBuffer[0] = "";
    dataBuffer[1] = "";
  }
  
  bool sendParam(String cmd_route, float val){
    
    String msg_buffer = cmd_route;
    msg_buffer += ",";
    msg_buffer += String(val,2);
    
    masterSendData(msg_buffer);
    String data = masterReceiveDataChar();
    if (data == "1") return true;
    else return false;
  }

  bool send(String cmd_route, float valA, float valB){
    
    String msg_buffer = cmd_route;
    msg_buffer += ",";
    msg_buffer += String(valA,3);
    msg_buffer += ",";
    msg_buffer += String(valB,3);
    
    masterSendData(msg_buffer);
    String data = masterReceiveDataChar();
    if (data == "1") return true;
    else return false;
  }

private:
  int slaveAddr;
  String dataMsg = "", dataMsgBuffer = "", dataBuffer[2];

  void masterSendData(String i2c_msg){
    char charArray[i2c_msg.length() + 1];
    i2c_msg.toCharArray(charArray, i2c_msg.length() + 1);

    Wire.beginTransmission(slaveAddr); 
    Wire.write(charArray, i2c_msg.length());                
    Wire.endTransmission();
  }


  String masterReceiveData()
  {
    String i2c_msg = "";
    Wire.requestFrom(slaveAddr,15);
    while(Wire.available()){
      char c = Wire.read();
      i2c_msg += c;   
    }
    int indexPos = i2c_msg.indexOf((char)255);
    if (indexPos != -1) {
      return i2c_msg.substring(0, indexPos);
    }
    return i2c_msg;
  }

  String masterReceiveDataLarge()
  {
    String i2c_msg = "";
    Wire.requestFrom(slaveAddr,30);
    while(Wire.available()){
      char c = Wire.read();
      i2c_msg += c;   
    }
    int indexPos = i2c_msg.indexOf((char)255);
    if (indexPos != -1) {
      return i2c_msg.substring(0, indexPos);
    }
    return i2c_msg;
  }


  String masterReceiveDataChar()
  {
    String i2c_msg = "";
    Wire.requestFrom(slaveAddr,1);
    while(Wire.available()){
      char c = Wire.read();
      i2c_msg += c;   
    }
    int indexPos = i2c_msg.indexOf((char)255);
    if (indexPos != -1) {
      return i2c_msg.substring(0, indexPos);
    }
    return i2c_msg;
  }
  
};
