#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h> 
#include "fun.h"
#include "main.h"
void register_menu();
void check_register(char id[], char pw[]);
int check_already_id(char id[]);
void register_success();