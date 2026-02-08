#ifndef COMBAT_HPP
#define COMBAT_HPP

#include "event.hpp"
#include <iostream>

class combat: public event {
private:
    char representation = 'C';
protected:
    std::string enemy_name;
    int enemy_max_health;
    int enemy_current_health;
    int enemy_damage;
    int enemy_hit_chance;
    int enemy_flee_chance;    

    void enemy_attack(player* player);

    int run_away();
public:
    void damage_enemy(int ammount);
    int encounter(player* player);
    
};

#endif