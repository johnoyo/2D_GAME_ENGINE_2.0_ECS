#pragma once

#include "Header.h"
#include <string>

#define STRINGIFY(A) #A
#define LOWER_CASE(str) std::string(STRINGIFY(str)).replace(0, 1, 1, std::string(STRINGIFY(str)).front() + 32)

#define ENROLL_ENTITY(entity) ecs.EnrollEntity(entity, entities)

#define ADD_COMPONENT(component, entity) ecs.AddComponent<Component::component>(entity.component, entities.at(entity.ID).component, component)
#define GET_COMPONENT(component, entity) ecs.GetComponent<Component::component>(entity.component, component)

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#ifdef _DEBUG
#define ENGINE_LOG(f_, ...) printf(("ENGINE_LOG[%s]: " f_ " (%s::%d)\n"), __TIME__, ##__VA_ARGS__, __FILENAME__, __LINE__)
#else
#define ENGINE_LOG(f_, ...)
#endif // _DEBUG
