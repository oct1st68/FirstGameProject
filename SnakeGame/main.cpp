#include <bits/stdc++.h>
#include <conio.h>   // Dùng cho _kbhit() và _getch()
#include <windows.h> // Dùng cho Sleep()
#include <cstdlib>   // Dùng cho rand() và srand()
#include <ctime>     // Dùng cho time()
using namespace std;

// Kích thước sân chơi
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];  // Lưu tọa độ các đoạn thân rắn
int nTail = 0;               

// Biến lưu hướng di chuyển
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir, prevDir;  // Thêm biến để lưu hướng di chuyển trước đó

void setup() {
    srand(time(0));  // Khởi tạo random seed
    dir = STOP;  // Ban đầu rắn không di chuyển
    x = width / 2;  // Vị trí ban đầu của rắn
    y = height / 2;
    foodX = rand() % width;  // Vị trí ngẫu nhiên của mồi
    foodY = rand() % height;
    score = 0;
    nTail = 0;  // Ban đầu rắn không có thân
}

void draw() {
    // Di chuyển con trỏ về đầu màn hình thay vì xóa màn hình để tránh nhấp nháy
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    // Vẽ viền trên
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Vẽ sân chơi
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";  // Viền trái

            if (i == y && j == x) {
                cout << char(254);  // Vẽ đầu rắn
            } else if (i == foodY && j == foodX) {
                cout << "o";  // Vẽ mồi
            } else {
                bool isTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";  // Vẽ thân rắn
                        isTail = true;
                    }
                }
                if (!isTail) {
                    cout << " ";  // Khoảng trống
                }
            }

            if (j == width - 1) cout << "#";  // Viền phải
        }
        cout << endl;
    }

    // Vẽ viền dưới
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Hiển thị điểm số
    cout << "Score: " << score << endl;
    cout << "MadebyTrung" << endl;
}

void input() {
    if (_kbhit()) {  // Nếu có phím được nhấn
        switch (_getch()) {
            case 'a': if (prevDir != RIGHT) dir = LEFT; break;  // Không quay đầu ngược lại
            case 'd': if (prevDir != LEFT) dir = RIGHT; break;
            case 'w': if (prevDir != DOWN) dir = UP; break;
            case 's': if (prevDir != UP) dir = DOWN; break;
        }
    }
}

void logic() {
    // Lưu hướng di chuyển trước đó để ngăn việc quay đầu ngược lại
    prevDir = dir;

    // Cập nhật vị trí của thân rắn
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

    // Cập nhật vị trí đầu rắn theo hướng
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    // Kiểm tra nếu rắn ăn mồi
    if (x == foodX && y == foodY) {
        score += 10;  // Tăng điểm
        nTail++;      // Tăng chiều dài thân rắn
        // Đặt mồi mới ở vị trí ngẫu nhiên
        foodX = rand() % width;
        foodY = rand() % height;
    }

    // Kiểm tra va chạm với tường
    if (x < 0 || x >= width || y < 0 || y >= height) {
        cout << "Game Over!" << endl;
        system("pause");
        exit(0);
    }

    // Kiểm tra nếu rắn tự đâm vào thân
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            cout << "Game Over! You hit yourself!" << endl;
            system("pause");
            exit(0);
        }
    }
}

int main() {
    // Tắt chế độ hiện con trỏ trong console để màn hình vẽ mượt hơn
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &ConCurInf);

    setup();
    while (true) {
        draw();    // Vẽ rắn và sân chơi
        input();   // Nhận đầu vào từ bàn phím
        logic();   // Cập nhật logic di chuyển
        Sleep(100); // Độ trễ (tốc độ di chuyển)
    }
    
    return 0;
}
