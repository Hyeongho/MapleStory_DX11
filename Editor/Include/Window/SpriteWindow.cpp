#include "SpriteWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "Engine.h"
#include "PathManager.h"
#include "../EditorManager.h"
#include "../Object/SpriteEditObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "../Object/DragObject.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"

CSpriteWindow::CSpriteWindow() : m_SpriteObject(nullptr), m_AnimInstance(nullptr)
{
}

CSpriteWindow::~CSpriteWindow()
{
	SAFE_DELETE(m_AnimInstance);
}

bool CSpriteWindow::Init()
{
	CIMGUIWindow::Init();

	CIMGUIButton* Button = AddWidget<CIMGUIButton>("LoadTexture");

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::LoadTextureButton);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("SpriteEdit");

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::SpriteEditButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("Flip");

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::FlipButton);

	m_Sprite = AddWidget<CIMGUIImage>("SpriteOrigin", 200.f, 200.f);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(300.f);

	m_SpriteFrame = AddWidget<CIMGUIImage>("SpriteFrame", 200.f, 200.f);

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("AnimationListName", 200.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimName = AddWidget<CIMGUITextInput>("AnimNameInput", 80.f, 30.f);
	m_AnimName->SetHideName(true);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(300.f);

	Label = AddWidget<CIMGUILabel>("AnimationFrameName", 200.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimFrameName = AddWidget<CIMGUITextInput>("AnimFrameNameInput", 80.f, 30.f);
	m_AnimFrameName->SetHideName(true);

	m_AnimationList = AddWidget<CIMGUIListBox>("AnimationList", 200.f, 300.f);
	m_AnimationList->SetHideName(true);
	m_AnimationList->SetPageItemCount(6);
	m_AnimationList->SetSelectCallback<CSpriteWindow>(this, &CSpriteWindow::SelectAnimation);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("AddAnim", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::AddAnimationButton);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(300.f);

	m_AnimationFrameList = AddWidget<CIMGUIListBox>("AnimationFrameList", 200.f, 300.f);
	m_AnimationFrameList->SetHideName(true);
	m_AnimationFrameList->SetPageItemCount(6);
	m_AnimationFrameList->SetSelectCallback<CSpriteWindow>(this, &CSpriteWindow::SelectAnimationFrame);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("AddFrame", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::AddAnimationFrameButton);

	Button = AddWidget<CIMGUIButton>("DeleteFrame", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::DeleteFrameButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("AnimPlay", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::PlayAnimation);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("SaveSequence", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::SaveSequence);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("LoadSequence", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::LoadSequence);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("SaveAnim", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::SaveAnimation);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("LoadAnim", 80.f, 30.f);

	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::LoadAnimation);

	//Image->SetTexture("TeemoTest", TEXT("Teemo.jpg"));
	//Image->SetImageStart(0.f, 0.f);
	//Image->SetImageEnd(1215.f, 717.f);
	//Image->SetTint(255, 0, 0);

	m_AnimInstance = new CAnimationSequence2DInstance;

	m_AnimInstance->Init();

	m_AnimInstance->Start();

	m_AnimInstance->Stop();

	return true;
}

void CSpriteWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	m_AnimInstance->Update(DeltaTime);

	if (m_AnimInstance->IsPlay())
	{
		CAnimationSequence2DData* AnimData = m_AnimInstance->GetCurrentAnimation();

		if (AnimData)
		{
			int Frame = AnimData->GetCurrentFrame();

			AnimationFrameData  FrameData = AnimData->GetAnimationSequence()->GetFrameData(Frame);

			m_SpriteFrame->SetImageStart(FrameData.Start.x, FrameData.Start.y);

			m_SpriteFrame->SetImageEnd(FrameData.Start.x + FrameData.Size.x, FrameData.Start.y + FrameData.Size.y);
		}
	}
}

