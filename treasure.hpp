#ifndef TREASURE_HPP
#define TREASURE_HPP

#include "event.hpp"

class treasure : public event{
    bool taken = false;
public:
    int encounter(player* player);
    treasure();
};

#endif