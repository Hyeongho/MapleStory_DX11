#include "DefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "IMGUIMenuBar.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUIManager.h"

CDefaultScene::CDefaultScene() : m_Data(nullptr)
{
    SetTypeID<CDefaultScene>();

    m_Data = new CData;
}

CDefaultScene::~CDefaultScene()
{
    m_Data->ReleaseBook();
}

bool CDefaultScene::Init()
{
    return true;
}
