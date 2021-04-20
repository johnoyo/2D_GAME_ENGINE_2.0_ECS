#include "ScriptingSystem.h"

void ScriptingSystem::Start()
{
	for (unsigned int i = 0; i < scripts.size(); i++) {
		scripts.at(i).init(1.0f);
	}
}

void ScriptingSystem::Run()
{
	for (unsigned int i = 0; i < scripts.size(); i++) {
		scripts.at(i).update(1.0f);
	}
}

void ScriptingSystem::Clear()
{
}
