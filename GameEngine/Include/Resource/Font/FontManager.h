#pragma once

#include "../../GameInfo.h"

class CFontManager
{
	friend class CResourceManager;

private:
	CFontManager();
	~CFontManager();

private:
	IDWriteFactory5* m_WriteFactory;
	std::unordered_map<std::string, IDWriteFontCollection1*> m_mapFontFile;
	std::unordered_map<std::string, IDWriteTextFormat*>	 m_mapFont;
	std::unordered_map<unsigned int, ID2D1SolidColorBrush*>	 m_mapFontColor;
	TCHAR m_FontFamilyName[256];
	char m_FontFamilyNameMultibyte[256];

public:
	bool Init();
	bool CreateFontFile(const std::string& Name, const TCHAR* FileName, const std::string& PathName = FONT_PATH);
	bool LoadFont(const std::string& Name, const TCHAR* FontName, int Weight, float FontSize, 
		const TCHAR* LocalName, int Stretch = DWRITE_FONT_STRETCH_NORMAL);
	const TCHAR* GetFontFaceName(const std::string& Name);
	const char* GetFontFaceNameMultibyte(const std::string& Name);
	bool CreateFontColor(float r, float g, float b, float a);
	bool CreateFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	bool CreateFontColor(const Vector4& Color);
	bool CreateFontColor(unsigned int Color);
	ID2D1SolidColorBrush* FindFontColor(float r, float g, float b, float a);
	ID2D1SolidColorBrush* FindFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	ID2D1SolidColorBrush* FindFontColor(const Vector4& Color);
	ID2D1SolidColorBrush* FindFontColor(unsigned int Color);
	unsigned int CreateFontColorKey(float r, float g, float b, float a);
	unsigned int CreateFontColorKey(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	unsigned int CreateFontColorKey(const Vector4& Color);
	IDWriteTextLayout* CreateTextLayout(const TCHAR* Text, IDWriteTextFormat* Font, float Width, float Height);
	IDWriteTextLayout* CreateTextLayout(const TCHAR* Text, const std::string& FontName, float Width, float Height);

	IDWriteFontCollection1* FindFontFile(const std::string& Name);
	IDWriteTextFormat* FindFont(const std::string& Name);
};

