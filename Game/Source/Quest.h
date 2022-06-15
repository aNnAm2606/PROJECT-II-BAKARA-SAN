#ifndef __QUEST_H__
#define __QUEST_H__

#include <string>
#include "Item.h"
#include "Character.h"
#include "ClassActionPack.h"
#include "QuestModule.h"

#include "PugiXml/src/pugixml.hpp"

class Quest {
public:
	
protected:
	QuestModule::EQuest p_QuestId;

	std::string p_Title;
	std::string p_Description;
	std::string m_ProgressText;

	Item::EItemType p_Rewards[4];
public:
	Quest();
	virtual ~Quest();

	// Getters
	const char* getTitle() { return p_Title.c_str(); }
	const char* getDesc() { return p_Description.c_str(); }

	// Quest functions
	virtual void UpdateProgressText(){}

	virtual void UpdateCheck() {};

	virtual bool HasRequirements() { return true; };

	virtual void OnFinish(){}
	void Finish();

	virtual void OnGameSave(pugi::xml_node& quest){}
	virtual void OnGameLoad(pugi::xml_node& quest) {}

	const char* GetProgress() { return m_ProgressText.c_str(); }
	Item::EItemType* GetRewards() { return p_Rewards; }

	// Callbacks
	virtual void OnItemAdd(Item::EItemType item, size_t count){}
	virtual void OnItemRemove(Item::EItemType item, size_t count){}

	virtual void OnCharacterKilled(Character::ECharacterType character){}
};

typedef ClassActionPack<Quest, Item::EItemType, size_t> QuestItemCallbacks;
typedef ClassAction<Quest, Item::EItemType, size_t> QuestItemAction;

typedef ClassActionPack<Quest, Character::ECharacterType> QuestCharacterCallbacks;
typedef ClassAction<Quest, Character::ECharacterType> QuestCharacterAction;

typedef ClassActionPack<Quest> QuestCallbacks;
typedef ClassAction<Quest> QuestAction;

#endif  // __ABILITY_H__