#pragma once
#include <iostream>
#include "../Header.h"


namespace LevelHandler {

	void init(float dt) {
		/*std::cout << "Calling level init\n";

		FILE* f;
		fopen_s(&f, "res/levels/test1.txt", "r");

		if (!f) return;
		char c;
		char acc[3];
		int i = 0, j = 0, s = 0, h = 0, w = 0;
		int index = 0;

		while ((c = fgetc(f)) != '\n') {
			if (c == ',') {
				index = 0;
				h = atoi(acc);
				continue;
			}
			if (c == '.') {
				index = 0;
				w = atoi(acc);
				continue;
			}
			acc[index] = c;
			index++;
		}


		i = h - 1;

		struct pos {
			int i;
			int j;
			float k;
		};

		std::vector<pos> p;
		while ((c = fgetc(f)) != EOF) {
			if (c == 'B') {
				p.push_back({ i,j,16.0f });
			}
			else if (c == 'G') {
				std::cout << "i,j = " << i << ", " << j << "\n";
				p.push_back({ i,j,1.0f });
			}
			else if (c == 'C')
			{
				p.push_back({ i,j,3.0f });
			}
			else if (c == 'R')
			{
				p.push_back({ i,j,15.0f });
			}
			else if (c == 'E')
			{
				p.push_back({ i,j,4.0f });
			}
			else if (c == '>')
			{
				p.push_back({ i,j,8.0f });
			}
			else if (c == 'P')
			{
				p.push_back({ i,j,5.0f });
				std::cout << "i,j = " << i << ", " << j << "\n";
				s = p.size() - 1;
			}
			if (j == w) {

				j = 0;
				i--;
				continue;
			}
			j++;
		}

		for (unsigned int i = 0; i < p.size(); i++)
		{
			ecs.GetComponent<Component::Transform>(level[i].transform, transforms).scale.x = 30.0f;
			ecs.GetComponent<Component::Transform>(level[i].transform, transforms).scale.y = 30.0f;
		}

		for (unsigned int i = 0; i < p.size(); i++)
		{
			ecs.GetComponent<Component::Transform>(level[i].transform, transforms).position.x = p.at(i).j * ecs.GetComponent<Component::Transform>(level[i].transform, transforms).scale.x;
			ecs.GetComponent<Component::Transform>(level[i].transform, transforms).position.y = p.at(i).i * ecs.GetComponent<Component::Transform>(level[i].transform, transforms).scale.y;
		}

		fclose(f);*/
		levelSystem.LoadLevel("res/levels/test1.txt", renderingSystem, renderingSystem.Get_Vertex_Buffer(), renderingSystem.Get_Index_Buffer());
		
	}

	void update(float dt) {
		if (inputSystem.GetKeyPress(windowSystem.Get_Window(), GLFW_KEY_L)) 
			levelSystem.LoadLevel("res/levels/test4.txt", renderingSystem, renderingSystem.Get_Vertex_Buffer(), renderingSystem.Get_Index_Buffer());
	}

}

