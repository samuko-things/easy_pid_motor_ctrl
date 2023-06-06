
#include <sstream>
#include <iostream>
#include<unistd.h>

#include "arduino_serial_comm.hpp"

void delay_ms(unsigned long milliseconds) {
  usleep(milliseconds*1000);
}

ArduinoSerialCommApi serClient;




int main(int argc, char **argv) {

  bool isSuccessful;
  float data;
  float posA, posB;
  float velA, velB;

  std::string port = "/dev/ttyUSB0";
  serClient.connect(port, 115200, 100);

  if (serClient.connected()){
    std::cout << "Connection Successful !!!" << std::endl;
  }
  else {
    std::cout << "Connection Failed !!!" << std::endl;
  }

  delay_ms(5000); // wait for the arduino nano to fully setup

  isSuccessful = serClient.sendParam("mode", 0.0);
  std::cout << "isSuccessful: " << isSuccessful << std::endl;

  serClient.getParam("mode", data);
  std::cout << "data: " << data << std::endl;


  isSuccessful = serClient.send("pwm", -110.0, 0.0);
  std::cout << "isSuccessful: " << isSuccessful << std::endl;

  
  while (true)
  {
    serClient.get("vel", velA, velB);
    std::cout << "vel_readings: [" << velA << "," << velB << "]" << std::endl;

    serClient.get("pos", posA, posB);
    std::cout << "pos_readings: [" << posA << "," << posB << "]" << '\n' << std::endl;

    delay_ms(5);
  }
  
}





// int main(int argc, char **argv) {

//   bool isSuccessful;
//   float data;
//   float posA, posB;
//   float velA, velB;

//   std::string port = "/dev/ttyUSB0";
//   serClient.connect(port, 115200, 100);

//   if (serClient.connected()){
//     std::cout << "Connection Successful !!!" << std::endl;
//   }
//   else {
//     std::cout << "Connection Failed !!!" << std::endl;
//   }

//   delay_ms(5000); // wait for the arduino nano to fully setup

//   isSuccessful = serClient.sendParam("mode", 0.0);
//   std::cout << "isSuccessful: " << isSuccessful << std::endl;

//   serClient.getParam("mode", data);
//   std::cout << "data: " << data << std::endl;


//   isSuccessful = serClient.send("pwm", 105.0, 0.0);
//   std::cout << "isSuccessful: " << isSuccessful << std::endl;

//   delay_ms(3000);

//   serClient.get("vel", velA, velB);
//   std::cout << "vel_readings: [" << velA << "," << velB << "]" << std::endl;

//   serClient.get("pos", posA, posB);
//   std::cout << "pos_readings: [" << posA << "," << posB << "]" << std::endl;



//   isSuccessful = serClient.send("pwm", 250.0, 0.0);
//   std::cout << "isSuccessful: " << isSuccessful << std::endl;

//   delay_ms(3000);

//   serClient.get("vel", velA, velB);
//   std::cout << "vel_readings: [" << velA << "," << velB << "]" << std::endl;

//   serClient.get("pos", posA, posB);
//   std::cout << "pos_readings: [" << posA << "," << posB << "]" << std::endl;




//   isSuccessful = serClient.sendParam("mode", 1.0);
//   std::cout << "isSuccessful: " << isSuccessful << std::endl;

//   serClient.getParam("mode", data);
//   std::cout << "data: " << data << std::endl;

  
// }