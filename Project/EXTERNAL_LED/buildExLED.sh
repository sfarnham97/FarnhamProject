#!/bin/bash
config-pin p9.12 gpio

echo "building External_LED"
g++ -Wall GPIO.cpp External_LED.cpp -o External_LED -lpaho-mqtt3c -pthread
echo "finished"

