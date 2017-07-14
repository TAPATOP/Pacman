#pragma once
#include "Actor.h"
class Bot :
	public Actor
{
public:
	Bot();

	int move();
	void die();
	
	~Bot();
private:
	bool isVulnerable;
	unsigned int attackRange;
};
