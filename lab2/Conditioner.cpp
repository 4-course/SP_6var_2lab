#include "Conditioner.h"

Conditioner::Conditioner () {
	isTurnOn = false;
	isWorking = false;
	mode = warm;
}

void Conditioner::changeWork () {}

void Conditioner::changePower () {}

void Conditioner::changeMode () {}

Conditioner::~Conditioner () {}
