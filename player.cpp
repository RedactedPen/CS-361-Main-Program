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
    printf("The ")
    this->current_health -= ammount;
}

void player::attack(combat* combat){
    combat->damage_enemy(this->damage);
}