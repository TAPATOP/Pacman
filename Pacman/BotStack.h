///////////////////////////////////////////
/// This BotStack is meant to have all of it's elements pushed at once, and then having all of them
/// popped at once. It takes int y and int x and returns an ItskoVector2i
//////////////////////////////////////////

#pragma once
#include<iostream>

#include"Global_Constants.h"
#include"ItskoVector2i.h"

class BotStack
{
public:
	BotStack();
	BotStack(unsigned int size);
	BotStack(BotStack&);

	BotStack& operator=(BotStack const & otherOne);

	void push(int y, int x);

	bool pop();
	ItskoVector2i top();
	ItskoVector2i topNpop();

	void visualize() const;
	bool isEmpty();

	~BotStack();
private:
	void copyBotStack(BotStack const & other);
private:
	struct coords
	{
		coords()
		{
			y = 0;
			x = 0;
		};
		coords(int y, int x)
		{
			this->y = y;
			this->x = x;
		}
		int x;
		int y;
	};
	int stackSize;
	int maxSize;
	coords* coordinates;
};
