#pragma once
#include <iostream>
#include "../Header.h"

namespace Player {

	namespace Level_0 {

		void init(float dt) {

			//ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x = 15.0f;
			//ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y = 100.0f;
			//ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.x = 25.0f;
			//ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.y = 25.0f;
			//ecs.GetComponent<Component::Material>(player.material, materials).texture = "res/textures/player_r.png";

			ecs.GetComponent<Component::Material>(sps.material, materials).texture = "res/textures/super_mario_tiles.png";

			ecs.GetComponent<Component::Material>(player.material, materials).subTexture.coords = { 0.0f, 11.0f };
			ecs.GetComponent<Component::Material>(player.material, materials).subTexture.sprite_size = { 16.0f, 16.0f };
			ecs.GetComponent<Component::Material>(player.material, materials).subTexture.path = ecs.GetComponent<Component::Material>(sps.material, materials).texture;

		}

		void update(float dt) {

			// Background follow player
			ecs.GetComponent<Component::Transform>(background.transform, transforms).position.x = ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x + (-windowSystem.Get_Width() / 2.0f);
			ecs.GetComponent<Component::Transform>(background.transform, transforms).position.y = ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y + (-windowSystem.Get_Height() / 2.0f);

			// Camera follow player
			cameraSystem.Follow(player, (-windowSystem.Get_Width() / 2.0f), (-windowSystem.Get_Height() / 2.0f));

			// Player movement
			if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_D, GLFW_PRESS))
				ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x += 6.0f;

			if (inputSystem.GetKeyPress(windowSystem.Get_Window(), GLFW_KEY_SPACE))
				soundSystem.PlaySound("res/audio/bleep.mp3");

			if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_A, GLFW_PRESS))
				ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x -= 6.0f;

			if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_S, GLFW_PRESS)) 
				ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y -= 6.0f;

			if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_W, GLFW_PRESS)) 
				ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y += 6.0f;

			if (collisionSystem.CollisionBetween(player, enemy, renderingSystem.Get_Vertex_Buffer()))
				std::cout << "Player collided with enemy!!!\n";

			// NOTE: Maybe move this inside the gravity system??? 

			// Player movement with gravity enabled
			//if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_W, GLFW_PRESS) && ecs.GetComponent<Component::Gravity>(player.gravity, gravity).isGrounded)
			//	ecs.GetComponent<Component::Gravity>(player.gravity, gravity).appliedForce = 10.0f;

			//ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y += ecs.GetComponent<Component::Gravity>(player.gravity, gravity).appliedForce;
			//std::cout << ecs.GetComponent<Component::Gravity>(player.gravity, gravity).appliedForce << "\n";
		}

	}

}

