#include <EEPROM.h>
void setup() {
  // put your setup code here, to run once:
  int KPA_POS_ADDR = 0;
  bool f = true, x = false;
  Serial.begin(115200);

  delay(1000);
  Serial.println(sizeof(f));
  EEPROM.put(KPA_POS_ADDR, f);
  EEPROM.put(4, x);

  delay(2000);
  int a, b;
  EEPROM.get(KPA_POS_ADDR, a);
  Serial.println(a);

  EEPROM.put(KPA_POS_ADDR, x);
  // EEPROM.get(4, b);

  EEPROM.get(KPA_POS_ADDR, b);
//  if(b != 1){
//    Serial.println("false");
//  }

  
  Serial.println(b);

//  Serial.println(EEPROM.length());

}

void loop() {
  // put your main code here, to run repeatedly:

}
