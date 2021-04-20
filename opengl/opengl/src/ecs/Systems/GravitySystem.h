#pragma once
#include "../Header.h"
#include "InputSystem.h"

class GravitySystem {
public:
	void Start(float gravityForce);
	void Run();
private:
	float force;
};