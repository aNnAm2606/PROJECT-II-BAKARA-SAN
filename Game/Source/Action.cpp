#include "Action.h"

Action::Action() : action(nullptr)
{
}

Action::Action(void* ptr)
{
	action = ptr;
}

void Action::operator=(void* ptr)
{
	action = ptr;
}

bool Action::operator==(const Action& other)
{
	return action == other.action;
}
