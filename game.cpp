#include "game.hpp"


#define HIGH_PROBIBILITY 75
#define MID_PROBIBILITY 50
#define LOW_PROBIBILITY 20

int room_probibility(int depth){
    if(depth < 10){
        return HIGH_PROBIBILITY;
    }else if( depth < 20){
        return MID_PROBIBILITY;
    }else{
        return LOW_PROBIBILITY;
    }

    
}

int board::connect_room(room* room, int depth, int connecting_side){
    int probibility = room_probibility(depth);
    

    return 0;
}

int board::generate(){
    room* starting_room = new room;

    this->rooms.push_back(starting_room);
    starting_room->pos_x = STARTING_X;
    starting_room->pos_y = STARTING_Y;
    
    this->generation_board[STARTING_Y][STARTING_X];

    return 0;
}

int controller::start_game(){
    int generation_result = this->game_board.generate();
    if(generation_result != 0){
        printf("Error generating the dungeon. Exiting\n");
        return -1;
    }

    return -1;
}