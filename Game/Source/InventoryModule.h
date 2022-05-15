#ifndef __INVENTORY_MODULE_H__
#define __INVENTORY_MODULE_H__

#include "Module.h"
#include <vector>

#include "Item.h"
#include "Quest.h"

#define MAX_ITEMS 24

class InventoryModule : public Module
{
public:

	InventoryModule(bool startEnabled);

	// Destructor
	virtual ~InventoryModule();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node& save) override;
	bool SaveState(pugi::xml_node& save) override;

	// Inventory management
	bool AddItem(Item::EItemType item, size_t count=1);

	bool HasItem(Item::EItemType item, size_t* outindex=NULL);

	bool RemoveItem(Item::EItemType item, size_t count=1);
	bool RemoveItem(size_t index, size_t count=1);

	std::vector<Item::EItemType>* GetInventory() { return &m_Inventory; }
	size_t GetItemCount(Item::EItemType item);

	// Variables
	QuestItemCallbacks questOnAddCallbacks;
	QuestItemCallbacks questOnRemoveCallbacks;
private:
	std::vector<Item::EItemType> m_Inventory;
	std::vector<size_t> m_ItemCount;
};

#endif // __LOGOSCREEN_H__