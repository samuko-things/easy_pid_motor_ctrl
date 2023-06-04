#include <Wire.h>;



float round_dp(float val, int dp)
{
    if (val >= 0)
    {
        float rounded_val = (long)((val * pow(10, dp)) + 0.5);
        return (float)rounded_val / pow(10, dp);
    }
    else
    {
        float rounded_val = (long)((val * pow(10, dp)) - 0.5);
        return (float)rounded_val / pow(10, dp);
    }
}



void setup()
{
  Wire.begin();
  Serial.begin(115200);
}
 
void loop()
{
  delay(1000);
  long bigNum;
   
  byte a,b,c,d;
   
  Wire.requestFrom(54,4);
   
  a = Wire.read();
  b = Wire.read();
  c = Wire.read();
  d = Wire.read();
   
  bigNum = a;
  bigNum = (bigNum << 8) | b;
  bigNum = (bigNum << 8) | c;
  bigNum = (bigNum << 8) | d;

  float y = round_dp((float)bigNum/1e3, 3);
  Serial.print(y,3);
  Serial.print("\n");
}
