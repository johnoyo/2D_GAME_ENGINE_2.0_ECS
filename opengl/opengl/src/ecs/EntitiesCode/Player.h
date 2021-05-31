#pragma once
#include <iostream>
#include "../Header.h"

namespace Player {

	void init(float dt) {
		/*std::cout << "Calling player init\n";
		ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x = 15.0f;
		ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y = 100.0f;
		ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.x = 25.0f;
		ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.y = 25.0f;*/
		//ecs.GetComponent<Component::Material>(player.material, materials).texture = "res/textures/player_r.png";
		//ecs.GetComponent<Component::Gravity>(enemy.gravity, gravity).appliedForce = 1;


		ecs.GetComponent<Component::Material>(sps.material, materials).texture = "res/textures/super_mario_tiles.png";

		ecs.GetComponent<Component::Material>(player.material, materials).subTexture.coords = { 0.0f, 11.0f };
		ecs.GetComponent<Component::Material>(player.material, materials).subTexture.sprite_size = { 16.0f, 16.0f };
		ecs.GetComponent<Component::Material>(player.material, materials).subTexture.path = ecs.GetComponent<Component::Material>(sps.material, materials).texture;

	}

	void update(float dt) {
		// TODO: Change Set_Position_x() to take an entity as argument 
		// cameraSystem.Set_Position_x(ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x + (-windowSystem.Get_Width() / 2.0f));
		// cameraSystem.Set_Position_x(transforms.at(player.transform).position.x + (-windowSystem.Get_Width() / 2.0f));

		//std::cout << "Calling player update\n";
		if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_D, GLFW_PRESS))
			ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x+=6.0f;

		if (inputSystem.GetKeyPress(windowSystem.Get_Window(), GLFW_KEY_SPACE))
			soundSystem.PlaySound("res/audio/bleep.mp3");

		if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_A, GLFW_PRESS)) 
			ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x-=6.0f;

		if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_W, GLFW_PRESS) && ecs.GetComponent<Component::Gravity>(player.gravity, gravity).isGrounded)
			ecs.GetComponent<Component::Gravity>(player.gravity, gravity).appliedForce = 10.0f;

		//ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y += ecs.GetComponent<Component::Gravity>(player.gravity, gravity).appliedForce;
		std::cout << ecs.GetComponent<Component::Gravity>(player.gravity, gravity).appliedForce << "\n";

	
		//if (inputSystem.GetKeyDown(windowSystem.Get_Window(), GLFW_KEY_S, GLFW_PRESS)) ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y-=14.0f;
	}

}

