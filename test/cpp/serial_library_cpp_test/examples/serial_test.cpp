
#include <string>
#include <iostream>
#include <cstdio>

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "serial/serial.h"





void delay_ms(unsigned long milliseconds) {
#ifdef _WIN32
      Sleep(milliseconds); // 100 ms
#else
      usleep(milliseconds*1000); // 100 ms
#endif
}





void enumerate_ports()
{
	std::vector<serial::PortInfo> devices_found = serial::list_ports();

	std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while( iter != devices_found.end() )
	{
		serial::PortInfo device = *iter++;

		printf( "(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
     device.hardware_id.c_str() );
	}
}






class ArduinoSerialCommApi
{

public:
  ArduinoSerialCommApi() = default;

  ArduinoSerialCommApi(std::string port, unsigned long baud, int timeout_ms)
    : ser(port, baud, serial::Timeout::simpleTimeout(timeout_ms))

  {  
    // ser.setPort(port);
    // ser.setBaudrate(baud);
    // ser.setTimeout(timeout_ms);
  }

  void disconnect()
  {
    ser.close();
  }

  bool connected()
  {
    return ser.isOpen();
  }

  std::string send_msg(std::string msg_to_send){
    std::string res = "";
    while (res=="")
    {
      ser.write(msg_to_send);
      res = ser.readline();
    }
    return res;
  }

  bool sendParam(std::string cmd_route, float val){
    std::stringstream msg_stream;
    msg_stream << cmd_route << "," << val;

    std::string res = send_msg(msg_stream.str());
    int data = std::stoi(res);
    if (data) return true;
    else return false;
  }

  void getParam(std::string cmd_route, float &data){
    std::string res = send_msg(cmd_route);
    data = std::stof(res);
  }

  bool send(std::string cmd_route, float valA, float valB){
    std::stringstream msg_stream;
    msg_stream << cmd_route << "," << valA << "," << valB;

    std::string res = send_msg(msg_stream.str());
    int data = std::stoi(res);
    if (data) return true;
    else return false;
  }

  void get(std::string cmd_route, float &valA, float &valB){
    std::string res = send_msg(cmd_route);

    std::string delimiter = ",";
    size_t del_pos = res.find(delimiter);
    std::string token_1 = res.substr(0, del_pos);
    std::string token_2 = res.substr(del_pos + delimiter.length());

    valA = std::atoi(token_1.c_str());
    valB = std::atoi(token_2.c_str());
  }

private:
  serial::Serial ser;
};






int main(int argc, char **argv) {

  bool isSuccessful;
  float data;
  float posA, posB;
  float velA, velB;

  // port, baudrate, timeout in milliseconds
  std::string port = "/dev/ttyUSB0";
  unsigned long baud = 115200;
  int timeout_ms = 50;

  ArduinoSerialCommApi serClient(port, baud, timeout_ms);
  delay_ms(5000); // wait for the arduino nano to fully setup

  isSuccessful = serClient.sendParam("mode", 0.0);
  std::cout << "isSuccessful: " << isSuccessful << std::endl;

  serClient.getParam("mode", data);
  std::cout << "data: " << data << std::endl;


  isSuccessful = serClient.send("pwm", 105.0, 0.0);
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

//   // port, baudrate, timeout in milliseconds
//   std::string port = "/dev/ttyUSB0";
//   unsigned long baud = 115200;
//   int timeout_ms = 50;

//   ArduinoSerialCommApi serClient(port, baud, timeout_ms);
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