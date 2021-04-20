#pragma once

#include "System.h"
#include "Entities.h"
#include "Components.h"
#include <vector>
#include <string>

extern System ecs;

extern std::vector<Entity::BaseEntity> entities;

/* ------------------------------- Entities Declaration ---------------------------- */
extern Entity::BaseEntity player;
extern Entity::BaseEntity enemy;
extern Entity::BaseEntity level[90];
//extern Entity::BaseEntity block;
//extern Entity::BaseEntity ground;
extern Entity::BaseEntity lvlHandler;
extern Entity::BaseEntity camera;
/* --------------------------------------------------------------------------------- */

/* ------------------------- Component Vector Declaration -------------------------- */
extern std::vector<Component::Transform> transforms;
extern std::vector<Component::CollisionBox> collisionBoxes;
extern std::vector<Component::Material> materials;
extern std::vector<Component::Health> health;
extern std::vector<Component::Script> scripts;
extern std::vector<Component::Attributes> attributes;
extern std::vector<Component::Gravity> gravity;
/* --------------------------------------------------------------------------------- */
