#include "main.h"
void show_menu();


int main(void) 
{
	check_file();
    show_menu();
    return 0;
}



void show_menu() {
    CLS;
    int x = 35, y = 5;

    gotoxy(x, y++);printf("┌──────────────────────────────────────────┐");
    for (int i = 0; i < 18; i++) {gotoxy(x, y++);printf("│                                          │");}
    gotoxy(x, y++);printf("└──────────────────────────────────────────┘");
    gotoxy(x + 15, 6);  printf("☆  서원 문고 ☆");
    gotoxy(x + 12, 10); printf("1. 로그인     (Login)");
    gotoxy(x + 12, 14); printf("2. 회원가입   (Sign Up)");
    gotoxy(x + 12, 18); printf("3. 종료       (Exit)");


    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);  //위에 두개 이건 한번만 사용하면 됨.


    while (1) 
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //이건 배경 색상 변경용
        if (mouse_click(46, 9, 68, 10)) {
            gotoxy(47, 10);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("1. 로그인      (Login)");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(170);
			login_menu();
            break;
        }

        if (mouse_click(46, 13, 68, 14)) {
            gotoxy(47, 14);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("2. 회원가입    (Sign Up)");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(170);
            register_menu();
            break;
        }

        if (mouse_click(46, 17, 68, 18)) {
            gotoxy(47, 18);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("3. 종료        (Exit)");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(170);
            exit(0);
        }
    }
}
