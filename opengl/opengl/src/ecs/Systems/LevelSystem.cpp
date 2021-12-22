#include "LevelSystem.h"

void LevelSystem::LoadLevel(const std::string& level_path, RenderingSystem& rend, VertexBuffer& vertex_buffer, IndexBuffer& index_buffer)
{
	FILE* f;
	fopen_s(&f, level_path.c_str(), "r");

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
		} else if (c == 'G') {
			p.push_back({ i,j,1.0f });
		} else if (c == 'C') {
			p.push_back({ i,j,3.0f });
		} else if (c == 'R') {
			p.push_back({ i,j,15.0f });
		} else if (c == 'E') {
			p.push_back({ i,j,4.0f });
		} else if (c == '>') {
			p.push_back({ i,j,8.0f });
		} else if (c == 'P') {
			p.push_back({ i,j,5.0f });
			s = p.size() - 1;
		}
		if (j == w) {
			j = 0;
			i--;
			continue;
		}
		j++;
	}

	vertex_buffer.Reset();
	int level_index = 0;
	int enemy_index = 0;
	int collectible_index = 0;

	// Update the position of the entities
	for (unsigned int i = 0; i < p.size(); i++) {
		if (i == s) continue;
		if (p.at(i).k == 1.0f) {
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.x = 30.0f;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.y = 30.0f;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).position.x = p.at(i).j * ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.x;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).position.y = p.at(i).i * ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.y;
			ecs.GetComponent<Component::Attributes>(level[level_index].attributes, attributes).Enabled = true;
			ecs.GetComponent<Component::CollisionBox>(level[level_index].collisionBox, collisionBoxes).CBEnabled = true;

			level_index++;
		} else if (p.at(i).k == 4.0f) {
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.x = 30.0f;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.y = 30.0f;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x = p.at(i).j * ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.x;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.y = p.at(i).i * ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.y;
			ecs.GetComponent<Component::Attributes>(enemy.attributes, attributes).Enabled = true;
			ecs.GetComponent<Component::CollisionBox>(enemy.collisionBox, collisionBoxes).CBEnabled = true;
			enemy_index++;
		}
	}
	std::cout << "lvl indx: " << level_index << "\n";
	std::cout << "p size: " << p.size() << "\n";
	// Upadate the position of the player last
	ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.x = 29.0f;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.y = 29.0f;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x = p.at(s).j * ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.x;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y = p.at(s).i * ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.y;
	ecs.GetComponent<Component::Attributes>(player.attributes, attributes).Enabled = true;
	ecs.GetComponent<Component::CollisionBox>(player.collisionBox, collisionBoxes).CBEnabled = true;
	ecs.GetComponent<Component::Gravity>(player.gravity, gravity).appliedForce = 0;

	// NOTE: i have to do this for every entity array
	for (unsigned int i = level_index; i < 90; i++) {
		ecs.GetComponent<Component::Attributes>(level[i].attributes, attributes).Enabled = false;
		ecs.GetComponent<Component::CollisionBox>(level[i].collisionBox, collisionBoxes).CBEnabled = false;
	}

	// Recalculate all collision boxes
	for (unsigned int i = 0; i < entities.size(); i++) {
		if (entities.at(i).collisionBox != -1 && entities.at(i).transform != -1 && entities.at(i).attributes != -1) {
			if (attributes.at(entities.at(i).attributes).Enabled && collisionBoxes.at(entities.at(i).collisionBox).CBEnabled) {
				collisionBoxes.at(entities.at(i).collisionBox).tl.x = transforms.at(entities.at(i).transform).position.x;
				collisionBoxes.at(entities.at(i).collisionBox).tl.y = transforms.at(entities.at(i).transform).position.y + transforms.at(entities.at(i).transform).scale.y;

				collisionBoxes.at(entities.at(i).collisionBox).tr.x = transforms.at(entities.at(i).transform).position.x + transforms.at(entities.at(i).transform).scale.x;
				collisionBoxes.at(entities.at(i).collisionBox).tr.y = transforms.at(entities.at(i).transform).position.y + transforms.at(entities.at(i).transform).scale.y;

				collisionBoxes.at(entities.at(i).collisionBox).br.x = transforms.at(entities.at(i).transform).position.x + transforms.at(entities.at(i).transform).scale.x;
				collisionBoxes.at(entities.at(i).collisionBox).br.y = transforms.at(entities.at(i).transform).position.y;

				collisionBoxes.at(entities.at(i).collisionBox).bl.x = transforms.at(entities.at(i).transform).position.x;
				collisionBoxes.at(entities.at(i).collisionBox).bl.y = transforms.at(entities.at(i).transform).position.y;
			}
		}
	}

	fclose(f);

	rend.Init_Vertex_Buffer();

	current_level++;

}

void LevelSystem::LoadLevel(Entity::BaseEntity entt, RenderingSystem& rend, VertexBuffer& vertex_buffer, IndexBuffer& index_buffer)
{
	ecs.GetComponent<Component::Attributes>(entt.attributes, attributes).Enabled = true;
	rend.Draw_Lone_Quad(entt);
}
