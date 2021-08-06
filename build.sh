#!/bin/sh
if g++ -o Game.out main.cpp; then
	echo "Build succeeded!";
	./Game.out Adam;
else
	echo "Build failed! See output for more info.";
fi
