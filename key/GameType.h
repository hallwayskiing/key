#pragma once
#include"Engine.h"
class GameType
{
	int best_time = 999, best_num = 0;//��ʷ��¼
	char startFlag=0;
	std::string readLine, typeLine;
	int randomLine = 0, numRight = 0, timeuse = 0; //�����������ȷ������ʹ��ʱ��
public:
	void Start();

	GameType();
};
