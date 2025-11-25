#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include "fun.h"
#include "main.h"
#include "user_menu.h"

int book_count = 0;
int money = 0;

void user_menu(char id[])
{
    system("cls");
    load_books();

    int page = 0;
    char search[100] = {0};
    int filtered_index[MAX_BOOKS];
    int filtered_count = book_count;

    for (int i = 0; i < book_count; i++) filtered_index[i] = i;

    while (1)
    {
        system("cls");
        int x = 2, y = 2;


        gotoxy(x, y);
        printf("┌──────────────────────────────────────────────────────────────────────────────────────────────┐");

        gotoxy(x, y + 1);
        printf("│ 도서검색 : %-67s(Enter로 검색) │", search);

        gotoxy(x, y + 2);
        printf("│                 (코드, 도서명, 작가명, 출판사명)                                             │");

        gotoxy(x, y + 3);
        printf("├──────────────────────────────────────────────────────────────────────────────────────────────┤");

        gotoxy(x, y + 4);
        printf("│ 코드   제목                        작가                           출판사      가격     수량  │");

        gotoxy(x, y + 5);
        printf("├──────────────────────────────────────────────────────────────────────────────────────────────┤");

        for (int i = 0; i < 5; i++)
        {
            int idx = page * 5 + i;
            gotoxy(2, 8 + i);

            if (idx < filtered_count)
            {
                Book b = books[filtered_index[idx]];
                printf("│ %-6s %-27s %-30s %-10s  %-7d%4d개  │",
                    b.code, b.title, b.author, b.publisher, b.price, b.count);
            }
            else
            {
                printf("│                                                                                              │");
            }
        }

        gotoxy(x, y + 11);
        printf("├──────────────────────────────────────────────────────────────────────────────────────────────┤");

        gotoxy(x, y + 12);
        printf("│                                      <   %d / %d   >                                           │",
            page + 1, (filtered_count + BOOKS_PER_PAGE - 1) / BOOKS_PER_PAGE);

        gotoxy(x, y + 13);
        printf("├──────────────────────────────────────────────────────────────────────────────────────────────┤");

        gotoxy(x, y + 14);
        printf("│ [내 서재]                                                                             [설정] │");

        gotoxy(x, y + 15);
        printf("├──────────────────────────────────────────────────────────────────────────────────────────────┤");

        gotoxy(x, y + 16);
        printf("│ [ %s님이 로그인 중입니다 ]                                       [보유 잔액 : %10d 원] │", id, money);

        gotoxy(x, y + 17);
        printf("└──────────────────────────────────────────────────────────────────────────────────────────────┘");

        gotoxy(16, 3);
        fflush(stdout);
        int ch = _getch();

        if (ch == 0 || ch == 224)
        {
            ch = _getch();
            if (ch == 75 && page > 0) page--;
            if (ch == 77 && page * 5 + 5 < filtered_count) page++;
        }
        else if (ch == 8)
        {
            size_t len = strlen(search);
            if (len > 0) search[len - 1] = '\0';
        }
        else if (ch == 27 || ch == 'q' || ch == 'Q') break;
        else if (ch == 'a' || ch == 'A') { my_library(id); continue; }
        else if (ch == 's' || ch == 'S')
        {
            settings(id);

            return;
        }
        else if (ch == 13)
        {

        }
        else if (strlen(search) < 90)
        {
            strncat(search, (char[]) { ch, 0 }, 1);
        }

        filtered_count = 0;
        for (int i = 0; i < book_count; i++)
            if (strstr(books[i].code, search) ||
                strstr(books[i].title, search) ||
                strstr(books[i].author, search) ||
                strstr(books[i].publisher, search))
            {
                filtered_index[filtered_count++] = i;
            }


        if (filtered_count > 0 && page * 5 >= filtered_count) page = 0;
    }
}

void load_books()
{
    FILE* fp = fopen("booklist.txt", "r");
    if (!fp)
    {
        printf("booklist.txt 파일을 열 수 없습니다.\n");
        system("pause");
        exit(1);
    }

    book_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';

        char* code = strtok(line, "|");
        char* title = strtok(NULL, "|");
        char* author = strtok(NULL, "|");
        char* publisher = strtok(NULL, "|");
        char* price = strtok(NULL, "|");

        if (!publisher || !price) continue;

        int exist = -1;
        for (int i = 0; i < book_count; i++)
        {
            if (!strcmp(books[i].title, title) &&
                !strcmp(books[i].author, author) &&
                !strcmp(books[i].publisher, publisher))
            {
                exist = i;
                break;
            }
        }

        if (exist != -1)
        {
            books[exist].count++;
        }
        else
        {
            strcpy(books[book_count].code, code);
            strcpy(books[book_count].title, title);
            strcpy(books[book_count].author, author);
            strcpy(books[book_count].publisher, publisher);
            books[book_count].price = atoi(price);
            books[book_count].count = 1;
            book_count++;
        }

        if (book_count >= MAX_BOOKS) break;
    }

    fclose(fp);
}


void my_library(char id[])
{
    system("cls");
    printf("[%s님의 서재]\n", id);
    printf("서재 기능\n");
    system("pause");
}
