#include "CameraSystem.h"

CameraSystem::CameraSystem(float left, float right, float bottom, float top)
	: m_Projection_Matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View_Matrix(1.0f)
{
	m_View_Projection_Matrix = m_Projection_Matrix * m_View_Matrix;
}


void CameraSystem::Recalculate_View_Matrix()
{
	glm::mat4 tranform = 
		glm::translate(glm::mat4(1.0f), ecs.GetComponent<Component::Transform>(camera.transform, transforms).position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(0.0f/*Rotation*/), glm::vec3(0, 0, 1));

	m_View_Matrix = glm::inverse(tranform);
	m_View_Projection_Matrix = m_Projection_Matrix * m_View_Matrix;
}

void CameraSystem::Start()
{
	std::cout << "Starting camera system ...\n";
}

void CameraSystem::Run()
{
	std::cout << "Running camera system ...\n";
}