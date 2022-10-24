#pragma once

#include "Thread.h"
#include "ThreadQueue.h"
#include "../ClientInfo.h"

class CSeolhuiuiThread :
    public CThread
{
public:
	CSeolhuiuiThread();
	virtual ~CSeolhuiuiThread();

private:
	CThreadQueue<LoadingMessage> m_Queue;

public:
	CThreadQueue<LoadingMessage>* GetLoadingQueue()
	{
		return &m_Queue;
	}

	void AddMessage(bool Complete = 0.f, float Percent = 0.f)
	{
		LoadingMessage Msg;

		Msg.Complete = Complete;
		Msg.Percent = Percent;

		m_Queue.push(Msg);
	}

public:
	bool Init();
	virtual void Run();
};

