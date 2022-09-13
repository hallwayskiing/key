#include "GameBall.h"

void GameBall::logo()
{
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 23);
	printf("������        ������       ��       ��  \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 22);
	printf("��    ��    ��     ��      ��       ��  \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 21);
	printf("��    ��    ��     ��      ��       ��  \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 20);
	printf("������      ��     ��      ��       ��    \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 19);
	printf("��    ��    ��     ��      ��       �� \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 18);
	printf("��    ��    ��     ��      �� ��    �� �� \n");
	gotoxy(MAPWIDTH / 2 - 22, MAPHEIGHT - 17);
	printf("������       ������ ��     ����     ����");
}
void GameBall::Model()
{
	while (1) {
		Map();
		logo();
		//�ٶȺ��Ѷȡ���ʼ��Ϸ
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
		case 0://�Ѷ�ѡ��
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
		case 1://�ٶ�ѡ��
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
		case 2://��ʼ��Ϸ
		{
			startFlag = 1;
			return;
		}
		case 3: //�������˵�
			startFlag = 0; return;
		}
	}
}
void GameBall::Init()
{
	Map();

	//����Ϸʱ������Ϸ����
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

	//��ʼ����
	for (int i = 0; i < boardLength; i++)
	{
		board[i] = MAPWIDTH / 2 - 2 + 2 * i;
		gotoxy(board[i], MAPHEIGHT - 3);
		printf("��");
	}

	//����
	for (int i = MAPWIDTH / 2 - 15; i <= MAPWIDTH / 2 + 15; i += 2)//i+=2����Ϊ�����ַ�ռ������λ��
	{
		gotoxy(i, 10);
		printf("��");
	}

	//������
	for (int i = 0; i <= MAPWIDTH; i += 2)//i+=2����Ϊ�����ַ�ռ������λ��
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		gotoxy(i, 2);
		boardMap[i + 1 + 200] = 1;
		boardMap[i + 200] = 1;
		printf("��");
		gotoxy(i, 4);
		boardMap[i + 1 + 400] = 1;
		boardMap[i + 400] = 1;
		printf("��");
		gotoxy(i, 6);
		boardMap[i + 1 + 600] = 1;
		boardMap[i + 600] = 1;
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

	//��ʼ������
	gotoxy(0, 0);
	std::cout << "Score: 0";

	gotoxy(MAPWIDTH, 0);
}
void GameBall::boardMove()
{
	if (_kbhit())//����û������˼����е�ĳ����
	{
		//getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224
		key = _getch();//��һ�ε��÷��صĲ���ʵ��ֵ
		if (key == 0 || key == 224)//�ж��Ƿ�Ϊ�����
		{
			key = _getch();//�ڶ��ε��÷���ʵ��ֵ
			if (key != 75 && key != 77)//�ж��Ƿ�Ϊ���ҷ���� 
				key = 0;
		}
	}
	if (key == 75 && board[0] > 1)//����
	{
		gotoxy(board[boardLength - 2], MAPHEIGHT - 3);
		printf("    ");
		gotoxy(board[0] - 4, MAPHEIGHT - 3);
		printf("����");
		gotoxy(0, 0);
		for (int i = 0; i < boardLength; i++)
			board[i] -= 4;
	}
	else if (key == 77 && board[boardLength - 1] < MAPWIDTH - 2)//����
	{
		gotoxy(board[0], MAPHEIGHT - 3);
		printf("    ");
		gotoxy(board[boardLength - 1] + 2, MAPHEIGHT - 3);
		if (board[boardLength - 1] > MAPWIDTH - 6)
			printf("��");
		else printf("����");//��ֹԽ��

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

	if (!ball.hitFlag)//ײ��ʱ�������һ��λ�ã���ֹ��ȥ����
	{
		gotoxy(ball.pre_x, ball.pre_y);
		printf("  ");
	}
	gotoxy(ball.x, ball.y);
	printf("��");
	gotoxy(0, 0);
	ball.pre_x = ball.x, ball.pre_y = ball.y;
	ball.hitFlag = 0;
}
bool GameBall::Reflect(Ball &ball)
{
	//ײ�����䣬�����෴
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

	for (int i = 0; i < boardLength; i++)//ײ������
		if (ball.x == board[i] && ball.y == MAPHEIGHT - 3)
		{

			switch (ball.direc)
			{
			case Direction::rightDown:ball.direc = Direction::rightUp; break;
			case Direction::leftDown: ball.direc = Direction::leftUp; break;
			}
			score++;
			ball.hitFlag = 1;//��ֹײ����ȥ����
			return true;
		}
	if (ball.x >= MAPWIDTH - 2 || ball.x <= 1)//ײ�����ұ߽�
	{
		//��ֱ���򲻱䣬ˮƽ�����෴
		switch (ball.direc)
		{
		case Direction::rightDown:ball.direc = Direction::leftDown; break;
		case Direction::leftDown: ball.direc = Direction::rightDown; break;
		case Direction::rightUp:ball.direc = Direction::leftUp; break;
		case Direction::leftUp:ball.direc = Direction::rightUp; break;
		};
		return true;
	}
	if (ball.y <= 1)//ײ���ϱ߽�
	{
		switch (ball.direc)
		{
		case Direction::rightUp:ball.direc = Direction::rightDown; break;
		case Direction::leftUp: ball.direc = Direction::leftDown; break;
		}
		return true;
	}

	//ײ������
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
		ball.hitFlag = 1;//��ֹײ����ȥ����
		return true;
	}

	//ײ��������
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

	//�����ײ�����Ϸ����
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
		printf("Score��%d\n", score);
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