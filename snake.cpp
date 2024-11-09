#include "snake.h"

void HideCursor() { // Ẩn con trỏ soạn thảo
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;  // Ẩn con trỏ
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void Setup() {
    gameOver = false;
    paused = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    lastMoveTime = GetTickCount(); // Lấy thời gian hiện tại
}

void Draw() {

}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'p':
            paused = !paused;
            if (paused == false) system("cls");
            break;
        case 'x':
            cout << "Are you sure you want to quit? (y/n):";
            char confirm;
            confirm = _getch();
            if (confirm == 'y' || confirm == 'Y') gameOver = true;
            system("cls");
            break;
        }
    }
}

void Logic() {

}

void ShowInstructions() {

}

void GameOverScreen() {

}