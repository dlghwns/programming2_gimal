#pragma once

#define MAX_BOOKS 100
#define BOOKS_PER_PAGE 5

typedef struct
{
    char code[10];
    char title[100];
    char author[100];
    char publisher[100];
    int price;
    int count;
} Book;

Book books[MAX_BOOKS];

void user_menu(char id[]);
void load_books();
void my_library(char id[]);