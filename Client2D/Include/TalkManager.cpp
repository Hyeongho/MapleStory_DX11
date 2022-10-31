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
	SetTalk(1000, { L"���� ��ȭ 1", L"���� ��ȭ 2" });

	SetTalk(2000, { L"���� ���� ����" });

	SetTalk(1001, { L"ȫ�� ��ȭ 1", L"ȫ�� ��ȭ 2", L"���� ����"});
}
