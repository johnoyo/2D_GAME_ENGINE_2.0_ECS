#pragma once
#include "../Header.h"
#include "RenderingSystem.h"
#include "CollisionSystem.h"
#include "GravitySystem.h"
#include <string>

class LevelSystem {
public:
	void Start();
	void Run();
	void Clear();

	void LoadLevel(const std::string& level_path, GravitySystem& grav, RenderingSystem& rend, VertexBuffer& vertex_buffer, IndexBuffer& index_buffer);
	void LoadLevel(Entity::BaseEntity entt, RenderingSystem& rend, VertexBuffer& vertex_buffer, IndexBuffer& index_buffer);
	inline unsigned int GetCurrentLevel() { return current_level; }
private:
	unsigned int current_level = 0;
};