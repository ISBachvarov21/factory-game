//
// Created by Ivaylo on 24.8.2026 г..
//

#ifndef WORLD_H
#define WORLD_H
#include <span>
#include <unordered_map>

#include "ClassRegistry.h"
#include "Entity.h"
#include "sol/sol.hpp"

class World {
    std::unordered_map<EntityId, Entity> m_entities;
    std::unordered_map<ClassId, std::vector<EntityId>> m_entities_by_classes;
    std::unordered_map<EntityId, sol::reference> m_lua_instances;

    EntityId m_nextEntityId = 1;

    sol::table CreateLuaInstance(ClassId class_id, EntityId entity_id, const ClassRegistry& registry, sol::state& lua);

public:
    sol::table SpawnEntity(ClassId class_id, const ClassRegistry& registry, sol::state& lua);
    void DeleteEntity(EntityId entity);
    void DeleteAllEntities();
    std::span<const EntityId> GetAllEntityIdsFromClass(ClassId class_id);
    sol::object GetEntity(EntityId entity);

};

#endif //WORLD_H
