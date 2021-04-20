#pragma once
#include <functional>
#include "glm/glm.hpp"

namespace Component {

	struct Transform {
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		// glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 10.0f, 10.0f, 10.0f };
	};

	struct CollisionBox {
		glm::vec3 bl;
		glm::vec3 br;
		glm::vec3 tl;
		glm::vec3 tr;
		bool CBEnabled = true;
	};

	struct Material {
		std::string texture = "-";
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct Animation {
		std::string film;
		float step;
	};

	struct Gravity {
		bool gravityEnabled = true;
		bool collides = true;
		bool isGrounded = false;
		float appliedForce = 0.0f;
	};

	struct AudioSource {
		std::string audio;
	};

	struct Health {
		int health = 100;
	};

	struct Script {
		std::function<void(float)> init;
		std::function<void(float)> update;
	};

	struct Attributes {
		bool Static = false;
		bool CBEnabled = true;
		bool Enabled = true;
		int bufferIndex;
	};

}
