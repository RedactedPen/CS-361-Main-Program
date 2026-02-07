#include "event.hpp"
#include <iostream>
class combat: public event{
protected:
    std::string enemy_name;
    int enemy_max_health;
    int enemy_current_health;
    int enemy_damage;
    int enemy_hit_chance;

    char representation = 'C';

    void damage_enemy(int ammount);
public:
    virtual int encounter() = 0;
};