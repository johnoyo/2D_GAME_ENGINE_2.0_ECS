#pragma once
#include <iostream>
#include "../Header.h"

namespace Enemy {

	void init(float dt) {
		ecs.GetComponent<Component::Material>(enemy.material, materials).texture = "res/textures/enemy.png";
	}

	namespace Level_0 {

		void update(float dt) {
			//std::cout << "Calling enemy update 0 \n";
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x--;
			ecs.GetComponent<Component::Gravity>(enemy.gravity, gravity).gravityEnabled = false;
		}

	}

	namespace Level_1 {

		void update(float dt) {
			//std::cout << "Calling enemy update 1 \n";
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x--;
			ecs.GetComponent<Component::Gravity>(enemy.gravity, gravity).gravityEnabled = true;
		}

	}

}
