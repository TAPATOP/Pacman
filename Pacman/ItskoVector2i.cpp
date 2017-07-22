#include "ItskoVector2i.h"



ItskoVector2i::ItskoVector2i()
{
	stateCode = 0;
}

ItskoVector2i::ItskoVector2i(int y, int x)
{
	this->y = y;
	this->x = x;
}

ItskoVector2i::ItskoVector2i(int y, int x, int stateCode) 
	: ItskoVector2i(y, x)
{
	this->stateCode = stateCode;
}

void ItskoVector2i::setX(int x)
{
	this->x = x;
}

void ItskoVector2i::setY(int y)
{
	this->y = y;
}

void ItskoVector2i::setStateCode(int code)
{
	stateCode = code;
}

int ItskoVector2i::getX()
{
	return x;
}

int ItskoVector2i::getY()
{
	return y;
}

int ItskoVector2i::getStateCode()
{
	return stateCode;
}


ItskoVector2i::~ItskoVector2i()
{
}

bool operator==(ItskoVector2i& vector, int num)
{
	return (vector.getX() == num && vector.getY() == num);
}

void operator*=(ItskoVector2i& vector, int num)
{
	vector.setX(vector.getX() * num);
	vector.setY(vector.getY() * num);
}

