#pragma once

#include "../../Ref.h"

class CAnimationSequence2D :
    public CRef
{
    friend class CAnimationManager;

protected:
    CAnimationSequence2D();
    ~CAnimationSequence2D();

private:
    class CScene* m_Scene;
    CSharedPtr<class CTexture> m_Texture;
    std::vector<AnimationFrameData> m_vecFrameData;

public:
    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

public:
    class CTexture* GetTexture()    const
    {
        return m_Texture;
    }

    const AnimationFrameData& GetFrameData(int Index)   const
    {
        return m_vecFrameData[Index];
    }

    int GetFrameCount() const
    {
        return (int)m_vecFrameData.size();
    }

public:
    bool Init(class CTexture* Texture);
    bool Init(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
    void AddFrame(const Vector2& StartPos, const Vector2& Size);
    void AddFrame(float StartX, float StartY, float Width, float Height);
    void DeleteFrame(int Index);
    void ClearFrame();
    bool SaveFullPath(const char* FullPath);
    bool LoadFullPath(const char* FullPath);
    bool Save(const char* FileName, const std::string& PathName);
    bool Load(const char* FileName, const std::string& PathName);
};
