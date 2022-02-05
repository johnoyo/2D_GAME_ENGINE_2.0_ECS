#include "CollisionSystem.h"

void CollisionSystem::Start()
{
	unsigned int i = 0;
	for (i = 0; i < entities.size(); i++) {
		if (entities.at(i).collisionBox != -1 && entities.at(i).transform != -1) {
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

void CollisionSystem::Run(VertexBuffer& buffer)
{
	// update collision boxes of non-static objects
	for (unsigned int i = 0; i < entities.size(); i++) {
		if (entities.at(i).transform != -1 && transforms.at(entities.at(i).transform).Static == false) {
			Entity::BaseEntity entt = entities.at(i);

			glm::vec3 tr = transforms.at(entt.transform).position;
			glm::vec3 sc = transforms.at(entt.transform).scale;

			// update collision box on x-axis
			if (entities.at(i).collisionBox != -1) {
				collisionBoxes.at(entt.collisionBox).tl.x = tr.x;
				collisionBoxes.at(entt.collisionBox).tr.x = tr.x + sc.x;
				collisionBoxes.at(entt.collisionBox).br.x = tr.x + sc.x;
				collisionBoxes.at(entt.collisionBox).bl.x = tr.x;
			}

			// move player on x-axis
			buffer.Update_PositionX_On_Quad(transforms.at(entt.transform).bufferIndex, transforms.at(entt.transform));
			// collision check on x-axis
			if(entities.at(i).collisionBox != -1) Check_For_Collisions(entt, entt.collisionBox, transforms.at(entt.transform).bufferIndex, buffer, X_AXIS);

			// update collision box on y-axis
			if (entities.at(i).collisionBox != -1) {
				collisionBoxes.at(entt.collisionBox).tl.y = tr.y + sc.y;
				collisionBoxes.at(entt.collisionBox).tr.y = tr.y + sc.y;
				collisionBoxes.at(entt.collisionBox).br.y = tr.y;
				collisionBoxes.at(entt.collisionBox).bl.y = tr.y;
			}

			// move player on y-axis
			buffer.Update_PositionY_On_Quad(transforms.at(entt.transform).bufferIndex, transforms.at(entt.transform));
			// collision check on y-axis
			if (entities.at(i).collisionBox != -1) Check_For_Collisions(entt, entt.collisionBox, transforms.at(entt.transform).bufferIndex, buffer, Y_AXIS);
		}
	}
}

void CollisionSystem::Clear()
{
}

bool CollisionSystem::CollisionBetween(Entity::BaseEntity e0, Entity::BaseEntity e1, VertexBuffer& buffer)
{
	bool collision = false;

	collision = check_corner_br_tl_bool(collisionBoxes.at(e0.collisionBox).br, collisionBoxes.at(e1.collisionBox).tl, collisionBoxes.at(e1.collisionBox).br);
	if (collision) return true;

	collision = check_corner_tr_bl_bool(collisionBoxes.at(e0.collisionBox).tr, collisionBoxes.at(e1.collisionBox).bl, collisionBoxes.at(e1.collisionBox).tr);
	if (collision) return true;

	collision = check_corner_tl_br_bool(collisionBoxes.at(e0.collisionBox).tl, collisionBoxes.at(e1.collisionBox).br, collisionBoxes.at(e1.collisionBox).tl);
	if (collision) return true;

	collision = check_corner_bl_tr_bool(collisionBoxes.at(e0.collisionBox).bl, collisionBoxes.at(e1.collisionBox).tr, collisionBoxes.at(e1.collisionBox).bl);
	if (collision) return true;

	return false;
}

bool CollisionSystem::check_corner_br_tl_bool(glm::vec3 p_br, glm::vec3 e_tl, glm::vec3 e_br) {
	if (p_br.y <= e_tl.y && p_br.x >= e_tl.x && p_br.y >= e_br.y && p_br.x <= e_br.x)
		return true;
	return false;
}

bool CollisionSystem::check_corner_tr_bl_bool(glm::vec3 p_tr, glm::vec3 e_bl, glm::vec3 e_tr) {
	if (p_tr.y >= e_bl.y && p_tr.x >= e_bl.x && p_tr.y <= e_tr.y && p_tr.x <= e_tr.x)
		return true;
	return false;
}

bool CollisionSystem::check_corner_tl_br_bool(glm::vec3 p_tl, glm::vec3 e_br, glm::vec3 e_tl) {
	if (p_tl.y >= e_br.y && p_tl.x <= e_br.x && p_tl.y <= e_tl.y && p_tl.x >= e_tl.x)
		return true;
	return false;
}

bool CollisionSystem::check_corner_bl_tr_bool(glm::vec3 p_bl, glm::vec3 e_tr, glm::vec3 e_bl) {
	if (p_bl.y <= e_tr.y && p_bl.x <= e_tr.x && p_bl.y >= e_bl.y && p_bl.x >= e_bl.x)
		return true;
	return false;
}

void CollisionSystem::change_position_x(Entity::BaseEntity& p, VertexBuffer& buffer) {

	glm::vec3 tr = transforms.at(p.transform).position;
	glm::vec3 sc = transforms.at(p.transform).scale;

	// update collision box on x-axis
	collisionBoxes.at(p.collisionBox).tl.x = tr.x;
	collisionBoxes.at(p.collisionBox).tr.x = tr.x + sc.x;
	collisionBoxes.at(p.collisionBox).br.x = tr.x + sc.x;
	collisionBoxes.at(p.collisionBox).bl.x = tr.x;

	// move player on x-axis
	buffer.Update_PositionX_On_Quad(transforms.at(p.transform).bufferIndex, transforms.at(p.transform));
}

void CollisionSystem::change_position_y(Entity::BaseEntity& p, VertexBuffer& buffer) {

	glm::vec3 tr = transforms.at(p.transform).position;
	glm::vec3 sc = transforms.at(p.transform).scale;

	// update collision box on y-axis
	collisionBoxes.at(p.collisionBox).tl.y = tr.y + sc.y;
	collisionBoxes.at(p.collisionBox).tr.y = tr.y + sc.y;
	collisionBoxes.at(p.collisionBox).br.y = tr.y;
	collisionBoxes.at(p.collisionBox).bl.y = tr.y;

	// move player on y-axis
	buffer.Update_PositionY_On_Quad(transforms.at(p.transform).bufferIndex, transforms.at(p.transform));

}

bool CollisionSystem::check_corner_br_tl(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_br, glm::vec3 e_tl, glm::vec3 e_br, int axis)
{
	if (p_br.y < e_tl.y && p_br.x > e_tl.x && p_br.y > e_br.y && p_br.x < e_br.x) {
		//std::cout << "bottom right\n";
		if (axis == X_AXIS) {
			transforms.at(p.transform).position.x += e_tl.x - p_br.x;
			change_position_x(p, buffer);
		}
		else if (axis == Y_AXIS) {
			transforms.at(p.transform).position.y += e_tl.y - p_br.y;
			change_position_y(p, buffer);
		}
		return true;
	}
	return false;
}

bool CollisionSystem::check_corner_tr_bl(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tr, glm::vec3 e_bl, glm::vec3 e_tr, int axis)
{
	if (p_tr.y > e_bl.y && p_tr.x > e_bl.x && p_tr.y < e_tr.y && p_tr.x < e_tr.x) {
		//std::cout << "top right\n";
		if (axis == X_AXIS) {
			transforms.at(p.transform).position.x += e_bl.x - p_tr.x;
			change_position_x(p, buffer);
		}
		else if (axis == Y_AXIS) {
			//transforms.at(p.transform).position.y += e_bl.y - 0.5f - p_tr.y;
			transforms.at(p.transform).position.y += e_bl.y - p_tr.y;
			change_position_y(p, buffer);
		}
		return true;
	}
	return false;
}

bool CollisionSystem::check_corner_tl_br(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tl, glm::vec3 e_br, glm::vec3 e_tl, int axis)
{
	if (p_tl.y > e_br.y && p_tl.x < e_br.x && p_tl.y < e_tl.y && p_tl.x > e_tl.x) {
		//std::cout << "top left\n";
		if (axis == X_AXIS) {
			transforms.at(p.transform).position.x += e_br.x - p_tl.x;
			change_position_x(p, buffer);
		}
		else if (axis == Y_AXIS) {
			//transforms.at(p.transform).position.y += e_br.y - 0.5f - p_tl.y;
			transforms.at(p.transform).position.y += e_br.y - p_tl.y;
			change_position_y(p, buffer);
		}
		return true;
	}
	return false;
}

bool CollisionSystem::check_corner_bl_tr(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_bl, glm::vec3 e_tr, glm::vec3 e_bl, int axis)
{
	if (p_bl.y < e_tr.y && p_bl.x < e_tr.x && p_bl.y > e_bl.y && p_bl.x > e_bl.x) {
		//std::cout << "bottom left\n";
		if (axis == X_AXIS) {
			transforms.at(p.transform).position.x += e_tr.x - p_bl.x;
			change_position_x(p, buffer);
		}
		else if (axis == Y_AXIS) {
			transforms.at(p.transform).position.y += e_tr.y - p_bl.y;
			change_position_y(p, buffer);
		}
		return true;
	}
	return false;
}

bool CollisionSystem::check_side_l_r(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_br, glm::vec3 p_tr, glm::vec3 e_bl, glm::vec3 e_tl, glm::vec3 e_tr, int axis)
{
	if (p_br.y <= e_bl.y && p_tr.y >= e_tl.y && p_br.x > e_bl.x && p_tr.x > e_tl.x && p_tr.x < e_tr.x) {
		if (axis == X_AXIS) {
			//std::cout << "left to right\n";
			transforms.at(p.transform).position.x += e_bl.x - p_br.x;
			change_position_x(p, buffer);
		}

		return true;
	}
	return false;
}

bool CollisionSystem::check_side_r_l(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tl, glm::vec3 p_bl, glm::vec3 e_tr, glm::vec3 e_br, glm::vec3 e_bl, int axis)
{
	if (p_tl.y >= e_tr.y && p_bl.y <= e_br.y && p_tl.x < e_tr.x && p_bl.x < e_br.x && p_tl.x > e_bl.x) {
		if (axis == X_AXIS) {
			//std::cout << "right to left\n";
			transforms.at(p.transform).position.x += e_br.x - p_bl.x;
			change_position_x(p, buffer);
		}

		return true;
	}
	return false;
}

bool CollisionSystem::check_side_b_t(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_tl, glm::vec3 p_tr, glm::vec3 e_bl, glm::vec3 e_br, glm::vec3 e_tl, int axis)
{
	if (p_tl.x <= e_bl.x && p_tl.y > e_bl.y && p_tr.x >= e_br.x && p_tr.y > e_br.y && p_tl.y < e_tl.y) {
		if (axis == Y_AXIS) {
			//std::cout << "bottom to top\n";
			//transforms.at(p.transform).position.y += e_bl.y - 0.5f - p_tl.y;
			transforms.at(p.transform).position.y += e_bl.y - p_tl.y;
			change_position_y(p, buffer);
		}

		return true;
	}
	return false;
}

bool CollisionSystem::check_side_t_b(VertexBuffer& buffer, Entity::BaseEntity& p, glm::vec3 p_br, glm::vec3 p_bl, glm::vec3 e_tr, glm::vec3 e_tl, glm::vec3 e_bl, int axis)
{
	if (p_bl.x <= e_tl.x && p_bl.y < e_tl.y && p_br.y < e_tr.y && p_br.x >= e_tr.x && p_bl.y > e_bl.y) {
		if (axis == Y_AXIS) {
			//std::cout << "top to bottom\n";
			transforms.at(p.transform).position.y += e_tl.y - p_bl.y;
			change_position_y(p, buffer);
		}

		return true;
	}
	return false;
}

void CollisionSystem::Check_For_Collisions(Entity::BaseEntity& p, int collisionBox, int bufferIndex, VertexBuffer& buffer, int axis)
{
	unsigned int i = 0;
	if (p.gravity != -1/* && axis == Y_AXIS*/) {
		gravity.at(p.gravity).collides = true;
		gravity.at(p.gravity).isGrounded = false;
	}
	for (i = 0; i < collisionBoxes.size(); i++) {
		bool tmp = false;
		if (i != collisionBox && collisionBoxes.at(i).Enabled) {

			tmp = check_corner_br_tl(buffer, p, collisionBoxes.at(collisionBox).br, collisionBoxes.at(i).tl, collisionBoxes.at(i).br, axis);
			if (tmp != false) {
				if (p.gravity != -1/* && axis == Y_AXIS*/) gravity.at(p.gravity).isGrounded = true;
				return;
			}

			tmp = check_corner_tr_bl(buffer, p, collisionBoxes.at(collisionBox).tr, collisionBoxes.at(i).bl, collisionBoxes.at(i).tr, axis);
			if (tmp != false) {
				return;
			}

			tmp = check_corner_tl_br(buffer, p, collisionBoxes.at(collisionBox).tl, collisionBoxes.at(i).br, collisionBoxes.at(i).tl, axis);
			if (tmp != false) {
				return;
			}

			tmp = check_corner_bl_tr(buffer, p, collisionBoxes.at(collisionBox).bl, collisionBoxes.at(i).tr, collisionBoxes.at(i).bl, axis);
			if (tmp != false) {
				if (p.gravity != -1/* && axis == Y_AXIS*/) gravity.at(p.gravity).isGrounded = true;
				return;
			}

			tmp = check_side_l_r(buffer, p, collisionBoxes.at(collisionBox).br, collisionBoxes.at(collisionBox).tr, collisionBoxes.at(i).bl, collisionBoxes.at(i).tl, collisionBoxes.at(i).tr, axis);
			if (tmp != false) {
				return;
			}

			tmp = check_side_r_l(buffer, p, collisionBoxes.at(collisionBox).tl, collisionBoxes.at(collisionBox).bl, collisionBoxes.at(i).tr, collisionBoxes.at(i).br, collisionBoxes.at(i).bl, axis);
			if (tmp != false) {
				return;
			}

			tmp = check_side_t_b(buffer, p, collisionBoxes.at(collisionBox).br, collisionBoxes.at(collisionBox).bl, collisionBoxes.at(i).tr, collisionBoxes.at(i).tl, collisionBoxes.at(i).bl, axis);
			if (tmp != false) {
				if (p.gravity != -1/* && axis == Y_AXIS*/) gravity.at(p.gravity).isGrounded = true;
				return;
			}

			tmp = check_side_b_t(buffer, p, collisionBoxes.at(collisionBox).tl, collisionBoxes.at(collisionBox).tr, collisionBoxes.at(i).bl, collisionBoxes.at(i).br, collisionBoxes.at(i).tl, axis);
			if (tmp != false) {
				return;
			}
		}
	}
	if (p.gravity != -1/* && axis == Y_AXIS*/) {
		gravity.at(p.gravity).collides = false;
		gravity.at(p.gravity).isGrounded = false;
	}
	return;
}

/*

for each non-static entity with collision box do {
	move entity on x-axis
	for each entity with collision box do {
		...
	}

	move entity on y-axis
	for each entity with collision box do {
		...
	}
}

*/
