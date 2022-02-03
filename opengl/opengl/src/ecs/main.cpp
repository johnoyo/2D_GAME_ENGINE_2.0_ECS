#include "Header.h"
#include<iostream>

#include "Systems\CameraSystem.h"
#include "Systems\RenderingSystem.h"
#include "Systems\WindowSystem.h"
#include "Systems\TextureSystem.h"
#include "Systems\ScriptingSystem.h"
#include "Systems\InputSystem.h"
#include "Systems\CollisionSystem.h"
#include "Systems\GravitySystem.h"
#include "Systems\LevelSystem.h"
#include "Systems\SoundSystem.h"

System ecs = System();

std::vector<Entity::BaseEntity> entities;

/* ------------------------------- Entities ---------------------------- */
Entity::BaseEntity player;
Entity::BaseEntity enemy;
Entity::BaseEntity level[90];
Entity::BaseEntity camera;
Entity::BaseEntity lvlHandler;
Entity::BaseEntity sps;
/* --------------------------------------------------------------------- */

/* ------------------------- Component Vector -------------------------- */
std::vector<Component::Transform> transforms;
std::vector<Component::CollisionBox> collisionBoxes;
std::vector<Component::Material> materials;
std::vector<Component::Health> health;
std::vector<Component::Script> scripts;
std::vector<Component::Attributes> attributes;
std::vector<Component::Gravity> gravity;
/* --------------------------------------------------------------------- */

/* ------------------------------------ Systems ------------------------------------ */
WindowSystem windowSystem = WindowSystem(600.0f, 600.0f, "test", false);
TextureSystem textureSystem;
RenderingSystem renderingSystem;
CameraSystem cameraSystem = CameraSystem(0.0f, windowSystem.Get_Width(), 0.0f, windowSystem.Get_Height());
ScriptingSystem scriptingSystem;
InputSystem inputSystem;
CollisionSystem collisionSystem;
GravitySystem gravitySystem;
LevelSystem levelSystem;
SoundSystem soundSystem;
/* --------------------------------------------------------------------------------- */

#include "EntitiesCode\Player.h"
#include "EntitiesCode\Enemy.h"
#include "EntitiesCode\LevelHandler.h"

