#pragma once

#include "ClientFlag.h"
#include "GameInfo.h"

struct CharacterInfo
{
	int HP;
	int MaxHP;

	int MP;
	int MaxMP;

	int Exp;
	int MaxExp;

	int Attack;
	int Armor;

	int Level;
};

struct LoadingMessage
{
	bool Complete;
	float Percent;
};

struct TileResultData 
{
	std::function<void(const std::list<Vector3>&)> Callback;
	std::list<Vector3> vecPath;
};
