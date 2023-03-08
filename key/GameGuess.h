#pragma once
#include"Game.h"
class GameGuess:public Game
{
private:
	int randomNum;//随机给定的数，每次初始化g时随机生成
	int guessNum;//用户输入的数
	int guessTimes;//猜的次数

	void init();

	void load();

	bool run();

public:	
	GameGuess();
};

