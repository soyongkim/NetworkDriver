#!/bin/bash

sudo ifconfig sl0 down

PID=`ps -eaf | grep slat | grep -v grep | awk '{print $2}'`
if [[ "" !=  "$PID" ]]; then
	echo "killing $PID"
	kill -9 $PID
fi
