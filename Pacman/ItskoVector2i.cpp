#include "ItskoVector2i.h"



ItskoVector2i::ItskoVector2i()
{
}

ItskoVector2i::ItskoVector2i(int y, int x)
{
	this->y = y;
	this->x = x;
}

void ItskoVector2i::setX(int x)
{
	this->x = x;
}

void ItskoVector2i::setY(int y)
{
	this->y = y;
}

int ItskoVector2i::getX()
{
	return x;
}

int ItskoVector2i::getY()
{
	return y;
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

