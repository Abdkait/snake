#include <iostream>
#include <conio.h>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <ctime>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;

int x,y,fruitX, fruitY, score;

enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
    gameOver = false;
    dir = STOP;
    x = width/2 - 1;
    y = height/2 - 1;
    fruitX = rand() % (width-2) + 1;
    fruitY = rand() % (height-2) + 1;
    score = 0;
}

void Draw(){
    system("cls");

    for(int i = 0; i < width; i++){
        cout << "#";
    }
    cout << "        score: " << score << endl;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width+2; j++){
            if( j == 0 || j == width - 1) {
                cout << "#";
            }else if(i == y && j == x) {
                cout << "0";
            }else if(i == fruitY && j == fruitX){
                cout << "F";
            }else{
                cout << " ";
            }
        }
        cout << endl;
    }

    for(int i = 0; i < width; i++){
        cout << "#";
    }
    cout << "      X: " << x << "\tY: " << y << "\t";
    cout << "      FruitX: " << fruitX << "  FruitY: " << fruitY << endl;
}

void Input(){
    if (_kbhit()){
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            default:
                dir = STOP;
        }
    }
}

void Logic(){
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
    if(x >= width - 1){
        printf("@");
        x = 1;
    }
    else if(x <= 0){
        x = width - 2;
    }
    if(y > height - 1){
        y = 0;
    }
    else if(y < 0){
        y = height - 1;
    }
    if (x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % (width-2) + 1;
        fruitY = rand() % (height-2) + 1;
    }
}
/*
int main() {
    using namespace std::chrono;
    //auto frame_duration = milliseconds(1000 / 60);

    duration<long long, ratio<1, 1000>> frame_duration = std::chrono::milliseconds(1000 / 144);
    Setup();
    while (!gameOver){
        time_point <steady_clock, steady_clock::duration> start_time = steady_clock::now();
        Draw();
        Input();
        Logic();
        time_point <steady_clock, steady_clock::duration> end_time = steady_clock::now();
        duration elapsed_time = duration_cast<milliseconds>(end_time - start_time);
        if (elapsed_time < frame_duration) {
            std::this_thread::sleep_for(frame_duration - elapsed_time);
        }
    }
    return 0;
}
*/

int main(){
    using namespace std::this_thread;
    using namespace std::chrono;
    srand(time(0));
    Setup();
    auto frame_duration = milliseconds(1000 / 30);
    while(!gameOver){
        auto start_time = steady_clock::now();
        Draw();
        Input();
        Logic();
        sleep_for(nanoseconds(50000000));
        auto end_time = steady_clock::now();
        auto elapsed_time = duration_cast<milliseconds>(end_time - start_time);
        std::this_thread::sleep_for(frame_duration - elapsed_time);
        //sleep_until(system_clock::now() + seconds(0));
    }
}