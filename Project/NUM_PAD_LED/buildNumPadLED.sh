#!/bin/bash

echo "building Num Pad LED's"
g++ -Wall LED.cpp NumPadLED.cpp -o NumPadLED -lpaho-mqtt3c
echo "finished"

