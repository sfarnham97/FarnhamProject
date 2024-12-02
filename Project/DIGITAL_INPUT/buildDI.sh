#!/bin/bash
config-pin p8.16 gpio_pu

echo "building Digital Input"
g++ -Wall GPIO.cpp DigitalInput.cpp -o DigitalInput -lpaho-mqtt3c -pthread
echo "finished"

