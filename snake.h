#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <fstream>

using namespace std;

bool gameOver, paused;
int width, height, delay;
int x, y, fruitX, fruitY, score;
int maxx = 0;
int tailX[1000], tailY[1000];
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
DWORD lastMoveTime;

void HideCursor(); // Ẩn con trỏ soạn thảo tránh gây khó nhìn (cái này viết rô)
void SetupGameSettings(); // Cài đặt thiết lập chọn kích cỡ khung và tốc độ rắn
void Setup(); //  Các thiết lập ban đầu về chiều dài, chiều rộng khung, toạ độ hiển thị của rắn, thức ăn, điểm, số đốt đuôi
void Draw(); // Vẽ khung, điểm, nói chung là giao diện chơi
void Input(); // Thiết lập các nút bấm vào trong trò chơi
void GenerateFruit(); // Thiết lập mồi không xuất hiện trên thân rắn
void Logic(); // Các hàm kiểm tra về các hành vi của rắn
void ShowInstructions(); // Dòng mô tả trò chơi cho người dùng cuối
void GameOverScreen(); // Màn hình thua cuộc