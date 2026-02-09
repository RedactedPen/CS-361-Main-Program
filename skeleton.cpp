#include "skeleton.hpp"

skeleton::skeleton(){
    this->enemy_name = "Skeleton";
    this->enemy_max_health = 4;
    this->enemy_current_health = 4;
    this->enemy_damage = 2;
    this->enemy_hit_chance = 75;
    this->enemy_flee_chance = 50;
}