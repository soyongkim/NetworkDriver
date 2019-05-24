#!/bin/bash

if [ -z "$1" ]; then
	echo "No argument. Insert ip host part [ex] (1 or 2) -> 192.168.93.(1 or 2)"
else
	modprobe slip
	slattach -p slip -s 115200 -L -m /dev/ttyVLC &
	ifconfig sl0 192.168.93.$1
fi
