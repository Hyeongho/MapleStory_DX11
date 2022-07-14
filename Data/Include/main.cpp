#include "DataManager.h"

#ifdef _DEBUG

#pragma comment(lib, "GameEngine_Debug.lib")

#else

#pragma comment(lib, "GameEngine.lib")

#endif // _DEBUG


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	if (!CDataManager::GetInst()->Init(hInstance))
	{
		CDataManager::DestroyInst();
		return 0;
	}

	CDataManager::GetInst()->CreateDefaultSceneMode();

	int Ret = CDataManager::GetInst()->Run();

	CDataManager::DestroyInst();

	return Ret;
}
