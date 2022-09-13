#pragma once
#include"Engine.h"
class GameSnake
{
private:
	int startFlag = 1;//�ж��Ƿ������Ϸ
	int autoFlag = 0;//�Զ�ģʽ
	int findFlag = 0;//Ѱ·ģʽ
	int modelChoice = 0;//ģʽѡ��:�ܷ�ǽ/������
	int key = 72;//��ʼ������
	int crossFlag = 0;//��Խ�߽�ʱ������ת��
	int eatFlag = 0;//�ж����Ƿ�Ե���ʳ��
	int createFlag = 1;//�Ƿ�����ʳ��
	int createTimes = 0;//����ʳ��Ĵ���������ʱֹͣ����
    int score = 0;//�÷�
	short color[2] = { 0 };//��ɫ�ı�,[0]����һ�ε���ɫ��[1]���µ���ɫ
	struct
	{
		int x=0;
		int y=0;
	}food;
	struct
	{
		int speed = 150;//���ƶ����ٶ�
		int speedChange = 2;//�ߵļ��ٶ�
		int len = 3;//�ߵĳ���
		std::vector<int>x ;//���������ÿһ��С������x������
		std::vector<int>y ;//���������ÿһ��С������y������
	}snake;

	void logo();
	
	void Init();//��ʼ��
	
	void Move();//�ƶ�
	
	void Food();//��ʳ�ж���ʳ������
	
	bool Status();//�����ж�
	
	void Model();//ģʽѡ��
	
public:
	void Start();

	GameSnake();
	
};
