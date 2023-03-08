#include "GameSnake.h"

void GameSnake::showLogo()
{
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 23);
	printf("  ■■■      ■■■      ■■■      ■    ■      ■■ \n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 22);
	printf("■          ■     ■    ■     ■    ■   ■     ■     ■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 21);
	printf("■          ■     ■    ■     ■    ■  ■      ■     ■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 20);
	printf("  ■■      ■     ■    ■     ■    ■■        ■■■■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 19);
	printf("       ■   ■     ■    ■     ■    ■  ■      ■      \n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 18);
	printf("       ■   ■     ■    ■     ■    ■   ■     ■       \n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT - 17);
	printf(" ■■■     ■     ■     ■■■ ■   ■    ■     ■■■");
}

void GameSnake::move()
{
	int pre_key = key;//记录前一个按键的方向
	if (!crossFlag)//穿越边界时不允许转弯
	{
		switch (moveMode)
		{
		case MoveMode::AUTO://自动模式下用随机方向代替用户输入
			if (!_kbhit())//按任意键退出自动模式
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
			else moveMode = MoveMode::NORMAL;
			break;
		case MoveMode::FIND://寻路模式
			if (!_kbhit())
			{
				if (food.x > snake.x[0])key = 77;//右
				else if (food.x < snake.x[0])key = 75;//左
				if (food.x == snake.x[0])
					if (food.y > snake.y[0])key = 80;//下
					else if (food.y < snake.y[0])key = 72;//上
			}
			else moveMode = MoveMode::NORMAL;
			break;
		case MoveMode::NORMAL://正常模式
			if (_kbhit())//如果用户按下了键盘中的某个键
			{
				//getch()读取方向键的时候，会返回两次，第一次调用返回0或者224
				switch (key = _getch())//第一次调用返回的不是实际值
				{
				case 0://判断是否为方向键
				case 224:key = _getch(); break;//第二次调用返回实际值
				case 'a':
				case 'A'://按A开启自动模式
				{
					moveMode = MoveMode::AUTO;
					key = pre_key;
					break;
				}
				case 'f':
				case 'F'://按F开启寻路模式
				{
					moveMode = MoveMode::FIND;
					key = pre_key;
					break;
				}
				case 27://按ESC退出
					snake.speed = 0; break;
				default: key = pre_key; break;
				}
			}
			break;
		}
	}

	/*
	*蛇移动时候先擦去蛇尾的一节
	*eatFlag为0表明此时没有吃到食物，因此每走一步就要擦除掉蛇尾，以此营造一个移动的效果
	*为1表明吃到了食物，就不需要擦除蛇尾，以此营造一个蛇身增长的效果
	*/
	if (eatFlag == 0)
	{
		gotoxy(snake.x[static_cast<std::vector<int, std::allocator<int>>::size_type>(snake.len) - 1], snake.y[static_cast<std::vector<int, std::allocator<int>>::size_type>(snake.len) - 1]);
		printf("  ");//擦去蛇尾
	}

	//将蛇身的每一节依次向前移动一节
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) - 1];
		snake.y[i] = snake.y[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) - 1];
	}

	//如果当前移动方向和前一次方向相反，把当前移动的方向改为前一次的方向
	if (pre_key == 72 && key == 80)
		key = 72;
	if (pre_key == 80 && key == 72)
		key = 80;
	if (pre_key == 75 && key == 77)
		key = 75;
	if (pre_key == 77 && key == 75)
		key = 77;

	//判断移动方向
	switch (key)
	{
	case 75:
		snake.x[0] -= 2;//往左
		break;
	case 77:
		snake.x[0] += 2;//往右
		break;
	case 72:
		snake.y[0]--;//往上
		break;
	case 80:
		snake.y[0]++;//往下
		break;
	}

	//打印出蛇头
	gotoxy(snake.x[0], snake.y[0]);
	HWND hWnd = GetConsoleWindow();
	printf("■");
	gotoxy(MAPWIDTH, 0);

	//由于目前没有吃到食物，changFlag值为0
	eatFlag = 0;
	crossFlag = 0;
	return;
}

void GameSnake::newFood()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y || createFlag == 0)//蛇头碰到食物 或者 上次未生成
	{
		createFlag = 1;
		createTimes = 1;
		srand((unsigned)time(0) + rand());
		while (createTimes++)//再次生成食物
		{
			int flag = 1;
			food.x = rand() % (MAPWIDTH - 16) + 8;
			food.y = rand() % (MAPHEIGHT - 8) + 4;

			//随机生成的食物不能在蛇的身体上
			for (int i = 0; i < snake.len; i++)
			{
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			}

			if (food.x == snake.x[0] || food.y == snake.y[0])flag = 0;

			if (flag == 1 && food.x % 2 == 1)//因为★占用两个字节，横坐标必须为奇数，否则只能吃到一半
				break;

			if (createTimes > 500)//超时
			{
				createFlag = 0;
				break;
			}
		}

		//绘制食物
		if (createFlag)
		{
			gotoxy(food.x, food.y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//默认白色
			printf("★");

			snake.len++;
			snake.x.resize(snake.len, 0);
			snake.y.resize(snake.len, 0);
			score += 1;
			snake.speed -= snake.speedChange;
			eatFlag = 1;//不用擦除蛇尾			
						
			//打印出分数
			gotoxy(0, 0);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			std::cout << "Score: " << score;

			//吃到食物后改变颜色
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

bool GameSnake::status()//死亡判定
{
	if (gameMode == GameMode::NOOB)//Noob模式
	{
		//碰到边界，从另一边穿出
		if (snake.y[0] < 2 || snake.y[0] > MAPHEIGHT - 2)
		{
			crossFlag = 1;//crossFlag控制move中读取键盘的开关，穿越边界时不允许转弯
			gotoxy(snake.x[0], snake.y[0]);
			printf("  ");
			snake.y[0] = MAPHEIGHT - snake.y[0];
			gotoxy(snake.x[0], snake.y[0]);
			printf("■");
			return true;
		}
		if (snake.x[0] < 4 || snake.x[0] > MAPWIDTH - 4)
		{
			crossFlag = 1;
			gotoxy(snake.x[0], snake.y[0]);
			printf("  ");
			snake.x[0] = MAPWIDTH - snake.x[0] + 1;//+1 保持奇偶一致
			gotoxy(snake.x[0], snake.y[0]);
			printf("■");
			return true;
		}
	}
	else//不是NOOB模式
	{
		//碰到边界，游戏结束
		if (snake.y[0] < 1 || snake.y[0] > MAPHEIGHT - 1)
			return false;
		if (snake.x[0] < 1 || snake.x[0] > MAPWIDTH - 2)
			return false;

		//碰到蛇身，游戏结束
		if (gameMode == GameMode::NORMAL)//Normal模式
			for (int i = 1; i < snake.len; i++)
			{
				if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
					return false;
			}
		return true;
	}
	return true;
}

bool GameSnake::chooseMode()
{
	while (1) {
		showMap();
		showLogo();
		//速度和难度（死亡判定）、开始游戏
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 2);
		printf("Back -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
		printf("Start-> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
		printf("Long -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
		printf("Speed-> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
		printf("Mode -> ");

		switch (choose(5))
		{
		case 0://难度选择
		{
			showMap();
			showLogo();
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
			printf("Noob->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
			printf("Easy->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
			printf("Normal->");
			switch (choose(3)) {
			case 0:gameMode = GameMode::NORMAL; break;
			case 1:gameMode = GameMode::EASY; break;
			case 2:gameMode = GameMode::NOOB; break;
			}
			break;
		}
		case 1://速度选择
			showMap();
			showLogo();
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
			printf("Crazy->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
			printf("Fast->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
			printf("Normal->");
			gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
			printf("Slow->  ");
			switch (choose(4))
			{
			case 0: snake.speed = 200; break;
			case 1: snake.speed = 150; break;
			case 2: snake.speed = 100; break;
			case 3:snake.speed = 1; snake.speedChange = 0; break;
			}
			break;
		case 2://初始长度
			gotoxy(MAPWIDTH / 2 + 2, MAPHEIGHT - 6);
			printf("Enter: ");
			std::cin >> snake.len;
			break;
		case 3://开始游戏
			return true;
		case 4://返回主菜单
			return false;//进入游戏后立刻退出，返回主菜单
		}
	}
}

void GameSnake::init()//初始化
{
	//重置参数
	gameMode = GameMode::NORMAL;//默认游戏模式为NORMAL
	moveMode = MoveMode::NORMAL;//默认移动模式为NORMAL
	crossFlag = 0;//转弯控制关
	key = 72;//默认方向：上
	eatFlag = 0;//吃到食物的标志
	createFlag = 1;//生成食物的标志
	createTimes = 0;
	snake.speed = 150;
	snake.speedChange = 2;
	snake.len = 3;
	score = 0;
}

void GameSnake::load() {
	showMap();
	srand((unsigned)time(0) + rand());
	while (1)
	{
		food.x = rand() % (MAPWIDTH - 2) + 2;
		food.y = rand() % (MAPHEIGHT - 1) + 1;
		//生成的食物横坐标必须与初始化时蛇头所在坐标的奇偶一致，因为一个字符占两个字节位置，若不一致会导致吃食物的时候只吃到一半
		if (food.x % 2 == 1)
			break;
	}

	snake.x.resize(snake.len, 0);
	snake.y.resize(snake.len, 0);

	//将光标移到食物的坐标处打印食物
	gotoxy(food.x, food.y);
	printf("★");
	//在屏幕中间生成蛇头
	snake.x[0] = MAPWIDTH / 2;
	snake.y[0] = MAPHEIGHT / 2;
	//打印蛇头
	gotoxy(snake.x[0], snake.y[0]);
	printf("■");

	//生成初始蛇身
	for (int i = 1; i < snake.len; i++)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1] + 1;
		gotoxy(snake.x[i], snake.y[i]);
		printf("■");
	}

	//生成初始分数条
	gotoxy(0, 0);
	printf("Score: 0");

	//初始化结束后将光标移到屏幕最上方，避免光标在蛇身处一直闪烁
	gotoxy(MAPWIDTH, 0);
	return;
}

bool GameSnake::run()
{
	while (snake.speed > 0)
	{
		if (!status())
			break;
		move();
		newFood();
		Sleep(snake.speed);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//默认白色
	gotoxy(snake.x[0], snake.y[0]);
	Sleep(2000);
	showLogo();
	gotoxy(MAPWIDTH / 2 - 9, MAPHEIGHT - 10);
	printf("Game Over!\n");
	gotoxy(MAPWIDTH / 2 - 9, MAPHEIGHT - 8);
	printf("Score：%d\n", score);
	gotoxy(MAPWIDTH, 0);
	Sleep(3000);
	gotoxy(MAPWIDTH / 2 - 9, MAPHEIGHT - 6);
	printf("Press R to replay");
	gotoxy(MAPWIDTH, 0);
	char ch = _getch();
	if (toupper(ch) == 'R') return true;
	return false;
}

GameSnake::GameSnake()
{
	start();
}
