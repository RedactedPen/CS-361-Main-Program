#ifndef START_HPP
#define START_HPP

#include "event.hpp"

class start : public event{
public:
    int encounter(player* player);
    start();
};

#endif