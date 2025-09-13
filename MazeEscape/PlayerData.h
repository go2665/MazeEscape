#pragma once
#include "Position.h"

struct PlayerData
{
	const float MaxHealth = 100.0f;

	Position CurrentPosition = Position(0,0);
	float Health = MaxHealth;
	float AttackPower = 20.0f;
	int Gold = 0;


	PlayerData() : CurrentPosition(0, 0), AttackPower(20.0f), Health(100.0f), Gold(0) {}

};