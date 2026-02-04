#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "event.hpp"
#include "player.hpp"

#define GAME_SIZE 101
#define STARTING_X 50
#define STARTING_Y 10-0

class room{
public:
    int pos_x;
    int pos_y;

    room* top_door;
    room* right_door;
    room* bottom_door;
    room* left_door;

    event* held_event;
};

class board{
private:
    std::vector<room*> rooms;

    //Addressed by [y][x]. [0][0] is the top left
    room* generation_board[GAME_SIZE][GAME_SIZE];
public:

    //0: Success
    //1: Fatal issue
    int connect_room(room* room, int depth, int connecting_side);

    //Generates the full board
    //0: Success
    //1: Fatal issue
    int generate();
};

class controller{
private:
    board game_board;
    player player;
public:
    //Controller constructor
    controller();

    //Starts a brand new game
    //-1: Error
    //0: Player exited the game
    //1: Player won
    //2: Player lost (died) 
    int start_game();
};

#endif