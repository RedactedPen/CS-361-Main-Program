#include "player.hpp"

int player::heal(int ammount){
    if(this->current_health + ammount <= max_health){
        this->current_health += ammount;
    }else{
        ammount = this->max_health - this->current_health;
        this->current_health = this->max_health;
    }
    return ammount;
}

void player::take_damage(int ammount, std::string source){
    std::cout << "The  " << source << " deals " << ammount << " damage to you" << std::endl;
    this->current_health -= ammount;
    std::cout << "You now have " << this->current_health << " health" << std::endl;
}

int player::attack(){
    return this->damage;
}

bool player::alive(){
    return this->current_health > 0;
}