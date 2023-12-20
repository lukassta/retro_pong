#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

int input;

int w = 30;
int h = 20;

float ballX = w/2.0;
float ballY = h/2.0;

int playerH = 5;
float playerY = 2;
float playerSpeed = 0.05;


int angle = 45;
float speed = 0.1;

void physics_thread(){
    while(true){
        ballX+=cos(angle*3.14159/180)*speed;
        ballY+=sin(angle*3.14159/180)*speed;

        if(ballY < 0){
            ballY = -ballY;
            angle = 360 - angle;
        }
        else if(h < ballY){
            ballY = 2*h-ballY;
            angle = 360 - angle;
        }

        if( 1 <= ballX && ballX <= 2 && playerY <= ballY && ballY <= playerY + playerH){
            angle = angle/180*180+abs(180 - angle%180);
        }

        if(ballX < 0){
            ballX = -ballX;
            angle = angle/180*180+abs(180 - angle%180);
        }
        else if(w < ballX){
            ballX = 2*w-ballX;
            angle = angle/180*180+abs(180 - angle%180);
        }
       
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
            if(x == 1 && playerY <= y && y <= playerY + playerH) std::cout << "[]";
            else if(x == round(ballXCoordinate) && y == round(ballYCoordinate)) std::cout << "()";
            else std::cout << air << air;
        }
        std::cout << "\n";
    }
}

int main(){
    std::thread input_t(&input_thread);
    std::thread physics_t(&physics_thread);

    while(true) {
        if(input == 100 && playerY + playerH <= h-1) playerY += playerSpeed;
        if(input == 97  && playerY >= 0) playerY -= playerSpeed;
        
        render(ballX,ballY);
    }
    return 0;
}