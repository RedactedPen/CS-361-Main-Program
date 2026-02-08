#include "combat.hpp"

class skeleton: public combat{
    protected:
    std::string enemy_name = "skeleton";
    int enemy_max_health = 4;
    int enemy_current_health = 4;
    int enemy_damage = 2;
    int enemy_hit_chance = 75;
    int enemy_flee_chance = 50;

public:
    int encounter(player* player);
}