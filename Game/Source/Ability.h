#ifndef __ABILITY_H__
#define __ABILITY_H__

class Character;

class Ability {
protected:
	Character* p_Character;
private:

public:
	Ability(Character* character);
	~Ability();

	virtual void Execute() = 0;
};

#endif  // __ABILITY_H__