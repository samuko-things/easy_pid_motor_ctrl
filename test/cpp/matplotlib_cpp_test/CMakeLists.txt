cmake_minimum_required (VERSION 3.15.0)

project( matplotlib-test )

set(Python3_EXECUTABLE "/usr/bin/python3.10")
find_package( Python3 REQUIRED COMPONENTS Interpreter Development NumPy)
# Found Python3: /usr/bin/python3.10 (found version "3.10.6")
# Found Python3: /home/samuko/anaconda3/bin/python3.9 (found version "3.9.13")
include_directories( ${Python3_INCLUDE_DIRS} include)

add_executable( testplot src/testplot.cpp )
target_link_libraries( testplot ${Python3_LIBRARIES} )

add_executable( animation src/animation.cpp )
target_link_libraries( animation ${Python3_LIBRARIES} )