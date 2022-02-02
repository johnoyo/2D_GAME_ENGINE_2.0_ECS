#include "GravitySystem.h"

void GravitySystem::Start(float gravityForce, float thres)
{
	force = gravityForce;
	threshold = thres;
}

void GravitySystem::ResetGravity(float gravityForce, float thres)
{
	// Reset gravity forces
	force = gravityForce;
	threshold = thres;

	// Reset force applied to each entity
	for (unsigned int i = 0; i < entities.size(); i++) {
		Entity::BaseEntity entt = entities.at(i);
		if (entt.gravity != -1) {
			gravity.at(entt.gravity).appliedForce = 0.0f;
		}
	}
}

void GravitySystem::Run()
{
	for (unsigned int i = 0; i < entities.size(); i++) {
		Entity::BaseEntity entt = entities.at(i);
		if (entt.gravity != -1 && gravity.at(entt.gravity).gravityEnabled && !gravity.at(entt.gravity).isGrounded) {

			if (!gravity.at(entt.gravity).collides) gravity.at(entt.gravity).appliedForce += -0.1f * force;
			else gravity.at(entt.gravity).appliedForce = -1.0f;

			transforms.at(entt.transform).position.y += 2.0f * gravity.at(entt.gravity).appliedForce;
		}
		else if (entt.gravity != -1 && gravity.at(entt.gravity).gravityEnabled && gravity.at(entt.gravity).isGrounded) {
			if (gravity.at(entt.gravity).appliedForce <= threshold) gravity.at(entt.gravity).appliedForce = threshold;
		}
	}
}

