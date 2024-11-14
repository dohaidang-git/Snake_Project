#include "snake.h"

void HideCursor() { // Ẩn con trỏ soạn thảo
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;  // Ẩn con trỏ
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void SetupGameSettings() {
    int difficultyChoice;
    int sizeChoice;

    cout << "Choose the size:\n";
    cout << "1. Small (20x10)\n";
    cout << "2. Normal (40x20)\n";
    cout << "3. Large (60x30)\n";
    cout << "Your choice: ";
    cin >> sizeChoice;

    switch (sizeChoice) {
        case 1:
            width = 20;
            height = 10;
            break;
        case 2:
            width = 40;
            height = 20;
            break;
        case 3:
            width = 60;
            height = 30;
            break;
        default:
            cout << "The choice is not avaiable! Using the default size (40x20).\n";
            width = 40;
            height = 20;
    }

    cout << "\nChoose the difficulty:\n";
    cout << "1. Easy (Slow)\n";
    cout << "2. Normal\n";
    cout << "3. Hard (Fast)\n";
    cout << "Your Choice: ";
    cin >> difficultyChoice;

    switch (difficultyChoice) {
        case 1:
            delay = 150;
            break;
        case 2:
            delay = 100;
            break;
        case 3:
            delay = 50;
            break;
        default:
            cout << "The choice is not avaiable! Using the default difficulty (Normal).\n";
            delay = 100;
    }
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
void GenerateFruit() {
    bool fruitOnSnake;
    int maxCells = width * height;

    // Kiểm tra nếu rắn đã chiếm toàn bộ bảng
    if (nTail + 1 >= maxCells) {  // +1 để bao gồm cả đầu rắn
        cout << "\nCongratulations! You've filled the entire board!" << endl;
        gameOver = true;
        return;
    }

    do {
        fruitOnSnake = false;
        fruitX = rand() % width;
        fruitY = rand() % height;

        // Kiểm tra xem vị trí của quả có trùng với đầu rắn không
        if (fruitX == x && fruitY == y) {
            fruitOnSnake = true;
        }

        // Kiểm tra xem vị trí của quả có trùng với bất kỳ phần nào của đuôi rắn không
        for (int i = 0; i < nTail; i++) {
            if (tailX[i] == fruitX && tailY[i] == fruitY) {
                fruitOnSnake = true;
                break;
            }
        }
    } while (fruitOnSnake);  // Lặp lại nếu quả xuất hiện trên thân rắn
}

void Logic() {
    if (paused) return;  // Nếu đang tạm dừng, không cập nhật logic

    DWORD currentTime = GetTickCount();
    if (currentTime - lastMoveTime < 100)
        return;

    lastMoveTime = currentTime;

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height) {
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        GenerateFruit();  // Gọi hàm tạo quả với vị trí mới không trùng với thân rắn
    }
}

void Draw() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    ifstream input("file.txt");
    fstream output;
    output.open("file.txt");

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    input>>maxx;
    if (maxx < score) maxx = score;
    cout << "Score: " << score << endl;
    cout << "Highest Score: " << maxx << endl;
    output<<maxx;
    if (paused)
    {
        cout << "Game paused - Press P to continue." << endl;
    }
}
void ShowInstructions() {
    system("cls");
    cout << "=================== SNAKE GAME ===================" << endl;
    cout << "Instructions:" << endl;
    cout << "  - Use 'W' to move UP" << endl;
    cout << "  - Use 'A' to move LEFT" << endl;
    cout << "  - Use 'S' to move DOWN" << endl;
    cout << "  - Use 'D' to move RIGHT" << endl;
    cout << "  - Press 'X' to exit the game" << endl;
    cout << "\nObjective: Eat the '*' to grow the snake and score points." << endl;
    cout << "Avoid hitting the walls or your own tail!" << endl;
    cout << "\nPress any key to start playing..." << endl;
    _getch();
    system("cls");
}

void GameOverScreen() {
    cout << "\nGame Over! Final Score: " << score << endl;
    cout << "Do you want to play again? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        Setup();
    } else {
        gameOver = true;
    }
    system("cls");
}
