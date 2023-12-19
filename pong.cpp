#include <iostream>

int w = 30;
int h = 20;

void render(){
    system("clear");
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            std::cout << "..";
        }
        std::cout << "\n";
    }
}

int main(){
    while(true) {
        render();
    }
    return 0;
}