#include "BotLinkedList.h"



BotLinkedList::BotLinkedList()
{
	first = new listNode();
	current = first;
	last = first;
}


BotLinkedList::BotLinkedList(mapNode* mnode)
{
	first = new listNode();
	first->mapnode = mnode;
	current = first;

	last = new listNode();
	first->next = last;
}


void BotLinkedList::enqueue(mapNode* addMe)
{
	last->mapnode = addMe;
	last->next = new listNode();
	last = last->next;
}

void BotLinkedList::dequeue(mapNode * dequeueNode)
{
	if (first->mapnode == dequeueNode)
	{
		current = first; // just in case
		first = first->next;
		delete current;
		resetCurrent();
		return;
	}

	listNode* parent;
	do
	{
		parent = current;
	} while (moveCurrent() && current->mapnode != dequeueNode);
	
	if (current->next != nullptr)
	{
		parent->next = current->next;
		delete current;
	}
	resetCurrent();
}


void BotLinkedList::printAll()
{
	if (first == last)
	{
		return;
	}
	while (current->next != nullptr)
	{
		std::cout << current->mapnode->x << " " << current->mapnode->y << std::endl;
		moveCurrent();
	}
	resetCurrent();
}

BotLinkedList::~BotLinkedList()
{
	resetCurrent();
	while (current->next != nullptr)
	{
		listNode* nextNode = current->next;
		delete current;
		current = nextNode;
	}
	resetCurrent(); // double reset, just in case
}
/// TO DO

bool BotLinkedList::moveCurrent()
{
	if (current->next != nullptr)
	{
		current = current->next;
		return 1;
	}
	return 0;
}


void BotLinkedList::resetCurrent()
{
	current = first;
}