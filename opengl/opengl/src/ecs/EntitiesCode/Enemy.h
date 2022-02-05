#pragma once
#include <iostream>
#include "../Header.h"

namespace Enemy {

	namespace Level_0 {

		void init(float dt) {
			std::cout << "Calling enemy init 0 \n";
			ecs.GetComponent<Component::Material>(enemy.material, materials).texture = "res/textures/enemy.png";
		}

		void update(float dt) {
			//std::cout << "Calling enemy update 0 \n";
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x--;
			ecs.GetComponent<Component::Gravity>(enemy.gravity, gravity).Enabled = true;
		}

	}

	namespace Level_1 {

		void init(float dt) {
			std::cout << "Calling enemy init 1 \n";
			ecs.GetComponent<Component::Material>(enemy.material, materials).texture = "res/textures/enemy.png";
		}

		void update(float dt) {
			//std::cout << "Calling enemy update 1 \n";
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x++;
			ecs.GetComponent<Component::Gravity>(enemy.gravity, gravity).Enabled = false;
		}

	}

}
