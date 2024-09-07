#!/bin/sh

make -f makeLab4.mak
bash ./enablePWM.sh
bash ./Lab4GPIO.sh
./Lab4.exe
bash ./disablePWM.sh
bash ./disableGPIO.sh
