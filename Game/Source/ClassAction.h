#pragma once

template<class T, class... TArgs>
class ClassAction {
private:
	void (T::* action)(TArgs...);
	T* obj;
public:
	ClassAction(void (T::* _action)(TArgs...), T* _obj);

	void operator=(void (T::* _action)(TArgs...));
	bool operator==(const ClassAction<T, TArgs...>& other);

	void operator()(TArgs... args);

	void execute(TArgs... args);
};

template<class T, class ...TArgs>
inline ClassAction<T, TArgs...>::ClassAction(void(T::* _action)(TArgs...), T* _obj)
{
	action = _action;
	obj = _obj;
}

template<class T, class ...TArgs>
inline void ClassAction<T, TArgs...>::operator=(void(T::* _action)(TArgs...))
{
	action = _action;
}

template<class T, class ...TArgs>
inline bool ClassAction<T, TArgs...>::operator==(const ClassAction<T, TArgs...>& other)
{
	return obj == other.obj;
}

template<class T, class ...TArgs>
inline void ClassAction<T, TArgs...>::operator()(TArgs ...args)
{
	execute(args...);
}

template<class T, class ...TArgs>
inline void ClassAction<T, TArgs...>::execute(TArgs ...args)
{
	(obj->*action)(args...);
}