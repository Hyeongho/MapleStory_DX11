#include "TalkManager.h"

DEFINITION_SINGLE(CTalkManager)

CTalkManager::CTalkManager()
{
}

CTalkManager::~CTalkManager()
{
	m_mapTalk.clear();
}

bool CTalkManager::Init()
{
	CreateTalk();

	return true;
}

void CTalkManager::SetTalk(int ID, std::vector<const TCHAR*> Talk)
{
	m_mapTalk.insert(std::make_pair(ID, Talk));
}

std::vector<const TCHAR*> CTalkManager::FindTalk(int ID)
{
	auto iter = m_mapTalk.find(ID);

	if (iter == m_mapTalk.end())
	{
		//iter->second.clear();

		return {L""};
	}

	return iter->second;
}

void CTalkManager::CreateTalk()
{
	SetTalk(1000, { L"설희 대화 1", L"설희 대화 2" });

	SetTalk(2000, { L"보스 몬스터 입장" });

	SetTalk(1001, { L"홍아 대화 1", L"홍아 대화 2", L"보스 입장"});
}
