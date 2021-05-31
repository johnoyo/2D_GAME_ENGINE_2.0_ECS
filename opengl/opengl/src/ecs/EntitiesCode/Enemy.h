#pragma once
#include <iostream>
#include "../Header.h"

namespace Enemy {

	void init(float dt) {
		/*std::cout << "Calling enemy init\n";
		ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x = 200;
		ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.y = 50;

		ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.x = 30;
		ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.y = 30;*/
		ecs.GetComponent<Component::Gravity>(enemy.gravity, gravity).appliedForce = 1;
		ecs.GetComponent<Component::Material>(enemy.material, materials).texture = "res/textures/enemy.png";
	}

	void update(float dt) {
		//std::cout << "Calling enemy update\n";
		ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x++;
		//ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.y += 0.1f;
		//ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.y += ecs.GetComponent<Component::Gravity>(enemy.gravity, gravity).appliedForce;
	}

}
