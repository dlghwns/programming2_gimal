#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#define CLS system("cls")
#define PAUSE system("pause>nul")
void gotoxy(int x, int y);
void printclickpos();
void check_file();
void disable_mouse_input();
void enable_mouse_input();
int mouse_click(SHORT x1, SHORT y1, SHORT x2, SHORT y2);