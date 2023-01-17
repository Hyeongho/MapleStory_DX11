#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/PlayerStatus.h"
#include "../Widget/TalkWidget.h"
#include "../Widget/Fade.h"
#include "../Widget/QuesetWidget.h"
#include "../Widget/ClearWidget.h"
#include "../Widget/DeathNotice.h"

class CEntranceToTemple :
    public CSceneMode
{
public:
    CEntranceToTemple();
    ~CEntranceToTemple();

private:
    CSharedPtr<CPlayerStatus> m_PlayerStatus;
    CSharedPtr<CTalkWidget> m_TalkWidget;
    CSharedPtr<CFade> m_Fade;
    CSharedPtr<CQuesetWidget> m_Quset;
    CSharedPtr<CClearWidget> m_Clear;
    CSharedPtr<CDeathNotice> m_DeathNotice;
    std::function<void(bool, float)> m_LoadingFunction;

    std::list<class CMonsterManager*> m_MonsterList;

    int m_MobCount;
    int m_TotalMobCount;

    float m_SpawnTime;

public:
    virtual void Start();
    virtual bool Init();
    virtual void PostUpdate(float DeltaTime);

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateMap();
    void LoadSound();

    void CreatePotal();

    void MonsterSpawn(float DeltaTime);

    void Clear();

public:
    void CollisionBeginCallback(const CollisionResult& Result);
    void CollisionEndCallback(const CollisionResult& Result);

public:
    template <typename T>
    void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
    {
        m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }
};

