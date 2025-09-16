#pragma once
#include "Actor.h"
#include "Position.h"

class APlayer : public Actor
{
public:
	APlayer() = default;
	APlayer(const char* InName, float InHealth, float InAttackPower)
		: Actor(InName, InHealth, InAttackPower)
	{
	}

	inline void AddGold(int InGold) { Gold += InGold; }

protected:
	Position CurrentPosition = Position(0,0);
	int Gold = 0;
};


