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

inline int updown(int num_of_choice);//����ѡ��ģʽ,����Ϊѡ����Ŀ,����ֵΪ��ѡ�����Ŀ

void logoMain();

inline void Map();

void info();

void log();
	