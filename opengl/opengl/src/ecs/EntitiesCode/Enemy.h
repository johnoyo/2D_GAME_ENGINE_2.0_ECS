#pragma once
#include <iostream>
#include "../Header.h"

namespace Enemy {

	namespace Level_0 {

		void init(float dt) {
			std::cout << "Calling enemy init 0 \n";
			ecs.GetComponent<Component::Material>(enemy.Material, Material).texture = "res/textures/player_r.png";
			//ecs.GetComponent<Component::Transform>(enemy.Transform, Transform).rotation = 45.0f;

		}

		void update(float dt) {
			//std::cout << "Calling enemy update 0 \n";
			ecs.GetComponent<Component::Transform>(enemy.Transform, Transform).position.x--;
			//ecs.GetComponent<Component::Transform>(enemy.Transform, Transform).rotation++;
			ecs.GetComponent<Component::Gravity>(enemy.Gravity, Gravity).Enabled = false;
		}

	}

	namespace Level_1 {

		void init(float dt) {
			std::cout << "Calling enemy init 1 \n";
			ecs.GetComponent<Component::Material>(enemy.Material, Material).texture = "res/textures/player_r.png";
			//ecs.GetComponent<Component::Transform>(enemy.Transform, Transform).rotation = 45.0f;
		}

		void update(float dt) {
			//std::cout << "Calling enemy update 1 \n";
			ecs.GetComponent<Component::Transform>(enemy.Transform, Transform).position.x++;
			ecs.GetComponent<Component::Gravity>(enemy.Gravity, Gravity).Enabled = false;
		}

	}

}
