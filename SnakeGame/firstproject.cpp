#include "lib.cpp"
using namespace std;


const int width = 30;
const int height = 30;
int x, y, foodX, foodY, score, nTail;
int tailX[100], tailY[100];

enum Direction{Stop = 0, UP, DOWN, LEFT, RIGHT};
Direction dir, prevDir;


void setup(){
    srand(time(0));
    dir = Stop;
    x = rand() % (width/2);
    y = rand() % (height/2);
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw(){
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    //Vien tren
    for(int i = 0; i < width +2 ; i++){
        cout<<"-";
    }
    cout<<endl;

    for(int i = 0; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            if(j == 0) cout<<"|"; //Vien 

            if(i == y && j == x){
                cout<<(char)254; //Ve dau
            }
            else if(i == foodY && j == foodX){
                cout<<"o"; // Ve moi
            }
            else {
                bool isTail = false;
                for(int k = 0; k < nTail; k++ ){
                    if(tailX[k]== j && tailY[k] == x){
                        cout<<char(254); //Ve than
                        isTail = true;
                    }
                }
                    if(!isTail){
                         cout<<" ";
                    }
                }
            if(j == width - 1){  
                cout<<"|"; // Vien phai
        }
    }
    cout<<endl;
}

    for(int i = 1; i <= width +2 ; i++){
        cout<<"-";
    }
    cout<<endl;

    cout<<"Score: "<<score<<endl;
    cout<<"MadebyTrung"<<endl;
}

void logic(){
    prevDir = dir;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < nTail; i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }

    switch (dir){
        case LEFT : x--;
            break;
        case RIGHT : x++;
            break;
        case UP : y--;
            break;
        case DOWN : y++;
            break;
        default : break;
    }

    if(x==foodX && y==foodY){
        score+=10;
        nTail++;
        foodX = rand() % width;
        foodY = rand() % height;
    }


        if(x<0 || x>= width || y<0 || y>= height){
            cout<<"GAME OVER"<<endl;
            system("PAUSE");
            exit(0);
        }

        for(int i = 0; i < nTail; i++){
            if(tailX[i] == x && tailY[i] == y){
                cout<<"GAME OVER, YOU HIT YOURSELF"<<endl;
                system("PAUSE");
                exit(0);
            }
        }
        cout<<endl;
    }
void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (prevDir != RIGHT) dir = LEFT; break; 
            case 'd': if (prevDir != LEFT) dir = RIGHT; break;
            case 'w': if (prevDir != DOWN) dir = UP; break;
            case 's': if (prevDir != UP) dir = DOWN; break;
        }
    }
}

int main(){
	HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &ConCurInf);


    setup();
    while(true){
    	Draw();
    	input();
    	logic();
    	Sleep(100);
    }
	return 0;
}