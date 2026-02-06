#include "game.hpp"

#define HIGH_ROOM_PROBIBILITY 85
#define MID_ROOM_PROBIBILITY 40
#define LOW_ROOM_PROBIBILITY 20

#define CONNECTION_CHANCE 35

int room_probibility(int depth){
    if(depth < 5){
        return HIGH_ROOM_PROBIBILITY;
    }else if( depth < 10){
        return MID_ROOM_PROBIBILITY;
    }else{
        return LOW_ROOM_PROBIBILITY;
    }    
}

room* board::room_connection(room* target_room, int side){

    if(side == TOP){
        int pos_y = target_room->pos_y;
        if(pos_y <= 0){
            return (room*) -1;
        }else{
            return this->generation_board[pos_y - 1][target_room->pos_x];
        }
    }else if(side == LEFT){
        int pos_x = target_room->pos_x;
        if(pos_x <= 0){
            return (room*) -1;
        }else{
            return this->generation_board[target_room->pos_y ][pos_x - 1];
        }
    }else if(side == BOTTOM){
        int pos_y = target_room->pos_y;
        if(pos_y >= GAME_SIZE - 1){
            return (room*) -1;
        }else{
            return this->generation_board[pos_y + 1][target_room->pos_x];
        }
    }else if(side == RIGHT){
        int pos_x = target_room->pos_x;
        if(pos_x >= GAME_SIZE - 1){
            return (room*) -1;
        }else{
            return this->generation_board[target_room->pos_y ][pos_x + 1];
        }
    }else{
        return (room*) -1;
    }
}

room** board::room_addr(room* source_room, int side, int* pos_x, int* pos_y){
    if(side == TOP){
        int new_pos_y = source_room->pos_y;
        if(new_pos_y <= 0){
            return (room**) -1;
        }else{
            *pos_x = source_room->pos_x;
            *pos_y = new_pos_y - 1;
            return &this->generation_board[*pos_y][*pos_x];
        }
    }else if(side == LEFT){
        int new_pos_x = source_room->pos_x;
        if(new_pos_x <= 0){
            return (room**) -1;
        }else{
            *pos_y = source_room->pos_y;
            *pos_x = new_pos_x - 1;
            return &this->generation_board[*pos_y][*pos_x];
        }
    }else if(side == BOTTOM){
        int new_pos_y = source_room->pos_y;
        if(new_pos_y >= GAME_SIZE - 1){
            return (room**) -1;
        }else{
            *pos_x = source_room->pos_x;
            *pos_y = new_pos_y + 1;
            return &this->generation_board[*pos_y][*pos_x];
        }
    }else if(side == RIGHT){
        int new_pos_x = source_room->pos_x;
        if(new_pos_x >= GAME_SIZE - 1){
            return (room**) -1;
        }else{
            *pos_y = source_room->pos_y;
            *pos_x = new_pos_x + 1;
            return &this->generation_board[*pos_y][*pos_x];
        }
    }else{
        return (room**) -1;
    }
}

int board::can_connect(room* target_room, int side){
    //Check if we can put a room above this one
    room* con_room = room_connection(target_room, side);

    if(con_room == (room*) -1){
        return 0;
    }
    
    //Check if con_room has already established a connection
    if(target_room->doors[side]){
        return 3;
    }

    //Check if con_room is already generated
    if(!con_room){
        return 4;
    }

    //Check if con_room is open to connection
    if(con_room->doors[OPPOSITE(side)] == (room*)-1){
        return 2;
    }else{
        return 1;
    }

}

int board::connect_side(room* target_room, int depth, int side){
    int result = can_connect(target_room, side);
    switch(result){
        case 0:
            //The room cannot be connected to (i.e. it is out of bounds)
            //Nothing needs to be done
            break;
        case 1:
            //There is already a room on the target side
            //Run a chance to connect to it, otherwise close off this side to connection
            if((rand() % 100) <= CONNECTION_CHANCE){
                room* con_room = room_connection(target_room, side);
                con_room->doors[OPPOSITE(side)] = target_room;
                target_room->doors[side] = con_room;
            }else{
                target_room->doors[side] = (room*) -1;
            }
            break;
        case 2:
            //There is already a room on the target side that has closed itself to connection
            target_room->doors[side] = (room*) -1;
            break;
        case 3:
            //This room is already connected to the room on the target side
            break;
        case 4:
            //No room exists on the target side. 
            //Run a chance to create it, otherwise leave the connection null
            if((rand() % 100) <= room_probibility(depth)){
                room* con_room = new room;

                target_room->doors[side] = con_room;

                this->rooms.push_back(con_room);

                int pos_x, pos_y;
                room** room_spot = room_addr(target_room, side, &pos_x, &pos_y);
                con_room->pos_x = pos_x;
                con_room->pos_y = pos_y;
                *room_spot = con_room;

                return setup_room(con_room, depth + 1, OPPOSITE(side));
            }else{
                target_room->doors[side] = NULL;
                //Chance to mark a spot as unusable for all other rooms
                if(1){
                    int pos_x, pos_y;
                    room** room_spot = room_addr(target_room, side, &pos_x, &pos_y);
                    *room_spot = (room*) -1;
                }
            }
            break;
        default:
            //This code should never execute. Return an error code.
            return 1;
    }

    return 0;
}

int board::setup_room(room* target_room, int depth, int connecting_side){
    
    for(int i = 0; i < 4; i++){ 
        if(i == connecting_side){
            //The room is the room that spawned this one.
            //Guarantee a connection
            target_room->doors[connecting_side] = room_connection(target_room, connecting_side);
        }else{
            int result = connect_side(target_room, depth, i); 
            if(result == 1){
                return 1;
            }
        }
    }
    return 0;
}

int board::generate(){
    room* starting_room = new room;

    this->rooms.push_back(starting_room);
    starting_room->pos_x = STARTING_X;
    starting_room->pos_y = STARTING_Y;
    
    this->generation_board[STARTING_Y][STARTING_X] = starting_room;

    //Telling the setup room code that the bottom is the soawning side
    //side for the room will make it mark that side as -1 due to some
    //wierdness. It makes this easy though.
    setup_room(starting_room, 0, BOTTOM);

    return 0;
}

void board::print_dungeon(){
    for(int i = 0; i < GAME_SIZE; i++){
        printf("_");
    }
    printf("\n");

    for(int i = 0; i < GAME_SIZE; i++){
        printf("|");
        for(int j = 0; j < GAME_SIZE; j++){
            room* room = this->generation_board[i][j];
            if(room){
                printf("R");
            }else{
                printf(" ");
            }
        }
        printf("|\n");
    }

    for(int i = 0; i < GAME_SIZE; i++){
        printf("_");
    }
    printf("\n");
}

int controller::start_game(){
    int generation_result = this->game_board.generate();
    if(generation_result != 0){
        printf("Error generating the dungeon. Exiting\n");
        return -1;
    }

    game_board.print_dungeon();

    return this->game_board.rooms.size();
}