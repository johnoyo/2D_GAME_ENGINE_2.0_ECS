#include "GravitySystem.h"

void GravitySystem::Start(float gravityForce)
{
	force = gravityForce;
}

void GravitySystem::Run()
{
	for (unsigned int i = 0; i < entities.size(); i++) {
		Entity::BaseEntity entt = entities.at(i);
		if (entt.gravity != -1 && gravity.at(entt.gravity).gravityEnabled && !gravity.at(entt.gravity).isGrounded) {
			if (!gravity.at(entt.gravity).collides) gravity.at(entt.gravity).appliedForce += -0.1f * force;
			else  gravity.at(entt.gravity).appliedForce = -1.0f;

			transforms.at(entt.transform).position.y += gravity.at(entt.gravity).appliedForce;
		}
	}
}
