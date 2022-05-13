#pragma once

class Function
{
private:
	void* function;
public:
	Function();
	Function(void* ptr);

	void operator=(void* ptr);
	template<class T, class ...TArgs> T Invoke(TArgs... args);
};

template<class T, class ...TArgs>
inline T Function::Invoke(TArgs ...args)
{
	T (*func) (TArgs...) = (T (*)(TArgs...))function;

	return func(args...);
}