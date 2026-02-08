#ifndef EVENT_HPP
#define EVENT_HPP
#include "player.hpp"

class event{
protected:
    bool persistent;
    char representation;
public:

    //0 Event resolved, nothing else needs to be done
    //1 Event resolved, player needs to be sent back to the room they came from
    virtual int encounter(player* player) = 0;

    char map_representation();
};

#endif