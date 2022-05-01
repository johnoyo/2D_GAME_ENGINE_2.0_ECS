#include "ShadowCastSystem.h"

void ShadowCastSystem::Start(glm::vec4 shadow_color)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities.at(i).Transform != -1 && entities.at(i).Shadow != -1) {
			if (Shadow.at(entities.at(i).Shadow).Enabled) {
				Shadow.at(entities.at(i).Shadow).position = Transform.at(entities.at(i).Transform).position;
				Shadow.at(entities.at(i).Shadow).bufferIndex = Transform.at(entities.at(i).Transform).bufferIndex;
				Shadow.at(entities.at(i).Shadow).color = shadow_color;
			}
		}
	}
}

void ShadowCastSystem::Run(glm::vec3 player_position, VertexBuffer& buffer, RenderingSystem& rend)
{
	shadows_list.clear();

	glm::vec3 O = player_position;
	for (int i = 0; i < Shadow.size(); i++) {
		if (Shadow.at(i).Enabled) {
			std::vector<glm::vec2> shadow_points;
			std::vector<glm::vec2> edge_points;

			std::vector<glm::vec2> vertices;
			vertices.push_back(buffer.Get_Buffer()[Shadow.at(i).bufferIndex + 0].position);
			vertices.push_back(buffer.Get_Buffer()[Shadow.at(i).bufferIndex + 1].position);
			vertices.push_back(buffer.Get_Buffer()[Shadow.at(i).bufferIndex + 2].position);
			vertices.push_back(buffer.Get_Buffer()[Shadow.at(i).bufferIndex + 3].position);

			// Find all shadow points
			for (int j = 0; j < 4; j++) {

				glm::vec2 E = vertices[i];

				float rdx, rdy;
				rdx = E.x - O.x;
				rdy = E.y - O.y;

				float base_ang = atan2f(rdy, rdx);

				rdx = Shadow.at(i).shadow_distance * cosf(base_ang);
				rdy = Shadow.at(i).shadow_distance * sinf(base_ang);

				shadow_points.push_back({ rdx, rdy });

				// Find Intersection points between shadow line and all edges, store closer one for each edge 
			}

			shadows_list.push_back(vertices[3]);
			shadows_list.push_back(shadow_points[3]);
			shadows_list.push_back(shadow_points[0]);
			shadows_list.push_back(vertices[0]);

			shadows_list.push_back(vertices[0]);
			shadows_list.push_back(shadow_points[0]);
			shadows_list.push_back(shadow_points[1]);
			shadows_list.push_back(vertices[1]);

			shadows_list.push_back(vertices[1]);
			shadows_list.push_back(shadow_points[1]);
			shadows_list.push_back(shadow_points[2]);
			shadows_list.push_back(vertices[2]);
		}
	}
}
