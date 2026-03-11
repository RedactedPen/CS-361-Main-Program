#include "player.hpp"
#include "transmit.hpp"

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
    std::string damage_message = "The " + source + " deals ";
    damage_message += std::to_string(ammount) + " damage to you";

    damage_message = send_request(COLORER, "red:" + damage_message);
    std::cout << damage_message << std::endl;

    this->current_health -= ammount;


    std::string health_message =  std::to_string(this->current_health);
    health_message = send_request(COLORER, "green:" + health_message);

    std::cout << "You now have " << health_message << " health" << std::endl;
}

int player::attack(){
    return this->damage;
}

bool player::alive(){
    return this->current_health > 0;
}