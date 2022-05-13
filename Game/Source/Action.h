#pragma once

class Action
{
private:
	void* action;
public:
	Action();
	Action(void* ptr);

	void* getActionPtr() { return action; }

	void operator=(void* ptr);
	bool operator==(const Action& other);

	template<class ...TArgs> void operator()(TArgs... args);
	template<class ...TArgs> void execute(TArgs... args);
};

template<class ...TArgs>
inline void Action::operator()(TArgs... args)
{
	execute<TArgs...>(args...);
}

template<class ...TArgs>
inline void Action::execute(TArgs ...args)
{
	void (*func) (TArgs...) = (void (*)(TArgs...))action;

	func(args...);
}