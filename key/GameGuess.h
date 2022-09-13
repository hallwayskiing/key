#pragma once
#include"Engine.h"
class GameGuess
{
	int randomNum = 0;//随机给定的数，每次开始时随机生成
	int guessNum = 0;//用户输入的数
	int guessTime = 0;//猜的次数

public:
	void Start();	

	GameGuess();
};

