#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main(int argc, char **argv){
    plt::plot({1,2,3,4}, "*");
    plt::show();
    return 0;
}

/// COMPILE WITH g++ : g++ testplot.cpp -o testplot -I /usr/include/python3.10 -lpython3.10
/// be sure to check the python 3 version you are using - mine is python3.10
/// both header and cpp file would likely be in the same folder before you run this in that folder