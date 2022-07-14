#include "FontManager.h"
#include "../../PathManager.h"
#include "../../Device.h"

CFontManager::CFontManager() : m_WriteFactory(nullptr), m_FontFamilyName{}, m_FontFamilyNameMultibyte{}
{
}

CFontManager::~CFontManager()
{
	{
		auto iter = m_mapFontFile.begin();
		auto iterEnd = m_mapFontFile.end();

		for (; iter != iterEnd; iter++)
		{
			SAFE_RELEASE(iter->second);
		}
	}

	{
		auto iter = m_mapFont.begin();
		auto iterEnd = m_mapFont.end();

		for (; iter != iterEnd; iter++)
		{
			SAFE_RELEASE(iter->second);
		}
	}

	{
		auto iter = m_mapFontColor.begin();
		auto iterEnd = m_mapFontColor.end();

		for (; iter != iterEnd; iter++)
		{
			SAFE_RELEASE(iter->second);
		}
	}

	SAFE_RELEASE(m_WriteFactory);
}

bool CFontManager::Init()
{
	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_WriteFactory), (IUnknown**)&m_WriteFactory)))
	{
		return false;
	}

	// Engine Font Loading
	CreateFontFile("Default", TEXT("NotoSansKR-Regular.otf"));

	const TCHAR* FontFace = GetFontFaceName("Default");

	LoadFont("Default", FontFace, 600, 20.f, TEXT("ko"));

	return true;
}

bool CFontManager::CreateFontFile(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	IDWriteFontCollection1* FontCollection = FindFontFile(Name);

	if (FontCollection)
	{
		return true;
	}

	TCHAR FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
	{
		lstrcpy(FullPath, Info->Path);
	}

	lstrcat(FullPath, FileName);

	IDWriteFontFile* FontFile = nullptr;

	if (FAILED(m_WriteFactory->CreateFontFileReference(FullPath, nullptr, &FontFile)))
	{
		return false;
	}

	IDWriteFontSetBuilder1* Builder = nullptr;

	if (FAILED(m_WriteFactory->CreateFontSetBuilder(&Builder)))
	{
		return false;
	}

	Builder->AddFontFile(FontFile);

	IDWriteFontSet* FontSet = nullptr;

	if (FAILED(Builder->CreateFontSet(&FontSet)))
	{
		return false;
	}

	if (FAILED(m_WriteFactory->CreateFontCollectionFromFontSet(FontSet, &FontCollection)))
	{
		return false;
	}

	m_mapFontFile.insert(std::make_pair(Name, FontCollection));

	SAFE_RELEASE(FontSet);
	SAFE_RELEASE(Builder);
	SAFE_RELEASE(FontFile);

	return true;
}

bool CFontManager::LoadFont(const std::string& Name, const TCHAR* FontName, int Weight, float FontSize, const TCHAR* LocalName, int Stretch)
{
	IDWriteTextFormat* Font = FindFont(Name);

	if (Font)
	{
		return true;
	}

	if (FAILED(m_WriteFactory->CreateTextFormat(FontName, nullptr, (DWRITE_FONT_WEIGHT)Weight,
		DWRITE_FONT_STYLE_NORMAL, (DWRITE_FONT_STRETCH)Stretch, FontSize, LocalName, &Font)))
	{
		return false;
	}

	m_mapFont.insert(std::make_pair(Name, Font));

	return true;
}

const TCHAR* CFontManager::GetFontFaceName(const std::string& Name)
{
	IDWriteFontCollection1* FontCollection = FindFontFile(Name);

	if (!FontCollection)
	{
		return nullptr;
	}

	IDWriteFontFamily* Family = nullptr;

	if (FAILED(FontCollection->GetFontFamily(0, &Family)))
	{
		return nullptr;
	}

	IDWriteLocalizedStrings* LocalizedName = nullptr;

	if (FAILED(Family->GetFamilyNames(&LocalizedName)))
	{
		return nullptr;
	}

	memset(m_FontFamilyName, 0, sizeof(TCHAR) * 256);

	if (FAILED(LocalizedName->GetString(0, m_FontFamilyName, 256)))
	{
		return nullptr;
	}


	return m_FontFamilyName;
}

const char* CFontManager::GetFontFaceNameMultibyte(const std::string& Name)
{
	if (!GetFontFaceName(Name))
	{
		return nullptr;
	}


	memset(m_FontFamilyNameMultibyte, 0, 256);

#ifdef UNICODE

	int	Length = WideCharToMultiByte(CP_ACP, 0, m_FontFamilyName, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_ACP, 0, m_FontFamilyName, -1, m_FontFamilyNameMultibyte, Length, 0, 0);

#else

	strcpy_s(m_FontFamilyNameMultibyte, m_FontFamilyName);

#endif // UNICODE


	return m_FontFamilyNameMultibyte;
}

