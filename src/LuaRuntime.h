#ifndef LUARUNTIME_H
#define LUARUNTIME_H
#include <sol/sol.hpp>
#include <filesystem>

#include "World.h"

class LuaRuntime {
public:
    LuaRuntime() = default;
    ~LuaRuntime() = default;
    void init();
    void load_definitions();

    friend class World;

private:
    sol::state m_lua;
    ClassRegistry m_classRegistry;
    World m_world;
};

#endif //LUARUNTIME_H
