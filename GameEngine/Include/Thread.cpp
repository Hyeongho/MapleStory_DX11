#include "Thread.h"

CThread::CThread() : m_Thread(0), m_StartEvent(0), m_Loop(false)
{
}

CThread::~CThread()
{
	if (m_StartEvent)
	{
		CloseHandle(m_StartEvent);
		m_StartEvent = 0;
	}
}

bool CThread::Init()
{
	m_StartEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	m_Thread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunction, this, 0, nullptr);

	return true;
}

void CThread::Start()
{
	SetEvent(m_StartEvent);
}

void CThread::Pause()
{
	DWORD Count = 0;

	do
	{
		Count = SuspendThread(m_Thread);
	} while (Count <= 0);
}

void CThread::Resume()
{
	DWORD Count = 0;

	do
	{
		Count = ResumeThread(m_Thread);
	} while (Count >= 0);
}

void CThread::Stop()
{
	if (m_Thread)
	{
		m_Loop = false;
		Start();

		// 스레드가 종료될때까지 기다린다.
		WaitForSingleObject(m_Thread, INFINITE);
		CloseHandle(m_Thread);
		m_Thread = 0;
	}
}

void CThread::WaitStartEvent()
{
	WaitForSingleObject(m_StartEvent, INFINITE);
}

unsigned int __stdcall CThread::ThreadFunction(void* Arg)
{
	CThread* Thread = (CThread*)Arg;

	WaitForSingleObject(Thread->m_StartEvent, INFINITE);

	//Sleep(1000);

	do
	{
		Thread->Run();
	} while (Thread->m_Loop);

	return 0;
}
