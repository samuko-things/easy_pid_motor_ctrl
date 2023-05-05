#include <EEPROM.h>
void setup() {
  // put your setup code here, to run once:
  int KPA_POS_ADDR = 0;
  float f = 0.7623, x = 0.0;
  Serial.begin(9600);

  delay(1000);
  Serial.println(sizeof(f));
  EEPROM.put(KPA_POS_ADDR, f);
  EEPROM.put(4, x);

  delay(2000);
  float a, b;
  EEPROM.get(KPA_POS_ADDR, a);
  // EEPROM.get(4, b);

  EEPROM.get(4, b);

  Serial.println(a,4);
  Serial.println(b,4);

  Serial.println(EEPROM.length());

}

void loop() {
  // put your main code here, to run repeatedly:

}
