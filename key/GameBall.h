#pragma once
#include"Engine.h"
class GameBall
{
private:
	int startFlag = 1;//�ж��Ƿ�ʼ��Ϸ
	int modelChoice = 1;//�Ѷ����ã��峤
	int boardLength = 6;
	int speed = 75;
	int key = 75, pre_key = 75;//��¼�������򣬳�ʼΪ��
	int score = 0;//��¼����
	std::map<int,int>boardMap;

	enum class Direction//��¼��ķ��򣬳�ʼΪ����
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
		int hitFlag = 0;//��¼ײ��
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