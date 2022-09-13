#pragma once
#include"Engine.h"
class GameBall
{
private:
	int startFlag = 1;//判断是否开始游戏
	int modelChoice = 1;//难度设置：板长
	int boardLength = 6;
	int speed = 75;
	int key = 75, pre_key = 75;//记录按键方向，初始为左
	int score = 0;//记录分数
	std::map<int,int>boardMap;

	enum class Direction//记录球的方向，初始为左上
	{
		leftUp, leftDown, rightUp, rightDown
	};

	int board[10] = { 0 };
	
	struct Ball
	{
		int x = MAPWIDTH / 2;
		int y = MAPHEIGHT - rand() % 20;
		int pre_x = 0;
		int pre_y = 0;
		int hitFlag = 0;//记录撞击
		Direction direc;
		Ball(Direction);
	};
    void ballMove(Ball &ball);

	void logo();

	void Model();

	void Init();

	void boardMove();

	bool Reflect(Ball &ball);

public:
	void ShowScore();

	void Start();

	GameBall();
};
