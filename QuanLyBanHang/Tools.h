#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

extern HANDLE hConsole;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;
extern WORD defaultWordAttributes;
extern int width;
extern int height;

//Khai b�o c�c h�m cua tools
void initRandomSeed();
int getRandNum();
void alignTextPositionWidth(std::string text, float n);
void alignTextPositionHeight(float n);
void getDefaultAttribute();
void resetColor();
void textColor(int n);