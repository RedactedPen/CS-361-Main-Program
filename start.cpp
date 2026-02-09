#include "start.hpp"

start::start(){
    this->representation = 'S';
}

int start::encounter(player* player){
    if(player->has_treasure){
        printf("You have left the dungeon with the treasure in hand. \n");
        printf("Congratulations! You win.\n");
        return 2;
    }else if(player->moves > 0){
        printf("You have returned to the dungeon entrance, but you aren't ready to leave yet\n");
    }
    return 0;
}