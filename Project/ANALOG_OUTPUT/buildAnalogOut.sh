#!/bin/bash
config-pin p9.22 pwm

echo "building Analog Output"
g++ -Wall util.cpp PWM.cpp AnalogOutput.cpp -o AnalogOutput -lpaho-mqtt3c
echo "finished"

