#pragma once
#include "../Header.h"
#include "RenderingSystem.h"
#include <vector>

class CollisionSystem {
public:
	void Start();
	void Run(VertexBuffer& buffer);
	void Clear();
private:
	void change_position_x(Entity::BaseEntity& p, VertexBuffer& buffer);
	void change_position_y(Entity::BaseEntity & p, VertexBuffer& buffer);

	bool check_corner_br_tl(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_br, glm::vec3 e_tl, glm::vec3 e_br, int axis);
	bool check_corner_tr_bl(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tr, glm::vec3 e_bl, glm::vec3 e_tr, int axis);
	bool check_corner_tl_br(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tl, glm::vec3 e_br, glm::vec3 e_tl, int axis);
	bool check_corner_bl_tr(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_bl, glm::vec3 e_tr, glm::vec3 e_bl, int axis);

	bool check_side_l_r(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_br, glm::vec3 p_tr, glm::vec3 e_bl, glm::vec3 e_tl, glm::vec3 e_tr, int axis);
	bool check_side_r_l(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tl, glm::vec3 p_bl, glm::vec3 e_tr, glm::vec3 e_br, glm::vec3 e_bl, int axis);
	bool check_side_b_t(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tl, glm::vec3 p_tr, glm::vec3 e_bl, glm::vec3 e_br, glm::vec3 e_tl, int axis);
	bool check_side_t_b(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_br, glm::vec3 p_bl, glm::vec3 e_tr, glm::vec3 e_tl, glm::vec3 e_bl, int axis);
	
	void Check_For_Collisions(Entity::BaseEntity& p, int collisionBox, int bufferIndex, VertexBuffer& buffer, int axis);

};