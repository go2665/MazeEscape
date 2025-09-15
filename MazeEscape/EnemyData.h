#pragma once
#include <stdlib.h>

struct EnemyData
{
	float Health = 50.0f;
	float AttackPower = 5.0f;
	int DropGold = 20;

	EnemyData(float Modifier = 1.0f)
	{
		// RAND_MAX : rand() 함수로 얻을 수 있는 최대값
		// rand() / RAND_MAX
		// (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) = 0.0f ~ 1.0f
		// (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f = 0.0f ~ 0.2f
		// 0.9f + (static_cast<float>(rand()) / (static_cast<float>(RAND_MAX)) * 0.1f) = 0.9f ~ 1.1f

		float randomFactor = 0.9f + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.2f);
		Health = Health * Modifier * randomFactor;
		AttackPower = AttackPower * Modifier * randomFactor;
		DropGold = static_cast<int>(DropGold * Modifier * randomFactor);
	}
};