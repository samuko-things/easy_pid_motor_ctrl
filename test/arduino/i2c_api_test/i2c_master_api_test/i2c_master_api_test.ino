
// i2c master uno
#include <Wire.h>


///////// my sepcial delay function ///////////////
void delayMs(int ms) {
  for (int i = 0; i < ms; i += 1) {
    delayMicroseconds(1000);
  }
}
//////////////////////////////////////////////////


class I2CAPI {
public:
  I2CAPI (int slave_addr){
    slaveAddr = slave_addr;
  }
  
  void get(String cmd_route, float &dataVal){
    masterSendData(cmd_route);
    dataMsg = masterReceiveData();
    dataVal = dataMsg.toFloat();
    dataMsg = "";
  }

  void get(String cmd_route, float (&dataArr)[2]){
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

    dataArr[0] = dataBuffer[0].toFloat();
    dataArr[1] = dataBuffer[1].toFloat();

    dataMsg = "";
    dataMsgBuffer = "";
    dataBuffer[0] = "";
    dataBuffer[1] = "";
  }
  
  bool send(String cmd_route, float val){
    
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
    msg_buffer += String(valA,2);
    msg_buffer += ",";
    msg_buffer += String(valB,2);
    
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

I2CAPI api(4);




unsigned long pidPrevTime, pidSampleTime = 1000; // in ms (i.e 1000/pidSampleTime in Hz)
bool toogle = true;

void setup()
{
  Wire.begin();                 
  Serial.begin(115200);

  delay(2000);

  bool mode = false;
  while (!mode){
    mode = api.send("mode", 0);
    Serial.println(mode);
  }
  
  pidPrevTime = millis();
  delay(2000);
}




void loop()
{
  bool isSuccessful;
  float val, valArr[2];
  
  for (int pwmVal = -250; pwmVal <= 255; pwmVal += 5) {
    isSuccessful = api.send("pwmA", pwmVal);
    api.get("velA", valArr[0]);

//    val2 = api.send("pwm", pwmVal, 0);
//    api.get("pos", valArr);
      Serial.println(valArr[0]);
    delayMs(10);
   }
  for (int pwmVal = 255; pwmVal >= -255; pwmVal -= 5) {
    isSuccessful = api.send("pwmA", pwmVal);
    api.get("velA", valArr[0]);

//    val2 = api.send("pwm", pwmVal, 0);
//    api.get("pos", valArr);
      Serial.println(valArr[0]);
    delayMs(10);
  }
//  if ((millis() - pidPrevTime) >= pidSampleTime) {
//    /* CODE SHOULD GO IN HERE*/
//
//    if (toogle){
//      String val2 = api.send("pwmA", 110);
//    Serial.println(val2);
//    toogle = false;
//    } else {
//      String val2 = api.send("pwmA", -110);
//    Serial.println(val2);
//    toogle = true;
//    }
//    
//
//    pidPrevTime = millis();
//  }
  
// val = api.get("posA");
}














//void setup()
//{
//  Wire.begin();                 
//  Serial.begin(115200);
//
//  
//}
//
//void loop()
//{
////  float val = api.get("posA");
////  //bool val = api.send("pwmA", 120);
////  Serial.println(val,4);
////  Serial.println();
// // masterSendData("val1");
//  // String info = masterReceiveData();
//  
//  //String info = getVal("val1");
//  
//  //Serial.println(info.length());
//  //Serial.println(info);
//  //Serial.println();
//  
//  delay(1000);
//  masterSendData("samuko");
//}
//
//
//
//
///////////////////////////////////////////////////////////
//String getVal(String cmd){
//  masterSendData(cmd);
//  return masterReceiveData();
//}
//
////////////////////////////////////////////////////////////
//
//void masterSendData(String msg){
//  char charArray[20];
//  msg.toCharArray(charArray, msg.length() + 1);
//  
//  Wire.beginTransmission(4); 
//  Wire.write(charArray, msg.length());                
//  Wire.endTransmission();
//}
//
//
//
//String masterReceiveData()
//{
//  String i2c_msg = "";
//  Wire.requestFrom(4,100);
//  while(Wire.available()){
//    char c = Wire.read();
//    i2c_msg += c; 	
//  }
//  int indexPos = i2c_msg.indexOf((char)255);
//  if (indexPos != -1) {
//    return i2c_msg.substring(0, indexPos);
//  }
//  return i2c_msg;
//}
//
/////////////////////////////////////////////////////////////
