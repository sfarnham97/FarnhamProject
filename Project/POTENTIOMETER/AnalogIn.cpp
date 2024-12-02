/*
AnalogIn.cpp
THis program implements the AnalogIn.h header file to control
analog inputs on the Beagle Bone Black

made by Shawn Farnham
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "AnalogIn.h"

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"
#define ADC 1

using namespace std;

AnalogIn::AnalogIn(){}

AnalogIn::AnalogIn(unsigned int n){
  number = n;
}

//virtual unsigned int AnalogIn::getNumber(){return number;}

void AnalogIn::setNumber(unsigned int n){
  number = n;
}

int AnalogIn::readAdcSample(){
  int number;
  stringstream ss;
  ss << ADC_PATH << ADC << "_raw";
  fstream fs;
  fs.open(ss.str().c_str(), fstream::in);
  fs >> number;
  fs.close();
  return number;
}

AnalogIn::~AnalogIn(){}
