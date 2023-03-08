#pragma once
#include"Game.h"
class GameSnake:public Game
{
private:
	struct
	{
		int x;
		int y;
	}food;

	struct
	{
		int speed;//蛇移动的速度
		int speedChange;//蛇的加速度
		int len;//蛇的长度
		std::vector<int>x ;//组成蛇身的每一个小方块中x的坐标
		std::vector<int>y ;//组成蛇身的每一个小方块中y的坐标
	}snake;

	enum class GameMode {
		NOOB,EASY,NORMAL
	};

	enum class MoveMode {
		NORMAL,AUTO,FIND
	};

	int key;//蛇的移动方向
	int crossFlag;//穿越边界时的转弯控制
	int eatFlag;//判断蛇是否吃掉了食物
	int createFlag;//是否生成食物
	int createTimes;//生成食物的次数，过大时停止生成
    int score;//得分
	short color[2];//颜色改变,[0]是上一次的颜色，[1]是新的颜色
	GameMode gameMode;
	MoveMode moveMode;
	
	
	
	void move();//移动
	
	void newFood();//进食判定和食物生成
	
	bool status();//死亡判定
	
	bool chooseMode();//模式选择

	void showLogo();
	
	void init();//初始化

	void load();

	bool run();	

public:
	GameSnake();
};

