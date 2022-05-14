#ifndef __PMQUEST1_H__
#define __PMQUEST1_H__

#include "Quest.h"

class PMQuest1 : public Quest {
private:
	size_t m_ItemCount;
public:
	PMQuest1();
	~PMQuest1();

	virtual void UpdateCheck() override;

	virtual bool HasRequirements() override;
	virtual void Finish() override;

	void OnItemAdd(Item::EItemType item, size_t count) override;
	void OnItemRemove(Item::EItemType item, size_t count) override;
};

#endif  // __ABILITY_H__