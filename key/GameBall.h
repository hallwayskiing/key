#pragma once
#include"Game.h"
class GameBall:public Game
{
private:
	int boardLength;
	int speed;
	int key, pre_key;//记录按键方向，初始为左
	int score;//记录分数
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
	
	void boardMove();

	bool reflect(Ball &ball);

	void showLogo();

	void init();

	bool chooseMode();

	void load();

	bool run();

public:
	void showScore();

	GameBall();
};
