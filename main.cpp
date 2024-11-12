#include "snake.cpp"

// Khúc này là phần chạy game nè
int main() 
{
    HideCursor();
    srand(static_cast<unsigned int>(time(0)));
    ShowInstructions();
    SetupGameSettings();
    Setup();
    while (true) {
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(10);  // Tạm dừng ngắn chỉ để giảm tải CPU
        }
        GameOverScreen();
        if (gameOver) break;
    }
    return 0;
}