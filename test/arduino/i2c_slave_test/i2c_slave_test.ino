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
  Serial.begin(115200);
  Wire.begin(54);
  Wire.onRequest(requestEvent);

  
//  Serial.println(y,4);
}
 
void loop()
{
  delay(5);
}
 
void requestEvent()
{
  float x = 8923.456;
  float y = round_dp(x,3)*1e3;
  Serial.println(y);
  long bigNum = long(y);
  byte myArray[4];
   
  myArray[0] = (bigNum >> 24) & 0xFF;
  myArray[1] = (bigNum >> 16) & 0xFF;
  myArray[2] = (bigNum >> 8) & 0xFF;
  myArray[3] = bigNum & 0xFF;
   
  Wire.write(myArray, 4);
}
