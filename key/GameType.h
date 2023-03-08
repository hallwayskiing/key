#pragma once
#include"Game.h"
class GameType:public Game
{
	int best_time;//历史记录
	int best_num;//历史纪录
	std::fstream wordList;
	int lineNum;

	void init();//初始化

	void load();

	bool run();//游戏体

public:
	GameType();
};

