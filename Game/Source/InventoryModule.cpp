#include "InventoryModule.h"
#include "Dialog.h"

#include "Log.h"

#include "App.h"
#include "PlayerModule.h"

InventoryModule::InventoryModule(bool startEnabled) : Module(startEnabled)
{
	name.Create("inventory");
}

// Destructor
InventoryModule::~InventoryModule()
{}

// Called before render is available
bool InventoryModule::Awake(pugi::xml_node& config)
{
	LOG("Loading InventoryModule");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool InventoryModule::Start()
{

	return true;
}

// Called each loop iteration
bool InventoryModule::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool InventoryModule::Update(float dt)
{
	

	return true;
}

// Called each loop iteration
bool InventoryModule::PostUpdate()
{
	bool ret = true;

	

	return ret;
}

// Called before quitting
bool InventoryModule::CleanUp()
{
	LOG("Freeing InventoryModule");

	return true;
}

bool InventoryModule::LoadState(pugi::xml_node& save)
{
	m_Inventory.clear();
	m_ItemCount.clear();

	pugi::xml_node item = save.first_child();

	for (item = save.first_child(); item; item = item.next_sibling()) {
		Item::EItemType item_t = (Item::EItemType)item.attribute("id").as_int();
		int item_c = item.attribute("count").as_int();

		AddItem(item_t, item_c);
	}

	return true;
}

bool InventoryModule::SaveState(pugi::xml_node& save)
{
	size_t size = m_Inventory.size();

	for (size_t i = 0; i < size; i++) {
		pugi::xml_node item = save.append_child("item");
		
		item.append_attribute("id") = m_Inventory[i];
		item.append_attribute("count") = m_ItemCount[i];
	}

	return true;
}

bool InventoryModule::AddItem(Item::EItemType item, size_t count)
{
	size_t index;

	if (!HasItem(item, &index)) {
		if (m_Inventory.size() == MAX_ITEMS) {
			return false;
		}

		m_Inventory.push_back(item);
		m_ItemCount.push_back(count);
	}
	else {
		m_ItemCount[index] += count;
	}

	questOnAddCallbacks(item, count);

	std::cout << "[Inventory] Item added - type(" << item << ") count(" << count << ")" << std::endl;

	return true;
}

bool InventoryModule::HasItem(Item::EItemType item, size_t* outindex)
{
	size_t size = m_Inventory.size();

	bool hasItem = false;

	for (size_t i = 0; i < size; i++) {
		if (m_Inventory[i] == item) {
			if (outindex) *outindex = i;

			hasItem = true;
			break;
		}
	}

	return hasItem;
}

bool InventoryModule::RemoveItem(Item::EItemType item, size_t count)
{
	size_t size = m_Inventory.size();

	size_t index;

	if (HasItem(item, &index)) {
		return RemoveItem(index, count);
	}

	return false;
}

bool InventoryModule::RemoveItem(size_t index, size_t count)
{
	if (index >= m_Inventory.size()) return false;

	Item::EItemType item = m_Inventory[index];

	if (m_ItemCount[index] < count) {
		count = m_ItemCount[index];
	}

	m_ItemCount[index] -= count;

	if (m_ItemCount[index] == 0) {
		m_Inventory.erase(m_Inventory.begin() + index);
		m_ItemCount.erase(m_ItemCount.begin() + index);
	}

	questOnRemoveCallbacks(item, count);
	
	std::cout << "[Inventory] Item removed - type(" << item << ") count(" << count << ")" << std::endl;

	return true;
}

size_t InventoryModule::GetItemCount(Item::EItemType item)
{
	size_t count = 0;

	size_t index;
	if (HasItem(item, &index)) {
		count = m_ItemCount[index];
	}

	return count;
}

void InventoryModule::UseItem(size_t index)
{
	Item::EItemType type = m_Inventory[index];

	switch (type) {
	case Item::EItemType::EITEMTYPE_CYAN_POTION_SMALL:
		app->playerModule->HealTeam(5);
		break;
	}

	RemoveItem(index);
}