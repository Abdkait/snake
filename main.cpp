#include <iostream>
#include <conio.h>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <ctime>

bool gameOver;
const int width = 20;
const int height = 20;
const int difficult = 5;

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
        std::cout << "#";
    }
    std::cout << "        score: " << score << std::endl;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width+2; j++){
            if( j == 0 || j == width - 1) {
                std::cout << "#";
            }else if(i == y && j == x) {
                std::cout << "0";
            }else if(i == fruitY && j == fruitX){
                std::cout << "F";
            }else{
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    for(int i = 0; i < width; i++){
        std::cout << "#";
    }
    std::cout << "      X: " << x << "\tY: " << y << "\t";
    std::cout << "      FruitX: " << fruitX << "  FruitY: " << fruitY << std::endl;
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
    }
    if(x >= width - 1){
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

int main(){
    srand(time(0));
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(300 / difficult));
    }