/* Uncomment this to get rid of the console when the application is running */
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main() {
/* ------------------------------------ Enroll Entities ------------------------------------ */
	ecs.EnrollEntity(player, entities);
	ecs.EnrollEntity(enemy, entities);
	ecs.EnrollEntity(camera, entities);
	ecs.EnrollEntity(lvlHandler, entities);
	ecs.EnrollEntity(sps, entities);

	for (unsigned int i = 0; i < 90; i++)
		ecs.EnrollEntity(level[i], entities);
/* ----------------------------------------------------------------------------------------- */

/* ------------------------------------ Add Components to Entities ------------------------------------ */
	ecs.AddComponent<Component::Transform>(player.transform, entities.at(player.ID).transform, transforms);
	ecs.AddComponent<Component::Health>(player.health, entities.at(player.ID).health, health);
	ecs.AddComponent<Component::Script>(player.script, entities.at(player.ID).script, scripts);
	ecs.AddComponent<Component::Material>(player.material, entities.at(player.ID).material, materials);
	ecs.AddComponent<Component::CollisionBox>(player.collisionBox, entities.at(player.ID).collisionBox, collisionBoxes);
	ecs.AddComponent<Component::Attributes>(player.attributes, entities.at(player.ID).attributes, attributes);
	//ecs.AddComponent<Component::Gravity>(player.gravity, entities.at(player.ID).gravity, gravity);

	ecs.AddComponent<Component::Transform>(enemy.transform, entities.at(enemy.ID).transform, transforms);
	ecs.AddComponent<Component::Script>(enemy.script, entities.at(enemy.ID).script, scripts);
	ecs.AddComponent<Component::Material>(enemy.material, entities.at(enemy.ID).material, materials);
	ecs.AddComponent<Component::CollisionBox>(enemy.collisionBox, entities.at(enemy.ID).collisionBox, collisionBoxes);
	ecs.AddComponent<Component::Gravity>(enemy.gravity, entities.at(enemy.ID).gravity, gravity);
	ecs.AddComponent<Component::Attributes>(enemy.attributes, entities.at(enemy.ID).attributes, attributes);
	ecs.AddComponent<Component::Gravity>(enemy.gravity, entities.at(enemy.ID).gravity, gravity);


	for (unsigned int i = 0; i < 90; i++) {
		ecs.AddComponent<Component::Transform>(level[i].transform, entities.at(level[i].ID).transform, transforms);
		ecs.AddComponent<Component::CollisionBox>(level[i].collisionBox, entities.at(level[i].ID).collisionBox, collisionBoxes);
		ecs.AddComponent<Component::Attributes>(level[i].attributes, entities.at(level[i].ID).attributes, attributes);
		ecs.AddComponent<Component::Material>(level[i].material, entities.at(level[i].ID).material, materials);
	}

	ecs.AddComponent<Component::Transform>(camera.transform, entities.at(camera.ID).transform, transforms);

	ecs.AddComponent<Component::Script>(lvlHandler.script, entities.at(lvlHandler.ID).script, scripts);

	ecs.AddComponent<Component::Material>(sps.material, entities.at(sps.ID).material, materials);
/* ---------------------------------------------------------------------------------------------------- */

/* ------------------------------------ Attach scripts to Entities ------------------------------------ */
	ecs.GetComponent<Component::Script>(player.script, scripts).init.push_back(Player::Level_0::init);
	ecs.GetComponent<Component::Script>(player.script, scripts).update.push_back(Player::Level_0::update);

	ecs.GetComponent<Component::Script>(enemy.script, scripts).init.push_back(Enemy::Level_0::init);
	ecs.GetComponent<Component::Script>(enemy.script, scripts).update.push_back(Enemy::Level_0::update);
	ecs.GetComponent<Component::Script>(enemy.script, scripts).update.push_back(Enemy::Level_1::update);

	ecs.GetComponent<Component::Script>(lvlHandler.script, scripts).init.push_back(LevelHandler::Level_0::init);
	ecs.GetComponent<Component::Script>(lvlHandler.script, scripts).init.push_back(LevelHandler::Level_1::init);
	ecs.GetComponent<Component::Script>(lvlHandler.script, scripts).update.push_back(LevelHandler::update);
/* ---------------------------------------------------------------------------------------------------- */

/* ------------------------------------ Init components of Entities ------------------------------------ */
	ecs.GetComponent<Component::Attributes>(player.attributes, attributes).Static = false;
	ecs.GetComponent<Component::Attributes>(enemy.attributes, attributes).Static = false;

	for (unsigned int i = 0; i < 90; i++)
		ecs.GetComponent<Component::Attributes>(level[i].attributes, attributes).Static = true;
/* ----------------------------------------------------------------------------------------------------- */

/* ------------------------------------ Start Systems ------------------------------------ */
	windowSystem.Start(1);
	textureSystem.Start();
	renderingSystem.Start(cameraSystem.Get_View_Projection_Matrix());
	scriptingSystem.Start(levelSystem.GetCurrentLevel());
	collisionSystem.Start();
	gravitySystem.Start(6.0f, -6.0f);
	cameraSystem.Start();
	soundSystem.Start();
/* --------------------------------------------------------------------------------------- */

	static double limitFPS = 1.0 / 60.0;

	double lastTime = glfwGetTime();
	double timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;

	while (!windowSystem.Window_Should_Close()) {

		// - Measure time
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

		// - Only update at 60 frames / s
		while (deltaTime >= 1.0) {			
/* ------------------------------------ Run Systems ------------------------------------ */
			scriptingSystem.Run(levelSystem.GetCurrentLevel());
			gravitySystem.Run();
			textureSystem.Run(renderingSystem);
			// NOTE: if the ground on which the player lands is very thin, if he has a lot of speed he is gonna clip through
			collisionSystem.Run(renderingSystem.Get_Vertex_Buffer());
/* ------------------------------------------------------------------------------------- */
			updates++;
			deltaTime--;
		}
		// - Render at maximum possible frames
		renderingSystem.Render(cameraSystem.Get_View_Projection_Matrix());
		frames++;

		// - Reset after one second
		if (glfwGetTime() - timer > 1.0) {
			timer++;
			std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
			updates = 0, frames = 0;
		}

		windowSystem.Swap_Buffers();
		windowSystem.Poll_For_Events();
	}

/* ------------------------------------ Clear Systems ------------------------------------ */
	renderingSystem.Clear();
	textureSystem.Clear();
	windowSystem.Terminate();
/* --------------------------------------------------------------------------------------- */
	return 0;
}

/**

struct Entity_player {
int ID;
int Transform;
int Renderable;
int CollisionBox;
}

std::vector<Component::Transform> transform;
.
.
.


int main() {
Entity_player ep;
ecs.enrollEntity(ep.ID);
ecs.addComponenet<Component::Transform>(ep.Transform);


}
----------------------------------------------------------------------

int main() {
	ecs = System();

	cams = ...
	texs = ...
	rends = ...
	cols = ...
	.
	.
	.
	wins = ...

	// enroll systems
	// enroll entities

	// add components to entities

	ecs.StartSystems();

	while() {

		ecs.RunSystems();

	}
}


*/