#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <vector>

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

    std::cout << "\r._";
    for(int x = 1; x < screenWidth+3; x++) std::cout << "__";
    std::cout << "_.\n";

    std::cout << "\r|  _";
    for(int x = 2; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_  |\n";

    for(int y = 0; y < screenHeight; y++){
        std::cout << "\r| |.";
        for(int x = 0; x < screenWidth; x++){
            if(paused && y == screenHeight/2 && screenWidth/2-2 <= x && x <= screenWidth/2+1 ) std::cout << pausedGraphic[(x-screenWidth/2+2)*2] << pausedGraphic[(x-screenWidth/2+2)*2+1];
            else if(x == 1 && playerYCoordinate <= y && y <= playerYCoordinate + playerHeight) std::cout << "[]";
            else if(x == round(ballXCoordinate) && y == round(ballYCoordinate)) std::cout << "()";
            else std::cout << "  ";
        }
        std::cout << ".| |\n";
    }

    std::cout << "\r|  _";
    for(int x = 2; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_  |\n";

    std::cout << "\r._";
    for(int x = 1; x < screenWidth+3; x++) std::cout << "__";
    std::cout << "_.\n";

    return;
}


void render(int state, int screenWidth, int screenHeight){
    std::vector<std::string> graphics;
    if(state == 0) graphics = {
        "            _____   ____  _   _  _____            ",
        "           |  __ \\ / __ \\| \\ | |/ ____|           ",
        "           | |__) | |  | |  \\| | |  __            ",
        "           |  ___/| |  | | . ` | | |_ |           ",
        "           | |    | |__| | |\\  | |__| |           ",
        "           |_|     \\____/|_| \\_|\\_____|           ",
        "                                                  ",
        "    Esc-quit    1-training     2-PvE     3-PvP    ",
        " P1: A-up S-stop D-down    P2: J-up K-stop L-down ",
        "      Q-exit to menu    P-pause    O-unpause      ",
        "            U-updatea width and height            "};
    else if(state == 4) graphics = {
        "__     ______  _    _    __          ______  _   _  ",
        "\\ \\   / / __ \\| |  | |   \\ \\        / / __ \\| \\ | | ",
        " \\ \\_/ / |  | | |  | |    \\ \\  /\\  / / |  | |  \\| | ",
        "  \\   /| |  | | |  | |     \\ \\/  \\/ /| |  | | . ` | ",
        "   | | | |__| | |__| |      \\  /\\  / | |__| | |\\  | ",
        "   |_|  \\____/ \\____/        \\/  \\/   \\____/|_| \\_| "};
    else if(state == 5) graphics = {
        "__     ______  _    _   _      ____   _____ _______ ",
        "\\ \\   / / __ \\| |  | | | |    / __ \\ / ____|__   __|",
        " \\ \\_/ / |  | | |  | | | |   | |  | | (___    | |   ",
        "  \\   /| |  | | |  | | | |   | |  | |\\___ \\   | |   ",
        "   | | | |__| | |__| | | |___| |__| |____) |  | |   ",
        "   |_|  \\____/ \\____/  |______\\____/|_____/   |_|   "};
    else if(state == 6) graphics = {
        " _____  __    __          ______  _   _ ",
        "|  __ \\/_ |   \\ \\        / / __ \\| \\ | |",
        "| |__) || |    \\ \\  /\\  / / |  | |  \\| |",
        "|  ___/ | |     \\ \\/  \\/ /| |  | | . ` |",
        "| |     | |      \\  /\\  / | |__| | |\\  |",
        "|_|     |_|       \\/  \\/   \\____/|_| \\_|"};
    else if(state == 7) graphics = {
        " _____ ___    __          ______  _   _ ",
        "|  __ \\__ \\   \\ \\        / / __ \\| \\ | |",
        "| |__) | ) |   \\ \\  /\\  / / |  | |  \\| |",
        "|  ___/ / /     \\ \\/  \\/ /| |  | | . ` |",
        "| |    / /_      \\  /\\  / | |__| | |\\  |",
        "|_|   |____|      \\/  \\/   \\____/|_| \\_|"};
    else graphics = {""};

    system("clear");
    std::cout << "\r._";
    for(int x = 1; x < screenWidth+3; x++) std::cout << "__";
    std::cout << "_.\n";

    std::cout << "\r|  _";
    for(int x = 2; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_  |\n";

    
    for(int y = 0; y < screenHeight; y++){
        std::cout << "\r| | ";
        
        for(int x = 0; x < screenWidth; x++){
            if( screenHeight/2-graphics.size()/2 <= y   && y < screenHeight/2+graphics.size()/2 &&
                screenWidth/2-graphics[0].size()/4 <= x && x < screenWidth/2+graphics[0].size()/4)
                std::cout << graphics[y-screenHeight/2+graphics.size()/2][(x+graphics[0].size()/4- screenWidth/2)*2] 
                          << graphics[y-screenHeight/2+graphics.size()/2][(x+graphics[0].size()/4- screenWidth/2)*2+1];
                        //   std::cout << y-screenHeight/2+graphics.size()/2 << " "<<(x+graphics[0].size()/4- screenWidth/2)*2 << " ";
            else std::cout << "  ";
            // if(state == 0) std::cout << "menu";

            // if(state == 4) std::cout << "You won";
            // if(state == 5) std::cout << "You lost";
            // if(state == 6) std::cout << "P1 won";
            // if(state == 7) std::cout << "P2 won";
        }
        std::cout << " | |\n";
    }

    std::cout << "\r|  _";
    for(int x = 2; x < screenWidth+2; x++) std::cout << "__";
    std::cout << "_  |\n";

    std::cout << "\r._";
    for(int x = 1; x < screenWidth+3; x++) std::cout << "__";
    std::cout << "_.\n";

    return;
}

void restartGameData(int w, int h, float* speed, float* ballX, float* ballY, int playerH, float* playerY, int* angle){
    *ballX = w/(float)2;
    *ballY = h/(float)2;

    *speed = 0.1;
    *angle = 180;

    *playerY = h/(float)2 - playerH/(float)2;
}

int main(){
    std::thread input_t(&input_thread);

    int gameState = 0;
    // 0 - menu screen
    // 1 - training
    // 2 - PvE
    // 3 - PvP
    // 4 - you won
    // 5 - you lost
    // 6 - player 1 won
    // 7 - player 2 won

    int w = 30;
    int h = 20;

    float ballX, ballY;
    int angle;
    float speed;

    float playerY;
    int playerH = 5;
    
    float playerSpeed = 0.05;


    restartGameData(w, h, &speed, &ballX, &ballY, playerH, &playerY, &angle);

    while(true){
        if(gameState == 0){
            render(gameState, w, h);
            if(input == 49){
                restartGameData(w, h, &speed, &ballX, &ballY, playerH, &playerY, &angle);
                gameState = 1;
            }
            if(input == 50){
                restartGameData(w, h, &speed, &ballX, &ballY, playerH, &playerY, &angle);
                gameState = 2;
            }
            if(input == 51){
                restartGameData(w, h, &speed, &ballX, &ballY, playerH, &playerY, &angle);
                gameState = 3;
            }
            continue;
        }
        else if(4 <= gameState){
            render(gameState, w, h);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            gameState = 0;
            input = 0;
            continue;
        }
        else if(paused){
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

        //Training
        if(gameState == 1){
            if(ballX < 0) gameState = 0;
            if(w-1 < ballX){
                ballX = 2*(w-1)-ballX;
                angle = angle/180*180+abs(180 - angle%180);
            }
        }
        
        //PvE
        if(gameState == 2){
            if(ballX < 0)   gameState = 5;
            if(w-1 < ballX) gameState = 4;
        }
        //PvP
        if(gameState == 3){
            if(ballX < 0)   gameState = 7;
            if(w-1 < ballX) gameState = 6;
        }
        

        render(w, h, ballX, ballY, playerY, playerH);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}