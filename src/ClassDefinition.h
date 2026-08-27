#ifndef CLASSDEFINITION_H
#define CLASSDEFINITION_H
#include "Ids.h"
#include "sol/sol.hpp"

struct ClassDefinition {
    ClassId id;
    std::string name;

    sol::table lua_class;

    AssetId asset_id;
};

#endif //CLASSDEFINITION_H
