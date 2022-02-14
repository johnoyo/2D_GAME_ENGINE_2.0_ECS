#pragma once

#include "System.h"
#include "Entities.h"
#include "Components.h"
#include <vector>
#include <string>

extern System ecs;

extern std::vector<Entity::BaseEntity> entities;

/* ------------------------------- Entities Declaration ---------------------------- */
extern Entity::BaseEntity background;
extern Entity::BaseEntity player;
extern Entity::BaseEntity enemy;
extern Entity::BaseEntity wall[400];
extern Entity::BaseEntity level[10000];
extern Entity::BaseEntity lvlHandler;
extern Entity::BaseEntity camera;
extern Entity::BaseEntity sps;
/* --------------------------------------------------------------------------------- */

/* ------------------------- Component Vector Declaration -------------------------- */
extern std::vector<Component::Transform> transforms;
extern std::vector<Component::CollisionBox> collisionBoxes;
extern std::vector<Component::Material> materials;
extern std::vector<Component::Health> health;
extern std::vector<Component::Script> scripts;
extern std::vector<Component::Gravity> gravity;
/* --------------------------------------------------------------------------------- */
