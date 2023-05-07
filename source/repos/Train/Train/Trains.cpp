#include "Trains.h"

Trains::Trains(string name, int number)
{
	this->name = name;
	this->number = number;
}

void Trains::setName(int name)
{
	this->name = name;
}

string Trains::getName()
{
	return name;
}

void Trains::setNumber(int number)
{
	this->number = number;
}

int Trains::getNumber()
{
	return number;
}