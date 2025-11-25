#include "register.h"


void check_register(char id[], char pw[]);
int check_already_id(char id[]);
void register_success();

void register_menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);


    int x = 35, y = 5;
    char id[100] = { 0 }, id_c[100] = { 0 }, pw[100] = { 0 };
    int idx_id = 0, idx_idc = 0, idx_pw = 0; // 단계별 idx
    char c;
    int step = 0; // 0=ID, 1=ID확인, 2=PW

    CLS;

    // 화면 그리기
    gotoxy(x, y++); printf("┌──────────────────────────────────────────┐");
    for (int i = 0; i < 18; i++) { gotoxy(x, y++); printf("│                                          │"); }
    gotoxy(x, y++); printf("└──────────────────────────────────────────┘");
    gotoxy(x + 16, 6); printf("☆  회원가입 ☆");
    gotoxy(x + 5, 11); printf("아이디 : ");
    gotoxy(x + 5, 14); printf("아이디 확인 : ");
    gotoxy(x + 5, 17); printf("비밀번호 : ");
    gotoxy(x + 2, 23); printf("돌아가기");

    gotoxy(x + 14, 11);

    while (1) {
        enable_mouse_input();

        // 1. 키보드 처리
        if (_kbhit()) {
            c = _getch();
            enable_mouse_input(); // 키 입력 직후 마우스 모드 재활성화

            if (c == '\r') {  // Enter
                if (step == 0) { step = 1; gotoxy(x + 19, 14); }
                else if (step == 1) { step = 2; gotoxy(x + 16, 17); }
                else break;
            }
            else if (c == '\b') {  // Backspace
                if (step == 0 && idx_id > 0) { idx_id--; printf("\b \b"); }
                else if (step == 1 && idx_idc > 0) { idx_idc--; printf("\b \b"); }
                else if (step == 2 && idx_pw > 0) { idx_pw--; printf("\b \b"); }
            }
            else {
                if (step == 0 && idx_id < 99) { id[idx_id++] = c; putchar(c); }
                else if (step == 1 && idx_idc < 99) { id_c[idx_idc++] = c; putchar(c); }
                else if (step == 2 && idx_pw < 99) { pw[idx_pw++] = c; putchar('*'); }
            }
        }

        if (mouse_click(37, 23, 45, 23)) {
            show_menu();  // 돌아가기
            return;
        }

        Sleep(1);
    }

    // 각 단계마다 입력 종료 시 널문자 추가
    id[idx_id] = '\0';
    id_c[idx_idc] = '\0';
    pw[idx_pw] = '\0';

    // 아이디 확인
    if (strcmp(id, id_c) != 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        gotoxy(x + 9, 20); printf("아이디가 일치하지 않습니다.");
        gotoxy(x + 13, 21); printf("다시 시도해주세요.");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        PAUSE;
        register_menu();
        return;
    }

    // 이미 존재하는 ID 확인
    if (check_already_id(id)) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        gotoxy(x + 9, 20); printf("이미 존재하는 아이디입니다.");
        gotoxy(x + 13, 21); printf("다시 시도해주세요.");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        PAUSE;
        register_menu();
        return;
    }

    check_register(id, pw);
}

int check_already_id(char id[])
{
    char path[MAX_PATH];
    sprintf(path, "%s\\SW_BOOKSTORE\\userdata.txt", getenv("APPDATA"));

    FILE* fp = fopen(path, "r");
    if (!fp) return 0;  // 파일 없으면 사용 가능

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char f_id[100];
        if (sscanf(line, "%99s", f_id) == 1) {
            f_id[99] = '\0';

            if (strcmp(f_id, id) == 0) {
                fclose(fp);
                return 1; // 이미 존재하는 ID
            }
        }
    }
    fclose(fp);
    return 0;
}

// 회원정보 등록
void check_register(char id[], char pw[])
{
    char path[MAX_PATH];
    sprintf(path, "%s\\SW_BOOKSTORE\\userdata.txt", getenv("APPDATA"));

    FILE* fp = fopen(path, "a");
    if (!fp) return;

    int first_money = 100000;
    fprintf(fp, "%s %s %d\n", id, pw, first_money);
    fclose(fp);

    register_success();
}


void register_success()
{
    int x = 35, y = 5;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(x, y++); printf("┌──────────────────────────────────────────┐");
    for (int i = 0; i < 18; i++) { gotoxy(x, y++); printf("│                                          │"); }
    gotoxy(x, y++); printf("└──────────────────────────────────────────┘");
    gotoxy(x + 16, 6); printf("☆  회원가입 ☆");

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    gotoxy(x + 10, 12); printf("회원가입이 완료되었습니다!");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    PAUSE;
    show_menu();
}