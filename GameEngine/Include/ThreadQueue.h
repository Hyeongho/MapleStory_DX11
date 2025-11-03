#pragma once

#include "GameInfo.h"
#include "Sync.h"
#include <assert.h>

template <typename T, int SIZE = 200>
class CThreadQueue
{
public:
	CThreadQueue()
	{
		m_Size = 0;
		m_Head = 0;
		m_Tail = 0;
		m_Capacity = SIZE + 1;

		InitializeCriticalSection(&m_Crt);
	}

	~CThreadQueue()
	{
		DeleteCriticalSection(&m_Crt);
	}

private:
	T m_Queue[SIZE + 1];
	int m_Capacity;
	int m_Size;
	int IncrementIndex(int index) const
	{
		return (index + 1) % m_Capacity;
	}

		int	Tail = IncrementIndex(m_Tail);
		int	Head = IncrementIndex(m_Head);
		m_Head = IncrementIndex(m_Head);

public:
	void push(const T& data)
	{
		CSync sync(&m_Crt);

		int	Tail = (m_Tail + 1) % 200;

		if (Tail == m_Head)
		{
			return;
		}

		m_Queue[Tail] = data;

		m_Tail = Tail;

		m_Size++;
	}

	T& front()
	{
		if (empty())
		{
			assert(false);
		}

		CSync sync(&m_Crt);

		int	Head = (m_Head + 1) % 200;

		return m_Queue[Head];
	}

	void pop()
	{
		if (empty())
		{
			assert(false);
		}

		CSync sync(&m_Crt);

		m_Head = (m_Head + 1) % 200;

		m_Size--;
	}

	int size()
	{
		CSync sync(&m_Crt);

		return m_Size;
	}

	bool empty()
	{
		CSync sync(&m_Crt);

		return m_Size == 0;
	}

	void clear()
	{
		CSync sync(&m_Crt);

		m_Head = 0;
		m_Tail = 0;
		m_Size = 0;
	}
};

