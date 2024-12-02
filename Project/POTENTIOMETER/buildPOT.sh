#!/bin/bash

echo "building Potentiometer"
g++ -Wall AnalogIn.cpp Potentiometer.cpp -o Potentiometer -lpaho-mqtt3c
echo "finsished"
