#pragma once
#include"Engine.h"
class Game
{
public:	
	virtual void init() = 0;
	virtual void load() = 0;
	virtual bool run() = 0;
	virtual void start();
	virtual bool chooseMode();
	virtual void showLogo();
};

