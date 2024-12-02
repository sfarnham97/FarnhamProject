#!/bin/bash

echo "building Temp Sensor"
g++ -Wall AnalogIn.cpp TempSensor.cpp -o TempSensor -lpaho-mqtt3c
echo "finsihed"
