#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include "fun.h"
#include "main.h"
#include "user_menu.h"
#include "settings.h"


int settings(char id[])
{
    int cursor = 0;
    int key;
    int x = 2, y = 1;

    char* menu[3] = { "잔액충전", "로그아웃", "회원탈퇴" };
    int menu_count = 3;

    while (1)
    {
        system("cls");

        gotoxy(x, y);
        printf("┌──────────────────────────────────────────────────────────────┐");
        gotoxy(x, y + 1);
        printf("│                             설정                             │");
        gotoxy(x, y + 2);
        printf("├──────────────────────────────────────────────────────────────┤");
        gotoxy(x, y + 3);
        printf("│                                                              │");

        for (int i = 0; i < menu_count; i++)
        {
            gotoxy(x, y + 4 + i);

            if (cursor == i)
                printf("│                       ▶  %-12s  ◀                     │", menu[i]);
            else
                printf("│                          %-12s                        │", menu[i]);
        }
        gotoxy(x, y + 7);
        printf("│                                                              │");
        gotoxy(x, y + 8);
        printf("│                                                              │");
        gotoxy(x, y + 9);
        printf("├──────────────────────────────────────────────────────────────┤");
        gotoxy(x, y + 10);
        printf("│           ↑↓ 이동        Enter 선택       ESC 뒤로           │");
        gotoxy(x, y + 11);
        printf("└──────────────────────────────────────────────────────────────┘");

        key = _getch();

        if (key == 224)
        {
            key = _getch();
            if (key == 72 && cursor > 0) cursor--;
            else if (key == 80 && cursor < menu_count - 1) cursor++;
        }
        else if (key == 13)
        {
            if (cursor == 0) charge_money();
            else if (cursor == 1) { show_menu(); return 0; }
            else if (cursor == 2) { delete_account(id); show_menu(); return 0; }
        }
        else if (key == 27) user_menu(id);
    }
}


void delete_account(char id[])
{
    int x = 2, y = 2;
    int key;

    while (1)
    {
        system("cls");
        gotoxy(x, y);     printf("┌─────────────────────────────────────────────────────────────────────┐");
        gotoxy(x, y + 1); printf("│                      정말 탈퇴하시겠습니까?                         │");
        gotoxy(x, y + 2); printf("├─────────────────────────────────────────────────────────────────────┤");
        gotoxy(x, y + 3); printf("│              [  Yes (Y) ]                    [  No (N) ]            │");
        gotoxy(x, y + 4); printf("└─────────────────────────────────────────────────────────────────────┘");

        key = _getch();

        if (key == 'y' || key == 'Y')
        {
            system("cls");
            printf("회원 탈퇴가 완료되었습니다.\n");
            system("pause");
            return;
        }
        else if (key == 'n' || key == 'N' || key == 27)
        {
            settings(id);
        }
    }
}

void charge_money()
{
    extern int money;

    int x = 2, y = 2;
    int amount = 0;

    while (1)
    {
        system("cls");

        gotoxy(x, y);     printf("┌──────────────────────────────────────────────────────────┐");
        gotoxy(x, y + 1); printf("│                      잔액 충전하기                       │");
        gotoxy(x, y + 2); printf("├──────────────────────────────────────────────────────────┤");
        gotoxy(x, y + 3); printf("│   충전 금액을 입력하세요 (1만원 단위 / 최소 1만원)       │");
        gotoxy(x, y + 4); printf("│                                                          │");
        gotoxy(x, y + 5); printf("│   입력: ");
        printf("%9d원                                      │", amount);
        gotoxy(x, y + 6); printf("│                                                          │");
        gotoxy(x, y + 7); printf("├──────────────────────────────────────────────────────────┤");
        gotoxy(x, y + 8); printf("│   Enter: 확인    ESC: 취소                               │");
        gotoxy(x, y + 9); printf("└──────────────────────────────────────────────────────────┘");

        int key = _getch();

        if (key == 27) return;    // ESC → 취소

        else if (key == 13)       // Enter
        {
            if (amount >= 10000 && amount % 10000 == 0)
            {
                money += amount;
                system("cls");
                printf("충전 완료! 현재 잔액: %d원\n", money);
                system("pause");
                return;
            }
            else
            {
                system("cls");
                printf("잘못된 금액입니다.\n1만원 단위, 최소 1만원 이상 입력하세요.\n");
                system("pause");
            }
        }
        // 숫자 입력
        else if (key >= '0' && key <= '9')
        {
            amount = amount * 10 + (key - '0');
        }
        // 백스페이스
        else if (key == 8)
        {
            amount /= 10;
        }
    }
}