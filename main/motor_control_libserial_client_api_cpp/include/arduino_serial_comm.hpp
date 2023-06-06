#ifndef ARDUINO_SERIAL_COMMS_HPP
#define ARDUINO_SERIAL_COMMS_HPP

// #include <cstring>
#include <sstream>
// #include <cstdlib>
#include <libserial/SerialPort.h>
#include <iostream>

#include <chrono>


LibSerial::BaudRate convert_baud_rate(int baud_rate)
{
  // Just handle some common baud rates
  switch (baud_rate)
  {
    case 1200: return LibSerial::BaudRate::BAUD_1200;
    case 1800: return LibSerial::BaudRate::BAUD_1800;
    case 2400: return LibSerial::BaudRate::BAUD_2400;
    case 4800: return LibSerial::BaudRate::BAUD_4800;
    case 9600: return LibSerial::BaudRate::BAUD_9600;
    case 19200: return LibSerial::BaudRate::BAUD_19200;
    case 38400: return LibSerial::BaudRate::BAUD_38400;
    case 57600: return LibSerial::BaudRate::BAUD_57600;
    case 115200: return LibSerial::BaudRate::BAUD_115200;
    case 230400: return LibSerial::BaudRate::BAUD_230400;
    default:
      std::cout << "Error! Baud rate " << baud_rate << " not supported! Default to 57600" << std::endl;
      return LibSerial::BaudRate::BAUD_57600;
  }
}

class ArduinoSerialCommApi
{

public:

  ArduinoSerialCommApi() = default;

  void connect(const std::string &serial_device, int32_t baud_rate, int32_t timeout_ms)
  {  
    timeout_ms_ = timeout_ms;
    serial_conn_.Open(serial_device);
    serial_conn_.SetBaudRate(convert_baud_rate(baud_rate));
  }

  void disconnect()
  {
    serial_conn_.Close();
  }

  bool connected() const
  {
    return serial_conn_.IsOpen();
  }

 
  // std::string send_msg(const std::string &msg_to_send, bool print_output = true)
  // {
  //   std::string response = "";

  //   serial_conn_.FlushIOBuffers(); // Just in case

  //   while (response == "")
  //   {
  //     try
  //     {
  //       serial_conn_.Write(msg_to_send);
  //       serial_conn_.ReadLine(response, '\n', timeout_ms_);
  //     }
  //     catch (const LibSerial::ReadTimeout&)
  //     {
  //         continue;
  //     }
  //   }
    
  //   return response;
  // }


  std::string send_msg(const std::string &msg_to_send)
  {
    auto prev_time = std::chrono::system_clock::now();
    std::chrono::duration<double> duration;

    std::string response = "";

    serial_conn_.FlushIOBuffers(); // Just in case

    while (response == "")
    {
      try {

        try
        {
          serial_conn_.Write(msg_to_send);
          serial_conn_.ReadLine(response, '\n', timeout_ms_);
          duration = (std::chrono::system_clock::now() - prev_time);
        }
        catch (const LibSerial::ReadTimeout&)
        {
            continue;
        }

        duration = (std::chrono::system_clock::now() - prev_time);
        if (duration.count() > 2.0)
        {
          throw duration.count();
        }
      }
      catch (double x ) {
          std::cerr << "Error getting response from arduino nano, wasted much time \n";
      }
      
    }
    
    return response;
  }


  bool sendParam(std::string cmd_route, float val) {
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


  bool send(std::string cmd_route, float valA, float valB) {
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
    LibSerial::SerialPort serial_conn_;
    int timeout_ms_;
};

#endif // DIFFDRIVE_ARDUINO_ARDUINO_COMMS_HPP