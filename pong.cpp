#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

int input;

int w = 30;
int h = 20;

float ballX = 0;
float ballY = 5;

void physics_thread(){
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void input_thread(){
    while(true){
        system("stty raw");
        input = getchar(); 
        if(input == 27) {
            system("stty cooked");
            exit(0);
        }  
    }
}

void render(int ballXCoordinate, int ballYCoordinate){
    char air = '.';

    system("clear");
    for(int y = 0; y < h; y++){
        std::cout << "\r";
        for(int x = 0; x < w; x++){
            if(x == round(ballXCoordinate) && y == round(ballYCoordinate)) std::cout << "()";
            else std::cout << air << air;
        }
        std::cout << "\n";
    }
}

int main(){
    std::thread input_t(&input_thread);
    std::thread physics_t(&physics_thread);

    while(true) {
        render(ballX,ballY);
    }
    return 0;
}