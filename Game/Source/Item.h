#ifndef __ITEM_H__
#define __ITEM_H__

class Item {
public:
	enum EItemType {
		EITEMTYPE_CAT,
		EITEMTYPE_HEALPOTION,
		EITEMTYPE_NONE
	};
private:

public:
	Item();
	~Item();
};

#endif  // __ABILITY_H__