#include"BotStack.h"



BotStack::BotStack()
{
	stackSize = 0;
	coordinates = new coords[10];
	maxSize = 10;
	std::cout << "Default BotStack constructor called ?!" << std::endl;
}

BotStack::BotStack(unsigned int size)
{
	stackSize = 0;
	maxSize = size;
	coordinates = new coords[size];
}

BotStack::BotStack(BotStack& oldOne)
{
	copyBotStack(oldOne);
}
// CONSTRUCTORS above
//

BotStack& BotStack::operator=(BotStack const & Other)
{
	copyBotStack(Other);
	return *this;
}

void BotStack::push(int y, int x)
{
	if (stackSize >= maxSize)
	{
		std::cout << "BotStack overflow :<, aborting push" << std::endl;
		return;
	}

	coordinates[stackSize].x = x;
	coordinates[stackSize].y = y;
	stackSize++;
}

bool BotStack::pop()
{
	if (isEmpty()) return 0;

	stackSize--;
	return 1;

}


ItskoVector2i BotStack::top()
{
	if (isEmpty()) return ItskoVector2i(0, 0, gc::emptyBotStack);

	return ItskoVector2i(coordinates[stackSize - 1].y, coordinates[stackSize - 1].x);
}


ItskoVector2i BotStack::topNpop()
{
	ItskoVector2i returnMePls = top();
	pop();

	return returnMePls;
}


void BotStack::visualize() const
{

	for (int i = 0; i < stackSize; i++)
	{
		std::cout << "[" << i << "]: " << coordinates[i].y << " " << coordinates[i].x << std::endl;
	}
}

bool BotStack::isEmpty()
{
	return stackSize == 0;
}

//void BotStack::flushStack()
//{
//	delete[] coordinates;
//	stackSize = 0;
//}

void BotStack::copyBotStack(BotStack const &other)
{
	delete[] coordinates;

	stackSize = other.stackSize;

	coordinates = new coords[stackSize];

	for (int i = 0; i < stackSize; i++)
	{
		coordinates[i].x = other.coordinates[i].x;
		coordinates[i].y = other.coordinates[i].y;
	}
}
// WARNING: Untested
//

//void BotStack::resize()
//{
//	MAX *= 2;
//
//	ItskoVector2i* replacer = new ItskoVector2i[MAX];
//
//	for (int i = 0; i < stackSize; i++)
//	{
//		replacer[i] = data[i];
//	}
//
//	delete[] data;
//	data = replacer;
//}


BotStack::~BotStack()
{
	delete[] coordinates;
	stackSize = 0;
	maxSize = 0;
}