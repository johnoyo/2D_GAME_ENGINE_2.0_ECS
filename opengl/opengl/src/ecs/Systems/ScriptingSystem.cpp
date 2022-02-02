#include "ScriptingSystem.h"

void ScriptingSystem::Start()
{
	for (unsigned int i = 0; i < scripts.size(); i++) {
		scripts.at(i).init(1.0f);
	}
}

void ScriptingSystem::Run(int current_level)
{
	for (unsigned int i = 0; i < scripts.size(); i++) {
		//scripts.at(i).update(1.0f);
		if (current_level < scripts.at(i).update.size())
			scripts.at(i).update[current_level - 1](1.0f);
		else
			scripts.at(i).update[scripts.at(i).update.size() - 1](1.0f);
	}
}

void ScriptingSystem::Clear()
{
}