bool CFontManager::CreateFontColor(float r, float g, float b, float a)
{
	ID2D1SolidColorBrush* Brush = FindFontColor(r, g, b, a);

	if (Brush)
	{
		return true;
	}

	if (FAILED(CDevice::GetInst()->Get2DRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &Brush)))
	{
		return false;
	}

	m_mapFontColor.insert(std::make_pair(CreateFontColorKey(r, g, b, a), Brush));

	return true;
}

bool CFontManager::CreateFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	ID2D1SolidColorBrush* Brush = FindFontColor(r, g, b, a);

	if (Brush)
	{
		return true;
	}

	if (FAILED(CDevice::GetInst()->Get2DRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(r / 255.f, g / 255.f, b / 255.f, a / 255.f), &Brush)))
	{
		return false;
	}

	m_mapFontColor.insert(std::make_pair(CreateFontColorKey(r, g, b, a), Brush));

	return true;
}

bool CFontManager::CreateFontColor(const Vector4& Color)
{
	ID2D1SolidColorBrush* Brush = FindFontColor(Color);

	if (Brush)
	{
		return true;
	}

	if (FAILED(CDevice::GetInst()->Get2DRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(Color.x, Color.y, Color.z, Color.w), &Brush)))
	{
		return false;
	}

	m_mapFontColor.insert(std::make_pair(CreateFontColorKey(Color), Brush));

	return true;
}

bool CFontManager::CreateFontColor(unsigned int Color)
{
	ID2D1SolidColorBrush* Brush = FindFontColor(Color);

	if (Brush)
	{
		return true;
	}

	float	r, g, b, a;

	b = (Color & 0x000000ff) / 255.f;
	g = ((Color >> 8) & 0x000000ff) / 255.f;
	r = ((Color >> 16) & 0x000000ff) / 255.f;
	a = ((Color >> 24) & 0x000000ff) / 255.f;

	if (FAILED(CDevice::GetInst()->Get2DRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &Brush)))
	{
		return false;
	}

	m_mapFontColor.insert(std::make_pair(Color, Brush));

	return true;
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(float r, float g, float b, float a)
{
	return FindFontColor(CreateFontColorKey(r, g, b, a));
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return FindFontColor(CreateFontColorKey(r, g, b, a));
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(const Vector4& Color)
{
	return FindFontColor(CreateFontColorKey(Color));
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(unsigned int Color)
{
	auto iter = m_mapFontColor.find(Color);

	if (iter == m_mapFontColor.end())
	{
		return nullptr;
	}

	return iter->second;
}

unsigned int CFontManager::CreateFontColorKey(float r, float g, float b, float a)
{
	unsigned int	Color = 0;
	unsigned char R, G, B, A;

	R = (unsigned char)(r * 255);
	G = (unsigned char)(g * 255);
	B = (unsigned char)(b * 255);
	A = (unsigned char)(a * 255);

	Color = A;
	Color = (Color << 8) | R;
	Color = (Color << 8) | G;
	Color = (Color << 8) | B;

	return Color;
}

unsigned int CFontManager::CreateFontColorKey(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	unsigned int Color = 0;

	Color = a;
	Color = (Color << 8) | r;
	Color = (Color << 8) | g;
	Color = (Color << 8) | b;

	return Color;
}

unsigned int CFontManager::CreateFontColorKey(const Vector4& Color)
{
	unsigned int Result = 0;
	unsigned char R, G, B, A;

	R = (unsigned char)(Color.x * 255);
	G = (unsigned char)(Color.y * 255);
	B = (unsigned char)(Color.z * 255);
	A = (unsigned char)(Color.w * 255);

	Result = A;
	Result = (Result << 8) | R;
	Result = (Result << 8) | G;
	Result = (Result << 8) | B;

	return Result;
}

IDWriteTextLayout* CFontManager::CreateTextLayout(const TCHAR* Text, IDWriteTextFormat* Font, float Width, float Height)
{
	IDWriteTextLayout* Layout = nullptr;

	if (FAILED(m_WriteFactory->CreateTextLayout(Text, lstrlen(Text), Font, Width, Height, &Layout)))
	{
		return nullptr;
	}

	return Layout;
}

IDWriteTextLayout* CFontManager::CreateTextLayout(const TCHAR* Text, const std::string& FontName, float Width, float Height)
{
	IDWriteTextFormat* Font = FindFont(FontName);

	if (!Font)
	{
		return nullptr;
	}

	return CreateTextLayout(Text, Font, Width, Height);
}

IDWriteFontCollection1* CFontManager::FindFontFile(const std::string& Name)
{
	auto iter = m_mapFontFile.find(Name);

	if (iter == m_mapFontFile.end())
	{
		return nullptr;
	}

	return iter->second;
}

IDWriteTextFormat* CFontManager::FindFont(const std::string& Name)
{
	auto iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
	{
		return nullptr;
	}

	return iter->second;
}
