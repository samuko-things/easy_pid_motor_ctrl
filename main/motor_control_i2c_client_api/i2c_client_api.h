#include <Wire.h>

class I2CAPI {
public:
  I2CAPI (int slave_addr){
    slaveAddr = slave_addr;
  }
  
  float get(String cmd_route){
    masterSendData(cmd_route);
    String data = masterReceiveData();
    return data.toFloat();
  }
  
  bool send(String cmd_route, float val){
    String msg_buffer = "";
    
    msg_buffer += cmd_route;
    msg_buffer += ",";
    msg_buffer += String(val,2);
    
    masterSendData(msg_buffer);
    String data = masterReceiveData();
    
    if (data == "true") return true;
    else if (data == "false") return false;
  }
  
//  bool send(String cmd_route, float valA, float valB){
//    String msg_buffer = "";
//    
//    msg_buffer += cmd_route;
//    msg_buffer += ",";
//    msg_buffer += String(valA,2);
//    msg_buffer += ",";
//    msg_buffer += String(valB,2);
//    
//    masterSendData2(msg_buffer);
//    String data = masterReceiveData();
//    
//    if (data == "true") return true;
//    else if (data == "false") return false;
//  }

private:
  int slaveAddr;

  void masterSendData(String i2c_msg){
    char charArray[10];
    i2c_msg.toCharArray(charArray, i2c_msg.length() + 1);

    Wire.beginTransmission(slaveAddr); 
    Wire.write(charArray, i2c_msg.length());                
    Wire.endTransmission();
  }
  
  
  void masterSendData2(String i2c_msg){
    char charArray[20];
    i2c_msg.toCharArray(charArray, i2c_msg.length() + 1);

    Wire.beginTransmission(slaveAddr); 
    Wire.write(charArray, i2c_msg.length());                
    Wire.endTransmission();
  }



  String masterReceiveData()
  {
    String i2c_msg = "";
    Wire.requestFrom(slaveAddr,10);
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
