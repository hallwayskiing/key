#pragma once
class GamePlane
{
	//�ɻ�
	int keyPlane = 0;
	struct
	{
		int x = 58;//�ɻ�ͷ��x����
		int y = 20;//�ɻ�ͷ��y����
	}plane;
	void initPlane()
	{
		for (int i = 0; i < 12; i++)
		{
			gotoxy(plane.x - 6 + i, plane.y + 3);
			printf("��");
		}
		gotoxy(plane.x - 4, plane.y + 2);
		printf("��");
		gotoxy(plane.x + 4, plane.y + 2);
		printf("��");
		for (int i = 0; i < 8; i++)
		{
			gotoxy(plane.x, plane.y + i);
			printf("��");
		}
		gotoxy(0, 0);
	}
	void planeMove()
	{
		keyPlane = 0;
		if (_kbhit())
		{
			map();
			keyPlane = _getch();//��һ�ε��÷��صĲ���ʵ��ֵ
			if (keyBall == 0 || keyBall == 224)//�ж��Ƿ�Ϊ�����
				keyBall = _getch();//�ڶ��ε��÷���ʵ��ֵ
		}
		switch (keyPlane)
		{
		case 72:plane.y--; break;
		case 75:plane.x = plane.x - 2; break;
		case 77:plane.x = plane.x + 2;; break;
		case 80:plane.y++; break;
		}
	}
	void gamePlane()
	{
		while (1)
		{
			initPlane();
			planeMove();
		}
	}
};
