#pragma once
class GamePlane
{
	//飞机
	int keyPlane = 0;
	struct
	{
		int x = 58;//飞机头的x坐标
		int y = 20;//飞机头的y坐标
	}plane;
	void initPlane()
	{
		for (int i = 0; i < 12; i++)
		{
			gotoxy(plane.x - 6 + i, plane.y + 3);
			printf("■");
		}
		gotoxy(plane.x - 4, plane.y + 2);
		printf("■");
		gotoxy(plane.x + 4, plane.y + 2);
		printf("■");
		for (int i = 0; i < 8; i++)
		{
			gotoxy(plane.x, plane.y + i);
			printf("■");
		}
		gotoxy(0, 0);
	}
	void planeMove()
	{
		keyPlane = 0;
		if (_kbhit())
		{
			map();
			keyPlane = _getch();//第一次调用返回的不是实际值
			if (keyBall == 0 || keyBall == 224)//判断是否为方向键
				keyBall = _getch();//第二次调用返回实际值
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

