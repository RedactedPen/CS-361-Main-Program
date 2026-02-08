#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "item.hpp"

class player{
private:
    int max_health = 10;
    int current_health;
    
    int damage = 2;

    std::vector<item> inventory;

public:
    //Heals the player
    //Returns the ammount of health restored
    int heal(int ammount);

    //Causes the player to take damage
    //Internally checks if the player died and handles the death if needed
    void take_damage(int ammount, std::string source);

    //Allows the player to attack the enemy
    int attack();

    //Returns whether or not the player is alive
    bool alive();
};

#endif 