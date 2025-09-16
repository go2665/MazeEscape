#pragma once
#include <string>
class Actor
{
public:
	Actor() = default;
	Actor(const char* InName, float InHealth, float InAttackPower)
		: Name(InName), Health(InHealth), MaxHealth(InHealth), AttackPower(InAttackPower)
	{
	}

	/// <summary>
	/// Target에게 공격하는 함수
	/// </summary>
	/// <param name="InTarget">공격 받는 대상</param>
	void Attack(Actor* InTarget);

	/// <summary>
	/// 지정된 피해량만큼 본인에게 피해를 적용
	/// </summary>
	/// <param name="InDamage">적용할 피해량</param>
	void TakeDamage(float InDamage);

	/// <summary>
	/// 이 Actor의 생존 여부를 알려주는 함수
	/// </summary>
	/// <returns>true면 살아있다. false면 죽었다.</returns>
	inline bool IsAlive() { return Health > 0; }

protected:
	inline void SetHealth(float InHealth)
	{
		if (InHealth > MaxHealth)
		{
			Health = MaxHealth;
		}
		else
		{
			Health = InHealth;
		}
	}

	std::string Name = "액터";
	float Health = 100.0f;
	float MaxHealth = 100.0f;
	float AttackPower = 10.0f;
};
