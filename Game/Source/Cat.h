#ifndef __CAT_H__
#define __CAT_H__

#include "NPC.h"

class Cat : public NPC {
private:
	
public:
	Cat();
	~Cat();

	void Init();
	void OnUpdate() override;

	void OnInteract();

};

#endif  // __LOG_H__