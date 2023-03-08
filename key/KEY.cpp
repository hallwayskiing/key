#include"GameBall.h"
#include"GameGuess.h"
#include"GameSnake.h"
#include"GameType.h"

//#define RELEASE

int main()
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT wrt = { 0, 0, MAPWIDTH, MAPHEIGHT };
	SetConsoleWindowInfo(hStdOutput, TRUE, &wrt); // 设置窗体尺寸
	COORD coord = { MAPWIDTH, MAPHEIGHT };
	SetConsoleScreenBufferSize(hStdOutput, coord); // 设置缓冲尺寸

#ifdef RELEASE

	log();

#endif // DEBUG

	while (1) {
		showMap();
		showMainLogo();
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 2);
		printf("Quit -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
		printf("Ball -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
		printf("Snake-> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
		printf("Type -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
		printf("Guess-> ");
		Game* game = nullptr;
		switch (choose(5))
		{
		case 0:
			game = new GameGuess();
			break;
		case 1:
			game = new GameType();
			break;
		case 2:
			game = new GameSnake();;
			break;
		case 3:
			game = new GameBall();;
			break;
		case 4:
			return 0;
		}
		delete game;
	}
}
