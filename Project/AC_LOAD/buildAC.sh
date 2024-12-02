#!/bin/bash
config-pin p9.12 gpio

echo "building AC_Load"
g++ -Wall GPIO.cpp AC_Load.cpp -o AC_Load -lpaho-mqtt3c -pthread
echo "finished"

