#!/bin/bash

modprobe slip
slattach -p slip -s 115200 -L -m /dev/ttyVLC &
ifconfig sl0 192.168.93.2