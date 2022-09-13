#pragma once
#include"Engine.h"
class GameSnake
{
private:
	int startFlag = 1;//判断是否进行游戏
	int autoFlag = 0;//自动模式
	int findFlag = 0;//寻路模式
	int modelChoice = 0;//模式选择:能否穿墙/穿身体
	int key = 72;//初始方向：上
	int crossFlag = 0;//穿越边界时不允许转弯
	int eatFlag = 0;//判断蛇是否吃掉了食物
	int createFlag = 1;//是否生成食物
	int createTimes = 0;//生成食物的次数，过大时停止生成
    int score = 0;//得分
	short color[2] = { 0 };//颜色改变,[0]是上一次的颜色，[1]是新的颜色
	struct
	{
		int x=0;
		int y=0;
	}food;
	struct
	{
		int speed = 150;//蛇移动的速度
		int speedChange = 2;//蛇的加速度
		int len = 3;//蛇的长度
		std::vector<int>x ;//组成蛇身的每一个小方块中x的坐标
		std::vector<int>y ;//组成蛇身的每一个小方块中y的坐标
	}snake;

	void logo();
	
	void Init();//初始化
	
	void Move();//移动
	
	void Food();//进食判定和食物生成
	
	bool Status();//死亡判定
	
	void Model();//模式选择
	
public:
	void Start();

	GameSnake();
	
};

