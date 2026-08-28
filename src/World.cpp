#include "World.h"

#include "LuaRuntime.h"

sol::table World::CreateLuaInstance(
    ClassId class_id,
    EntityId entity_id)
{
    const auto& definition =
        m_runtime->m_classRegistry.get(class_id);

    sol::table instance = m_runtime->m_lua.create_table();

    instance["_entity_id"] = entity_id;

    instance[sol::metatable_key] =
        definition.lua_class;

    if (sol::object init_obj =
            definition.lua_class["init"];
        init_obj.is<sol::function>())
    {
        sol::protected_function init = init_obj;

        auto result = init(instance);

        [[unlikely]]
        if (!result.valid())
        {
            sol::error error = result;
            throw std::runtime_error(error.what());
        }
    }

    return instance;
}

sol::table World::SpawnEntity(ClassId class_id) {
    EntityId entity_id = m_nextEntityId++;
    m_entities.emplace(
        entity_id,
        Entity{
            .Id = entity_id,
            .ClassId = class_id,
        }
    );

    m_entities_by_classes[class_id].push_back(entity_id);

    sol::table instance = CreateLuaInstance(class_id, entity_id);
    m_lua_instances.emplace(entity_id, instance);
    return instance;
}

sol::object World::GetEntity(EntityId entity) {
    return m_lua_instances.at(entity);
}

void World::DeleteEntity(EntityId entity) {
    auto class_id = m_entities.at(entity).ClassId;
    m_entities.erase(entity);
    auto& entities = m_entities_by_classes[class_id];
    std::erase(entities, entity);
}

void World::DeleteAllEntities() {
    m_entities.clear();
    m_entities_by_classes.clear();
}

std::span<const EntityId> World::GetAllEntityIdsFromClass(ClassId class_id) {
    return m_entities_by_classes[class_id];
}

void World::SetLuaRuntime(LuaRuntime* runtime) {
    this->m_runtime = runtime;
}