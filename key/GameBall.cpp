#include "GameBall.h"

void GameBall::logo()
{
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 23);
	printf("■■■        ■■■       ■       ■  \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 22);
	printf("■    ■    ■     ■      ■       ■  \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 21);
	printf("■    ■    ■     ■      ■       ■  \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 20);
	printf("■■■      ■     ■      ■       ■    \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 19);
	printf("■    ■    ■     ■      ■       ■ \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 18);
	printf("■    ■    ■     ■      ■ ■    ■ ■ \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 17);
	printf("■■■       ■■■ ■     ■■     ■■");
}
void GameBall::Model()
{
	while (1) {
		Map();
		logo();
		//速度和难度、开始游戏
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
		printf("Back -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
		printf("Start-> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
		printf("Speed-> \n");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
		printf("Model-> ");
		switch (updown(4))
		{		
		case 0://难度选择
		{
			Map();
			logo();
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
			printf("Easy->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
			printf("Normal->");
		    gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
			printf("Hard->  ");
			modelChoice = updown(3);
			break;
		}
		case 1://速度选择
		{
			Map();
			logo();
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
			printf("Slow->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
			printf("Normal->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
			printf("Fast->  ");
			switch (updown(3)) 
			{
			case 0: speed = 50; break;
			case 1: speed = 75; break;
			case 2: speed = 100; break;		
			}
			break;
		}
		case 2://开始游戏
		{
			startFlag = 1;
			return;
		}
		case 3: //返回主菜单
			startFlag = 0; return;
		}
	}
}
void GameBall::Init()
{
	Map();

	//新游戏时重置游戏参数
	srand((unsigned)time(0));
	score = 0;
	key = 0;

	switch (modelChoice)
	{
	case 0: boardLength = 4;
		break;
	case 1: boardLength = 6;
		break;
	case 2: boardLength = 8;
		break;
	}

	//初始挡板
	for (int i = 0; i < boardLength; i++)
	{
		board[i] = MAPWIDTH / 2 - 2 + 2 * i;
		gotoxy(board[i], MAPHEIGHT - 3);
		printf("■");
	}

	//跳板
	for (int i = MAPWIDTH / 2 - 15; i <= MAPWIDTH / 2 + 15; i += 2)//i+=2是因为横向字符占用两个位置
	{
		gotoxy(i, 10);
		printf("■");
	}

	//玻璃板
	for (int i = 0; i <= MAPWIDTH; i += 2)//i+=2是因为横向字符占用两个位置
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		gotoxy(i, 2);
		boardMap[i + 1 + 200] = 1;
		boardMap[i + 200] = 1;
		printf("■");
		gotoxy(i, 4);
		boardMap[i + 1 + 400] = 1;
		boardMap[i + 400] = 1;
		printf("■");
		gotoxy(i, 6);
		boardMap[i + 1 + 600] = 1;
		boardMap[i + 600] = 1;
		printf("■");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

	//初始分数条
	gotoxy(0, 0);
	std::cout << "Score: 0";

	gotoxy(MAPWIDTH, 0);
}
void GameBall::boardMove()
{
	if (_kbhit())//如果用户按下了键盘中的某个键
	{
		//getch()读取方向键的时候，会返回两次，第一次调用返回0或者224
		key = _getch();//第一次调用返回的不是实际值
		if (key == 0 || key == 224)//判断是否为方向键
		{
			key = _getch();//第二次调用返回实际值
			if (key != 75 && key != 77)//判断是否为左右方向键 
				key = 0;
		}
	}
	if (key == 75 && board[0] > 1)//向左
	{
		gotoxy(board[boardLength - 2], MAPHEIGHT - 3);
		printf("    ");
		gotoxy(board[0] - 4, MAPHEIGHT - 3);
		printf("■■");
		gotoxy(0, 0);
		for (int i = 0; i < boardLength; i++)
			board[i] -= 4;
	}
	else if (key == 77 && board[boardLength - 1] < MAPWIDTH - 2)//向右
	{
		gotoxy(board[0], MAPHEIGHT - 3);
		printf("    ");
		gotoxy(board[boardLength - 1] + 2, MAPHEIGHT - 3);
		if (board[boardLength - 1] > MAPWIDTH - 6)
			printf("■");
		else printf("■■");//防止越界

		for (int i = 0; i < boardLength; i++)
			board[i] += 4;
		gotoxy(0, 0);
	}

	pre_key = key;
}

void GameBall::ballMove(Ball &ball)
{
	switch (ball.direc)
	{
	case Direction::rightUp:
	{
		ball.x += 2;
		ball.y--;
		break;
	}

	case Direction::leftDown:
	{
		ball.x -= 2;
		ball.y++;
		break;
	}

	case Direction::rightDown:
	{
		ball.x += 2;
		ball.y++;
		break;
	}

	case Direction::leftUp:
	{
		ball.x -= 2;
		ball.y--;
		break;
	}
	}

	if (!ball.hitFlag)//撞击时不清除上一个位置，防止擦去挡板
	{
		gotoxy(ball.pre_x, ball.pre_y);
		printf("  ");
	}
	gotoxy(ball.x, ball.y);
	printf("■");
	gotoxy(0, 0);
	ball.pre_x = ball.x, ball.pre_y = ball.y;
	ball.hitFlag = 0;
}
bool GameBall::Reflect(Ball &ball)
{
	//撞击角落，方向相反
	if (ball.x <= 1 && ball.y == MAPHEIGHT - 3) 
	{ 
		ball.direc = Direction::rightUp;
		return true;
	}
	else if (ball.x >= MAPWIDTH - 2 && ball.y == MAPHEIGHT - 3)
	{
		ball.direc = Direction::leftUp;
		return true;
	}
	if (ball.x <= 1 && ball.y == 1) 
	{ 
		ball.direc = Direction::rightDown;
		return true; 
	}
	else if (ball.x >= MAPWIDTH - 2 && ball.y == 1)
	{
		ball.direc = Direction::rightDown;
		return true;
	}

	for (int i = 0; i < boardLength; i++)//撞击挡板
		if (ball.x == board[i] && ball.y == MAPHEIGHT - 3)
		{

			switch (ball.direc)
			{
			case Direction::rightDown:ball.direc = Direction::rightUp; break;
			case Direction::leftDown: ball.direc = Direction::leftUp; break;
			}
			score++;
			ball.hitFlag = 1;//防止撞击擦去挡板
			return true;
		}
	if (ball.x >= MAPWIDTH - 2 || ball.x <= 1)//撞击左右边界
	{
		//垂直方向不变，水平方向相反
		switch (ball.direc)
		{
		case Direction::rightDown:ball.direc = Direction::leftDown; break;
		case Direction::leftDown: ball.direc = Direction::rightDown; break;
		case Direction::rightUp:ball.direc = Direction::leftUp; break;
		case Direction::leftUp:ball.direc = Direction::rightUp; break;
		};
		return true;
	}
	if (ball.y <= 1)//撞击上边界
	{
		switch (ball.direc)
		{
		case Direction::rightUp:ball.direc = Direction::rightDown; break;
		case Direction::leftUp: ball.direc = Direction::leftDown; break;
		}
		return true;
	}

	//撞击跳板
	if (ball.x >= MAPWIDTH / 2 - 15 && ball.x <= MAPWIDTH / 2 + 15 && ball.y == 10)
	{
		switch (ball.direc)
		{
		case Direction::rightDown:ball.direc = Direction::rightUp; break;
		case Direction::leftDown: ball.direc = Direction::leftUp; break;
		case Direction::rightUp:ball.direc = Direction::rightDown; break;
		case Direction::leftUp: ball.direc = Direction::leftDown; break;
		}
		score++;
		ball.hitFlag = 1;//防止撞击擦去挡板
		return true;
	}

	//撞击玻璃板
	if (ball.x >= 0 && ball.x <= MAPWIDTH && (ball.y == 6 || ball.y == 4 || ball.y == 2) && boardMap[ball.x + 100 * ball.y])
	{
		switch (ball.direc)
		{
		case Direction::rightDown:ball.direc = Direction::rightUp; break;
		case Direction::leftDown: ball.direc = Direction::leftUp; break;
		case Direction::rightUp:ball.direc = Direction::rightDown; break;
		case Direction::leftUp: ball.direc = Direction::leftDown; break;
		}
		boardMap[ball.x + 100 * ball.y] = 0;
		score++;
		return true;
	}

	//触及底部，游戏结束
	if (ball.y >= MAPHEIGHT)
		return false;

	return true;
}

void GameBall::ShowScore()
{
	gotoxy(0, 0);
	std::cout << "Score: "<<score;
	gotoxy(MAPWIDTH, 0);
}

void GameBall::Start()
	{
		Ball ball_1(Direction::leftUp), ball_2(Direction::leftUp), ball_3(Direction::leftUp);
		Model();
		Init();
		if (!startFlag)return;
		while (Reflect(ball_1)&& Reflect(ball_2)&& Reflect(ball_3))
		{
			boardMove();
			ballMove(ball_1);
			ballMove(ball_2);
			ballMove(ball_3);
			ShowScore();
			Sleep(speed);
		}

		Sleep(2000);
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
		printf("Game Over!\n");
		gotoxy(0, 0);
		Sleep(2000);
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
		printf("Score：%d\n", score);
		gotoxy(0, 0);
		Sleep(2000);
		while (_kbhit())int i = _getch();
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
		printf("Press R to replay");
		gotoxy(0, 0);
		char ch = _getch();
		if (ch == 'r' || ch == 'R') Start();
		return;
	}

	GameBall::GameBall()
	{
		Start();
	}

	GameBall::Ball::Ball(Direction x)
	{
		Ball::direc = x;
	}
