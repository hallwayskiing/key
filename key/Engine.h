#pragma once
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<string>
#include<Windows.h>
#include<time.h>
#include<fstream>
#include<vector>
#include<map>
#define MAPWIDTH 119 //119
#define MAPHEIGHT 29  //29

inline void gotoxy(int LocationX, int LocationY);

inline int choose(int num_of_choice);//上下选择模式,参数为选项数目,返回值为已选择的项目

void showMainLogo();

inline void showMap();

void info();

void log();
	
