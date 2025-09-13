#pragma once
#include "Position.h"

struct PlayerData
{
	const float MaxHealth = 100.0f;

	Position CurrentPosition = Position(0,0);
	float Health = MaxHealth;
	int Gold = 0;


	PlayerData() : CurrentPosition(0, 0), Health(100.0f), Gold(0) {}

};