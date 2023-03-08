#include "Engine.h"

using namespace std;

inline void gotoxy(int x, int y)
{
	COORD c{ (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

inline int choose(int x)//上下选择模式,参数为选项数目,返回值为已选择的项目
{
	int MOD = 0;
	COORD d{};
	d.X = MAPWIDTH / 2 + 1;
	d.Y = MAPHEIGHT - 10;
	while (1)
	{
		switch (_getch())
		{
		case 80:
			if (MOD != x - 1)//不允许越界
			{
				d.Y = d.Y + 2;
				gotoxy(d.X, d.Y);
				MOD++;
				break;
			}
			else continue;
		case 72:
			if (MOD != 0)
			{
				d.Y = d.Y - 2;
				gotoxy(d.X, d.Y);
				MOD--;
				break;
			}
			else continue;
		case 13:return MOD;
		}
	}
}

void showMainLogo()
{
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT *0.2);
	printf("  ■■■      ■       ■■         ■■■        ■■■  \n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT * 0.2 + 1);
	printf("■     ■            ■     ■    ■      ■    ■      ■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT * 0.2 + 2);
	printf("■     ■     ■     ■     ■    ■      ■    ■      ■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT * 0.2 + 3);
	printf("■     ■     ■     ■■■■     ■■■■■    ■■■■■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT * 0.2 + 4);
	printf("■     ■     ■     ■           ■      ■    ■      ■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT * 0.2 + 5);
	printf("■     ■     ■     ■           ■      ■    ■      ■\n");
	gotoxy(MAPWIDTH / 2 - 30, MAPHEIGHT * 0.2 + 6);
	printf("■     ■     ■      ■■■       ■■■■      ■■■■   ");
}

inline void showMap()
{
	system("cls");

	//打印上下边框
	for (int i = 0; i <= MAPWIDTH; i += 2)//i+=2是因为横向字符占用两个位置
	{
		gotoxy(i, 0);
		printf("-");
		gotoxy(i, MAPHEIGHT);
		printf("-");
	}

	//打印左右边框
	for (int i = 1; i < MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		printf("|");
		gotoxy(MAPWIDTH, i);
		printf("|");
	}
}

void info()
{
	showMap();
	showMainLogo();
	gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 10);
	printf("MADE BY: NIE88 ");
	gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 8);
	printf("QQ: 541814852 ");
	gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 6);
	printf("THANKS FOR USING ");
	gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
	printf("BACK-> ");
	int ch = _getch();
}

void log()
{
	fstream registerList;
	registerList.open("D:\\register.txt", ios::in | ios::out | ios::app);
	if (registerList.is_open() == false)
	{
		printf("OPEN FILE ERROR!\n");
		exit(EXIT_FAILURE);
	}
	while (1) {
		string usernameReg;
		string passwordReg;
		string usernameLog;
		string passwordLog;
		string readLine;
		showMap();
		showMainLogo();
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 4);
		printf("More -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 6);
		printf("Quit -> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 8);
		printf("Login-> ");
		gotoxy(MAPWIDTH / 2 - 7, MAPHEIGHT - 10);
		printf("Sign -> ");

		switch (choose(4))
		{
		case 0://注册
		{
			system("cls");
			showMap();
			showMainLogo();
			gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 10);
			printf("Account: ");
			cin >> usernameReg;
			gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 8);
			printf("Password: ");
			for (int i = 0; i <= 5; i++)
			{
				passwordReg.push_back(_getch());
				printf("*");
			}
			gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 6);
			printf("Success!");
			registerList << '\n' << usernameReg << passwordReg;

			Sleep(2000);
			break;
		}
		case 1://登陆
		{
			system("cls");
			showMap();
			showMainLogo();
			registerList.clear();
			registerList.seekp(0, ios::beg);
			gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 10);
			printf("Account: ");
			cin >> usernameLog;
			gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 8);
			printf("Password: ");
			for (int i = 0; i < 6; i++)
			{
				passwordLog.push_back(_getch());
				printf("*");
			}

			while (!registerList.eof())
			{
				getline(registerList, readLine);
				if (usernameLog + passwordLog == readLine)
				{
					gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 6);
					printf("Log in success!");
					registerList.close();
					Sleep(2000);
					return;
				}
			}
			gotoxy(MAPWIDTH / 2 - 10, MAPHEIGHT - 6);
			printf("Wrong account or password!");
			Sleep(2000);
			break;
		}
		case 2: //退出
		{
			registerList.close();
			exit(0);
		}
		case 3://信息
		{
			info();
			break;
		}
		}
	}
}