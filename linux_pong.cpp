#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <vector>

int input;

void input_thread(){
    while(true){
        system("stty raw");
        input = getchar(); 
        if(input == 27) {
            system("stty cooked");
            system("clear");
            exit(0);
        }  
    }
}

void render(int state, bool paused, int screenWidth, int screenHeight, float ballXCoordinate, float ballYCoordinate, float paddleOneYCoordinate, float paddleTwoYCoordinate, int paddleHeight){
    std::string pausedGraphic = "[Paused]";

    system("clear");

    std::cout << "\r._";
    for(int x = 1; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_.\n";

    std::cout << "\r| ._";
    for(int x = 2; x < screenWidth+1; x++) std::cout << "__";
    std::cout << "_. |\n";

    for(int y = 0; y < screenHeight; y++){
        std::cout << "\r| |";
        for(int x = 0; x < screenWidth; x++){
            if(paused && y == screenHeight/2 && screenWidth/2-2 <= x && x <= screenWidth/2+1 ) std::cout << pausedGraphic[(x-screenWidth/2+2)*2] << pausedGraphic[(x-screenWidth/2+2)*2+1];
            else if(x == 1 && paddleOneYCoordinate <= y && y <= paddleOneYCoordinate + paddleHeight) std::cout << "[]";
            else if(state != 1 && x == screenWidth-2 && paddleTwoYCoordinate <= y && y <= paddleTwoYCoordinate + paddleHeight) std::cout << "[]";
            else if(x == round(ballXCoordinate) && y == round(ballYCoordinate)) std::cout << "()";
            else std::cout << "  ";
        }
        std::cout << "| |\n";
    }

    std::cout << "\r| ._";
    for(int x = 2; x < screenWidth+1; x++) std::cout << "__";
    std::cout << "_. |\n";

    std::cout << "\r._";
    for(int x = 1; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_.\n";

    return;
}


void render(int state, int screenWidth, int screenHeight){
    std::vector<std::string> graphics;
    if(state == 0) graphics = {
        "            _____   ____  _   _  _____          ",
        "           |  __ \\ / __ \\| \\ | |/ ____|         ",
        "           | |__) | |  | |  \\| | |  __          ",
        "           |  ___/| |  | | . ` | | |_ |         ",
        "           | |    | |__| | |\\  | |__| |         ",
        "           |_|     \\____/|_| \\_|\\_____|         ",
        "                                                ",
        " Esc-quit  1-training   2-PvE(easy)  3-PvE(hard)",
        "P1: A-up S-stop D-down    P2: J-up K-stop L-down",
        "      Q-exit to menu    P-pause    O-unpause    ",
        "            U-updatea width and height          "};
    else if(state == 5) graphics = {
        "__     ______  _    _    __          ______  _   _  ",
        "\\ \\   / / __ \\| |  | |   \\ \\        / / __ \\| \\ | | ",
        " \\ \\_/ / |  | | |  | |    \\ \\  /\\  / / |  | |  \\| | ",
        "  \\   /| |  | | |  | |     \\ \\/  \\/ /| |  | | . ` | ",
        "   | | | |__| | |__| |      \\  /\\  / | |__| | |\\  | ",
        "   |_|  \\____/ \\____/        \\/  \\/   \\____/|_| \\_| "};
    else if(state == 6) graphics = {
        "__     ______  _    _   _      ____   _____ _______ ",
        "\\ \\   / / __ \\| |  | | | |    / __ \\ / ____|__   __|",
        " \\ \\_/ / |  | | |  | | | |   | |  | | (___    | |   ",
        "  \\   /| |  | | |  | | | |   | |  | |\\___ \\   | |   ",
        "   | | | |__| | |__| | | |___| |__| |____) |  | |   ",
        "   |_|  \\____/ \\____/  |______\\____/|_____/   |_|   "};
    else if(state == 7) graphics = {
        " _____  __    __          ______  _   _ ",
        "|  __ \\/_ |   \\ \\        / / __ \\| \\ | |",
        "| |__) || |    \\ \\  /\\  / / |  | |  \\| |",
        "|  ___/ | |     \\ \\/  \\/ /| |  | | . ` |",
        "| |     | |      \\  /\\  / | |__| | |\\  |",
        "|_|     |_|       \\/  \\/   \\____/|_| \\_|"};
    else if(state == 8) graphics = {
        " _____ ___    __          ______  _   _ ",
        "|  __ \\__ \\   \\ \\        / / __ \\| \\ | |",
        "| |__) | ) |   \\ \\  /\\  / / |  | |  \\| |",
        "|  ___/ / /     \\ \\/  \\/ /| |  | | . ` |",
        "| |    / /_      \\  /\\  / | |__| | |\\  |",
        "|_|   |____|      \\/  \\/   \\____/|_| \\_|"};
    else graphics = {""};

    system("clear");

    std::cout << "\r._";
    for(int x = 1; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_.\n";

    std::cout << "\r| ._";
    for(int x = 2; x < screenWidth+1; x++) std::cout << "__";
    std::cout << "_. |\n";

    
    for(int y = 0; y < screenHeight; y++){
        std::cout << "\r| |";
        
        for(int x = 0; x < screenWidth; x++){
            if( screenHeight/2-graphics.size()/2 <= y   && y < screenHeight/2+graphics.size()/2 &&
                screenWidth/2-graphics[0].size()/4 <= x && x < screenWidth/2+graphics[0].size()/4)
                std::cout << graphics[y-screenHeight/2+graphics.size()/2][(x+graphics[0].size()/4- screenWidth/2)*2] 
                          << graphics[y-screenHeight/2+graphics.size()/2][(x+graphics[0].size()/4- screenWidth/2)*2+1];
                        //   std::cout << y-screenHeight/2+graphics.size()/2 << " "<<(x+graphics[0].size()/4- screenWidth/2)*2 << " ";
            else std::cout << "  ";
        }
        std::cout << "| |\n";
    }

    std::cout << "\r| ._";
    for(int x = 2; x < screenWidth+1; x++) std::cout << "__";
    std::cout << "_. |\n";

    std::cout << "\r._";
    for(int x = 1; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_.\n";

    return;
}

void restartGameData(bool* paused, int w, int h, float* speed, float* ballX, float* ballY, int paddleH, float* paddleOneY, float* paddleTwoY, int* angle){
    *ballX = w/(float)2;
    *ballY = h/(float)2;

    *speed = 0.15;
    *angle = 180;

    *paddleOneY = h/(float)2 - paddleH/(float)2;
    *paddleTwoY = h/(float)2 - paddleH/(float)2;

    *paused = false;
}

int main(){
    std::thread input_t(&input_thread);

    int gameState = 0;
    // 0 - menu screen
    // 1 - training
    // 2 - PvE (easy)
    // 3 - PvE (hard)
    // 4 - PvP
    // 5 - you won
    // 6 - you lost
    // 7 - player 1 won
    // 8 - player 2 won

    bool paused = false;

    int w = 30;
    int h = 20;

    float ballX, ballY;
    int angle;
    float speed;
    float acceleration = 0.01;

    float paddleOneY, paddleTwoY;
    int paddleH = 5;
    
    float paddleSpeed = 0.1;

    float hardBotTarget = 0;

    restartGameData(&paused, w, h, &speed, &ballX, &ballY, paddleH, &paddleOneY, &paddleTwoY, &angle);

    while(true){
        if(input == 'p') paused = true;
        if(input == 'o') paused = false;
        if(input == 'q' && gameState != 0){
            gameState = 0;
            continue;
        }
        if(gameState == 0){
            render(gameState, w, h);
            if(input == '1'){
                restartGameData(&paused, w, h, &speed, &ballX, &ballY, paddleH, &paddleOneY, &paddleTwoY, &angle);
                gameState = 1;
            }
            if(input == '2'){
                restartGameData(&paused, w, h, &speed, &ballX, &ballY, paddleH, &paddleOneY, &paddleTwoY, &angle);
                gameState = 2;
            }
            if(input == '3'){
                restartGameData(&paused, w, h, &speed, &ballX, &ballY, paddleH, &paddleOneY, &paddleTwoY, &angle);
                gameState = 3;
            }
            // if(input == '4'){
            //     restartGameData(&paused, w, h, &speed, &ballX, &ballY, paddleH, &paddleOneY, &paddleTwoY, &angle);
            //     gameState = 4;
            // }
            continue;
        }
        else if(5 <= gameState){
            render(gameState, w, h);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            gameState = 0;
            input = 0;
            continue;
        }
        else if(paused){
            render(gameState, paused, w, h, ballX, ballY, paddleOneY, paddleTwoY, paddleH);
            continue;
        }
        
        if(input == 'a'  && paddleOneY >= 0) paddleOneY -= paddleSpeed;
        if(input == 'd' && paddleOneY + paddleH <= h-1) paddleOneY += paddleSpeed;

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

        if(1 <= ballX && ballX <= 2 && paddleOneY <= ballY && ballY <= paddleOneY + paddleH){
            // angle = angle/180*180+abs(180 - angle%180);
            if(ballY-paddleOneY-paddleH/2.0 < 0) angle = 360+round((ballY-paddleOneY-paddleH/2.0)/(paddleH/2.0)*90);
            else                               angle = round((ballY-paddleOneY-paddleH/2.0)/(paddleH/2.0)*90);
            speed += acceleration;

            if(gameState == 3){
                float temp = ballY+tan(angle*3.14159/180)*(w-4);
                if((int)round(temp)/h%2) hardBotTarget = h-abs(((temp)-(int)round(temp)/h*h));
                else                     hardBotTarget = abs(((temp)-(int)round(temp)/h*h));
            }
        }

        if(gameState != 1 && w-3 <= ballX && ballX <= w-2 && paddleTwoY <= ballY && ballY <= paddleTwoY + paddleH){
            // angle = angle/180*180+abs(180 - angle%180);
            angle = 180-round((ballY-paddleTwoY-paddleH/2.0)/(paddleH/2.0)*90);

            speed += acceleration;

            if(gameState == 3) hardBotTarget = h/2;
        }

        //Training
        if(gameState == 1){
            if(ballX < 0) gameState = 0;
            if(w-1 < ballX){
                ballX = 2*(w-1)-ballX;
                angle = angle/180*180+abs(180 - angle%180);
            }
        }
        
        //PvE(easy)
        if(gameState == 2){
            if(ballX < 0)   gameState = 6;
            if(w-1 < ballX) gameState = 5;

            if(paddleTwoY+paddleH/2.0 < ballY && paddleTwoY+paddleH < h-1)      paddleTwoY += paddleSpeed;
            else if(paddleTwoY+paddleH/2.0 > ballY && paddleTwoY > 0) paddleTwoY -= paddleSpeed;
            else;
        }

        //PvE(hard)
        if(gameState == 3){
            if(ballX < 0)   gameState = 6;
            if(w-1 < ballX) gameState = 5;
            if(90 <= angle && angle <= 270){
                if(paddleTwoY+paddleH/2.0 < h/2.0 && paddleTwoY+paddleH < h-1)      paddleTwoY += paddleSpeed;
                else if(paddleTwoY+paddleH/2.0 > h/2.0 && paddleTwoY > 0) paddleTwoY -= paddleSpeed;
            }
            else{
                if(paddleTwoY+paddleH/2.0 < hardBotTarget && paddleTwoY+paddleH < h-1)      paddleTwoY += paddleSpeed;
                else if(paddleTwoY+paddleH/2.0 > hardBotTarget && paddleTwoY > 0) paddleTwoY -= paddleSpeed;
            }
        }

        //PvP
        if(gameState == 4){
            if(ballX < 0)   gameState = 8;
            if(w-1 < ballX) gameState = 7;

            if(input == 'j'  && paddleTwoY >= 0) paddleTwoY -= paddleSpeed;
            if(input == 'l' && paddleTwoY + paddleH <= h-1) paddleTwoY += paddleSpeed;
        }
        
        render(gameState, paused, w, h, ballX, ballY, paddleOneY, paddleTwoY, paddleH);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}