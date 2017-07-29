#include "BotLinkedList.h"



BotLinkedList::BotLinkedList()
{
	first = nullptr;
	current = first;
}

BotLinkedList::BotLinkedList(mapNode* mnode)
{
	first = new listNode();
	first->mapnode = mnode;
	current = first;
}

BotLinkedList::BotLinkedList(BotLinkedList & oldList)
{
	if (oldList.first == nullptr)
	{
		first = nullptr;
		current = first;
		return;
	}

	listNode* newListNode = new listNode();

	first = newListNode;
	current = first;

	current->mapnode = oldList.current->mapnode;


	while (oldList.current->next != nullptr)
	{
		oldList.current = oldList.current->next;

		newListNode = new listNode();

		current->next = newListNode;
		current = current->next;
		current->mapnode = oldList.current->mapnode;
	}
	oldList.resetCurrent();
}
// CONSTRUCTORS above
//

BotLinkedList & BotLinkedList::operator=(BotLinkedList & oldList)
{
	if (oldList.current == nullptr) return *(new BotLinkedList());

	deleteEverything();

	this->first = oldList.first;
	this->current = oldList.current;

	while (oldList.current->next != nullptr)
	{
		current->next = new listNode();
		current->next = oldList.current->next;
		current->mapnode = oldList.current->mapnode;

		current = current->next;
		oldList.current = oldList.current->next;
	}
	current->next = nullptr;

	oldList.resetCurrent();
	resetCurrent();
	return *this;
}

void BotLinkedList::enqueue(mapNode* addMe)
{
	listNode* parent = nullptr;
	
	listNode* newNode = new listNode();
	newNode->mapnode = addMe;

	if (first == nullptr)
	{
		first = newNode;

		resetCurrent();
		return;
	}

	do
	{
		if (
			addMe->Fvalue() < current->mapnode->Fvalue() ||
			(addMe->Fvalue() == current->mapnode->Fvalue() && addMe->Hcost < current->mapnode->Hcost)
			)
		{
			break;
		}
		parent = current;
	} while (moveCurrent());

	if (parent == current) // if this is true, then newNode must be last
	{
		current->next = newNode;
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
		std::cout << current->mapnode->Hcost << " " << current->mapnode->Gcost << std::endl;
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
	deleteEverything();
}

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

void BotLinkedList::deleteEverything()
{
	resetCurrent();

	while (current != nullptr && current->next != nullptr)
	{
		listNode* nextNode = current->next;

		delete current;
		current = nextNode;
	}
	resetCurrent(); // double reset, just in case
}
// mapNodes MUST NOT BE DELETED
//