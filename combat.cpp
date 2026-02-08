#include "combat.hpp"
#include "input.hpp"



void combat::enemy_attack(player* player){
    int attack_chance = 1 + (rand() % 100);

    if(attack_chance <= this->enemy_hit_chance){
        std::cout << "The " << this->enemy_name << " attacks you!\n";
        player->take_damage(this->enemy_damage, this->enemy_name);
    }else{
        std::cout << "The " << this->enemy_name << " tried to attack you, but missed!\n";
    }
}

int combat::run_away(){
    int flee_chance = 1 + (rand() % 100);
    if(flee_chance <= this->enemy_flee_chance){
        printf("You successfully ran away!\n");
        return 1;
    }else{
        printf("You tried to run away, but failed!\n");
        return 0;
    }
}

int combat::encounter(player* player){
    do{
        std::string message = "You are in combat with a " + this->enemy_name + "\n";
        message += "1. Attack the " + this->enemy_name + "\n";
        message += "2. Attempt to run away (" + this->enemy_flee_chance;
        message += "%% chance of success)\n";
        int input = get_int_input(1, 2, message);

        switch(input){
            case 1:
                player->attack();
                break;
            case 2:
                if(this->run_away()){
                    return 1;
                }
                break;
            default:
                printf("Error processing your input. \n");
                continue;
        }

        this->enemy_attack(player);
    }while(this->enemy_current_health > 0);

    return 0;
}