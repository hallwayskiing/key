#include "GameSnake.h"

void GameSnake::logo()
{
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 23);
	printf("  ������      ������      ������      ��    ��      ���� \n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 22);
	printf("��          ��     ��    ��     ��    ��   ��     ��     ��\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 21);
	printf("��          ��     ��    ��     ��    ��  ��      ��     ��\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 20);
	printf("  ����      ��     ��    ��     ��    ����        ��������\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 19);
	printf("       ��   ��     ��    ��     ��    ��  ��      ��      \n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 18);
	printf("       ��   ��     ��    ��     ��    ��   ��     ��       \n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 17);
	printf(" ������     ��     ��     ������ ��   ��    ��     ������");
}
void GameSnake::Init()//��ʼ��
{
	Map();
	srand((unsigned)time(0) + rand());
	while (1)
	{
		food.x = rand() % (MAPWIDTH - 2) + 2;
		food.y = rand() % (MAPHEIGHT - 1) + 1;
		//���ɵ�ʳ�������������ʼ��ʱ��ͷ�����������żһ�£���Ϊһ���ַ�ռ�����ֽ�λ�ã�����һ�»ᵼ�³�ʳ���ʱ��ֻ�Ե�һ��
		if (food.x % 2 == 1)
			break;
	}

	snake.x.resize(snake.len, 0);
	snake.y.resize(snake.len, 0);

	//������Ƶ�ʳ������괦��ӡʳ��
	gotoxy(food.x, food.y);
	printf("��");
	//����Ļ�м�������ͷ
	snake.x[0] = MAPWIDTH / 2;
	snake.y[0] = MAPHEIGHT / 2;
	//��ӡ��ͷ
	gotoxy(snake.x[0], snake.y[0]);
	printf("��");

	//���ɳ�ʼ����
	for (int i = 1; i < snake.len; i++)
	{
		snake.x[i] = snake.x[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) - 1];
		snake.y[i] = snake.y[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) - 1] + 1;
		gotoxy(snake.x[i], snake.y[i]);
		printf("��");
	}

	//���ɳ�ʼ������
	gotoxy(0, 0);
	printf("Score: 0");

	//��ʼ�������󽫹���Ƶ���Ļ���Ϸ�����������������һֱ��˸
	gotoxy(MAPWIDTH, 0);
	return;
}
void GameSnake::Move()
{
	int pre_key = key;//��¼ǰһ�������ķ���
	if (!crossFlag)//��Խ�߽�ʱ������ת��
	{
		if (autoFlag)//�Զ�ģʽ���������������û�����
		{
			if (!_kbhit())//��������˳��Զ�ģʽ
			{
				srand((unsigned)time(0) + rand());
				switch (rand() % 4)
				{
				case 0:key = 72; break;
				case 1:key = 75; break;
				case 2:key = 77; break;
				case 3:key = 80; break;
				}
			}
			else autoFlag = 0;
		}
		else if (findFlag)//Ѱ·ģʽ
		{
			if (!_kbhit())
			{
				if (food.x > snake.x[0])key = 77;//��
				else if (food.x < snake.x[0])key = 75;//��
				if (food.x == snake.x[0])
					if (food.y > snake.y[0])key = 80;//��
					else if (food.y < snake.y[0])key = 72;//��
			}
			else findFlag = 0;
		}
		else//����ģʽ
		{
			if (_kbhit())//����û������˼����е�ĳ����
			{
				//getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224
				switch (key = _getch())//��һ�ε��÷��صĲ���ʵ��ֵ
				{
				case 0://�ж��Ƿ�Ϊ�����
				case 224:key = _getch(); break;//�ڶ��ε��÷���ʵ��ֵ
				case 'a':
				case 'A'://��A�����Զ�ģʽ
				{
					autoFlag = 1;
					key = pre_key;
					break;
				}
				case 'f':
				case 'F'://��F����Ѱ·ģʽ
				{
					findFlag = 1;
					key = pre_key;
					break;
				}
				case 27://��ESC�˳�
					snake.speed = 0; break;
				default: key = pre_key; break;
				}
			}
		}
	}

	/*
	*���ƶ�ʱ���Ȳ�ȥ��β��һ��
	*eatFlagΪ0������ʱû�гԵ�ʳ����ÿ��һ����Ҫ��������β���Դ�Ӫ��һ���ƶ���Ч��
	*Ϊ1�����Ե���ʳ��Ͳ���Ҫ������β���Դ�Ӫ��һ������������Ч��
	*/
	if (eatFlag == 0)
	{
		gotoxy(snake.x[static_cast<std::vector<int, std::allocator<int>>::size_type>(snake.len) - 1], snake.y[static_cast<std::vector<int, std::allocator<int>>::size_type>(snake.len) - 1]);
		printf("  ");//��ȥ��β
	}

	//��������ÿһ��������ǰ�ƶ�һ��
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) - 1];
		snake.y[i] = snake.y[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) - 1];
	}

	//�����ǰ�ƶ������ǰһ�η����෴���ѵ�ǰ�ƶ��ķ����Ϊǰһ�εķ���
	if (pre_key == 72 && key == 80)
		key = 72;
	if (pre_key == 80 && key == 72)
		key = 80;
	if (pre_key == 75 && key == 77)
		key = 75;
	if (pre_key == 77 && key == 75)
		key = 77;

	//�ж��ƶ�����
	switch (key)
	{
	case 75:
		snake.x[0] -= 2;//����
		break;
	case 77:
		snake.x[0] += 2;//����
		break;
	case 72:
		snake.y[0]--;//����
		break;
	case 80:
		snake.y[0]++;//����
		break;
	}

	//��ӡ����ͷ
	gotoxy(snake.x[0], snake.y[0]);
	HWND hWnd = GetConsoleWindow();
	printf("��");
	gotoxy(MAPWIDTH, 0);

	//����Ŀǰû�гԵ�ʳ�changFlagֵΪ0
	eatFlag = 0;
	crossFlag = 0;
	return;
}
void GameSnake::Food()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y || createFlag == 0)//��ͷ����ʳ�� ���� �ϴ�δ����
	{
		createFlag = 1;
		createTimes = 1;
		srand((unsigned)time(0) + rand());
		while (createTimes++)//�ٴ�����ʳ��
		{
			int flag = 1;
			food.x = rand() % (MAPWIDTH - 16) + 8;
			food.y = rand() % (MAPHEIGHT - 8) + 4;

			//������ɵ�ʳ�ﲻ�����ߵ�������
			for (int i = 0; i < snake.len; i++)
			{
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			}

			if (food.x == snake.x[0] || food.y == snake.y[0])flag = 0;

			if (flag == 1 && food.x % 2 == 1)//��Ϊ��ռ�������ֽڣ����������Ϊ����������ֻ�ܳԵ�һ��
				break;

			if (createTimes > 500)//��ʱ
			{
				createFlag = 0;
				break;
			}
		}

		//����ʳ��
		if (createFlag)
		{
			gotoxy(food.x, food.y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//Ĭ�ϰ�ɫ
			printf("��");

			snake.len++;
			snake.x.resize(snake.len, 0);
			snake.y.resize(snake.len, 0);
			score += 1;
			snake.speed -= snake.speedChange;
			eatFlag = 1;//���ò�����β			
						
			//��ӡ������
			gotoxy(0, 0);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			std::cout << "Score: " << score;

			//�Ե�ʳ���ı���ɫ
			do
			{
				color[1] = rand() % 6 + 1;
			} while (color[1] == color[0]);
			color[0] = color[1];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[1]);
		}


	}

	return;
}
bool GameSnake::Status()//�����ж�
{
	if (modelChoice == 2)//Noobģʽ
	{
		//�����߽磬����һ�ߴ���
		if (snake.y[0] < 2 || snake.y[0] > MAPHEIGHT - 2)
		{
			crossFlag = 1;//ch����move�ж�ȡ���̵Ŀ��أ���Խ�߽�ʱ������ת��
			gotoxy(snake.x[0], snake.y[0]);
			printf("  ");
			snake.y[0] = MAPHEIGHT - snake.y[0];
			gotoxy(snake.x[0], snake.y[0]);
			printf("��");
			return true;
		}
		if (snake.x[0] < 4 || snake.x[0] > MAPWIDTH - 4)
		{
			crossFlag = 1;
			gotoxy(snake.x[0], snake.y[0]);
			printf("  ");
			snake.x[0] = MAPWIDTH - snake.x[0] + 1;//+1 ������żһ��
			gotoxy(snake.x[0], snake.y[0]);
			printf("��");
			return true;
		}
	}
	else//��modelChoice=0,1
	{
		//�����߽磬��Ϸ����
		if (snake.y[0] < 1 || snake.y[0] > MAPHEIGHT - 1)
			return false;
		if (snake.x[0] < 1 || snake.x[0] > MAPWIDTH - 2)
			return false;

		//������������Ϸ����
		if (modelChoice == 0)//Normalģʽ
			for (int i = 1; i < snake.len; i++)
			{
				if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
					return false;
			}
		return true;
	}
	return true;
}
void GameSnake::Model()
{
	while (1) {
		Map();
		logo();
		//�ٶȺ��Ѷȣ������ж�������ʼ��Ϸ
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 2);
		printf("Back -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
		printf("Start-> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
		printf("Long -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
		printf("Speed-> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
		printf("Model-> ");

		switch (updown(5))
		{
		case 0://�Ѷ�ѡ��
		{
			Map();
			logo();
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
			printf("Noob->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
			printf("Easy->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
			printf("Normal->");
			modelChoice = updown(3);
			break;
		}
		case 1://�ٶ�ѡ��
		{
			Map();
			logo();
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
			printf("Crazy->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
			printf("Slow->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
			printf("Normal->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
			printf("Fast->  ");
			switch (updown(4))
			{
			case 0: snake.speed = 100; break;
			case 1: snake.speed = 150; break;
			case 2: snake.speed = 200; break;
			case 3:snake.speed = 1; snake.speedChange = 0; break;
			}
			break;
		}
		case 2://��ʼ����
		{
			do
			{
				gotoxy(MAPWIDTH / 2 + 2, MAPHEIGHT - 6);
				printf("Enter: ");
				std::cin >> snake.len;
			} while (snake.len < 1);
			break;
		}
		case 3://��ʼ��Ϸ
		{
			startFlag = 1;
			return;
		}

		case 4://�������˵�
			startFlag = 0; return;//������Ϸ�������˳����������˵�
		}
	}
}

	void GameSnake::Start()
	{
		//����
		autoFlag = 0;//�Զ�ģʽ��
		findFlag = 0;//Ѱ·ģʽ��
		modelChoice = 0;//Ĭ��ģʽΪNormal
		snake.speed = 150;
		snake.len = 3;
		key = 72;//Ĭ�Ϸ���
		score = 0;

		Model();
		Init();
		if (!startFlag)return;
		while (snake.speed > 0)
		{
			if (!Status())
				break;
			Move();
			Food();
			Sleep(snake.speed);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//Ĭ�ϰ�ɫ
		gotoxy(snake.x[0], snake.y[0]);
		Sleep(2000);
		logo();
		gotoxy(MAPWIDTH / 2 - 9, MAPHEIGHT - 10);
		printf("Game Over!\n");
		gotoxy(MAPWIDTH / 2 - 9, MAPHEIGHT - 8);
		printf("Score��%d\n", score);
		gotoxy(MAPWIDTH, 0);
		Sleep(3000);
		while (_kbhit())modelChoice = _getch();
		gotoxy(MAPWIDTH / 2 - 9, MAPHEIGHT - 6);
		printf("Press R to replay");
		gotoxy(MAPWIDTH, 0);
		char ch = _getch();
		if (ch == 'r' || ch == 'R') Start();
		else return;
	}

	GameSnake::GameSnake()
	{
		Start();
	}