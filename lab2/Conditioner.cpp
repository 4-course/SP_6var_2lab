#include <windows.h>
#include "Conditioner.h"

Conditioner::Conditioner () {
	isTurnOn = false;
	isWorking = false;
	mode = cold;
	time = 0;
}

void Conditioner::addWork () {
	time += 60;
}

void Conditioner::minusWork () {
	time--;
}

void Conditioner::changePower() {
	if (isTurnOn) {
		time = 0;
	}
	isTurnOn = !isTurnOn;
}

void Conditioner::changeMode () {
	if (mode == cold)
		mode = warm;
	else
		mode = cold;
}

int Conditioner::getTime() {
	return time;
}

bool Conditioner::isWorkingNow() {
	return isWorking;
}

bool Conditioner::isTurnedOn() {
	return isTurnOn;
}

bool Conditioner::isColdMode() {
	return mode == cold;
}

Conditioner::~Conditioner () {}
