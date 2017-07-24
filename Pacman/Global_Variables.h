#pragma once

namespace gv
{
	///////////////////////
	/// MAP- RELATED below
	///////////////////////

	const char wallSquare = '#';
	const char walkableSquare = '.';
	const char defaultPlayerDisplay = 'p';

	const char knotSquare = 'k';

	const char smallBall = '1';
	const char bigBall = '2';

	const int smallBallValue = 50;
	const int bigBallValue = 101;
	const int defaultValue = 0;
	const int botValue = 500;

	const unsigned int maxLoadedMapHeight = 100;
	const unsigned int maxLoadedMapWidth = 100;

	const unsigned int defaultX = 0;
	const unsigned int defaultY = 0;
	const unsigned int defaultMovementSpeed = 100;

	////////////////////
	/// GUI Below
	////////////////////

	const unsigned int windowWidth = 800;
	const unsigned int windowHeight = 600;

	//////////////////
	/// Controls Below
	//////////////////

	const char up = 'w';
	const char down = 's';
	const char left = 'a';
	const char right = 'd';
	const char stop = ' ';

	///////////////////////
	/// Return Codes Below
	//////////////////////

	const int playerDied = 69;
	const int botDied = 70;
	const int emptyBotStack = 80;
}

/// TO DO: Make controls work with capitalized letters
