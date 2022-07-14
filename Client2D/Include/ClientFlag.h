#pragma once

enum class Gender
{
	None, 
	Male, 
	Female
};

enum class Player_Attack
{
	Normal, 
	Attack_Start, 
	Attack_End
};

enum class EPlayer_State
{
	Idle,
	Walk,
	Jump, 
	Rope, 
	Ladder, 
	Attack,
	PhantomBlow, 
	BladeFury, 
	Die
};

enum class EMonster_State
{
	Idle,
	Move,
	Trace, 
	Attack,
	Die
};

enum class EFade_State
{
	Normal, 
	FadeIn_Start, 
	FadeIn_End, 
	FadeOut_Start, 
	FadeOut_End
};
