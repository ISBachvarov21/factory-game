#include "LuaRuntime.h"

#include "World.h"

void LuaRuntime::init() {
    m_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table);

    std::string packagePath = m_lua["package"]["path"];
    packagePath += ";../../scripts/?.lua;../../scripts/?/init.lua";
    packagePath += ";./scripts/?.lua;./scripts/?/init.lua";
    m_lua["package"]["path"] = packagePath;

    m_lua["register_class"] = [this](const std::string& className, const sol::table& lua_class) {
        ClassDefinition class_definition;
        class_definition.name = className;
        AssetId assetId;
        if ((assetId = lua_class.get_or("_asset_id", 0)) != 0) {
            class_definition.asset_id = assetId;
        }
        class_definition.lua_class = lua_class;
        this->m_classRegistry.registerClass(class_definition);
    };

    m_lua.new_usertype<World>("World",
        "spawn", [this](World* world, const std::string &className) {
            ClassId class_id = this->m_classRegistry.get(className).id;
            return world->SpawnEntity(class_id, this->m_classRegistry, this->m_lua);
        },
        "deleteEntity", &World::DeleteEntity,
        "deleteAllEntities", &World::DeleteAllEntities,
        "getEntityById", &World::GetEntity,
        "getAllEntityIdsFromClass", &World::GetAllEntityIdsFromClass
    );
    m_lua["world"] = &m_world;
}

void LuaRuntime::load_definitions() {
    using filepath = std::filesystem::path;
    filepath definitionsPath = "../../scripts/definitions/";

    for (const auto& entry : std::filesystem::directory_iterator(definitionsPath)) {
        std::cout << entry.path().string() << std::endl;
        if (entry.is_regular_file() && entry.path().extension() == ".lua") {
            m_lua.script_file(entry.path().string());
        }
    }
}
