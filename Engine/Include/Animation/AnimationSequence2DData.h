#pragma once

#include "../GameInfo.h"

struct Animation2DNotify
{
	std::string	Name;
	int	Frame;
	bool Call;
	std::function<void()>	Function;

	Animation2DNotify() : Frame(0), Call(false)
	{
	}
};

class CAnimationSequence2DData
{
	friend class CAnimationSequence2DInstance;

private:
	CAnimationSequence2DData();
	~CAnimationSequence2DData();

private:
	std::string	m_Name;
	std::string	m_SequenceName;
	CSharedPtr<class CAnimationSequence2D>	m_Sequence;
	int m_Frame;		// 현재 애니메이션 프레임
	float m_Time;			// 애니메이션 동작 시간
	float m_FrameTime;	// 1프레임당 시간
	float m_PlayTime;
	float m_PlayScale;		// 재생 비율
	bool m_Loop;
	bool m_Reverse;
	std::function<void()> m_EndFunction;
	std::vector<Animation2DNotify*>	m_vecNotify;

public:
	void Save(FILE* File);
	void Load(FILE* File);

public:
	const std::string& GetName()	const
	{
		return m_Name;
	}

	int GetCurrentFrame()	const
	{
		return m_Frame;
	}

	float GetAnimationTime()	const
	{
		return m_Time;
	}

	class CAnimationSequence2D* GetAnimationSequence()	const
	{
		return m_Sequence;
	}

public:
	template <typename T>
	void SetEndFunction(T* Obj, void (T::* Func)())
	{
		m_EndFunction = std::bind(Func, Obj);
	}

	template <typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void (T::* Func)())
	{
		Animation2DNotify* Notify = new Animation2DNotify;

		Notify->Name = Name;
		Notify->Frame = Frame;
		Notify->Function = std::bind(Func, Obj);

		m_vecNotify.push_back(Notify);
	}
};


