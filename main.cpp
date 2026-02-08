#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "game.hpp"
#include "input.hpp"


int start_screen(){
    std::string menu = "Welcome to DungeonCrawler.exe\n";
    menu += "1. Start new game\n";
    menu += "2. View tutorial\n";
    menu += "3. Exit Game\n";

    return get_int_input(1, 3, menu);
}

int main(){
    srand(time(nullptr));

    int selection = -1;
    do{
        selection = start_screen();

        if(selection == 1){
            //start game
            controller game_controller;
            int result = game_controller.start_game();
            if(result == 2){
                printf("You died!\n");
            }
        }else if(selection == 2){
            //Show tutorial;
        }else if (selection != 3){
            printf("Error processing selection. Exiting the game\n");
            selection = 3;
        }

    }while(selection != 3);

    printf("Goodbye!\n");

    return 0;
}