#pragma once

#include "GameInfo.h"

class CThread
{
protected:
	CThread();
	virtual ~CThread() = 0;

private:
	std::string	m_Name;
	HANDLE m_Thread;
	HANDLE m_StartEvent;

protected:
	bool m_Loop;

public:
	void SetLoop(bool Loop)
	{
		m_Loop = Loop;
	}

public:
	bool Init();

public:
	virtual void Run() = 0;

public:
	void Start();
	void Pause();
	void Resume();

private:
	void WaitStartEvent();
	// 멀티스레드 함수 형태
	static unsigned int __stdcall ThreadFunction(void* Arg);

public:
	template <typename T>
	static T* CreateThread(const std::string& Name)
	{
		T* Thread = new T;

		Thread->m_Name = Name;

		if (!Thread->Init())
		{
			SAFE_DELETE(Thread);
			return nullptr;
		}

		return Thread;
	}
};

