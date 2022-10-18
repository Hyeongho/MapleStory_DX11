#pragma once

#include "ClientInfo.h"
#include "Data/Data.h"


class CClientSceneManager
{
public:
	bool Init();

public:
	void ChangeScene();

private:

	DECLARE_SINGLE(CClientSceneManager)
};

