#pragma once
class ItskoVector2i
{
public:
	ItskoVector2i();
	ItskoVector2i(int y, int x);

	void setX(int x);
	void setY(int y);

	int getX();
	int getY();

	friend bool operator ==(ItskoVector2i& vector, int num);
	friend void operator *= (ItskoVector2i& vector, int num);

	~ItskoVector2i();
private:
	int x; // width
	int y; // height
};

