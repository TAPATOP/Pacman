#pragma once
#include<iostream>

#include"mapNode.h"


class BotLinkedList
{
public:
	BotLinkedList();
	BotLinkedList(BotLinkedList&);
	BotLinkedList(mapNode*);

	BotLinkedList& operator=(BotLinkedList&);

	void enqueue(mapNode*);
	void dequeue(mapNode*);
	mapNode* dequeueFirst();

	void printAll();
	bool isEmpty();
	bool isNodeQueued(mapNode*);

	void deleteEverything();
	~BotLinkedList();
private:
	bool moveCurrent();
	void resetCurrent();
private:
	struct listNode
	{
		listNode()
		{
			next = nullptr;
		}

		mapNode* mapnode;
		listNode* next;
	};
private:
	listNode* first;
	listNode* current;
};

