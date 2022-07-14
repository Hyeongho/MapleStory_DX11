#pragma once

#include "Thread.h"
#include "ThreadQueue.h"
#include "../ClientInfo.h"

class CEToTempleThread :
    public CThread
{
public:
	CEToTempleThread();
	virtual ~CEToTempleThread();

private:
	CThreadQueue<LoadingMessage> m_Queue;

public:
	CThreadQueue<LoadingMessage>* GetLoadingQueue()
	{
		return &m_Queue;
	}

	void AddMessage(bool Complete, float Percent)
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

