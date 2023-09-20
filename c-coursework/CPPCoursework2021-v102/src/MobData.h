#pragma once
#include "UtilEnums.h"
//#include "UtilMovementPosition.h"
#include "SimpleImage.h"

struct MobData {
    //std::string mob_name;
    int hp;
    //MovementPosition mob_position;
    int mob_x;
    int mob_y;
    int y_sort;
    bool in_range;
    bool moving;
    EnemyType type;
    //SimpleImage texture;
    //std::string texture_url;
    SimpleImage mob_texture;
    //Direction mob_direction;
};
