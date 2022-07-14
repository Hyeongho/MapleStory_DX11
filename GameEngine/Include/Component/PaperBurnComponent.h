#pragma once

#include "ObjectComponent.h"
#include "../Resource/Shader/PaperBurnConstantBuffer.h"
#include "../Resource/Texture/Texture.h"

class CPaperBurnComponent :
    public CObjectComponent
{
	friend class CGameObject;

protected:
	CPaperBurnComponent();
	CPaperBurnComponent(const CPaperBurnComponent& com);
	virtual ~CPaperBurnComponent();

private:
	CPaperBurnConstantBuffer* m_CBuffer;
	std::function<void()> m_FinishCallback;
	float m_FinishTime;
	CSharedPtr<class CMaterial> m_Material;
	CSharedPtr<CTexture> m_BurnTexture;
	bool m_StartPaperBurn;
	float m_Filter;

public:
	void StartPaperBurn();
	void SetMaterial(class CMaterial* Material);
	void SetInverse(bool Enable);
	void SetFinishTime(float Time)
	{
		m_FinishTime = Time;
	}

	void SetBurnTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);

	void SetOutLineColor(const Vector4& Color);
	void SetOutLineColor(float r, float g, float b, float a);
	void SetInLineColor(const Vector4& Color);
	void SetInLineColor(float r, float g, float b, float a);
	void SetCenterLineColor(const Vector4& Color);
	void SetCenterLineColor(float r, float g, float b, float a);
	void SetInFilter(float Filter);
	void SetOutFilter(float Filter);
	void SetCenterFilter(float Filter);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CPaperBurnComponent* Clone();

public:
	void SetShader();

public:
	template <typename T>
	void SetFinishCallback(T* Obj, void(T::* Func)())
	{
		m_FinishCallback = std::bind(Func, Obj);
	}
};

