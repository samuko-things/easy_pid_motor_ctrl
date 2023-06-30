/////////////////// STORING AND READING PARAMETERS FROM EEPROM /////////////////
#include <EEPROM.h>

int KP_A_ADDRESS = 0;
int KP_B_ADDRESS = 4;
int KI_A_ADDRESS = 8;
int KI_B_ADDRESS = 12;
int KD_A_ADDRESS = 16;
int KD_B_ADDRESS = 20;
int PPR_A_ADDRESS = 24;
int PPR_B_ADDRESS = 28;
int I2C_ADDRESS = 32;
int FIRST_TIME_ADDRESS = 36;
//int PIDMODE_ADDRESS = 40;



float getKP_A(){
  float KpA;
  EEPROM.get(KP_A_ADDRESS, KpA);
  return KpA;
}
void setKP_A(float KpA){
  EEPROM.put(KP_A_ADDRESS, KpA);
  kpA = getKP_A();
  pidMotorA.setKp(kpA);
}


float getKP_B(){
  float KpB;
  EEPROM.get(KP_B_ADDRESS, KpB);
  return KpB;
}
void setKP_B(float KpB){
  EEPROM.put(KP_B_ADDRESS, KpB);
  kpB = getKP_B();
  pidMotorB.setKp(kpB);
}



float getKI_A(){
  float KiA;
  EEPROM.get(KI_A_ADDRESS, KiA);
  return KiA;
}
void setKI_A(float KiA){
  EEPROM.put(KI_A_ADDRESS, KiA);
  kiA = getKI_A();
  pidMotorA.setKi(kiA);
}



float getKI_B(){
  float KiB;
  EEPROM.get(KI_B_ADDRESS, KiB);
  return KiB;
}
void setKI_B(float KiB){
  EEPROM.put(KI_B_ADDRESS, KiB);
  kiB = getKI_B();
  pidMotorB.setKi(kiB);
}



float getKD_A(){
  float KdA;
  EEPROM.get(KD_A_ADDRESS, KdA);
  return KdA;
}
void setKD_A(float KdA){
  EEPROM.put(KD_A_ADDRESS, KdA);
  kdA = getKD_A();
  pidMotorA.setKd(kdA);
}



float getKD_B(){
  float KdB;
  EEPROM.get(KD_B_ADDRESS, KdB);
  return KdB;
}
void setKD_B(float KdB){
  EEPROM.put(KD_B_ADDRESS, KdB);
  kdB = getKD_B();
  pidMotorB.setKd(kdB);
}


int getPPR_A(){
  float pprA;
  EEPROM.get(PPR_A_ADDRESS, pprA);
  return (int)pprA;
}
void setPPR_A(int pprA){
  EEPROM.put(PPR_A_ADDRESS, (float)pprA);
  encA_ppr = getPPR_A();
  encA.setPulsePerRev(encA_ppr);
}


int getPPR_B(){
  float pprB;
  EEPROM.get(PPR_B_ADDRESS, pprB);
  return (int)pprB;
}
void setPPR_B(int pprB){
  EEPROM.put(PPR_B_ADDRESS, (float)pprB);
  encB_ppr = getPPR_B();
  encB.setPulsePerRev(encB_ppr);
}


int getI2CADDRESS(){
  float address;
  EEPROM.get(I2C_ADDRESS, address);
  return (int)address;
}
void setI2CADDRESS(int address){
  EEPROM.put(I2C_ADDRESS, (float)address);
  i2cAddress = getI2CADDRESS();
  Wire.begin(i2cAddress);
}


void setFIRST_TIME(int val){
  EEPROM.put(FIRST_TIME_ADDRESS, (float)val);
}
int getFIRST_TIME(){
  float firstTime;
  EEPROM.get(FIRST_TIME_ADDRESS, firstTime);
  return (int)firstTime;
}




//void setPIDMODE(int pidMode){
//  EEPROM.put(PIDMODE_ADDRESS, pidMode);
//}
//int getPIDMODE(){
//  int pidMode;
//  EEPROM.get(PIDMODE_ADDRESS, pidMode);
//  return pidMode;
//}




void resetAllParams(){
  setKP_A(0.00);
  setKP_B(0.00);

  setKI_A(0.00);
  setKI_B(0.00);

  setKD_A(0.00);
  setKD_B(0.00);

  setKP_A(0.00);
  setKP_B(0.00);
  
  setPPR_A(1);
  setPPR_B(1);

//  setPIDMODE(0);

  setI2CADDRESS(1);
}


void initEEPROMparamsStorage(){
  int isFirstTime, setupCode = 11111; // please do not change
  isFirstTime = getFIRST_TIME();
  if(isFirstTime != setupCode){ //if not equal to 11111
    setFIRST_TIME(setupCode);
    resetAllParams();
//    Serial.println("initializing eeprom for the first time");
  }
//  else{
////    Serial.println("eeprom has already been initialized");
//  }
}



void updateGlobalParamsFromEERPOM(){
  initEEPROMparamsStorage();

  kpA = getKP_A();
  kpB = getKP_B();

  kiA = getKI_A();
  kiB = getKI_B();

  kdA = getKD_A();
  kdB = getKD_B();

  encA_ppr = getPPR_A();
  encB_ppr = getPPR_B();

//  pidMode = getPIDMODE();

  i2cAddress = getI2CADDRESS();

}
/////////////////////////////////////////////////////////////
