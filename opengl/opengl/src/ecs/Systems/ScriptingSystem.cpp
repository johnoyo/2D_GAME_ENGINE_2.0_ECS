#include "ScriptingSystem.h"

void ScriptingSystem::Start(int current_level)
{
	for (unsigned int i = 0; i < scripts.size(); i++) {
		//scripts.at(i).init(1.0f);
		if (attributes.at(i).Enabled) {
			if (current_level == 0) {
				scripts.at(i).init[0](1.0f);
				continue;
			}

			int size = scripts.at(i).init.size();
			if (current_level < size)
				scripts.at(i).init[current_level - 1](1.0f);
			else
				scripts.at(i).init[size - 1](1.0f);
		}
	}
}

void ScriptingSystem::Run(int current_level)
{
	for (unsigned int i = 0; i < scripts.size(); i++) {
		//scripts.at(i).update(1.0f);
		if (attributes.at(i).Enabled) {
			int size = scripts.at(i).update.size();
			if (current_level < size)
				scripts.at(i).update[current_level - 1](1.0f);
			else
				scripts.at(i).update[size - 1](1.0f);
		}
	}
}

void ScriptingSystem::Clear()
{
}
