#pragma once
#include"Engine.h"
class GameType
{
	int best_time = 999, best_num = 0;//历史纪录
	char startFlag=0;
	std::string readLine, typeLine;
	int randomLine = 0, numRight = 0, timeuse = 0; //随机行数，正确个数，使用时间
public:
	void Start();

	GameType();
};