void CSpriteWindow::LoadTextureButton()
{
	if (CEditorManager::GetInst()->GetEditMode() != EditMode::Sprite)
	{
		return;
	}

	TCHAR FilePath[MAX_PATH] = {};

	OPENFILENAME OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0DDSFile\0*.dds\0TGAFile\0*.tga\0PNGFile\0*.png\0JPGFile\0*.jpg\0JPEGFile\0*.jpeg\0BMPFile\0*.bmp");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		TCHAR FileName[MAX_PATH] = {};

		_wsplitpath_s(FilePath, 0, 0, 0, 0, FileName, MAX_PATH, 0, 0);

		char ConvertFileName[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FileName, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FileName, -1, ConvertFileName, Length, 0, 0);

		m_Sprite->SetTextureFullPath(ConvertFileName, FilePath);

		m_SpriteObject->GetSpriteComponent()->SetTextureFullPath(0, 0, (int)Buffer_Shader_Type::Pixel, ConvertFileName, FilePath);
		m_SpriteObject->GetSpriteComponent()->SetWorldScale((float)m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTextureWidth(),
			(float)m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTextureHeight(), 1.f);
	}
}

void CSpriteWindow::SpriteEditButton()
{
	CEditorManager::GetInst()->SetEditMode(EditMode::Sprite);

	if (!m_SpriteObject)
	{
		m_SpriteObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSpriteEditObject>("SpriteEditObject");
	}
}

void CSpriteWindow::FlipButton()
{
	if (!m_SpriteObject)
	{
		return;
	}

	if (!m_SpriteObject->GetSpriteComponent()->GetFlip())
	{
		m_SpriteObject->GetSpriteComponent()->SetFlip(true);
	}

	else
	{
		m_SpriteObject->GetSpriteComponent()->SetFlip(false);
	}
}

void CSpriteWindow::AddAnimationButton()
{
	if (m_AnimName->Empty())
	{
		return;
	}

	const char* Text = m_AnimName->GetTextMultibyte();

	if (m_AnimationList->CheckItem(Text))
	{
		return;
	}

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	if (!Resource->CreateAnimationSequence2D(Text, m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()))
	{
		return;
	}

	m_AnimationList->AddItem(Text);

	m_AnimInstance->AddAnimation(Text, Text, true, 1.f, 1.f, false);
}

void CSpriteWindow::AddAnimationFrameButton()
{
	int SelectIndex = m_AnimationList->GetSelectIndex();
	if (SelectIndex == -1)
	{
		return;
	}

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectIndex));

	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	Vector2 Size = DragObj->GetEndPos() - DragObj->GetStartPos();
	Size.x = abs(Size.x);
	Size.y = abs(Size.y);

	// StartPos를 이미지에서의 위치로 변경한다.

	Vector2 ConvertImagePos;
	ConvertImagePos.x = DragObj->GetStartPos().x - m_SpriteObject->GetWorldPos().x;
	ConvertImagePos.y = m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - (DragObj->GetStartPos().y - m_SpriteObject->GetWorldPos().y);

	Anim->AddFrame(ConvertImagePos, Size);

	int FrameCount = Anim->GetFrameCount() - 1;

	char FrameName[32] = {};
	sprintf_s(FrameName, "%d", FrameCount);

	m_AnimationFrameList->AddItem(FrameName);

	m_SpriteFrame->SetTexture(m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture());

	Vector2 ImageStartPos = DragObj->GetStartPos();
	Vector2 ImageEndPos = DragObj->GetEndPos();

	ImageStartPos.x -= m_SpriteObject->GetWorldPos().x;
	ImageStartPos.y -= m_SpriteObject->GetWorldPos().y;

	ImageEndPos.x -= m_SpriteObject->GetWorldPos().x;
	ImageEndPos.y -= m_SpriteObject->GetWorldPos().y;

	ImageEndPos.y = m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - ImageEndPos.y;
	ImageStartPos.y = m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - ImageStartPos.y;

	Vector2 StartPos, EndPos;
	StartPos.x = ImageStartPos.x < ImageEndPos.x ? ImageStartPos.x : ImageEndPos.x;
	StartPos.y = ImageStartPos.y < ImageEndPos.y ? ImageStartPos.y : ImageEndPos.y;

	EndPos.x = ImageStartPos.x > ImageEndPos.x ? ImageStartPos.x : ImageEndPos.x;
	EndPos.y = ImageStartPos.y > ImageEndPos.y ? ImageStartPos.y : ImageEndPos.y;

	m_SpriteFrame->SetImageStart(StartPos.x, StartPos.y);

	m_SpriteFrame->SetImageEnd(EndPos.x, EndPos.y);
}

