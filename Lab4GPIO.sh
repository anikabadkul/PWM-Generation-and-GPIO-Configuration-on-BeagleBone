#!/bin/sh

echo "rising" > /sys/class/gpio/gpio67/edge
cat /sys/class/gpio/gpio67/edge
cat /sys/class/gpio/gpio67/edge
cat /sys/class/gpio/gpio67/value
echo 'Enabled GPIO rising edge interrupt'
echo "in" > /sys/class/gpio/gpio67/direction
echo 1 > /sys/class/gpio/gpio67/value
echo "GPIO Enabled as IN"
