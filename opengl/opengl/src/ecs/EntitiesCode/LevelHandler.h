#pragma once
#include <iostream>
#include "../Header.h"


namespace LevelHandler {

	void init(float dt) {
		/*std::cout << "Calling level init\n";*/
		levelSystem.LoadLevel("res/levels/test1.txt", gravitySystem, renderingSystem, renderingSystem.Get_Vertex_Buffer(), renderingSystem.Get_Index_Buffer());

	}

	void update(float dt) {
		if (inputSystem.GetKeyPress(windowSystem.Get_Window(), GLFW_KEY_L))
			levelSystem.LoadLevel("res/levels/test4.txt", gravitySystem, renderingSystem, renderingSystem.Get_Vertex_Buffer(), renderingSystem.Get_Index_Buffer());

		if (inputSystem.GetKeyPress(windowSystem.Get_Window(), GLFW_KEY_K))
			levelSystem.LoadLevel("res/levels/test2.txt", gravitySystem, renderingSystem, renderingSystem.Get_Vertex_Buffer(), renderingSystem.Get_Index_Buffer());
	}

}

