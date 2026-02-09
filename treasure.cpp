#include "treasure.hpp"

treasure::treasure(){
    this->representation = 'T';
}

int treasure::encounter(player* player){
    if(this->taken){
        printf("You have returned to where you found the treasure. \n");
    }else{
        printf("You found a room filled with ancient and valuable treasure\n");
        printf("You take what you can and place it in your bag.\n");
        printf("With the treasure in hand, you know you need to get out of the dungeon as fast as possible\n");

        this->taken = true;
        player->has_treasure = true;
    }

    return 0;
}