#include "LevelSystem.h"

void LevelSystem::LoadLevel(const std::string& level_path, ScriptingSystem& scr, GravitySystem& grav, RenderingSystem& rend, VertexBuffer& vertex_buffer, IndexBuffer& index_buffer, Entity::BaseEntity background)
{
	std::ifstream is(level_path);

	char c;
	char acc[3];
	int i = 0, j = 0, s = 0, h = 0, w = 0;
	int index = 0;

	// Parse level dimensions
	while (is.get(c)) {
		if (c == '\n') break;

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

	// Parse level content
	std::vector<pos> p;
	while (is.get(c)) {
		if (c == 'B') {
			p.push_back({ i,j,6.0f });
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
	int wall_index = 0;
	int enemy_index = 0;
	int collectible_index = 0;

	// Reset all component properties of entities
	for (unsigned int i = 0; i < entities.size(); i++) {
		Entity::BaseEntity entt = entities.at(i);
		if (entt.transform != -1) {
			transforms.at(entt.transform).Static = true;
			transforms.at(entt.transform).Enabled = false;
		}
		if (entt.material != -1) {
			materials.at(entt.material).texture = "-";
			materials.at(entt.material).subTexture.path = "-";
			materials.at(entt.material).Enabled = false;
		}
		if (entt.script != -1) {
			scripts.at(entt.script).Enabled = false;
		}
	}

	// Set up background
	ecs.GetComponent<Component::Transform>(background.transform, transforms).position.x = 0.0f;
	ecs.GetComponent<Component::Transform>(background.transform, transforms).position.y = 0.0f;
	ecs.GetComponent<Component::Transform>(background.transform, transforms).scale.x = 1920.0f;
	ecs.GetComponent<Component::Transform>(background.transform, transforms).scale.y = 1080.0f;
	ecs.GetComponent<Component::Material>(background.material, materials).Enabled = true;
	ecs.GetComponent<Component::Material>(background.material, materials).texture = "res/textures/brickWall_2.jpg";
	ecs.GetComponent<Component::Transform>(background.transform, transforms).Static = false;
	ecs.GetComponent<Component::Transform>(background.transform, transforms).Enabled = true;

	// Re enable lvlHandler
	ecs.GetComponent<Component::Script>(lvlHandler.script, scripts).Enabled = true;

	// Update the position of the entities
	for (unsigned int i = 0; i < p.size(); i++) {
		if (i == s) continue;
		if (p.at(i).k == 1.0f) {
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.x = 30.0f;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.y = 30.0f;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).position.x = p.at(i).j * ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.x;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).position.y = p.at(i).i * ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).scale.y;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).Static = true;
			ecs.GetComponent<Component::Transform>(level[level_index].transform, transforms).Enabled = true;
			ecs.GetComponent<Component::Material>(level[level_index].material, materials).Enabled = true;
			ecs.GetComponent<Component::Material>(level[level_index].material, materials).texture = "res/textures/coinA.png";

			level_index++;
		} 
		else if (p.at(i).k == 6.0f) {
			ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).scale.x = 30.0f;
			ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).scale.y = 30.0f;
			ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).position.x = p.at(i).j * ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).scale.x;
			ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).position.y = p.at(i).i * ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).scale.y;
			ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).Static = true;
			ecs.GetComponent<Component::Transform>(wall[wall_index].transform, transforms).Enabled = true;
			ecs.GetComponent<Component::CollisionBox>(wall[wall_index].collisionBox, collisionBoxes).Enabled = true;
			ecs.GetComponent<Component::Material>(wall[wall_index].material, materials).Enabled = true;
			ecs.GetComponent<Component::Material>(wall[wall_index].material, materials).texture = "res/textures/brick_3.png";

			wall_index++;
		}
		else if (p.at(i).k == 4.0f) {
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.x = 30.0f;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.y = 30.0f;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.x = p.at(i).j * ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.x;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).position.y = p.at(i).i * ecs.GetComponent<Component::Transform>(enemy.transform, transforms).scale.y;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).Static = false;
			ecs.GetComponent<Component::Transform>(enemy.transform, transforms).Enabled = true;
			ecs.GetComponent<Component::CollisionBox>(enemy.collisionBox, collisionBoxes).Enabled = true;
			ecs.GetComponent<Component::Script>(enemy.script, scripts).Enabled = true;
			ecs.GetComponent<Component::Material>(enemy.material, materials).Enabled = true;
			enemy_index++;
		}
	}

	std::cout << "lvl indx: " << level_index << "\n";
	std::cout << "wall indx: " << wall_index << "\n";
	std::cout << "p size: " << p.size() << "\n";

	// Upadate the position of the player last
	ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.x = 29.0f;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.y = 29.0f;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).position.x = p.at(s).j * ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.x;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).position.y = p.at(s).i * ecs.GetComponent<Component::Transform>(player.transform, transforms).scale.y;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).Static = false;
	ecs.GetComponent<Component::Transform>(player.transform, transforms).Enabled = true;
	ecs.GetComponent<Component::CollisionBox>(player.collisionBox, collisionBoxes).Enabled = true;
	ecs.GetComponent<Component::Script>(player.script, scripts).Enabled = true;
	ecs.GetComponent<Component::Material>(player.material, materials).Enabled = true;

	// Recalculate all collision boxes
	for (unsigned int i = 0; i < entities.size(); i++) {
		if (entities.at(i).collisionBox != -1 && entities.at(i).transform != -1) {
			if (collisionBoxes.at(entities.at(i).collisionBox).Enabled) {
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

	is.close();

	rend.Init_Vertex_Buffer();

	current_level++;

	grav.ResetGravity(6.0f, -6.0f);
	scr.Start(current_level);

}

void LevelSystem::LoadLevel(Entity::BaseEntity entt, RenderingSystem& rend, VertexBuffer& vertex_buffer, IndexBuffer& index_buffer)
{
	rend.Draw_Lone_Quad(entt);
}
