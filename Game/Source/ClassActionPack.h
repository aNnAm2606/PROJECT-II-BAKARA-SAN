#pragma once
#include "ClassAction.h"
#include <vector>


template<class T, class... TArgs>
class ClassActionPack {
private:
	std::vector<ClassAction<T, TArgs...>> m_Actions;
public:
	void operator+=(const ClassAction<T, TArgs...>& action);
	void operator-=(const ClassAction<T, TArgs...>& action);

	void operator()(TArgs... args);
};

template<class T, class ...TArgs>
inline void ClassActionPack<T, TArgs...>::operator+=(const ClassAction<T, TArgs...>& action)
{
	m_Actions.push_back(action);
}

template<class T, class ...TArgs>
inline void ClassActionPack<T, TArgs...>::operator-=(const ClassAction<T, TArgs...>& action)
{
	size_t size = m_Actions.size();

	for (size_t i = 0; i < size; i++) {
		if (m_Actions[i] == action) {
			m_Actions.erase(m_Actions.begin() + i);
			break;
		}
	}
}

template<class T, class ...TArgs>
inline void ClassActionPack<T, TArgs...>::operator()(TArgs ...args)
{
	size_t size = m_Actions.size();

	for (size_t i = 0; i < size; i++) {
		m_Actions[i](args...);
	}
}
