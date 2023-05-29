

///////////////////////////////////////////////////////////////////////////////
// store encoder pulsePerRev needed by encoder
int encA_ppr = 0;
int encB_ppr = 0;

// motorA pid control global params needed by pid
float kpA = 0.0, kiA = 0.0, kdA = 0.0;
float outMinA = -255.0, outMaxA = 255.0;
float targetA = 0.00;
float outputA;

// motorB pid control global params needed by pid
float kpB = 0.0, kiB = 0.0, kdB = 0.0;
float outMinB = -255.0, outMaxB = 255.0;
float targetB = 0.00;
float outputB;

// check if in PID or PWM mode
int pidMode = 0; // true-PID, false-PWM

// initial i2cAddress
int i2cAddress = 0;

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
int PIDMODE_ADDRESS = 32;
int I2C_ADDRESS = 36;
int FIRST_TIME_ADDRESS = 40;



void setKP_A(float kpA){
  EEPROM.put(KP_A_ADDRESS, kpA);
}
float getKP_A(){
  float kpA;
  EEPROM.get(KP_A_ADDRESS, kpA);
  return kpA;
}


void setKP_B(float kpB){
  EEPROM.put(KP_B_ADDRESS, kpB);
}
float getKP_B(){
  float kpB;
  EEPROM.get(KP_B_ADDRESS, kpB);
  return kpB;
}



void setKI_A(float kiA){
  EEPROM.put(KI_A_ADDRESS, kiA);
}
float getKI_A(){
  float kiA;
  EEPROM.get(KI_A_ADDRESS, kiA);
  return kiA;
}



void setKI_B(float kiB){
  EEPROM.put(KI_B_ADDRESS, kiB);
}
float getKI_B(){
  float kiB;
  EEPROM.get(KI_B_ADDRESS, kiB);
  return kiB;
}



void setKD_A(float kdA){
  EEPROM.put(KD_A_ADDRESS, kdA);
}
float getKD_A(){
  float kdA;
  EEPROM.get(KD_A_ADDRESS, kdA);
  return kdA;
}



void setKD_B(float kdB){
  EEPROM.put(KD_B_ADDRESS, kdB);
}
float getKD_B(){
  float kdB;
  EEPROM.get(KD_B_ADDRESS, kdB);
  return kdB;
}




void setPPR_A(int pprA){
  EEPROM.put(PPR_A_ADDRESS, pprA);
}
int getPPR_A(){
  int pprA;
  EEPROM.get(PPR_A_ADDRESS, pprA);
  return pprA;
}


void setPPR_B(int pprB){
  EEPROM.put(PPR_B_ADDRESS, pprB);
}
int getPPR_B(){
  int pprB;
  EEPROM.get(PPR_B_ADDRESS, pprB);
  return pprB;
}



void setPIDMODE(int pidMode){
  EEPROM.put(PIDMODE_ADDRESS, pidMode);
}
int getPIDMODE(){
  int pidMode;
  EEPROM.get(PIDMODE_ADDRESS, pidMode);
  return pidMode;
}



void setI2CADDRESS(int i2cAddress){
  EEPROM.put(I2C_ADDRESS, i2cAddress);
}
int getI2CADDRESS(){
  int i2cAddress;
  EEPROM.put(I2C_ADDRESS, i2cAddress);
  return i2cAddress;
}


void setFIRST_TIME(int val){
  EEPROM.put(FIRST_TIME_ADDRESS, val);
}
int getFIRST_TIME(){
  int firstTime;
  EEPROM.put(I2C_ADDRESS, firstTime);
  return firstTime;
}




void resetAllParamsToZero(){
  setKP_A(0.00);
  setKP_B(0.00);

  setKI_A(0.00);
  setKI_B(0.00);

  setKD_A(0.00);
  setKD_B(0.00);

  setKP_A(0.00);
  setKP_B(0.00);
  
  setPPR_A(0);
  setPPR_B(0);

  setPIDMODE(0);

  setI2CADDRESS(0);
}


void initEEPROMparamsStorage(){
  int isFirstTime, val = 11111;
  isFirstTime = getFIRST_TIME();
  if(isFirstTime != val){ //if not equal to 11111
    setFIRST_TIME(val);
    resetAllParamsToZero();
    Serial.println("setting up eeprom for the first time");
  }
  else{
    Serial.println("no need for first time eeprom setup");
  }
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

  pidMode = getPIDMODE();

  i2cAddress = getI2CADDRESS();

}
/////////////////////////////////////////////////////////////
