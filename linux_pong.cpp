#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

int input;
bool paused = false;

void input_thread(){
    while(true){
        system("stty raw");
        input = getchar(); 
        if(input == 112) paused = true;
        if(input == 111) paused = false;
        if(input == 27 || input == 113) {
            system("stty cooked");
            system("clear");
            exit(0);
        }  
    }
}

void render(int screenWidth, int screenHeight, float ballXCoordinate, float ballYCoordinate, float playerYCoordinate, int playerHeight){
    std::string pausedGraphic = "[Paused]";

    system("clear");

    for(int y = 0; y < screenHeight; y++){
        std::cout << "\r";
        for(int x = 0; x < screenWidth; x++){
            if(paused && y == screenHeight/2 && screenWidth/2-2 <= x && x <= screenWidth/2+1 ) std::cout << pausedGraphic[(x-screenWidth/2+2)*2] << pausedGraphic[(x-screenWidth/2+2)*2+1];
            else if(x == 1 && playerYCoordinate <= y && y <= playerYCoordinate + playerHeight) std::cout << "[]";
            else if(x == round(ballXCoordinate) && y == round(ballYCoordinate)) std::cout << "()";
            else std::cout << "..";
        }
        std::cout << "\n";
    }
}

int main(){
    std::thread input_t(&input_thread);

    int gameMode;
    // 0 - menu screen
    // 1 - training
    // 2 - pve
    // 3 - pvp

    int w = 30;
    int h = 20;

    float ballX = w/2.0;
    float ballY = h/2.0;

    int playerH = 5;
    float playerY = 2;
    float playerSpeed = 0.05;


    int angle = 45;
    float speed = 0.1;

    while(true){
        if(paused){
            render(w, h, ballX, ballY, playerY, playerH);
            continue;
        }

        if(input == 100 && playerY + playerH <= h-1) playerY += playerSpeed;
        if(input == 97  && playerY >= 0) playerY -= playerSpeed;

        ballX+=cos(angle*3.14159/180)*speed;
        ballY+=sin(angle*3.14159/180)*speed;

        if(ballY < 0){
            ballY = -ballY;
            angle = 360 - angle;
        }
        else if(h-1 < ballY){
            ballY = 2*(h-1)-ballY;
            angle = 360 - angle;
        }

        if(1 <= ballX && ballX <= 2 && playerY <= ballY && ballY <= playerY + playerH){
            angle = angle/180*180+abs(180 - angle%180);
        }

        if(w-1 < ballX){
            ballX = 2*(w-1)-ballX;
            angle = angle/180*180+abs(180 - angle%180);
        }

        render(w, h, ballX, ballY, playerY, playerH);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}