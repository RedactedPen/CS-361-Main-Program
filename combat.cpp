#include "combat.hpp"
#include "input.hpp"

void combat::damage_enemy(int ammount){
    std::cout << "You attack the " << this->enemy_name << " for " << ammount << " damage" << std::endl;
    this->enemy_current_health -= ammount;
}

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
        std::string message = "\nYou are in combat with a " + this->enemy_name + "\n";
        message += "1. Attack the " + this->enemy_name + "\n";
        message += "2. Attempt to run away (" + std::to_string(this->enemy_flee_chance) + "% chance of success)\n";
        int input = get_int_input(1, 2, message);

        switch(input){
            case 1:
                this->damage_enemy(player->attack());
                break;
            case 2:
                if(this->run_away()){
                    return 1;
                }
                break;
        }
        if(this->enemy_current_health > 0){
            this->enemy_attack(player);
        }
    }while(this->enemy_current_health > 0 && player->alive());

    return 0;
}