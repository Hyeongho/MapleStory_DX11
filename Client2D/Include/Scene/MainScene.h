#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/PlayerStatus.h"
#include "../Widget/Fade.h"
#include "../Widget/DamageWidget.h"
#include "../Widget/DeathNotice.h"

class CMainScene :
    public CSceneMode
{
public: 
    CMainScene();
    ~CMainScene();

private:
    CSharedPtr<CPlayerStatus> m_PlayerStatus;
    CSharedPtr<CFade> m_Fade;
    CSharedPtr<CDamageWidget> m_DamageWidget;
    CSharedPtr<CDeathNotice> m_DeathNotice;
    std::function<void(bool, float)> m_LoadingFunction;

public:
    virtual void Start();
    virtual bool Init();
    virtual void PostUpdate(float DeltaTime);

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateMap();
    void LoadSound();

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

