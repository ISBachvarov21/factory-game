#ifndef ENTITY_H
#define ENTITY_H

#include "Ids.h"
#include "Transform.h"

// todo: expose _entity in lua objects.

struct Entity {
    EntityId Id = 0;
    AssetId AssetId = 0;
    ClassId ClassId = 0;
    Transform Transform = {.x = 0, .y = 0, .rotation = 0, .scale_x = 1, .scale_y = 1};
    bool shouldShow = true;
};

#endif //ENTITY_H
