#include "Sequence.h"

bool CSequence::Run()
{
	std::vector<CNode*> Children = GetChildren();

	if (Children.empty())
	{
		return false;
	}

	auto iter = Children.begin();
	auto iterEnd = Children.end();

	for (; iter != iterEnd; iter++)
	{
		if (!(*iter)->Run())
		{
			return false;
		}
	}

	return true;
}
