#pragma once

#include "Action.h"
#include <vector>

class ActionPack
{
private:
	std::vector<Action> actions;
public:
	void operator+=(const Action& action);
	void operator-=(const Action& action);

	template<class ...TArgs> void operator()(TArgs... args);
};

template<class ...TArgs>
inline void ActionPack::operator()(TArgs ...args)
{
	size_t size = actions.size();

	for (size_t i = 0; i < size; i++) {
		actions[i](args...);
	}
}