#include "GameGuess.h"

void GameGuess::Start()
{
	srand((unsigned)time(NULL));
	randomNum = rand() % 100 + 1;//随机数

	//初始化界面
	Map();
	gotoxy(MAPWIDTH / 2 - 9, 1);
	printf("Guess Number");

	for (guessTime = 1; guessTime <= 10; guessTime++)
	{
		gotoxy(MAPWIDTH / 2 - 9, 1 + 2 * guessTime);
		printf("Guess(1-100): ");
		std::cin >> guessNum;
		gotoxy(MAPWIDTH / 2 - 9, 2 + 2 * guessTime);
		if (guessNum > randomNum)printf("smaller\n");
		else if (guessNum < randomNum)printf("bigger\n");
		else
		{
			printf("WINNER\n");
			break;
		}
	}
	gotoxy(MAPWIDTH / 2 - 9, 3 + 2 * guessTime);
	switch (guessTime)
	{
	case 10:printf("Lose!\n"); break;
	case 9:
	case 8: printf("Bad!\n"); break;
	case 7:
	case 6:
	case 5: printf("Good!\n"); break;
	case 4:
	case 3:
	case 2: printf("Excellent!\n"); break;
	case 1: printf("Lucky!\n"); break;
	}
	gotoxy(MAPWIDTH / 2 - 9, 5 + 2 * guessTime);
	printf("Press R to replay");
	char ch = _getch();
	if (ch == 'r' || ch == 'R') Start();
	return;
}

GameGuess::GameGuess()
{
	Start();
}
