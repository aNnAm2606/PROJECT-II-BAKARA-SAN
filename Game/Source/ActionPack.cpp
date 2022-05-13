#include "ActionPack.h"

void ActionPack::operator+=(const Action& action)
{
	size_t size = actions.size();
	size_t i;

	for (i = 0; i < size; i++) {
		if (actions[i] == action) {
			break;
		}
	}

	if (i == size) {
		actions.emplace_back(action);
	}
}

void ActionPack::operator-=(const Action& action)
{
	size_t size = actions.size();

	for (size_t i = 0; i < size; i++) {
		if (actions[i] == action) {
			actions.erase(actions.begin() + i);
			break;
		}
	}
}