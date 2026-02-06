#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "game.hpp"

/*
Gets a user int input between min and max (inclusive).
Prompts for the input using message.
*/
int get_int_input(int min, int max, std::string message){
    message += "Enter your selection: ";
    int to_return;
    std::string input;
    bool sucess = false;
    size_t size;

    //Print the prompt
    std::cout << message;
    //Get user input
    getline(std::cin, input);    
    while(!sucess){
        try{
            to_return = std::stoi(input, &size);
            //Check if stoi consumed the whole string of the user's input and
            //if the input was within the minimum and maximum range
            if(size != input.size() || to_return > max || to_return < min){
                throw std::invalid_argument("Invalid input");
            }
        }
        catch (std::invalid_argument const& ex){
            //Print error message and reprompt
            std::cout << std::endl << "Invalid input" << std::endl << std::endl;
            std::cout << message;
            getline(std::cin, input);
            continue;
        }
        sucess = true;
    }
    return to_return;
}


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
            printf("Start game result: %d\n", result);
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