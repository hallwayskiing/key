#include "GameType.h"

void GameType::init() {
	best_time = 999;
	best_num = 0;
	lineNum = 0;
	wordList.open("words.txt", std::ios::in);
	if (!wordList.is_open())
	{
		printf("OPEN FILE ERROR!");
		exit(EXIT_FAILURE);
	}
	while (wordList.good()) {
		lineNum++;
		std::string str;
		getline(wordList, str);
	}
}

void GameType::load() {
	//初始化界面
	showMap();
	gotoxy(MAPWIDTH / 2 - 4, 1);
	printf("Type");
	gotoxy(MAPWIDTH / 2 - 10, 2);
	printf("Press 1 to start");
	gotoxy(0, 0);
	char startFlag;
	while (startFlag = _getch())if (startFlag == '1')break;
	Sleep(1000);
}

bool GameType::run()
{
	std::string readLine, typeLine;
	int timeuse = (int)time(0);
	int numRight = 0;
	for (int i = 0; i < 10; i++)
	{
		wordList.clear();
		wordList.seekp(0, std::ios::beg);
		srand((unsigned)time(0) + rand());
		int randomLine = rand() % lineNum;
		while (randomLine-->0)getline(wordList, readLine);//移动到第x行后读取,丢弃前x-1行
		getline(wordList, readLine);
		gotoxy(MAPWIDTH / 2 - 8, 3 + i * 2);
		std::cout << readLine;
		gotoxy(MAPWIDTH / 2 - 8, 4 + i * 2);
		getline(std::cin, typeLine);
		if (readLine == typeLine) numRight++;
	}
	timeuse = (int)time(0) - timeuse;
	if (timeuse < best_time)best_time = timeuse;
	if (numRight > best_num)best_num = numRight;
	gotoxy(MAPWIDTH / 2 - 8, 24);
	printf("Game over!");
	gotoxy(MAPWIDTH / 2 - 8, 25);
	printf("Time use: %d   Best: %d", timeuse, best_time);
	gotoxy(MAPWIDTH / 2 - 8, 26);
	printf("Score: %d      Best: %d", numRight * 10, best_num * 10);
	gotoxy(MAPWIDTH / 2 - 8, 27);
	wordList.close();
	printf("Press R to replay");
	char ch = _getch();
	if (toupper(ch) == 'R') return true;
	return false;
}

GameType::GameType()
{
	start();
}