void CSpriteWindow::SelectAnimationFrame(int Index, const char* Item)
{
	if (Index == -1)
	{
		return;
	}

	int SelectIndex = m_AnimationList->GetSelectIndex();
	if (SelectIndex == -1)
	{
		return;
	}

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectIndex));

	AnimationFrameData Data = Anim->GetFrameData(Index);

	m_SpriteFrame->SetImageStart(Data.Start.x, Data.Start.y);

	m_SpriteFrame->SetImageEnd(Data.Start.x + Data.Size.x, Data.Start.y + Data.Size.y);

	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	Vector2 StartPos, EndPos;

	float ImageHeight = (float)m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight();

	StartPos.x = Data.Start.x + m_SpriteObject->GetWorldPos().x;
	StartPos.y = ImageHeight - Data.Start.y + m_SpriteObject->GetWorldPos().y;

	EndPos.x = StartPos.x + Data.Size.x;
	EndPos.y = StartPos.y - Data.Size.y;

	DragObj->SetStartPos(StartPos);
	DragObj->SetEndPos(EndPos);
}

void CSpriteWindow::DeleteFrameButton()
{
	int SelectIndex = m_AnimationFrameList->GetSelectIndex();
	if (SelectIndex == -1)
	{
		return;
	}

	int SelectAnimIndex = m_AnimationList->GetSelectIndex();
	if (SelectAnimIndex == -1)
	{
		return;
	}

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectAnimIndex));

	Anim->DeleteFrame(SelectIndex);

	m_AnimationFrameList->DeleteItem(SelectIndex);
}

void CSpriteWindow::PlayAnimation()
{
	if (!m_SpriteObject)
	{
		return;
	}

	m_AnimInstance->Play();
}

void CSpriteWindow::SelectAnimation(int Index, const char* Item)
{
	m_AnimInstance->SetCurrentAnimation(Item);

	int FrameCount = m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameCount();

	m_AnimationFrameList->Clear();

	for (int i = 0; i < FrameCount; ++i)
	{
		char FrameName[32] = {};
		sprintf_s(FrameName, "%d", i + 1);
		m_AnimationFrameList->AddItem(FrameName);
	}

	m_SpriteFrame->SetTexture(m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetTexture());

	if (FrameCount > 0)
	{
		AnimationFrameData  Data = m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameData(Index);

		m_SpriteFrame->SetImageStart(Data.Start.x, Data.Start.y);

		m_SpriteFrame->SetImageEnd(Data.Start.x + Data.Size.x, Data.Start.y + Data.Size.y);
	}
}

void CSpriteWindow::SaveSequence()
{
	int SelectAnimIndex = m_AnimationList->GetSelectIndex();
	if (SelectAnimIndex == -1)
	{
		return;
	}

	TCHAR FilePath[MAX_PATH] = {};

	OPENFILENAME OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0Sequence File\0*.sqc");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(ANIMATION_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		FILE* pFile = nullptr;

		char FullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, FullPath, Length, 0, 0);

		m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->SaveFullPath(FullPath);
	}
}

void CSpriteWindow::LoadSequence()
{
	TCHAR FilePath[MAX_PATH] = {};

	OPENFILENAME OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0Sequence File\0*.sqc");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(ANIMATION_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		FILE* pFile = nullptr;

		char FullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, FullPath, Length, 0, 0);

		CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

		std::string	SequenceName;
		Resource->LoadSequence2D(SequenceName, FullPath);
	}
}

void CSpriteWindow::SaveAnimation()
{
	if (m_AnimationList->GetItemCount() == 0)
	{
		return;
	}

}

void CSpriteWindow::LoadAnimation()
{
}
