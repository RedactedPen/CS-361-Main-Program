#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

/*
Gets a user int input between min and max (inclusive).
Prompts for the input using message.
*/
int get_int_input(int min, int max, std::string message){
    int result = min - 1;
    bool first = true;
    message += "Enter your selection: ";

    do{
        if(!first){
            std::cout << "\nInvalid input\n" << std::endl;
        }
        first = false;
        std::cout << message;
        std::cin >> result;
    }while(result < min || result > max);

    return result;
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
        }else if(selection == 2){
            //Show tutorial;
        }else{
            printf("Error processing selection. Exiting the game\n");
            selection = 3;
        }

    }while(selection != 3);

    printf("Goodbye!\n");

    return 0;
}