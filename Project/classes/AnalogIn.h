/*
  AnalogIn.h
  header file to control analog inputs on Beagle Bone Black
  paired with AnalogIn.cpp

made by Shawn Farnham
*/
#ifndef ANALOGIN_H
#define ANALOGIN_H

class AnalogIn{
  private:
    unsigned int number;
  public:
    AnalogIn();
    AnalogIn(unsigned int n);
    virtual unsigned int getNumber() {return number; } // inline function
    virtual void setNumber(unsigned int n);
    virtual int readAdcSample();
    virtual ~AnalogIn();
};

#endif
