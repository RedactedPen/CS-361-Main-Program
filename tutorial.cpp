#include "tutorial.hpp"
#include "input.hpp"
void tutorial(){
    int selection = -1;
    do{
        std::string message = "--Tutorial--\n";
        message += "1. Basics\n";
        message += "2. Threats\n";
        message += "3. Exit the tutorial\n";

        selection = get_int_input(1, 3, message);

        switch(selection){
            case 1:
                printf("\n--Basics--\n");
                printf("You can win the game by finding the ancient treasure hidden in \n");
                printf("the dungeon and returning to the entrance with it in hand\n");
                printf("Your character has 10 starting health, which can be lowered\n");
                printf("through a variety of means. When your health reaches 0, you lose.\n");
                printf("When you lose the game, you will restart from the beginning.\n");
                printf("You may encounter enemies that will try to attack you. They will\n");
                printf("continue to attack you until they are defeated by lowering their\n");
                printf("health to 0. Alternativley, you can try to run away from them\n\n");
                break;
            case 2:
                printf("\nSkeletons\n");
                printf("Encountering a group of skeletons will cause them to attack you.\n");
                printf("They have 4 health and ahve a 75%% chance to do 2 damage\n\n");
                break;
        }
    }while(selection != 3);
}