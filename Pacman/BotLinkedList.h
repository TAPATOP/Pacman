#pragma once
#include<iostream>

#include"mapNode.h"


class BotLinkedList
{
public:
	BotLinkedList();
	BotLinkedList(mapNode*);

	void enqueue(mapNode*);
	void dequeue(mapNode*);

	void printAll();

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
	//listNode* last;
};

