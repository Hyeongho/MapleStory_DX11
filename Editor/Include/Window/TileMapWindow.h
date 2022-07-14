#pragma once

#include "IMGUIWindow.h"
#include "../EditorInfo.h"
#include "Component/TileMapComponent.h"

class CTileMapWindow :
    public CIMGUIWindow
{
public:
	CTileMapWindow();
	virtual ~CTileMapWindow();

private:
	class CIMGUITextInput* m_CountX;
	class CIMGUITextInput* m_CountY;
	class CIMGUITextInput* m_SizeX;
	class CIMGUITextInput* m_SizeY;
	class CIMGUIComboBox* m_ShapeCombo;
	class CIMGUIButton* m_TileMapCreateButton;
	CSharedPtr<CTileMapComponent> m_TileMap;
	//CSharedPtr<CTileMapComponent> m_Grid;

private:
	class CIMGUIComboBox* m_TypeCombo;
	class CIMGUIComboBox* m_TileEditCombo;
	class CIMGUITextInput* m_FrameStartX;
	class CIMGUITextInput* m_FrameStartY;
	class CIMGUITextInput* m_FrameEndX;
	class CIMGUITextInput* m_FrameEndY;
	class CIMGUIButton* m_DefaultFrameButton;

private:
	class CIMGUIButton* m_TileMapSaveButton;
	class CIMGUIButton* m_TileMapLoadButton;

private:
	class CIMGUIImage* m_Tile;
	class CIMGUIImage* m_TileFrame;

	class CIMGUIButton* m_TileLoadButton;

public:
	void SetTileMap(CTileMapComponent* TileMap)
	{
		m_TileMap = TileMap;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void CountXCallback();
	void CountYCallback();
	void SizeXCallback();
	void SizeYCallback();
	void TileMapCreateButton();
	void TileMapSaveButton();
	void TileMapLoadButton();

private:
	void FrameStartXCallback();
	void FrameStartYCallback();
	void FrameEndXCallback();
	void FrameEndYCallback();
	void DefaultFrameButton();

private:
	void LoadTile();
	void CreateFrameTile();

private:
	void CreateTileEditControl();
};

