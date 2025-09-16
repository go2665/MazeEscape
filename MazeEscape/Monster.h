#pragma once
#include "Actor.h"
class Monster : public Actor
{
public:
	Monster() :Actor("∏ÛΩ∫≈Õ", 30.0f, 5.0f) 	{ }
	Monster(const char* InName) :Actor(InName, 30.0f, 5.0f)	{ }
	Monster(const char* InName, float InHealth, float InAttackPower) : Actor(InName, InHealth, InAttackPower) {}

	inline int GetDropGold() const { return DropGold; }

protected:
	int DropGold = 10;
};
