#include "GameGuess.h"

void GameGuess::init() {
	guessNum = 0;
	guessTimes = 0;
	srand((unsigned)time(NULL)+rand());
	randomNum = rand() % 100 + 1;//随机数
}

void GameGuess::load() {
	//初始化界面
	showMap();
	gotoxy(MAPWIDTH / 2 - 9, 1);
	printf("Guess Number");
}

bool GameGuess::run()
{
	for (guessTimes = 1; guessTimes <= 10; guessTimes++)
	{
		gotoxy(MAPWIDTH / 2 - 9, 1 + 2 * guessTimes);
		printf("Guess(1-100): ");
		std::cin >> guessNum;
		gotoxy(MAPWIDTH / 2 - 9, 2 + 2 * guessTimes);
		if (guessNum > randomNum)printf("smaller\n");
		else if (guessNum < randomNum)printf("bigger\n");
		else
		{
			printf("WINNER\n");
			break;
		}
	}
	gotoxy(MAPWIDTH / 2 - 9, 3 + 2 * guessTimes);
	switch (guessTimes)
	{
	case 11:printf("Lose!\n"); break;
	case 10:
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
	gotoxy(MAPWIDTH / 2 - 9, 5 + 2 * guessTimes);
	printf("Press R to replay");
	char ch = _getch();
	if (toupper(ch) == 'R') return true;
	return false;
}

GameGuess::GameGuess()
{
	start();
}
