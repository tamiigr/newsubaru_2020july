#!/bin/sh
for str in ../*
do
	./nai_laser_on_off ${str}
	echo ${str}
	./../read ${str}.root
done
