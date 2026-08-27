#include "ClassRegistry.h"

void ClassRegistry::registerClass(ClassDefinition& class_definition) {
    class_definition.id = m_next_class_id++;
    m_classTable[class_definition.id] = class_definition;
}

const ClassDefinition& ClassRegistry::get(const ClassId& class_id) const {
    return m_classTable.at(class_id);
}

const ClassDefinition& ClassRegistry::get(const std::string &class_name) const {
    for (const auto &class_def: m_classTable | std::views::values) {
        if (class_def.name == class_name) {
            [[likely]]
            return class_def;
        }
    }
    [[unlikely]]
    return ClassDefinition();
}
