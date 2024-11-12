#include "snake.h"

void HideCursor() { // Ẩn con trỏ soạn thảo
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;  // Ẩn con trỏ
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

