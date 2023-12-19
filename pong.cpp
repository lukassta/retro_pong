#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

int w = 30;
int h = 20;
int input;

void input_thread()
{
    while(true){
        system("stty raw");
        input = getchar(); 
        if(input == 27) {
            system("stty cooked");
            exit(0);
        }  
    }
}

void render(int ballX, int ballY){
    char air = '.';

    system("clear");
    for(int y = 0; y < h; y++){
        std::cout << "\r";
        for(int x = 0; x < w; x++){
            if(x == round(ballX) && y == round(ballY)) std::cout << "()";
            else std::cout << air << air;
        }
        std::cout << "\n";
    }
}

int main(){
    std::thread input_t(&input_thread);
    while(true) {
        render(5,5);
    }
    return 0;
}