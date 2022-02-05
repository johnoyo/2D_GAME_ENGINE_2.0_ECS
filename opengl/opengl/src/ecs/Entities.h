#pragma once
#include "Components.h"

namespace Entity {

	struct BaseEntity
	{
		int ID = -1;
		int transform = -1;
		int collisionBox = -1;
		int material = -1;
		int animation = -1;
		int gravity = -1;
		int script = -1;
		int health = -1;
	};

}

