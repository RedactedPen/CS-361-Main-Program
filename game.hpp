#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "event.hpp"
#include "player.hpp"

//Board size values
#define GAME_SIZE 101
#define STARTING_X 50
#define STARTING_Y 100

//Used to index a room's doors array
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3

//Used to find the door sharing the connection in an adjacent room
#define OPPOSITE(val) (val < 2) ?  val + 2 : val - 2 

class room{
public:
    int pos_x = -1;
    int pos_y = -1;

    //-1
    room* doors[4] = {NULL, NULL, NULL, NULL};

    event* held_event = NULL;
};

class board{
private:
    

    //Addressed by [y][x]. [0][0] is the top left
    room* generation_board[GAME_SIZE][GAME_SIZE] = {};

    //Returns a pointer to the room on the side of target_room
    //Returns -1 if that room cannot exist (i.e. is out of bounds) or if there is an error
    room* room_connection(room* target_room, int side);

    //Same as room_connection, but instead returns a pointer to the pointer
    //to that room in the generation_board array. Stores the pos_x and pos_y
    //of the room in the provided variables
    room** room_addr(room* source_room, int side, int* pos_x, int* pos_y);

    //0: Connection is impossible
    //1: Another room exists in that spot and is open to connection
    //2: Another room exists in that spot and is closed to connection
    //3: Another room exists in that spot and has already connected to this room
    //4: That spot is empty
    int can_connect(room* target_room, int side);

    //0: Successfully ran the connection algorithm
    //1: Some error was encountered
    int connect_side(room* target_room, int depth, int side);

public:
    std::vector<room*> rooms;
    //0: Success
    //1: Fatal issue
    int setup_room(room* target_room, int depth, int connecting_side);

    //Generates the full board
    //0: Success
    //1: Fatal issue
    int generate();

    void print_dungeon();
};

class controller{
private:
    board game_board;
    player held_player;
public:

    //Starts a brand new game
    //-1: Error
    //0: Player exited the game
    //1: Player won
    //2: Player lost (died) 
    int start_game();
};

#endif