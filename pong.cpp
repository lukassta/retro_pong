#include <iostream>
#include <cmath>

int w = 30;
int h = 20;
char air = '.';

void render(int ballX, int ballY){
    system("clear");
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            if(x == round(ballX) && y == round(ballY)) std::cout << "()";
            else std::cout << air << air;
        }
        std::cout << "\n";
    }
}

int main(){
    while(true) {
        render(5,5);
    }
    return 0;
}