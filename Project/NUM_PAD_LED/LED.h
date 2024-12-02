/*
  LED.h
  THis class is designed to make BeagleBone Blacks onboard LEDS function
  it is partnered with LED.cpp
  Made by Shawn Farnham on 11-22-2024
*/
#ifndef LED_H
#define LED_H

#include <string>

using namespace std;
class LED{
  private:
    string path;
    int number;
    virtual void writeLED(string filename, string value);
    virtual void removeTrigger();
  public:
    LED(int number);
    virtual void turnOn();
    virtual void turnOff();
    virtual void flash(string delayms);
    virtual void outputState();
    ~LED();
};

#endif
