cmake_minimum_required(VERSION 3.16)
project(libserial_client LANGUAGES CXX)



include_directories(include)
add_executable( libserial_client_api examples/libserial_client_api.cpp )
target_link_libraries( libserial_client_api serial )

