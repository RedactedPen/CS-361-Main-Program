#include "game.hpp"
#include "input.hpp"
#include <cmath>

#define HIGH_ROOM_PROBIBILITY 85
#define MID_ROOM_PROBIBILITY 45
#define LOW_ROOM_PROBIBILITY 20

#define EVENT_DENSITY 40

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

char room::map_representation(){
    if(this->entered == false){
        return '?';
    }else{
        if(this->pos_x == STARTING_X && this->pos_y == STARTING_Y){
            return 'S';
        }else if(this->held_event){
            return this->held_event->map_representation();
        }
        return 'R';
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

    //Check if con_room is already generated
    if(!con_room){
        return 4;
    }
    
    //Check if con_room has already established a connection
    if(con_room->doors[OPPOSITE(side)] == target_room){
        return 3;
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

int board::add_events(){
    for(int i = 1; i < this->rooms.size(); i++){
        int chance = rand() % 100;
        if(chance <= EVENT_DENSITY){
            this->rooms.at(i)->held_event = new skeleton;
        }
    }
    return 0;
}

int board::generate(room** active_room){
    room* starting_room = new room;

    this->rooms.push_back(starting_room);
    starting_room->pos_x = STARTING_X;
    starting_room->pos_y = STARTING_Y;
    
    this->generation_board[STARTING_Y][STARTING_X] = starting_room;
    *active_room = starting_room;

    //Telling the setup room code that the bottom is the spawning side
    //side for the starting room will make it mark that side as -1 due to some
    //wierdness. It makes this easy though.
    int result = setup_room(starting_room, 0, BOTTOM);
    if(result == 1){
        return 1; 
    }

    //Set each unused door to null
    for(int i = 0; i < this->rooms.size(); i++){
        room* current_room = this->rooms.at(i);
        for(int j = 0; j < 4; j++){
            if(current_room->doors[j] == (room*) -1){
                current_room->doors[j] = NULL;
            }
        }
    }

    //Set each unused room to null
    for(int i = 0; i < GAME_SIZE; i++){
        for(int j = 0; j < GAME_SIZE; j++){
            if(this->generation_board[i][j] == (room*) -1){
                this->generation_board[i][j] = NULL;
            }
        }
    }

    //Add events as needed
    this->add_events();

    return 0;
}

void board::print_dungeon(room* current){
    for(int i = 0; i < GAME_SIZE; i++){
        std::string current_line = "";
        std::string next_line = "";
        int num_rooms = 0;
        for(int j = 40; j < GAME_SIZE - 40; j++){
            room* room = this->generation_board[i][j];
            if(room && room->found){
                num_rooms++;
                if(room == current){
                    current_line +="*";
                }else{
                    current_line+= room->map_representation();
                }
                if(room->doors[RIGHT] && (room->doors[RIGHT]->entered || room->entered)){
                    current_line += "-";
                }else{
                    current_line += " ";
                }

                if(room->doors[BOTTOM] && (room->doors[BOTTOM]->entered ||room->entered)){
                    next_line += "| ";
                }else{
                    next_line += "  ";
                }
            }else{
                current_line += "  ";
                next_line += "  ";
            }       
        }
        if(num_rooms){
            std::cout << current_line << std::endl << next_line << std::endl;
        }
    }
}

room* controller::room_interact(int* entering_side){
    if(this->active_room->held_event){
        int result = this->active_room->held_event->encounter(&this->held_player);
        switch(result){
            case 0:
                break;
            case 1:
                return this->active_room->doors[*entering_side];
        }
    }

    if(!this->held_player.alive()){
        return NULL;
    }

    std::string message = "You enter the room.\n";
    int option_number = 1;

    room* doors[5] = {NULL, NULL, NULL, NULL, NULL};

    for(int i = 1; i < 4; i++){
        int side = (*entering_side + i) % 4;
        if(this->active_room->doors[side]){
            doors[option_number] = this->active_room->doors[side];
            message += std::to_string(option_number);
            message += ". Enter the door on the ";
            switch(i){
                case 1:
                    message += "right";
                    break;
                case 2:
                    message += "far";
                    break;
                case 3:
                    message += "left";
                    break; 
            }
            message += " side of the room\n";
            option_number++;
        }
    }

    message += std::to_string(option_number);
    message += ". Return through the door behind you\n";
    doors[option_number] = this->active_room->doors[*entering_side];

    message += std::to_string(option_number + 1);
    message += ". View tutorial (Currently non funcitonal)\n";

    message += std::to_string(option_number + 2);
    message += ". Return to the title screen (Lose all progress)\n";

    int input = get_int_input(1, option_number + 2, message);
    if(input <= option_number){
        room* new_room = doors[input];

        for(int i = 0; i < 4; i++){
            if(new_room->doors[i] == this->active_room){
                *entering_side = i;
                break;
            }
        }
        return new_room;
    }else if(input == option_number + 1){
        printf("\nTutorial currently not implemented\n\n");
        return this->active_room;
    }else if(input == option_number + 2){
        return NULL;
    }else{
        printf("Error processing input\n");
        return this->active_room;
    }

    
}

int controller::game_loop(){
    int entering_side = 2;
    room* new_room = this->active_room;
    new_room->found = true;
    while(1){       
        new_room->entered = true;
        for(int i = 0; i < 4; i++){
            if(new_room->doors[i]){
                new_room->doors[i]->found = true;
            }
        }
        game_board.print_dungeon(this->active_room);
        new_room = room_interact(&entering_side);
        if(!new_room){
            break;
        }
        this->active_room = new_room;        
    }
    if(this->held_player.alive()){
        return 0;
    }else{
        return 2;
    }
}

int controller::start_game(){
    int generation_result = this->game_board.generate(&(this->active_room));
    if(generation_result != 0){
        printf("Error generating the dungeon. Exiting\n");
        return -1;
    }   

    return this->game_loop();
}