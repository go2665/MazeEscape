#include "Actor.h"

void Actor::Attack(Actor* InTarget)
{
	// AttackPower * 속성 * 버프효과 .....
	InTarget->TakeDamage(AttackPower); // AttackPower만큼 데미지 주기
}

void Actor::TakeDamage(float InDamage)
{
	SetHealth(Health - InDamage);

	printf("%s가 %.0f의 피해를 입었습니다.\n", Name.c_str(), InDamage);
	printf("(%.0f/%.0f)\n", Health, MaxHealth);

	if (!IsAlive())
	{
		// 사망 처리
		printf("%s가 죽었습니다.\n", Name.c_str());
	}
}
