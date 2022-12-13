#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/PlayerStatus.h"
#include "../Widget/TalkWidget.h"
#include "../Widget/Fade.h"

class CClearScene :
    public CSceneMode
{
public:
    CClearScene();
    ~CClearScene();

private:
    CSharedPtr<CPlayerStatus> m_PlayerStatus;
    CSharedPtr<CTalkWidget> m_TalkWidget;
    CSharedPtr<CFade> m_Fade;
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

