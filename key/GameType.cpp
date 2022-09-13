#include "GameType.h"

void GameType::Start()
{
	//打开文件
	std::fstream wordList;
	wordList.open("D:\\words.txt", std::ios::in);
	if (!wordList.is_open())
	{
		printf("OPEN FILE ERROR!");
		exit(EXIT_FAILURE);
	}

	//初始化界面
	Map();
	gotoxy(MAPWIDTH / 2 - 4, 1);
	printf("Type");
	gotoxy(MAPWIDTH / 2 - 10, 2);
	printf("Press 1 to start");
	gotoxy(0, 0);
	while (startFlag = _getch())if (startFlag == '1')break;
	Sleep(1000);

	timeuse = (int)time(0);
	numRight = 0;
	for (int i = 0; i < 10; i++)
	{
		wordList.clear();
		wordList.seekp(0, std::ios::beg);
		srand((unsigned)time(0) + rand());
		randomLine = rand() % 40 + 1;
		while (--randomLine)getline(wordList, readLine);//移动到第x行后读取,丢弃前x-1行
		getline(wordList, readLine);
		gotoxy(MAPWIDTH / 2 - 8, 3 + i * 2);
		std::cout << readLine;
		gotoxy(MAPWIDTH / 2 - 8, 4 + i * 2);
		std::cin >> typeLine;
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
	printf("Press R to replay");
	char ch = _getch();
	if (ch == 'r' || ch == 'R') Start();
	return;
}

GameType::GameType()
{
	Start();
}
