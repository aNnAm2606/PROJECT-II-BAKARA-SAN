#ifndef __QUEST_H__
#define __QUEST_H__

#include <string>
#include "Item.h"
#include "ClassActionPack.h"
#include "QuestModule.h"

class Quest {
public:
	
protected:
	QuestModule::EQuest p_QuestId;

	std::string p_Title;
	std::string p_Description;
public:
	Quest();
	virtual ~Quest();

	virtual void OnItemAdd(Item::EItemType item, size_t count){}
	virtual void OnItemRemove(Item::EItemType item, size_t count){}

	virtual void UpdateCheck(){};

	virtual bool HasRequirements() = 0;
	virtual void Finish() = 0;
};

typedef ClassActionPack<Quest, Item::EItemType, size_t> QuestItemCallbacks;
typedef ClassAction<Quest, Item::EItemType, size_t> QuestItemAction;

typedef ClassActionPack<Quest> QuestCallbacks;
typedef ClassAction<Quest> QuestAction;

#endif  // __ABILITY_H__