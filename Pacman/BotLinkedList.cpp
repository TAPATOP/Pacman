#include "BotLinkedList.h"



BotLinkedList::BotLinkedList()
{
	first = nullptr;
	//last = nullptr;
}


BotLinkedList::BotLinkedList(mapNode* mnode)
{
	first = new listNode();
	first->mapnode = mnode;
	current = first;
	//last = current;
}


void BotLinkedList::enqueue(mapNode* addMe)
{
	//last->mapnode = addMe;
	//last->next = new listNode();
	//last = last->next;
	listNode* parent = nullptr;
	
	listNode* newNode = new listNode();
	newNode->mapnode = addMe;
	
	//do
	//{
	//	if (addMe->Fvalue() <= current->mapnode->Fvalue() || newNodeWillBeLast == 1)
	//	{
	//		if (parent != nullptr)
	//		{
	//			parent->next = newNode;
	//			newNode->next = current;
	//		}
	//		else
	//		{
	//			first = newNode;
	//			newNode->next = current;
	//		}
	//	}
	//	else
	//	{
	//		newNodeWillBeLast = !moveCurrent();
	//	}
	//} while (true);
	if (first == nullptr)
	{
		first = newNode;
	//	last = newNode;
		resetCurrent();
		return;
	}

	do
	{
		if (addMe->Fvalue() <= current->mapnode->Fvalue()) // TO DO: in case of =, sort by H- value
		{
			break;
		}
		parent = current;
	} while (moveCurrent());

	if (parent == current) // if this is true, then newNode must be last
	{
		current->next = newNode;
		//last = newNode;
	}
	else if (parent == nullptr) // if this is true, then newNode must be first
		{
			first = newNode;
			newNode->next = current;
		}
	else
	{
		parent->next = newNode;
		newNode->next = current;
	}

	resetCurrent();
}

void BotLinkedList::dequeue(mapNode* dequeueNode)
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

mapNode* BotLinkedList::dequeueFirst()
{
	if (first != nullptr)
	{
		mapNode* returnedMapNode = first->mapnode;
		resetCurrent(); // just in case
		first = first->next;
		delete current;
		resetCurrent();
		return returnedMapNode;
	}
	return nullptr;
}


void BotLinkedList::printAll()
{
	if (first == nullptr)
	{
		return;
	}
	do
	{
		std::cout << current->mapnode->Hvalue << " " << current->mapnode->Gvalue << std::endl;
	} while (moveCurrent());
	resetCurrent();
}

bool BotLinkedList::isEmpty()
{
	return (first == nullptr);
}

bool BotLinkedList::isNodeQueued(mapNode * checkMe)
{
	while (current != nullptr)
	{
		if (current->mapnode == checkMe)
		{
			resetCurrent();
			return 1;
		}
		current = current->next;
	}
	resetCurrent();
	return 0;
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
