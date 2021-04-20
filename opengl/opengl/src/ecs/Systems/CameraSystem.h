#pragma once
#include "../Header.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>


class CameraSystem {
public:
	CameraSystem() { }
	CameraSystem(float left, float right, float bottom, float top);

	void Start();
	void Run();

	void Set_Position(const glm::vec3& position) { ecs.GetComponent<Component::Transform>(camera.transform, transforms).position = position; Recalculate_View_Matrix(); }
	void Set_Position_x(float position) { ecs.GetComponent<Component::Transform>(camera.transform, transforms).position.x = position; Recalculate_View_Matrix(); }
	void Set_Position_y(float position) { ecs.GetComponent<Component::Transform>(camera.transform, transforms).position.y = position; Recalculate_View_Matrix(); }
	void Incr_Position(const glm::vec3& position) { ecs.GetComponent<Component::Transform>(camera.transform, transforms).position.x += position.x;  ecs.GetComponent<Component::Transform>(camera.transform, transforms).position.y += position.y; Recalculate_View_Matrix(); }

	const glm::mat4& Get_Projection_Matrix() const { return m_Projection_Matrix; }
	const glm::mat4& Get_View_Matrix() const { return m_View_Matrix; }
	const glm::mat4& Get_View_Projection_Matrix() const { return m_View_Projection_Matrix; }

private:
	void Recalculate_View_Matrix();

	glm::mat4 m_Projection_Matrix;
	glm::mat4 m_View_Matrix;
	glm::mat4 m_View_Projection_Matrix;
};