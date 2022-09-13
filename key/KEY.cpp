#include"GameBall.h"
#include"GameGuess.h"
#include"GameSnake.h"
#include"GameType.h"

#define RELEASE

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
		Map();
        logoMain();
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
		switch (updown(5))
		{
		case 0:
		{
			GameGuess Guess;
			break;
		}
		case 1:
		{
			GameType Type;
			break;
		}
		case 2:
		{
			GameSnake Snake;
			break;
		}
		case 3:
		{
			GameBall Ball;
			break;
		}
		case 4:
			return 0;
		}
	}

	return 0;
}
