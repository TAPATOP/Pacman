//////////////////////
/// Stores x and y (or dx and dy) and a stateCode, used to send messages from
/// the logical to the GUI elements
/////////////////////

#pragma once
class ItskoVector2i
{
public:
	ItskoVector2i();
	ItskoVector2i(int y, int x);
	ItskoVector2i(int y, int x, int stateCode);

	void setX(int x);
	void setY(int y);
	void setStateCode(int code);

	int getX();
	int getY();
	int getStateCode();

	friend bool operator ==(ItskoVector2i& vector, int num);
	friend void operator *= (ItskoVector2i& vector, int num);

	~ItskoVector2i();
private:
	int x; // width
	int y; // height

	int stateCode;
};

