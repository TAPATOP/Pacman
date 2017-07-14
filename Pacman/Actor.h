#pragma once

class Actor
{
public:
	Actor();

	~Actor();
private:
	int x;
	int y;

	int dx;
	int dy;

	int movementSpeed; // lower is faster
};
