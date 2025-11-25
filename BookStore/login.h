#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h> 
#include "fun.h"
#include "main.h"
#include "user_menu.h"

#define CLS system("cls")
#define PAUSE system("pause>nul")
void login_menu();
int check_login(char id[], char pw[]);
