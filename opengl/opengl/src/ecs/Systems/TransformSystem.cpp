#include "TransformSystem.h"

void TransformSystem::Start()
{
}

void TransformSystem::Run(VertexBuffer& buffer)
{
	for (int i = 0; i < Transform.size(); i++) {
		if (Transform.at(i).Static == false) {
			// move player on x-axis
			//buffer.Update_PositionX_On_Quad(transforms.at(i).bufferIndex, transforms.at(i));

			// move player on y-axis
			//buffer.Update_PositionY_On_Quad(transforms.at(i).bufferIndex, transforms.at(i));

			buffer.Update_Position_On_Quad(Transform.at(i).bufferIndex, Transform.at(i));
		}
	}
}

void TransformSystem::Update(VertexBuffer& buffer, std::vector<int>& entities_to_be_updated)
{
	for (int i = 0; i < entities_to_be_updated.size(); i++) {
		buffer.Update_Position_On_Quad(Transform.at(entities_to_be_updated.at(i)).bufferIndex, Transform.at(entities_to_be_updated.at(i)));
	}
	entities_to_be_updated.clear();
}

void TransformSystem::Clear()
{
}
