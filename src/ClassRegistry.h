#ifndef CLASSREGISTRY_H
#define CLASSREGISTRY_H

#include "ClassDefinition.h"
#include <unordered_map>
#include <ranges>
#include <string>

class ClassRegistry {
    std::unordered_map<ClassId, ClassDefinition> m_classTable;
    uint32_t m_next_class_id = 1;


public:
    ClassRegistry() = default;
    ~ClassRegistry() = default;
    void registerClass(ClassDefinition& class_definition);
    const ClassDefinition& get(const ClassId& class_id) const;
    const ClassDefinition& get(const std::string& class_name) const;
};

#endif //CLASSREGISTRY_H
