#include "fun.h"

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void check_file() 
{
    char folder[MAX_PATH];
    char file[MAX_PATH];

    char* appdata = getenv("APPDATA");
    if (!appdata) return;  // APPDATA 환경변수 없으면 종료

    sprintf(folder, "%s\\SW_BOOKSTORE", appdata);

    // 폴더가 없으면 생성
    if (GetFileAttributesA(folder) == INVALID_FILE_ATTRIBUTES) {
        if (!CreateDirectoryA(folder, NULL)) {
            printf("폴더 생성 실패, 오류코드: %lu\n", GetLastError());
            return;
        }
    }

    // 파일 경로 생성
    sprintf(file, "%s\\userdata.txt", folder);

    // 파일 없으면 생성
    FILE* fp = fopen(file, "a");
    if (fp) fclose(fp);
}

void printclickpos() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD rec;
    DWORD read;

    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    ReadConsoleInput(hInput, &rec, 1, &read);

    if (rec.EventType == MOUSE_EVENT) {
        if (rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            COORD pos = rec.Event.MouseEvent.dwMousePosition;
            gotoxy(10, 90);  printf("X: %d, Y: %d", pos.X, pos.Y);
        }
    }
}

// x1, y1: 좌상단 좌표 x2, y2: 우하단 좌표
int mouse_click(SHORT x1, SHORT y1, SHORT x2, SHORT y2) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD rec;
    DWORD read;

    // 이벤트가 버퍼에 있는지 확인 (Peek)
    if (PeekConsoleInput(hInput, &rec, 1, &read) && read > 0) {

        // 이벤트를 버퍼에서 제거 (Read)
        // MOUSE_EVENT이든 KEY_EVENT이든 일단 소모하여 버퍼를 정리
        ReadConsoleInput(hInput, &rec, 1, &read);

        // 제거된 이벤트가 마우스 클릭 이벤트인지 확인
        if (rec.EventType == MOUSE_EVENT &&
            rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {

            COORD pos = rec.Event.MouseEvent.dwMousePosition;

            // 좌표 내 클릭인지 확인
            if ((pos.X >= x1 && pos.X <= x2) && (pos.Y >= y1 && pos.Y <= y2)) {
                return 1; // 클릭 감지
            }
        }
        // 마우스 클릭이 아니거나 다른 이벤트(키보드 등)는 0을 반환하고 종료
    }
    return 0;
}



void disable_mouse_input()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~ENABLE_MOUSE_INPUT); // 마우스 입력 끔
}

// 마우스 모드 켜기
void enable_mouse_input()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode | ENABLE_MOUSE_INPUT); // 마우스 입력 켬
}